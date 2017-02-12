/* 
 * File:   main.cpp
 * Author: Fabian
 *
 * Created on 8. Februar 2017, 17:06
 */

#ifndef UNICODE
    #define UNICODE
#endif
#ifndef _UNICODE
    #define _UNICODE
#endif

#include "main.h"

#include <windows.h>

#include "Window.h"
#include "ServiceGUI.h"


//int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
int main(int argc, char* argv[]){

    HINSTANCE hInstance = GetModuleHandle(NULL);
    
    Window window = Window(L"Service Starter", 350, 150, hInstance);
    
    if(!window.isInitSuccess()){
        return 0;
    }
    
    ServiceGUI *pServiceGUIApache = new ServiceGUI(&window, L"Apache2.4ServerDev", L"Apache");
    ServiceGUI *pServiceGUIMySQL = new ServiceGUI(&window, L"MySQLDev", L"MySQL");
    
    
    window.showWindow();
    
    WPARAM exitCode = window.handleMessages();
    
    
    delete pServiceGUIApache;
    delete pServiceGUIMySQL;
    
    
    return exitCode;
}
