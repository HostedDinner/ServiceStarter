/* 
 * File:   NotificationIconController.h
 * Author: Fabian
 *
 * Created on 1. November 2017, 10:52
 */

#ifndef NOTIFICATIONICONCONTROLLER_H
#define NOTIFICATIONICONCONTROLLER_H

#include <windows.h>
#include <Strsafe.h>

class NotificationIconController {
    
    static const GUID notificationIconGUID;
    
public:
    NotificationIconController(HWND window);
    virtual ~NotificationIconController();
private:
    
    /**
     * The associated window
     */
    HWND window;
    
    /**
     * WINAPI Structure holding information about the icon
     */
    NOTIFYICONDATA nid;

};

#endif /* NOTIFICATIONICONCONTROLLER_H */

