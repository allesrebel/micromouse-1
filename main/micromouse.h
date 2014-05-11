#ifndef MICROMOUSE_H
#define MICROMOUSE_H

//declaring global variables
extern volatile int sensorVal[8];          //global variable storing sensor values
extern volatile int encoder0;              //golbal variable storing encoder values
extern volatile int encoder5;
extern volatile int encoder6;
extern volatile int encoder7;

//function prototypes for adc
int conv_int(int input);
void adc_init();

//function prototypes for motor
void onlyRight();
void onlyLeft();
void moveRight();                          // do not use
void moveLeft();                           // do not use
void forward();                            // 40% duty
void stop();                               // 0% duty
void easeStop();                           // do not use! has _delay_cycles()
void slow();                               // 25% duty
void fast();                               // do not use
void torque();                             // full speed, only use to start motors
void invertHigh();                         // set invert high
void invertLow();                          // set invert low
void left90();                             // turn profile, test me
void right90();                            // turn profile, test me
void left45();                             // turn profile, not written yet
void right45();                            // turn profile, not written yet
void clockInit();                          // always use me before timerA0Init
void timerA0Init();                        // make sure to init the timer!
void motorInit();                          // i'm just the two above, in order!!

//function prototypes for encoder
void encoderInit();
void encoderReset(int encoderBit);

//function prototypes for floodfill
void addDist(int dist);
char getWalls();
void updateCosts();
void getNextDirection(); 
char inCenter(int x, int y);

#endif
