/* 
 * File:   NotificationIconController.cpp
 * Author: Fabian
 * 
 * Created on 1. November 2017, 10:52
 */

#ifndef UNICODE
    #define UNICODE
#endif
#ifndef _UNICODE
    #define _UNICODE
#endif

#include "NotificationIconController.h"

#include "constants.h"

const GUID NotificationIconController::notificationIconGUID = {0x0748a3c3, 0x3564, 0x4bfd, {0xb4, 0x9c, 0x61, 0xe1, 0x99, 0xbb, 0xe8, 0x2d}};

NotificationIconController::NotificationIconController(HWND window) {
    this->window = window;
    
    HINSTANCE hInstance = GetModuleHandle(NULL);
    
    this->nid.cbSize = sizeof(this->nid);
    this->nid.hWnd = this->window;
    this->nid.uFlags = NIF_ICON | NIF_TIP | NIF_GUID;
    this->nid.guidItem = notificationIconGUID;
    StringCchCopy(this->nid.szTip, ARRAYSIZE(this->nid.szTip), L"Service Starter");
    
    HICON hIcon = static_cast<HICON>(LoadImage(hInstance,
        MAKEINTRESOURCE(IDI_MAINICON),
        IMAGE_ICON,
        0, 0,
        LR_DEFAULTCOLOR | LR_DEFAULTSIZE));
    
    this->nid.hIcon = hIcon;
    
    //LoadIconMetric(hInstance, MAKEINTRESOURCE(IDI_MAINICON), LIM_SMALL, &(nid.hIcon));
    
    Shell_NotifyIcon(NIM_ADD, &this->nid);
    
}

NotificationIconController::~NotificationIconController() {
    Shell_NotifyIcon(NIM_DELETE, &this->nid);
}

