#include <Arduino.h>
#include <WiFi.h>
#include <Update.h>
#include <HTTPClient.h>

// pin variables
const int actionPin = 22;
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
long distance;
long duration;

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

// function that activates an LED;
void engageLed()
{
  // Activate LED
  digitalWrite(actionPin, HIGH);
  delay(10);
}

// function that deactivates an LED;
void disengageLed()
{
  // Deactivate LED
  digitalWrite(actionPin, LOW);
  delay(10);
}

// loop that continually measures the distance from the senzor and calls functions to activate/deactivate TBD depending on the argument forwarded
void distanceLoop(int distanceThreshold)
{
  if (measureDistance() < distanceThreshold)
  {
    engageLed();
  }
  else
  {
    disengageLed();
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

void setup()
{
  // serial monitoring
  Serial.begin(115200);
  Serial.println("Serial begin!");
  // pin setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(actionPin, OUTPUT);
  pinMode(micPinDigital, INPUT);
  pinMode(micPinAnalogue, INPUT);

  connectToWifi();
}

// main loop
void loop()
{
  distanceLoop(50);

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("Connected to wifi.");
    delay(1000);
  }
}
