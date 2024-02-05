//pins on the board
//input vars
int armedPin = 11; //launch switch //orange light //yellow wire 
int inPin = 7; //firing switch //slideswitch3 //green wire
int sensorPin = 9; //magnetic sensor //slideswitch4 //green wire

//output vars
int releasePin = 13; //solonoid 1 //object: ???
int launchPin = 12; //solonoid 2 //blue light //yellow wire
int lightPin = 8; //red light //orange wire
int armedLightPin = 6; //Green light //orange wire

//values
int inVal = 0;
int sensorVal = 0;
int armedVal = 0;
bool fired = false;
bool launch = false;
bool armed = false;

void setup() {
  // put your setup code here, to run once:
  //the vars that are set up to be outputs need to have digitalWrite command used on them for it to work
  pinMode(releasePin, OUTPUT);

  pinMode(launchPin, OUTPUT); //sets it up to allow elec from the circuit to the yellow wire so the blue light can flash blue (the flash of blue is meant to represent the solonoid being relased)

  pinMode(lightPin, OUTPUT); //sets it up to allow elec from the circuit to the orange wire so the red light can flash red 

  pinMode(armedLightPin, OUTPUT); //sets it up to allow elec from the circuit to orange wire so the grenn light can flash green

  //the vars that are set up to be outputs need to have digitalRead command used on them for 
  pinMode(inPin, INPUT); //sets up the pin that var inPin is assigned to so it can receive an input to send a signal to the ciruit

  pinMode(sensorPin, INPUT); //sets up the pin that var sensorPin is assigned to so it can receive an input to send a signal to the ciruit

  pinMode(armedPin, INPUT); //sets up the pin that var armedPin is assigned to so it can receice an input to send a signal to the ciruit
}

void loop() {
  // put your main code here, to run repeatedly:
  inVal = digitalRead(inPin);   // read the input pin //inVal given a value of high meaning it set to 1 and gets the elec signal from pin 7
  sensorVal = digitalRead(sensorPin);   // read the input pin //sensorVal is given a value of high meaning it set to 1 and get elec signal from pin 9
  armedVal = digitalRead(armedPin);   // read the input pin //armedVal is given a value of high meaning it set to 1 and get elec signal from pin 11

  //with digitalRead(var), the var that it is assigned to will be enter into a high state getting an int val of 1 while getting a signal from the pin that var in the parameter is assign to, when digitalWrite is called up with the var that got value digitalRead in the 2nd parameter, the signal from the pin that var parameter of digitalRead will go to the pin of the output var to perform the task that output var is assigned too

  //the if statement presented here is waited for an input from armedVal via armedPin showing the object is ready to launch
  if (armedVal == 1 ) {
    //sets the bool var armed to true, showing that the objected is ready to be launch
    armed = true;
    //The red light on the board will flash red to show the armed var is set to true and is ready to begin the launch process
    digitalWrite(lightPin, HIGH);
  } else {
    armed = false;
    //The red light will not flash red if the launch process has been done or something gone wrong
    digitalWrite(lightPin, LOW);
  }

  //this while loop will check to see if the bool var armed is made true and will run as long as armed is true
  while (armed == true) {
    //It is given the order to launch.
    //The boom box has been pressed and it is activating the Trebuchet, and releasing the pin to accelerate the weights
    //the if will activate if inPin gets an input from pin 7 which make the var inVar into 1 and if the object has not been release from the trebuchet
    if (inVal == 1 && fired == false) {
      //the blue light will flash blue to indicate that it's in the final stage to launch the object and it the solonoid 2 connected to it will release
      digitalWrite(launchPin, HIGH);
      //the light will flash red to indictate that statement presented here works as intended
      digitalWrite(lightPin, HIGH);
      //var bool launch is set to true to allow the final stage of the launch process to begin
      launch = true;
    }

    //the sensor is waiting for a magnetic field to pass by, as soon as it detects any strong magnetic field it will release the sling.
    //also needs to make sure that launch var has set to true that the trebuchet won't have already launch the object
    if (sensorVal != 0 && fired == false && launch == true) {
      //once an input has been recieved from pin 9 from var sensorPin and makes the var SensorVal into 1, the current going pin 13 will release solonoid 1 and launch the object 
      digitalWrite(releasePin, HIGH);
      //var fired will be made true to indict that the ball has been launched
      fired = true;
    }
  }

  //Trebuchet has fired and is finished its launch cycle. The Trebuchet resets all of its values so its ready for next launch.
  //Trebuchet is waiting for boom box to be turned off before resetting.
  //the if statement will activate if the both bool var fired and launch are set to true and the digitalRead for inPin no longer finds an input so it reset back to 0
  if (inVal == 0 && fired == true && launch == true) {
    //both bool var are reset
    fired = false;
    launch = false;
  }


}