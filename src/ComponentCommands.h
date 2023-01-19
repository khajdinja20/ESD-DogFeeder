// This header file contains all relevant commands relating to interaction with the outside world
#include <Arduino.h>

//--------------------Variables-----------------------
// Pin for the final activation(in our case the servo)
const int actionPin = 22;
// RGB pins
const int redPin = 13;
const int grnPin = 14;
const int bluPin = 15;
// pins for distance sensor
const int trigPin = 19;
const int echoPin = 18;

// variables for measuring distance
const int distanceThreshold = 50;

//---------------------Functions----------------------
long measureDistance();
void engageAction();
void disengageAction();
bool distanceLoop(int distanceThresh);
void controlRGB(int redAmount, int grnAmount, int bluAmount);
void testRGB(int delayAmount);
bool isSomethingThere(bool distance);