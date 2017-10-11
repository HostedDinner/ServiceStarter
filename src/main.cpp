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
#include "ScrollBarController.h"


//int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
int main(int argc, char* argv[]){
    
    int width = 350;
    int height = 130;

    HINSTANCE hInstance = GetModuleHandle(NULL);
    
    Window window = Window(L"Service Starter", width, height, hInstance);
    
    if(!window.isInitSuccess()){
        return 0;
    }    
    
    ConfigParser configP(L"config.xml");
    
    auto *confs = configP.pGetServiceConfigs();
    auto length = confs->size();
    
    std::vector<std::unique_ptr<ServiceGUI>> services;
    services.reserve(length);
    
    for (auto &elem : *confs) {
        std::unique_ptr<ServiceGUI> p(new ServiceGUI(&window, elem.first, elem.second));
        services.push_back(std::move(p));
    }
    
    
    //Adjust the Scrollbar (height of 1 element is 30, top margin is 10)
    ScrollBarController *scrBC = window.getpScrollBarController();
    scrBC->setRange(1, (length*30+10) / 10);
    

    window.showWindow();
    
    WPARAM exitCode = window.handleMessages();
    
    //cleaning the serviceGUI/Services is done by our smart pointer
    
    return exitCode;
}
