/* 
 * File:   WinService.cpp
 * Author: Fabian
 * 
 * Created on 8. Februar 2017, 23:31
 */

#ifndef UNICODE
    #define UNICODE
#endif
#ifndef _UNICODE
    #define _UNICODE
#endif

#include "WinService.h"

#include "ServiceConnection.h"

WinService::WinService(std::wstring name) {
    this->name = name;
    
    this->doServiceObservation = true;
    this->serviceChange = NULL;
    this->pChangeConnection = NULL;
    
    this->sn = SERVICE_NOTIFY();
    this->sn.dwVersion = SERVICE_NOTIFY_STATUS_CHANGE;
    this->sn.pContext = this;
    this->sn.pfnNotifyCallback = &WinService::serviceChangeDispatcher;
}

WinService::~WinService() {
    delete this->pChangeConnection;
}

void WinService::start() {
    std::thread(&WinService::start_intern, this).detach();
}

void WinService::stop() {
    std::thread(&WinService::stop_intern, this).detach();
}

DWORD WinService::status() {
    ServiceConnection con = ServiceConnection(this->name, SERVICE_QUERY_STATUS);
    
    if(!con.isOpenedSuccessful() && con.lastError() == ERROR_SERVICE_DOES_NOT_EXIST){
        return SERVICE_INVALID_NAME;
    }
    
    SERVICE_STATUS_PROCESS ssStatus;
    DWORD bytesNeeded; //I do not use this...
    
    //TODO: could handle error
    QueryServiceStatusEx(con.getSCService(), SC_STATUS_PROCESS_INFO, (LPBYTE) &ssStatus, sizeof(SERVICE_STATUS_PROCESS), &bytesNeeded);
    
    return ssStatus.dwCurrentState;
}




/*static*/ void WinService::serviceChangeDispatcher(PVOID pParameter) {
    PSERVICE_NOTIFY pInfo = (PSERVICE_NOTIFY) pParameter;
    ((WinService *) pInfo->pContext)->callServiceChange(pInfo);
}

void WinService::registerServiceChange(std::function<void(PSERVICE_NOTIFY)> callback, bool resubscribe) {
    //this function should be called in a seperate thread!
    if(this->doServiceObservation){

        if(!resubscribe && this->pChangeConnection != NULL){ //maybe there was some leftover?
            delete this->pChangeConnection; //also closes the handle(s), so no more notifications will be received on this channel
        }
        if(!resubscribe){ //first call
            this->pChangeConnection = new ServiceConnection(this->name, SERVICE_QUERY_STATUS, SC_MANAGER_ENUMERATE_SERVICE);
            this->serviceChange = callback;
        }
        
        NotifyServiceStatusChange(this->pChangeConnection->getSCService(), this->notifyMask, &this->sn);
        
        //SleepEx will wait till timeout or if a notification (above) will be received.
        //will wake up around every 2 seconds, so that the thread gets the chance to terminate (if doServiceObservation is false)
        DWORD WINAPI sleepRet = 0;
        
        while(this->doServiceObservation && sleepRet != WAIT_IO_COMPLETION){
            sleepRet = SleepEx(2000, true);
        }
        
    }
}


void WinService::cancelServiceChange() {
    this->doServiceObservation = false;
}






void WinService::callServiceChange(PSERVICE_NOTIFY pSN) {
    if(this->serviceChange != NULL){
        this->serviceChange(pSN);
        this->registerServiceChange(NULL, true);
    }
}

void WinService::start_intern(){
    ServiceConnection con = ServiceConnection(this->name, SERVICE_START);
    
    //TODO: could handle error, for example, if user has not the right to start the service
    bool succ = (StartService(con.getSCService(), 0, NULL) != 0);
}


void WinService::stop_intern() {
    ServiceConnection con = ServiceConnection(this->name, SERVICE_STOP);
    SERVICE_STATUS serviceStatus;
    
    //TODO: could handle error, for example, if user has not the right to stop the service
    bool succ = (ControlService(con.getSCService(), SERVICE_CONTROL_STOP, &serviceStatus) != 0);
}
