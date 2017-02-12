/* 
 * File:   WinService.h
 * Author: Fabian
 *
 * Created on 8. Februar 2017, 23:31
 */

#ifndef WINSERVICE_H
#define WINSERVICE_H

#include <windows.h>
#include <string>
#include <functional>


#include "ServiceConnection.h"


//Mingw does not provide them?
#ifndef SERVICE_NOTIFY_STOPPED

#define SERVICE_NOTIFY_STOPPED       0x00000001
#define SERVICE_NOTIFY_START_PENDING 0x00000002
#define SERVICE_NOTIFY_STOP_PENDING  0x00000004
#define SERVICE_NOTIFY_RUNNING       0x00000008

#endif //SERVICE_NOTIFY_STOPPED


#ifndef SERVICE_NOTIFY_STATUS_CHANGE
#define SERVICE_NOTIFY_STATUS_CHANGE 0x00000002
#endif //SERVICE_NOTIFY_STATUS_CHANGE


class WinService {
private:
    std::wstring name;

    volatile bool doServiceObservation;
    std::function<void(PSERVICE_NOTIFY)> serviceChange;
    ServiceConnection *pChangeConnection;
    PSERVICE_NOTIFY pSN;
    
public:
    /**
     * Constructor
     * 
     * @param name The name of the service which should be controlled
     */
    WinService(std::wstring name);
    virtual ~WinService();
    
    /**
     * Start the service
     * @return true on success
     */
    bool start();
    /**
     * Stops the service
     * @return true on success
     */
    bool stop();
    
    /**
     * gets the Status of the service
     * @return a value from dwCurrentState, https://msdn.microsoft.com/en-us/library/windows/desktop/ms685992(v=vs.85).aspx
     */
    DWORD status();
    
    /**
     * A global (static) function which dispatches the change notifies to the right instance of WinService.
     * @param pParameter is a PSERVICE_NOTIFY structure, which has a pContext part, where we stored the class
     */
    static void CALLBACK serviceChangeDispatcher(PVOID pParameter);
    
    /**
     * This function will subscribe to changing states of a service. It will sleep till an event happends.
     * When a event happends, then it will ressubcribe, thus ending in a loop, till doServiceObservation will be false.
     * This function should be called in a seperate thread!
     * Subsequent calls should not try to reconnect the the SCM, thats why there is the resubscribe parameter.
     * @param callback function, which will do something, if the status changes. Should be short living.
     * @param reregister false, if this is the first call to this function.
     */
    void registerServiceChange(std::function<void(PSERVICE_NOTIFY)> callback, bool resubscribe = false);
    /**
     * closes the connction to the SCM and sets doServiceObservation to false.
     * The registerServiceChange loop will close, because no new notfiies are received.
     */
    void cancelServiceChange();
    
    
private:
    /**
     * This function will call the atcual handling function and resubscribe to the change events.
     * @param pSN SERVICE_NOTIFY which holds the status informtion of the service.
     */
    void callServiceChange(PSERVICE_NOTIFY pSN);
    
};

#endif /* WINSERVICE_H */

