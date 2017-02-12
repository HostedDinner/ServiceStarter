/* 
 * File:   ServiceGUI.cpp
 * Author: Fabian
 * 
 * Created on 11. Februar 2017, 21:29
 */

#ifndef UNICODE
    #define UNICODE
#endif
#ifndef _UNICODE
    #define _UNICODE
#endif

#include "ServiceGUI.h"

#include "Window.h"
#include "WindowHelper.h"
#include "WinService.h"
#include "rgb.h"

//static initialisation
int ServiceGUI::nextInt = 0;
const rgb ServiceGUI::running = {115, 210, 22};
const rgb ServiceGUI::pending = {237, 212, 0};
const rgb ServiceGUI::stopped = {204, 0, 0};

ServiceGUI::ServiceGUI(Window *pWindow, std::wstring serviceName, std::wstring buttonName) {
    //copy from input
    this->pWindow = pWindow;
    this->serviceName = serviceName;
    this->buttonName = buttonName;
    this->id = this->getNextID();
    
    
    //Create a new WinService object. No side effect yet.
    this->pWinservice = new WinService(serviceName);
    
    
    int y = this->id*30 + 10; //using the id for determining the y value. Every new entry gets a new "row"
    
    this->startButton = pWindow->addButton(10, y, 100, 20, L"Start " + this->buttonName, std::bind(&WinService::start, this->pWinservice));
    this->stopButton = pWindow->addButton(120, y, 100, 20, L"Stop " + this->buttonName, std::bind(&WinService::stop, this->pWinservice));
    this->indicatorBox = pWindow->addStaticBox(230, y, 100, 20, stopped);
    
    //set the inital status
    DWORD initStatus = this->pWinservice->status();
    this->changeStatus(initStatus);
    
    //This should be launched in a new thread, because otherwise it will block the current thread
    //start receiving updates on service changes
    this->pChangeThread = new std::thread(&WinService::registerServiceChange, this->pWinservice, std::bind(&ServiceGUI::receiceStatus, this, std::placeholders::_1), false);
}

ServiceGUI::~ServiceGUI() {
    //tgis will stop bring the pChangeThread to halt, because no new notifications are received naymore
    this->pWinservice->cancelServiceChange();
    this->pChangeThread->join();
    
    delete this->pWinservice;
    delete this->pChangeThread;
}

void ServiceGUI::receiceStatus(PSERVICE_NOTIFY pSN) {
    SERVICE_STATUS_PROCESS ssStatus = pSN->ServiceStatus;
    this->changeStatus(ssStatus.dwCurrentState);
}


void ServiceGUI::changeStatus(DWORD status) {
    
    WindowHelper *wndHelper = pWindow->getpWindowHelper();
    
    switch(status){
        case SERVICE_START_PENDING:
        case SERVICE_STOP_PENDING:
            this->pWindow->changeColorBox(this->indicatorBox, pending);
            wndHelper->disableControl(this->startButton);
            wndHelper->disableControl(this->stopButton);
            break;
        case SERVICE_RUNNING:
            this->pWindow->changeColorBox(this->indicatorBox, running);
            wndHelper->disableControl(this->startButton);
            wndHelper->enableControl(this->stopButton);
            break;
        case SERVICE_STOPPED:
            this->pWindow->changeColorBox(this->indicatorBox, stopped);
            wndHelper->enableControl(this->startButton);
            wndHelper->disableControl(this->stopButton);
            break;
        default:
            break;
    }
}
