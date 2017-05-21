/* 
 * File:   rgb.h
 * Author: Fabian
 *
 * Created on 12. Februar 2017, 23:31
 */

#ifndef RGB_H
#define RGB_H

#include <windows.h>
#include <functional>

/**
 * simple struct for holding RGB color values.
 */
struct rgb { int r, g, b; };



/**
 * Holds information about a painting something on the GUI. Functor.
 */
struct paintRGB{
    /**
     * The color. This is used for dynamically change the color.
     */
    rgb color;
    
    /**
     * The function, which actually draws something on the screen. Called in the WM_PAINT message.
     */
    std::function<void(HDC, rgb)> f;
    
    /**
     * stores a RECT, whoch covers (appr.) the drawn area. This is for better invalidate the draw area.
     */
    RECT coveredRect;
    
    /**
    * simple offset
    */
   struct { int x, y; } offset;
    
    /**
     * Overloading the () for easier access.
     * @param hDC Device Context Handle
     */
    void operator()(HDC hDC) const{
        return f(hDC, color);
    }
    
    /**
     * 
     * @return the covered rect, moved by the offset
     */
    RECT trueCoveredRect(){
        RECT invalid = coveredRect;
        invalid.top += offset.x;
        invalid.bottom += offset.x;
        invalid.left += offset.y;
        invalid.right += offset.y;
        return invalid;
    }
};

#endif /* RGB_H */

