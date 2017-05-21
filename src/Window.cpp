/* 
 * File:   Window.cpp
 * Author: Fabian
 * 
 * Created on 8. Februar 2017, 17:36
 */

#ifndef UNICODE
    #define UNICODE
#endif
#ifndef _UNICODE
    #define _UNICODE
#endif

#include "Window.h"

#include <iostream>
#include <windowsx.h>
#include <functional>
#include <algorithm>

#include "WindowHelper.h"
#include "ScrollBarController.h"
#include "constants.h"

Window::Window(std::wstring title, int width, int height, HINSTANCE hInstance){
    std::wstring classname = L"MyWindowsClass";
    
    if(hInstance == NULL){
        this->hInstance = GetModuleHandle(NULL);
    }else{
        this->hInstance = hInstance;
    }
    
    this->nextSubWindowID = 1;
    this->offsetY = 0;
    
    this->clientX = width;
    this->clientY = height;
    
    this->initSuccess = true;
    
    
    if(!this->regClass(classname)){
        this->initSuccess = false;
        MessageBox(NULL, L"Window Registration Failed! (Reg Class)", L"Error!", MB_ICONEXCLAMATION | MB_OK);
    }
    
    if(!this->createMainWindow(classname, title, width, height)){
        this->initSuccess = false;
        MessageBox(NULL, L"Window Registration Failed! (Create Handle)", L"Error!", MB_ICONEXCLAMATION | MB_OK);
    }
    
    this->wndHelper = new WindowHelper();
    this->scrollBarController = new ScrollBarController(this->hwnd, 0, 100, 1);
    
    this->callbacks = new std::unordered_map<WPARAM, std::function<void()>>();
    this->paintJobs = new std::list<paintPair>();
}

Window::~Window() {
    delete callbacks;
    delete paintJobs;
    delete wndHelper;
    delete scrollBarController;
}

bool Window::showWindow() {
    bool show = ShowWindow(this->hwnd, SW_SHOWDEFAULT);
    show &= this->updateWindow();
    
    return show;
}

bool Window::updateWindow() {
    return (UpdateWindow(this->hwnd) != 0);
}

WPARAM Window::handleMessages() {
    MSG msg;
    
    while(GetMessage(&msg, NULL, 0, 0) > 0){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
}

bool Window::isInitSuccess() {
    return this->initSuccess;
}

HWND Window::getHandle() {
    return this->hwnd;
}

WindowHelper *Window::getpWindowHelper() {
    return this->wndHelper;
}

ScrollBarController *Window::getpScrollBarController() {
    return this->scrollBarController;
}


HWND Window::addButton(int x, int y, int width, int height, std::wstring caption, std::function<void()> onClick) {
    UINT_PTR id = nextSubWindowID++;
    
    HWND handle = CreateWindow(L"button", caption.c_str(), WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
        x, y, width, height,
        this->hwnd, (HMENU) id, this->hInstance, NULL);
    
    wndHelper->setMessageFont(handle);
    this->addCallback(MAKEWPARAM(id, BN_CLICKED), onClick);
    
    return handle;
}

HWND Window::addStaticText(int x, int y, int width, int height, std::wstring text) {
    UINT_PTR id = nextSubWindowID++;
    
    HWND handle =  CreateWindow(L"static", text.c_str(), WS_CHILD | WS_VISIBLE,
        x, y, width, height,
        this->hwnd, (HMENU) id, this->hInstance, NULL);
    
    wndHelper->setMessageFont(handle);
    
    return handle;
}

UINT_PTR Window::addStaticBox(int x, int y, int width, int height, rgb color) {
    UINT_PTR id = nextSubWindowID++;
    
    std::function<void(HDC, rgb)> func =
        [this, x, y, width, height](HDC hdc, rgb color)->void{
            this->drawRect( hdc, x, y, width, height, color );
        };
    
    
    RECT coveredRect = {x, y, x+width, y+height};
        
    this->addPaintJob(id, paintRGB{color, func, coveredRect, {0, 0}});
    
    InvalidateRect(this->hwnd, &coveredRect, false);
    
    return id;
}

void Window::changeColorBox(UINT_PTR id, rgb color) {
    for(auto &elem: *paintJobs) {
        if(elem.first == id){
            elem.second.color = color;
            
            elem.second.offset.x = this->offsetY;
            RECT invalidRect = elem.second.trueCoveredRect();
            
            InvalidateRect(this->hwnd, &invalidRect, false);
        }
    }
}






LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    
    Window *wnd = 0;
    
    if(msg == WM_NCCREATE){
        // retrieve Window instance from window creation data and associate
        wnd = reinterpret_cast<Window *>(((LPCREATESTRUCT)lParam)->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(wnd));
        wnd->setHWND(hwnd);
    }else{
        // retrieve associated Window instance
        wnd = reinterpret_cast<Window *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }
    
    if (wnd){
        return wnd->realWndProc(msg, wParam, lParam);
    }else{
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

LRESULT CALLBACK Window::realWndProc(UINT msg, WPARAM wParam, LPARAM lParam){
    switch(msg){
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hDC = BeginPaint(this->hwnd, &ps);
                
                for(auto &elem: *paintJobs) {
                    elem.second(hDC);
                }
                
                EndPaint(this->hwnd, &ps);
                return 0;
            }
        //it does not work anyway
        /*case WM_MOUSEHWHEEL:
            {
                std::wcout << L"a" << std::endl;
                if (((short) GET_WHEEL_DELTA_WPARAM(wParam))/WHEEL_DELTA > 0 ){
                    PostMessage (this->hwnd, WM_VSCROLL, SB_LINEUP, (LPARAM) 0);
                }
                if (((short) GET_WHEEL_DELTA_WPARAM(wParam))/WHEEL_DELTA < 0 ){
                    PostMessage (this->hwnd, WM_VSCROLL, SB_LINEDOWN, (LPARAM) 0);
                }
                return 0;
            }*/
        case WM_VSCROLL:
            {
                int movement = this->scrollBarController->handleScroll(LOWORD(wParam));
                if(movement != 0){
                    this->scrollContent(10*movement);
                }
                return 0;
            }
        case WM_SIZE:
            {
                if(wParam != SIZE_MINIMIZED){
                    int newX = LOWORD (lParam);
                    int newY = HIWORD (lParam);

                    //TODO: In some combinations this leads to wrong movement
                    //but this almost works...
                    //otherwise the behaviour is even more strange
                    if(newY > this->clientY && this->offsetY < 0){
                        this->scrollContent(newY - this->clientY);
                    }

                    this->scrollBarController->setPageSize(newY/10);


                    this->clientX = newX;
                    this->clientY = newY;
                
                }
                
                return 0;
            }
        case WM_GETMINMAXINFO:
            {
                LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
                lpMMI->ptMinTrackSize.x = this->clientMinX;
                lpMMI->ptMinTrackSize.y = this->clientMinY;
                return 0;
            }
        case WM_CLOSE:
            DestroyWindow(this->hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_COMMAND:
            {
                try{
                    std::function<void()> func = this->callbacks->at(wParam);
                    func();
                    return 0;
                }catch(std::out_of_range ex){

                }
                break;
            }
        default:
            return DefWindowProc(this->hwnd, msg, wParam, lParam);
    }
    return 0;
}


void Window::setHWND(HWND hwnd) {
    this->hwnd = hwnd;
}

bool Window::regClass(std::wstring classname){
    WNDCLASSEX wc;
    
    HICON hIcon = static_cast<HICON>(LoadImage(this->hInstance,
        MAKEINTRESOURCE(IDI_MAINICON),
        IMAGE_ICON,
        0, 0,
        LR_DEFAULTCOLOR | LR_DEFAULTSIZE));
    
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = Window::WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = sizeof(LONG_PTR);
    wc.hInstance     = hInstance;
    wc.hIcon         = hIcon;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = classname.c_str();
    wc.hIconSm       = hIcon;
    
    return RegisterClassEx(&wc);
}

bool Window::createMainWindow(std::wstring classname, std::wstring title, int width, int height) {
    
    DWORD style = WS_OVERLAPPEDWINDOW | WS_VSCROLL;
    DWORD exstyle = WS_EX_CLIENTEDGE;
    
    RECT clientAreaSize;
    clientAreaSize.left = 0;
    clientAreaSize.right = width;
    clientAreaSize.top = 0;
    clientAreaSize.bottom = height;
    
    AdjustWindowRectEx(&clientAreaSize, style, false, exstyle);
    //Scroll bar is not taken into account by AdjustWindowRect:
    clientAreaSize.right += GetSystemMetrics(SM_CXVSCROLL);
    
    this->clientMinX = clientAreaSize.right - clientAreaSize.left;
    this->clientMinY = clientAreaSize.bottom - clientAreaSize.top;
    
    CreateWindowEx(
        exstyle,
        classname.c_str(),
        title.c_str(),
        style,
        CW_USEDEFAULT, CW_USEDEFAULT, this->clientMinX, this->clientMinY,
        NULL, NULL, this->hInstance, this
    );
    
    return (this->hwnd != NULL); //this->hwnd was set in the Callback in WM_NCCREATE message
}

void Window::addCallback(WPARAM wParam, std::function<void()> func) {
    this->callbacks->insert(std::make_pair(wParam, func));
}

void Window::addPaintJob(UINT_PTR id, paintRGB paRGB) {
    this->paintJobs->push_back(std::make_pair(id, paRGB));
}


void Window::drawRect(HDC hDC, int x, int y, int width, int height, rgb color) {
    RECT rect;
    rect.left = x;
    rect.top = this->offsetY + y;
    rect.right = rect.left + width;
    rect.bottom = rect.top + height;

    HBRUSH brush = CreateSolidBrush(RGB(color.r,color.g,color.b));

    FillRect(hDC, &rect, brush);
    
    DeleteBrush(brush);
}

void Window::scrollContent(int pixel) {
    pixel = std::min(-1*this->offsetY, pixel); //never move further down then 0, content should always stay top aligned
    ScrollWindowEx(this->hwnd, 0, pixel, NULL, NULL, NULL, NULL, SW_ERASE | SW_INVALIDATE | SW_SCROLLCHILDREN);
    this->offsetY += pixel;
    UpdateWindow (this->hwnd);
}

