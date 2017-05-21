/* 
 * File:   ServiceConnection.h
 * Author: Fabian
 *
 * Created on 11. Februar 2017, 16:21
 */

#ifndef SERVICECONNECTION_H
#define SERVICECONNECTION_H

#include <windows.h>
#include <string>

/**
 * This is a helper class, which holds handles for the opened Service Control Manager and the opened service.
 */
class ServiceConnection {
private:
    
    SC_HANDLE hSCManager;
    SC_HANDLE hService;
    
    DWORD error;
    
public:
    /**
     * Constructor
     * 
     * @param name The name of the service which should be controlled
     * @param serviceAccess Which Access Rights does the Service need? https://msdn.microsoft.com/en-us/library/windows/desktop/ms685981(v=vs.85).aspx#access_rights_for_a_service
     * @param managerAccess Which access Rights does the Service Control Manager need? See https://msdn.microsoft.com/en-us/library/windows/desktop/ms685981(v=vs.85).aspx#access_rights_for_the_service_control_manager
     */
    ServiceConnection(std::wstring name, DWORD serviceAccess, DWORD managerAccess = SC_MANAGER_CONNECT);
    
    /**
     * Destructor
     */
    virtual ~ServiceConnection();
    
    /**
     * Gets the handle for the Service Control Manager
     * @return
     */
    SC_HANDLE getSCManager();
    /**
     * Gets the handle for the Service
     * @return
     */
    SC_HANDLE getSCService();
    
    bool isOpenedSuccessful();
    
    DWORD lastError();
private:

};

#endif /* SERVICECONNECTION_H */

