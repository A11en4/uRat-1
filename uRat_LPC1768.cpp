/*
#########################################
# Fall 2014 IEEE Micromouse Competition #
#########################################
Author: Darrel Weng

Source code for the microrat.

FRWD ~18cm
RTRN,LTRN ~90deg
*/
#include "mbed.h"
#define pwmOn 0.25f
#define pwmOff 0.0f
#define thresh 0.6f
#define fhresh 0.5f
#define FRWD 30
#define RTRN 15
#define LTRN 15

//=======================================
// Prototypes
void mvFwd(int);
void mvBck(int);
void mvRgt(int);
void mvLft(int);
void reorient();
//=======================================
// Debugging/Testing
//Serial pc(USBTX, USBRX); // default 9600 baud
// Wall Indicators
DigitalOut lw(LED3);
DigitalOut rw(LED1);
DigitalOut fw(LED2);
//=======================================
// 3 AnalogIn IR Sensors
AnalogIn front(p20);
AnalogIn left(p19);
AnalogIn right(p18);
//=======================================
// 4 PWM Outputs
/* 
a1,b1 = bck
a2,b2 = fwd
a1,b2 = rgt
a2,b1 = lft
*/
PwmOut a1(p21);
PwmOut a2(p22);
PwmOut b2(p23);
PwmOut b1(p24);
//=======================================
// 2 Quadrature Encoders (24 counts per input, 48 counts per revolution)
//DigitalIn rA(p27);
//DigitalIn rB(p28);
//DigitalIn lA(p29);
//DigitalIn lB(p30);
InterruptIn rA(p27);
InterruptIn lA(p29);
//=======================================
// Global Variables
int         netDist =   0; // encoder units
int         netAng  =   0;
uint32_t    rCount  =   0;
uint32_t    lCount  =   0;
bool        rWall   =   false;
bool        lWall   =   false;
bool        fWall   =   false;
//=======================================
// Directional Functions
// PLEASE DO NOT CALL THESE DIRECTLY
void fwd() {
    a1 = pwmOff;
    b1 = pwmOff;
    a2 = pwmOn;
    b2 = pwmOn;    
}
void bck() {
    a2 = pwmOff;
    b2 = pwmOff;
    b1 = pwmOn;
    a1 = pwmOn;    
}
void rgt() {
    a1 = pwmOff;
    b2 = pwmOff;
    a2 = pwmOn;
    b1 = pwmOn;   
}
void lft() {
    a2 = pwmOff;
    b1 = pwmOff;
    a1 = pwmOn;
    b2 = pwmOn;   
}
void stp() {
    a1 = pwmOff;
    a2 = pwmOff;
    b1 = pwmOff;
    b2 = pwmOff;   
}
void rbck() {
    b1 = pwmOn;
    a1 = pwmOff;
    b2 = pwmOff;
    a2 = pwmOff;
}
void rfwd() {
    b2 = pwmOn;
    b1 = pwmOff;
    a1 = pwmOff;
    a2 = pwmOff;
}
void lbck() {
    a1 = pwmOn;
    b1 = pwmOff;
    a2 = pwmOff;
    b2 = pwmOff;
}
void lfwd() {
    a2 = pwmOn;
    a1 = pwmOff;
    b1 = pwmOff;
    b2 = pwmOff;
}
//=======================================
// Wall Checking Function
void wallCheck(float side=thresh, float frnt=fhresh) {
    if (right > side) {
        rWall = true;
        rw = 1;
    } else {
        rWall = false;
        rw = 0;
    }
    if (left > side) {
        lWall = true;
        lw = 1;
    } else {
        lWall = false;
        lw = 0;
    }
    if (front > frnt) {
        fWall = true;
        fw = 1;
    } else {
        fWall = false;
        fw = 0;
    }
}
//=======================================
// Encoder Counting ISR's
void countL() {
    lCount++;
}
void countR() {
    rCount++;
}
//=======================================
const int err = 1;
// Closed-loop Functions
void mvFwd(int val=FRWD) {
    uint32_t l = lCount;
    uint32_t r = rCount;
    while((lCount-l<=val)&&(rCount-r<=val)){
        wallCheck(0.9f,0.7f);
        if (fWall) {
            break;   
        }
        else if (lWall) {
            rbck();
        }
        else if (rWall) {
            lbck();
        }
        else {
            fwd();
        }
    }
    bck();
    stp();
    wait(0.1);
    // compensation
    //if ((lCount-l-val>err)&&(rCount-r-val>err)) {
//        mvBck(lCount-l-val);        
//    }
    netDist += (lCount - l);
}
void mvBck(int val=FRWD) {
    uint32_t l = lCount;
    uint32_t r = rCount;
    while(((int)(lCount-l)<=val)&&((int)(rCount-r)<=val)){
        bck();
    }
    fwd();
    stp();
    wait(0.1);
    //if ((lCount-l-val>err)&&(rCount-r-val>err)) {
//        mvFwd(lCount-l-val);        
//    }
    netDist -= (lCount - l);
}
void mvLft(int val=LTRN) {
    uint32_t l = lCount;
    uint32_t r = rCount;
    while((lCount-l<=val)&&(rCount-r<=val)){
        lft();
    }
    rgt();
    stp();
    wait(0.1);
    //if ((lCount-l-val>err)&&(rCount-r-val>err)) {
//        mvRgt(lCount-l-val);        
//    }
    netAng += (lCount - l);
}
void mvRgt(int val=RTRN) {
    uint32_t l = lCount;
    uint32_t r = rCount;
    while((lCount-l<=val)&&(rCount-r<=val)) {
        rgt();
    }
    lft();
    stp();
    wait(0.1);
    //if ((lCount-l-val>err)&&(rCount-r-val>err)) {
//        mvLft(lCount-l-val);        
//    }
    netAng -= (lCount - l);
}
void reorientF() {
    if (lCount > rCount+err) {
        while(lCount > rCount+err) {
            rfwd();
        }
        rbck();
        stp();
    }
    else if (rCount > lCount+err) {
        while(rCount > lCount+err) {
            lfwd();
        }
        lbck();
        stp();
    }
    wait(0.1);
}
void turnAround() {
    mvRgt();
    wait(0.2);
    mvRgt();
    wait(0.2);
}
//=======================================
// AI Algorithms
// fWall, rWall, lWall are booleans indicating wall positions
// mvFwd() mvRgt() mvLft() mvBck() reorient() are available commands to use
// NOTE: 1) mvBck() is -VERY- iffy; please don't use
//       2) please call reorientF() after a mvFwd() command

// Simple example of how to use
void exampleAI() {
    wallCheck();
    if (!fWall) {
        mvFwd();
    }
    else if (!rWall) {
        mvRgt();
    } 
    else if (!lWall) {
        mvLft();
    }
    else {
        turnAround();    
    }
}
// Testing encoder counts
void distanceTest() {
    for (int i=0;i<4;i++) {
        mvFwd();
        mvRgt();
    }
    mvLft();
    mvLft();
    mvLft();
    for (int j=0;j<4;j++) {
        mvFwd();
        mvLft();
    }
    mvRgt();
    mvRgt();
    mvRgt();
}
/* YOUR GLOBAL VARIABLES HERE */

/* YOUR METHOD HERE */
void search() {
    
}
void execute_path() {
    
}
//==================================================================
// Main
int main() {
    // setup
    stp();
    lw = 0;
    rw = 0;
    fw = 0;
    rA.rise(&countR);
    rA.fall(&countR);
    lA.rise(&countL);
    lA.fall(&countL);
    /*
    * ANY ADDITIONAL SETUP HERE
    */
    // loop
    while(1) {
        //distanceTest();
        exampleAI();
        //pc.printf("%d,%d\n\r",(int)lCount,(int)rCount);
        //wallCheck();
    }
}
