#include "ComponentCommands.h"

long distance;
long duration;

//------------------------Functions------------------

// function that activates distance sensor and returns the distance in cm
long measureDistance()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // To send out a ping for detecting distance we need to activate the trigPin for 10microsecs
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Record the duration needed for the return signal
    duration = pulseIn(echoPin, HIGH);

    distance = duration * 0.034 * 2; // Converting from time to distance for easier use

    return distance;
}

// function that activates an action tied to pin 22;
void engageAction()
{
    // Activate LED
    digitalWrite(actionPin, HIGH);
    delay(10);
}

// function that deactivates an action tied to pin 22;
void disengageAction()
{
    // Deactivate LED
    digitalWrite(actionPin, LOW);
    delay(10);
}

// loop that continually measures the distance from the senzor and calls functions to activate/deactivate TBD depending on the desired distance treshold
bool distanceLoop(int distanceThresh)
{
    if (measureDistance() < distanceThresh)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Turns on the RGB led with amounts ranging from 0-255
void controlRGB(int redAmount, int grnAmount, int bluAmount)
{
    analogWrite(redPin, redAmount);
    analogWrite(grnPin, grnAmount);
    analogWrite(bluAmount, bluAmount);
}

// test if RGB led works with changeable delay between each diode
void testRGB(int delayAmount)
{
    analogWrite(redPin, 255);
    delay(delayAmount);
    analogWrite(redPin, 0);
    delay(delayAmount);
    analogWrite(grnPin, 255);
    delay(delayAmount);
    analogWrite(grnPin, 0);
    delay(delayAmount);
    analogWrite(bluPin, 255);
    delay(delayAmount);
    analogWrite(bluPin, 0);
    delay(delayAmount);
}

// function that checks if there is something in front of the distance senzor that is making noise, if YES it turns on an LED
bool isSomethingThereAndNoisy(bool distance)
{
    if (distance)
    {
        return true;
    }
    else
    {
        return false;
    }
}