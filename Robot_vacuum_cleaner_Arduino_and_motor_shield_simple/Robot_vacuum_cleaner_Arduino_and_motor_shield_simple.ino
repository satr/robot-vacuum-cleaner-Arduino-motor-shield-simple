/*
 Program for controlling a robot with two motors.
 The robot turns when motors changes their speed and direction.
 Front bumpers on left and right sides detect obstacles.
 Motor shield is used to run motors.
 */
//right side
const int pinRightMotorDirection = 4;//"Dir A" on motor-shield
const int pinRightMotorSpeed = 3;//"PWM A" on motor-shield
const int pinRightBumper = 5;
//left side
const int pinLeftMotorDirection = 7;//"Dir B" on motor-shield
const int pinLeftMotorSpeed = 6;//"PWM B" on motor-shield
const int pinLeftBumper = 8;
//timeouts - they are different to avoid robot stuck in a corner
const int turnRightTimeout = 150;
const int turnLeftTimeout = 200;
//set in counter how long a motor is running back: N/10 (in milliseconds)
int countDownWhileMovingToRight;
int countDownWhileMovingToLeft;
//Initialization
void setup() {
  initPins();
  runRightMotorForward();
  runLeftMotorForward();
  startMotors();
}
//Main loop
void loop() {
  verifyAndSetRightSide();
  verifyAndSetLeftSide();
  processRightSide();
  processLeftSide();
  delay(10);//repeat every 10 milliseconds
}
//---------------------------------------------------
void initPins(){
  pinMode(pinRightMotorDirection, OUTPUT);
  pinMode(pinRightMotorSpeed, OUTPUT);
  pinMode(pinRightBumper, INPUT_PULLUP);
  pinMode(pinLeftMotorDirection, OUTPUT);
  pinMode(pinLeftMotorSpeed, OUTPUT);
  pinMode(pinLeftBumper, INPUT_PULLUP);
}
void startMotors(){
  runRightMotorForward();
  runLeftMotorForward();
}
void processRightSide(){
  if(countDownWhileMovingToRight <= 0)//checks if counter was NOT ran when bumper had been pressed
    return;
  //otherwise - counter is counting down (as a delay) while the right motor is moving backward
  countDownWhileMovingToRight--;//decrease the counter if it WAS ran when bumper had been pressed
  if(countDownWhileMovingToRight <= 0)//if the running counter got down to zero
    runRightMotorForward();//run the right motor forward
}
void processLeftSide(){
  if(countDownWhileMovingToLeft <= 0)
    return;
  countDownWhileMovingToLeft--;
  if(countDownWhileMovingToLeft <= 0)
    runLeftMotorForward();
}
void verifyAndSetRightSide(){
  if(checkBumperIsNotPressed(pinRightBumper) //checks if right bumper has NOT been pressed
  )
    return;
  if(checkCounterIsNotSet(countDownWhileMovingToRight))//if the counter is not yet counting down
    runRightMotorBackward();//run the right motor backward
  countDownWhileMovingToRight = turnRightTimeout;//set the counter to maximum value to start it counting down
}
void verifyAndSetLeftSide(){
  if(checkBumperIsNotPressed(pinLeftBumper) //checks if left bumper has NOT been pressed
  )
    return;
  if(checkCounterIsNotSet(countDownWhileMovingToLeft))//if the counter is not yet counting down
    runLeftMotorBackward();//run the right motor backward
  countDownWhileMovingToLeft = turnLeftTimeout;//set the counter to maximum value to start it counting down
}
bool checkCounterIsNotSet(int counter){
  return counter <= 0;
}
bool checkBumperIsNotPressed(int pinBumper){
  return digitalRead(pinBumper) == HIGH;
}
void runRightMotorForward(){
  runMotorForward(pinRightMotorDirection, pinRightMotorSpeed);
}
void runLeftMotorForward(){
  runMotorForward(pinLeftMotorDirection, pinLeftMotorSpeed);
}
void runRightMotorBackward(){
  runMotorBackward(pinRightMotorDirection, pinRightMotorSpeed);
}
void runLeftMotorBackward(){
  runMotorBackward(pinLeftMotorDirection, pinLeftMotorSpeed);
}
void runMotorForward(int pinMotorDirection, int pinMotorSpeed){
  digitalWrite(pinMotorDirection, true); //set direction forward
  analogWrite(pinMotorSpeed, 255); //set max speed forward
}
void runMotorBackward(int pinMotorDirection, int pinMotorSpeed){
  digitalWrite(pinMotorDirection, false); //set direction backward
  analogWrite(pinMotorSpeed, 255); //set max speed backward
}

