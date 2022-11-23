#include <Arduino.h>
#include <WiFi.h>
#include <Update.h>
#include <HTTPClient.h>

// pin variables

const int actionPin = 22;
const int redPin = 13;
const int grnPin = 14;
const int bluPin = 15;
const int trigPin = 19;
const int echoPin = 18;
const int micPinDigital = 23;
const int micPinAnalogue = 4;

// stored variables for wifi setup

const char *SSID = "Hajdinjak";
const char *SSIDpassword = "7595zec590";
int timeOutCount = 0;

// variables for update(not yet implemented)

const char *url;
const char *host;
const char *file;
String type = "Smart DogFeeder";
const float currentVersion = 0.2;

// stored variables for microphone (not yet implemented)

int micValueDigi;
int micValueAnalogue;

// stored variables for distance senzor

int distanceThreshold = 50;
long distance;
long duration;

// variables to negate false positives

bool distanceActive = false;
bool soundActive = false;

// function that activates distance senzor and returns the distance in cm
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

// function that checks if there is something in front of the distance senzor that is making noise, if YES it turns on an LED
bool isSomethingThereAndNoisy(bool noise, bool distance)
{
  if (noise && distance)
  {
    return true;
  }
  else
  {
    return false;
  }
}
// Loop that continually checks the status of the microphone and changes bool depending on noise
void micLoop()
{
  if (digitalRead(micPinDigital) == HIGH)
  {
    soundActive = true;
  }
  else
  {
    soundActive = false;
  }
}

// loop that continually measures the distance from the senzor and calls functions to activate/deactivate TBD depending on the desired distance treshold
void distanceLoop(int distanceThresh)
{
  if (measureDistance() < distanceThresh)
  {
    distanceActive = true;
  }
  else
  {
    distanceActive = false;
  }
}

void connectToWifi()
{
  // WiFi activation and connection
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, SSIDpassword);
  Serial.println("Trying to connect to WiFi...");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(200);
    timeOutCount++;

    if (timeOutCount > 20)
    {
      ESP.restart();
    }
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
// main loop that acutally starts off everything
void workingLoop()
{
  if (isSomethingThereAndNoisy(soundActive, distanceActive))
  {
    controlRGB(255, 255, 255);
  }
  else
  {
    controlRGB(0, 0, 0);
  }
}

void setup()
{
  // serial monitoring
  Serial.begin(115200);
  Serial.println("Serial begin!");
  // pin setup (distance sensor)
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // pin setup microphone
  pinMode(micPinDigital, INPUT);
  pinMode(micPinAnalogue, INPUT);
  // pin setup(rgb led)
  pinMode(redPin, OUTPUT);
  pinMode(grnPin, OUTPUT);
  pinMode(bluPin, OUTPUT);
  // pin setup(action pin)
  pinMode(actionPin, OUTPUT);

  connectToWifi();
  testRGB(250);
}

// main loop
void loop()
{
  distanceLoop(distanceThreshold);
  micLoop();
  workingLoop();
}
