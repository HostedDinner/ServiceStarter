/* 
 * File:   Window.h
 * Author: Fabian
 *
 * Created on 8. Februar 2017, 17:36
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>
#include <string>
#include <utility>
#include <unordered_map>
#include <list>

#include "rgb.h"

class WindowHelper;
class ScrollBarController;


typedef std::pair<UINT_PTR, paintRGB> paintPair;


class Window {
    
private:
    HWND hwnd;
    HINSTANCE hInstance;
    UINT_PTR nextSubWindowID;
    
    WindowHelper *wndHelper;
    ScrollBarController *scrollBarController;
    
    bool initSuccess;
    
    int clientX;
    int clientY;
    
    int clientMinX;
    int clientMinY;
    
    /**
     * stores all interactive callbacks. e.g. callback function fo clicking a button.
     * WPARM is the composed value, which also is sent via WM_COMMAND. Use MAKEWPARAM(id, BN_CLICKED) to construct.
     */
    std::unordered_map<WPARAM, std::function<void()>> *callbacks;
    
    /**
     * stores the paint jobs. All functions are executed in the WM_PAINT message.
     */
    std::list<paintPair> *paintJobs;
    
    /**
     * How much space is added to the y value for paint jobs, which draw directly on the DC
     */
    int offsetY;
    
public:
    /**
     * Constructor
     * 
     * @param title The title of the Main window.
     * @param width The client area width.
     * @param height The client area height.
     * @param hInstance The hInstance (from main)
     */
    Window(std::wstring title, int width, int height, HINSTANCE hInstance = NULL);
    /**
     * Destructor
     */
    virtual ~Window();
    
    /**
     * Shows the window.
     * @return true on success.
     */
    bool showWindow();
    
    /**
     * Updates the window.
     * @return true on success.
     */
    bool updateWindow();
    /**
     * The Main message loop.
     * @return exit code.
     */
    WPARAM handleMessages();
    
    /**
     * Was the initailisation of the window successful?
     * @return true if the initialisation was successfull.
     */
    bool isInitSuccess();
    /**
     * Gets the handle to the window
     * @return handle
     */
    HWND getHandle();
    /**
     * Returns a pointer to  Window Helper instance.
     * @return pointer to the window helper.
     */
    WindowHelper *getpWindowHelper();
    
    /**
     * 
     * @return pointer to ScrollBarController (Vertical Scroll)
     */
    ScrollBarController *getpScrollBarController();
    
    
    //TODO add More Things
    
    /**
     * Adds a button on the window.
     * @param x x
     * @param y y
     * @param width width
     * @param height height
     * @param caption the caption of the button
     * @param onClick callback function executed on click
     * @return the handle to the button
     */
    HWND addButton(int x, int y, int width, int height, std::wstring caption, std::function<void()> onClick);
    /**
     * Adds a static text on the window.
     * @param x x
     * @param y y
     * @param width width
     * @param height height
     * @param text The text
     * @return The handle to the text
     */
    HWND addStaticText(int x, int y, int width, int height, std::wstring text);
    /**
     * Add a colors box to the window. This is realised via a paint job.
     * @param x x
     * @param y y
     * @param width width
     * @param height height
     * @param color color
     * @return The id in paint job list. Used for changing the color
     */
    UINT_PTR addStaticBox(int x, int y, int width, int height, rgb color);
    
    /**
     * Changes the color of a static box.
     * @param id the ID of the box.
     * @param color color
     */
    void changeColorBox(UINT_PTR id, rgb color);
    
    
private:
    /**
     * The Window Proc function
     * @param hwnd
     * @param msg
     * @param wParam
     * @param lParam
     * @return 
     */
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    
    /**
     * The Window Proc function in the scope of this class.
     * @param msg
     * @param wParam
     * @param lParam
     * @return 
     */
    LRESULT CALLBACK realWndProc(UINT msg, WPARAM wParam, LPARAM lParam);
    
    /**
     * sets the of the window
     * @param hwnd 
     */
    void setHWND(HWND hwnd);
    /**
     * register a class name to windows.
     * @param classname
     * @return true on success
     */
    bool regClass(std::wstring classname);
    /**
     * Creates the main window
     * @param classname
     * @param title the title of the window
     * @param width width
     * @param height height
     * @return true on success
     */
    bool createMainWindow(std::wstring classname, std::wstring title, int width, int height);
    
    /**
     * adds a callback for 
     * @param wParam the created WPARAM. Use MAKEWPARAM(id, BN_CLICKED) to construct. (Or similar)
     * @param func which function should be called.
     */
    void addCallback(WPARAM wParam, std::function<void()> func);
    /**
     * Adds a paint job to the list
     * @param id Which ID does it have
     * @param paRGB rgb and rect information about the job.
     */
    void addPaintJob(UINT_PTR id, paintRGB paRGB);
    
    /**
     * Draws a rect to the window. Must only be called inside the WM_PAINT, after BeginPaint.
     * @param hDC the Device Context Handle
     * @param x x
     * @param y y
     * @param width width
     * @param height height
     * @param color color
     */
    void drawRect(HDC hDC, int x, int y, int width, int height, rgb color);
    
    /**
     * Scrolls the content
     */
    void scrollContent(int pixel);
};

#endif /* WINDOW_H */

