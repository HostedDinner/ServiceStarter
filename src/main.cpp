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
#include "ConfigParser.h"


//int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
int main(int argc, char* argv[]){

    HINSTANCE hInstance = GetModuleHandle(NULL);
    
    Window window = Window(L"Service Starter", 350, 150, hInstance);
    
    if(!window.isInitSuccess()){
        return 0;
    }    
    
    ConfigParser configP(L"config.xml");
    
    auto *confs = configP.pGetServiceConfigs();
    auto length = confs->size();
    
    ServiceGUI *pServices[length];
    
    int i = 0;
    for (auto &elem : *confs) {
        pServices[i] = new ServiceGUI(&window, elem.first, elem.second);
        i++;
    }
    
    //ServiceGUI serviceGUIApache(&window, L"Apache2.4ServerDev", L"Apache");
    //ServiceGUI serviceGUIMySQL(&window, L"MySQLDev", L"MySQL");

    window.showWindow();
    
    WPARAM exitCode = window.handleMessages();
    
    //actually someone once told me, that calling delete is alway safe, but this is not true!
    if(length > 0 && pServices[0] != NULL){
        delete [] pServices;
    }
    
    return exitCode;
}
