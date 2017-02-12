/* 
 * File:   WindowHelper.h
 * Author: Fabian
 *
 * Created on 9. Februar 2017, 15:34
 */

#ifndef WINDOWHELPER_H
#define WINDOWHELPER_H

#include <windows.h>

class WindowHelper {
private:
    HFONT messageFont;
    
public:
    WindowHelper();
    virtual ~WindowHelper();
    
    /**
     * sets the correct font for text, buttons, etc.
     * @param hwnd
     * @return non-zero on success
     */
    bool setMessageFont(HWND hwnd);
    /**
     * Disables a control
     * @param hwnd
     * @return non-zero on success
     */
    bool disableControl(HWND hwnd);
    /**
     * Enables a control
     * @param hwnd
     * @return non-zero on success
     */
    bool enableControl(HWND hwnd);
private:
    /**
     * Grabs the correct font for text, buttons, etc.
     * @return HFONT object, will be destroyed by the destructor
     */
    HFONT getMessageFont();
};

#endif /* WINDOWHELPER_H */

