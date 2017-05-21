/* 
 * File:   ScrollBarController.h
 * Author: Fabian
 *
 * Created on 20. Mai 2017, 19:35
 */

#ifndef SCROLLBARCONTROLLER_H
#define SCROLLBARCONTROLLER_H

#include <windows.h>

class ScrollBarController {
    
private:
    SCROLLINFO scrollInfo;
    HWND window;
    bool vertical;
    
    
    
public:
    ScrollBarController(HWND window, int min, int max, int pageSize = 0, bool vertical = true);
    virtual ~ScrollBarController();
    
    void setPageSize(unsigned int pageSize);
    void setRange(int min, int max);
    void setPosition(int position);
    
    /**
     * 
     * @return amount of movement
     */
    int handleScroll(WORD type);
    
    
    int getPosition();
    
private: 
    
    

};

#endif /* SCROLLBARCONTROLLER_H */

