/* 
 * File:   ScrollBarController.cpp
 * Author: Fabian
 * 
 * Created on 20. Mai 2017, 19:35
 */

#include "ScrollBarController.h"

ScrollBarController::ScrollBarController(HWND window, int min, int max, int pageSize, bool vertical) {
    this->window = window;
    this->vertical = vertical;
    
    this->scrollInfo.cbSize = sizeof(SCROLLINFO);
    this->scrollInfo.fMask = SIF_PAGE | SIF_RANGE;
    this->scrollInfo.nMin = min;
    this->scrollInfo.nMax = max;
    this->scrollInfo.nPage = pageSize;
    
    SetScrollInfo(this->window, this->vertical ? SB_VERT : SB_HORZ, &this->scrollInfo, false);
}



ScrollBarController::~ScrollBarController() {
}



void ScrollBarController::setPageSize(unsigned int pageSize){
    this->scrollInfo.fMask = SIF_PAGE;
    this->scrollInfo.nPage = pageSize;
    
    SetScrollInfo(this->window, this->vertical ? SB_VERT : SB_HORZ, &this->scrollInfo, true);
}


void ScrollBarController::setRange(int min, int max){
    this->scrollInfo.fMask = SIF_RANGE;
    this->scrollInfo.nMin = min;
    this->scrollInfo.nMax = max;
    
    SetScrollInfo(this->window, this->vertical ? SB_VERT : SB_HORZ, &this->scrollInfo, true);
}

void ScrollBarController::setPosition(int position) {
    this->scrollInfo.fMask = SIF_POS;
    this->scrollInfo.nPos = position;
    
    SetScrollInfo(this->window, this->vertical ? SB_VERT : SB_HORZ, &this->scrollInfo, true);
}

int ScrollBarController::handleScroll(WORD type) {
    
    this->scrollInfo.fMask = SIF_ALL;
    GetScrollInfo(this->window, this->vertical ? SB_VERT : SB_HORZ, &this->scrollInfo);
    
    //store old value
    int oldPos = this->scrollInfo.nPos;
    int max = this->scrollInfo.nMax;
    int min = this->scrollInfo.nMin;
    int pageSize = (int) this->scrollInfo.nPage;
    
    int newPos = 0;
    
    switch(type){
        // User clicked the left arrow.
        // User clicked the top arrow.
        case SB_LINELEFT:
        //case SB_LINEUP:
            newPos = (oldPos > min) ? (oldPos - 1) : min;
            break;
              
        // User clicked the right arrow.
        // User clicked the bottom arrow.
        case SB_LINERIGHT:
        //case SB_LINEDOWN:
            newPos = (oldPos < max) ? (oldPos + 1) : max;
            break;
              
        // User clicked the scroll bar shaft left of the scroll box.
        // User clicked the scroll bar shaft above the scroll box.
        case SB_PAGELEFT:
        //case SB_PAGEUP:
            newPos = ((oldPos - pageSize) > min) ? (oldPos - pageSize) : min;
            break;
              
        // User clicked the scroll bar shaft right of the scroll box.
        // User clicked the scroll bar shaft below the scroll box.
        case SB_PAGERIGHT:
        //case SB_PAGEDOWN:
            newPos = ((oldPos + pageSize) < max) ? (oldPos + pageSize) : max;
            break;
              
        // User dragged the scroll box.
        case SB_THUMBTRACK: 
            newPos = this->scrollInfo.nTrackPos;
            break;
        
        //additional vertical:
        // User clicked the HOME keyboard key.
        case SB_TOP:
            newPos = min;
            break;
              
        // User clicked the END keyboard key.
        case SB_BOTTOM:
            newPos = max;
            break;
        default:
            newPos = oldPos;
            break;
    }
    
    
    this->setPosition(newPos);
    newPos = this->getPosition();

    return oldPos - newPos;
}

int ScrollBarController::getPosition() {
    this->scrollInfo.fMask = SIF_POS;
    GetScrollInfo(this->window, this->vertical ? SB_VERT : SB_HORZ, &this->scrollInfo);
    
    return this->scrollInfo.nPos;
}



