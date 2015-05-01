#ifndef _OF_CLOCK
#define _OF_CLOCK

//Good reference material for learning, not used in the patch
//Borrowed / adapted from here:
//https://gist.github.com/madc/2984060

#include "ofMain.h"

class ofClock {
    
public:
    void setup();
    void update( int, int , int );
    void draw();
    
private:
    int radius;
    
    int top;
    int left;
    
    float secondsAngle;
    float minutesAngle;
    float hoursAngle;
}; 

#endif