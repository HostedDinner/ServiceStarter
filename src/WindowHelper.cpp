/* 
 * File:   WindowHelper.cpp
 * Author: Fabian
 * 
 * Created on 9. Februar 2017, 15:34
 */

#ifndef UNICODE
    #define UNICODE
#endif
#ifndef _UNICODE
    #define _UNICODE
#endif

#include "WindowHelper.h"

WindowHelper::WindowHelper() {
    messageFont = this->getMessageFont();
}

WindowHelper::~WindowHelper() {
    DeleteObject(this->messageFont);
}

bool WindowHelper::setMessageFont(HWND hwnd) {
    //Wonder why this is necassary, stupid windows?
    return SendMessage (hwnd, WM_SETFONT, (WPARAM) this->messageFont, MAKELPARAM (true, 0));
    //return SendMessage (hwnd, WM_SETFONT, (WPARAM) GetStockObject (DEFAULT_GUI_FONT), MAKELPARAM (false, 0));
};


HFONT WindowHelper::getMessageFont() {
    NONCLIENTMETRICS metric;
    metric.cbSize = sizeof(NONCLIENTMETRICS);
    
    SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &metric, 0);
    return CreateFontIndirect(&metric.lfMessageFont);
}

bool WindowHelper::disableControl(HWND hwnd) {
    return EnableWindow(hwnd, false);
}

bool WindowHelper::enableControl(HWND hwnd) {
    return EnableWindow(hwnd, true);
}

