/* 
 * File:   ServiceGUI.h
 * Author: Fabian
 *
 * Created on 11. Februar 2017, 21:29
 */

#ifndef SERVICEGUI_H
#define SERVICEGUI_H

#include <windows.h>
#include <thread>

class Window;
class WinService;
struct rgb;
//#include "Window.h"
//#include "WinService.h"
//#include "rgb.h"

/**
 * Wrapper class for the management of the gui and connection to the underliing service.
 */
class ServiceGUI {
private:
    static int nextInt;
    
    /**
     * running color
     */
    static const rgb running;
    /**
     * pending color
     */
    static const rgb pending;
    /**
     * stopped color
     */
    static const rgb stopped;
    
    
    Window *pWindow;
    std::wstring serviceName;
    std::wstring buttonName;
    int id;
    WinService *pWinservice;
    
    HWND startButton;
    HWND stopButton;
    UINT_PTR indicatorBox;
    
    std::thread *pChangeThread;
    
public:
    /**
     * Constructor
     * 
     * @param pWindow A pointer to the window class, where we want to draw on.
     * @param serviceName The name of the service which should be controlled
     * @param buttonName The label on the Button of this service. "Start <...>" and "Stop <...>"
     */
    ServiceGUI(Window *pWindow, std::wstring serviceName, std::wstring buttonName);
    
    /**
     * Destructor
     */
    virtual ~ServiceGUI();
    
    /**
     * This function is called when the status of a service changes.
     * It will pass the status to the changeStatus function.
     * @param pSN receices struct, where the Service Information is inside
     */
    void receiceStatus(PSERVICE_NOTIFY pSN);
    
private:
    /**
     * Tracks the number of added services to the gui
     * @return an id, starting at 0
     */
    int getNextID(){return nextInt++;};
    
    /**
     * This function will change the buttons and the color of the indicator according to the status.
     * @param status a value from dwCurrentState, https://msdn.microsoft.com/en-us/library/windows/desktop/ms685992(v=vs.85).aspx
     */
    void changeStatus(DWORD status);
};

#endif /* SERVICEGUI_H */

