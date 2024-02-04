//pins on the board
//input vars
int armedPin = 11; //launch switch //orange light
int inPin = 7; //firing switch //slideswitch3
int sensorPin = 9; //magnetic sensor //slideswitch4

//output vars
int releasePin = 13; //solonoid 1 //object: ???
int launchPin = 12; //solonoid 2 //blue light 
int lightPin = 8; //red light 
int armedLightPin = 6; //Green light 

//values
int inVal = 0;
int sensorVal = 0;
int armedVal = 0;
bool fired = false;
bool launch = false;
bool armed = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(releasePin, OUTPUT);
  pinMode(launchPin, OUTPUT);
  pinMode(lightPin, OUTPUT);
  pinMode(armedLightPin, OUTPUT);
  pinMode(inPin, INPUT);
  pinMode(sensorPin, INPUT);
  pinMode(armedPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  inVal = digitalRead(inPin);   // read the input pin
  sensorVal = digitalRead(sensorPin);   // read the input pin
  armedVal = digitalRead(armedPin);   // read the input pin

  if (armedVal == 1) {
    armed = true;
    digitalWrite(lightPin, HIGH);
  } else {
    armed = false;
    digitalWrite(lightPin, LOW);
  }


  while (armed == true) {
    //It is given the order to launch.
    //The boom box has been pressed and it is activating the Trebuchet, and releasing the pin to accelerate the weights
    if (inVal == 1 && fired == false) {
      digitalWrite(launchPin, HIGH);
      digitalWrite(lightPin, HIGH);
      launch = true;
    }

    //the sensor is waiting for a magnetic field to pass by, as soon as it detects any strong magnetic field it will release the sling.
    if (sensorVal != 0 && fired == false && launch == true) {
      digitalWrite(releasePin, HIGH);
      fired = true;
    }
  }

  //Trebuchet has fired and is finished its launch cycle. The Trebuchet resets all of its values so its ready for next launch.
  //Trebuchet is waiting for boom box to be turned off before resetting.
  if (inVal == 0 && fired == true && launch == true) {
    fired = false;
    launch = false;
  }


}