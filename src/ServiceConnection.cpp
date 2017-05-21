/* 
 * File:   ServiceConnection.cpp
 * Author: Fabian
 * 
 * Created on 11. Februar 2017, 16:21
 */

#ifndef UNICODE
    #define UNICODE
#endif
#ifndef _UNICODE
    #define _UNICODE
#endif

#include "ServiceConnection.h"

ServiceConnection::ServiceConnection(std::wstring name, DWORD serviceAccess, DWORD managerAccess) {
    this->hSCManager = OpenSCManager(NULL, SERVICES_ACTIVE_DATABASE, managerAccess);
    this->hService = OpenService(this->hSCManager, name.c_str(), serviceAccess);
    if(this->hService == NULL){
        this->error = GetLastError();
    }
}

ServiceConnection::~ServiceConnection() {
    //closes the service handles
    CloseServiceHandle(this->hService);
    CloseServiceHandle(this->hSCManager);
}

SC_HANDLE ServiceConnection::getSCManager() {
    return this->hSCManager;
}

SC_HANDLE ServiceConnection::getSCService() {
    return this->hService;
}

bool ServiceConnection::isOpenedSuccessful(){
    return this->hService != NULL;
}

DWORD ServiceConnection::lastError() {
    return this->error;
}

