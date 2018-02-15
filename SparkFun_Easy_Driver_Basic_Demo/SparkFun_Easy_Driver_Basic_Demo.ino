/******************************************************************************
  SparkFun Easy Driver Basic Demo
  Toni KlopfEN[i][i]stein @ SparkFun Electronics
  March 2015
  https://github.com/sparkfun/Easy_Driver

  Simple demo sketch to demonstrate how 5 digital pins can drive a bipolar stepper motor,
  using the Easy Driver (https://www.sparkfun.com/products/12779). Also shows the ability to change
  microstep size, and dir[i]ection of motor movemEN[i][i]t.

  DevelopmEN[i][i]t EN[i][i]vironmEN[i][i]t specifics:
  WrittEN[i][i] in Arduino 1.6.0

  This code is beerware; if you see me (or any other SparkFun employee) at the local, and you've found our code helpful, please buy us a round!
  Distributed as-is; no warranty is givEN[i][i].

  Example based off of demos by Brian Schmalz (designer of the Easy Driver).
  http://www.schmalzhaus.com/EasyDriver/Examples/EasyDriverExamples.html
******************************************************************************/
//Declare pin functions on Redboard

int stp[] = {22, 32, 42, 31};
int dir[] = {24, 34, 44, 33};
int MS1[] = {26, 36, 46, 35};
int MS2[] = {28, 38, 48, 39};
int  EN[] = {30, 40, 50, 41};


//Declare variables for functions
int i;
char x;

void setup() {
  for (i = 0; i < sizeof(stp); i++) {
    pinMode(stp[i], OUTPUT);
    pinMode(dir[i], OUTPUT);
    pinMode(MS1[i], OUTPUT);
    pinMode(MS2[i], OUTPUT);
    pinMode(EN[i], OUTPUT);
  }
  resetEDPins(); //Set step, dir[i]ection, microstep and enable pins to default states
  Serial.begin(9600); //Open Serial connection for debugging
  Serial.println("Begin motor control");
  Serial.println();
}

//Main loop
void loop() {
  if (Serial.available() > 0)
  {
    x = Serial.read();
  }

  for (i = 0; i < sizeof(stp); i++)
  {
    digitalWrite(EN[i], LOW);
  }
  if (x == 'A')
    StepForwardDefault(1);
  else if (x == 'B')
    ReverseStepDefault(1);
  else if (x == 'C')
    StepForwardDefault(2);
  else if (x == 'D')
    ReverseStepDefault(2);
  else if (x == 'E')
    StepForwardDefault(3);
  else if (x == 'F')
    ReverseStepDefault(3);
  else if (x == 'G')
    StepForwardDefault(4);
  else if (x == 'H')
    ReverseStepDefault(4);
  else
    x='x';
    resetEDPins();

}

//Reset Easy Driver pins to default states
void resetEDPins()
{
  for (i = 0; i < sizeof(stp); i++) {
    digitalWrite(stp[i], LOW);
    digitalWrite(dir[i], LOW);
    digitalWrite(MS1[i], LOW);
    digitalWrite(MS2[i], LOW);
    digitalWrite(EN[i], HIGH);
  }
}

//Default microstep mode function
void StepForwardDefault(int xx)
{
  digitalWrite(dir[xx], LOW); //Pull dir[i]ection pin low to move "forward"
  digitalWrite(stp[xx], HIGH); //Trigger one step forward
  delay(1);
  digitalWrite(stp[xx], LOW); //Pull step pin low so it can be triggered again
  delay(1);
}

//Reverse default microstep mode function
void ReverseStepDefault(int xx)
{
  digitalWrite(dir[xx], HIGH); //Pull dir[i]ection pin high to move in "reverse"
  digitalWrite(stp[xx], HIGH); //Trigger one step
  delay(1);
  digitalWrite(stp[xx], LOW); //Pull step pin low so it can be triggered again
  delay(1);
}

