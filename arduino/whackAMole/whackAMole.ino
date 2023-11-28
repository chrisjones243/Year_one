#include <Servo.h>

// assign LEDs and button to pins
const int greenLEDPin[] = {4,5,6};
const int redLEDPin[] = {11,12,13};
const int scoreLED = 9;
const int playerOneButton = 2;
const int playerTwoButton = 3;
Servo servo;


// declare variables
// int redRandNumber;
int greenRandNumber;
int servoPosition = 90;
int difficulty = 0;
volatile bool redLEDOn;
volatile bool greenLEDOn;
volatile bool scoreLEDOn;
volatile bool playerOneButtonPressed = false;
volatile bool playerTwoButtonPressed = false;

// timer variables
unsigned long greenStartMillis;
unsigned long redStartMillis;
unsigned long servoStartMillis;
unsigned long currentMillis;
int greenPeriod = 1000;
int redPeriod = 1000; 

// bool startMenuOn;

volatile int playerOneScore;
volatile int playerTwoScore; 

void(* resetFunc) (void) = 0; //declare reset function at address 0

int randomDelayTime(bool forLED) {
  if (forLED) {
    switch (difficulty) {
      case 0:
        return 800;
        break;
      case 1:
        return 550;
        break;
      case 2:
        return 300;
        break;
    }
  } else {
    switch (difficulty) {
      case 0:
        return random(1000, 2000);
        break;
      case 1:
        return random(600, 800);
        break;
      case 2:
        return random(300, 600);
        break;
    }
  }
}


void startMenu() {
  Serial.begin(9600);

  digitalWrite(scoreLED, HIGH);

  while (!(playerOneButtonPressed && playerTwoButtonPressed)) {

      greenLEDOn = true;
      redLEDOn = true;
    
      digitalWrite(greenLEDPin[difficulty], HIGH);
      digitalWrite(redLEDPin[difficulty], HIGH);
      

      if (playerOneButtonPressed) {
        playerOneButtonPressed = false;
        if (difficulty > 0) {
          digitalWrite(greenLEDPin[difficulty], LOW);
          digitalWrite(redLEDPin[difficulty], LOW);
          difficulty--;
          
        }
      }
      if (playerTwoButtonPressed) {
        playerTwoButtonPressed = false;
        if (difficulty < 2) {
          digitalWrite(greenLEDPin[difficulty], LOW);
          digitalWrite(redLEDPin[difficulty], LOW);
          difficulty++;
        }
      }
      delay(500);
    
  
  } 
  Serial.println(playerOneButtonPressed);
  Serial.println(playerTwoButtonPressed);
  digitalWrite(scoreLED, LOW);
  digitalWrite(greenLEDPin[difficulty], LOW);
  digitalWrite(redLEDPin[difficulty], LOW);
  greenLEDOn = false;
  redLEDOn = false;
  playerTwoButtonPressed = false;
  playerOneButtonPressed = false;
  playerOneScore = 0;
  playerTwoScore = 0;
}


void blinkScoreLED(){
	digitalWrite(scoreLED, HIGH);
    delay(110);
  	digitalWrite(scoreLED, LOW);
    if (playerOneButtonPressed) {
      playerOneButtonPressed = false;
    } 
    if (playerTwoButtonPressed) {
      playerTwoButtonPressed = false;
    }
    scoreLEDOn = false;
}



void winnerBlinkLED(bool leftOrRight) {
  for (int i = 0; i < 8; i++) {
    if (leftOrRight) {
      for (int i = 0; i < 3; i++) {
        digitalWrite(greenLEDPin[i], HIGH);
        digitalWrite(redLEDPin[i], HIGH);
        delay(130);
        digitalWrite(greenLEDPin[i], LOW);
        digitalWrite(redLEDPin[i], LOW);
        delay(130);
      }
    } else {
      for (int i = 2; i >= 0; i--) {
        digitalWrite(greenLEDPin[i], HIGH);
        digitalWrite(redLEDPin[i], HIGH);
        delay(130);
        digitalWrite(greenLEDPin[i], LOW);
        digitalWrite(redLEDPin[i], LOW);
        delay(130);
      }
    }
  }

  for (int i = 0; i < 60; i++) {
  digitalWrite(greenLEDPin[0], HIGH);
  digitalWrite(greenLEDPin[1], HIGH);
  digitalWrite(greenLEDPin[2], HIGH);
  digitalWrite(redLEDPin[0], HIGH);
  digitalWrite(redLEDPin[1], HIGH);
  digitalWrite(redLEDPin[2], HIGH);
  digitalWrite(scoreLED, HIGH);
  delay(60);
  digitalWrite(greenLEDPin[0], LOW);
  digitalWrite(greenLEDPin[1], LOW);
  digitalWrite(greenLEDPin[2], LOW);
  digitalWrite(redLEDPin[0], LOW);
  digitalWrite(redLEDPin[1], LOW);
  digitalWrite(redLEDPin[2], LOW);
  digitalWrite(scoreLED, LOW);
  delay(60);
  }
}



void switchGreenLED() {
  if (digitalRead(greenLEDPin[greenRandNumber]) == HIGH) {
    greenLEDOn = false;
    digitalWrite(greenLEDPin[greenRandNumber], LOW);
    greenPeriod = randomDelayTime(false);
  } else {
    greenRandNumber = random(3);
    digitalWrite(greenLEDPin[greenRandNumber], HIGH);
    greenLEDOn = true;
    greenPeriod  = randomDelayTime(true);
  }
    
  greenStartMillis = currentMillis;
}


void switchRedLED() {
  if (digitalRead(redLEDPin[redRandNumber]) == HIGH) {
    redLEDOn = false;
    digitalWrite(redLEDPin[redRandNumber], LOW);
    redPeriod = randomDelayTime(false);
  } else {
    redRandNumber = random(3);
    digitalWrite(redLEDPin[redRandNumber], HIGH);
    redLEDOn = true;
    redPeriod = randomDelayTime(true);
  }
    
  redStartMillis = currentMillis;
}



void setup() {
  pinMode(playerOneButton, INPUT);
  pinMode(playerTwoButton, INPUT);
  pinMode(scoreLED, OUTPUT);
  attachInterrupt(0, playerOneInput, FALLING);
  attachInterrupt(1, playerTwoInput, FALLING);
  for (int i=0; i<3; i++){
    pinMode(greenLEDPin[i], OUTPUT);
    pinMode(redLEDPin[i], OUTPUT);
  }
  greenRandNumber = random(3);
  redRandNumber = random(3);
  playerOneScore = 0;
  playerTwoScore = 0;
  servo.attach(10);
  servo.write(servoPosition);
  startMenu();
  greenStartMillis = millis();
  redStartMillis = millis();
  servoStartMillis = millis();
} 



//run main program loop
void loop() {

  if (playerOneScore == 10 || playerTwoScore == 10) {
    winnerBlinkLED(playerOneScore < playerTwoScore); // true = left, false = right
    resetFunc();
  }

  currentMillis = millis();

  if (currentMillis - servoStartMillis >= 500) {
    servoPosition = 90 + (playerOneScore * 9 - playerTwoScore * 9);
    servo.write(servoPosition);
    servoStartMillis = currentMillis;
  }
  if (currentMillis - greenStartMillis >= greenPeriod && !redLEDOn) {
    switchGreenLED();
  }
  if (currentMillis - redStartMillis >= redPeriod && !greenLEDOn) {
    switchRedLED();
  }

  if (scoreLEDOn) {
    blinkScoreLED();
  }
  
}



void playerOneInput() {
  if (greenLEDOn) {
    playerOneButtonPressed = true;
    greenLEDOn = false;
    playerOneScore++;
    scoreLEDOn = true;
  }
}


void playerTwoInput() {
  if (redLEDOn) {
    playerTwoButtonPressed = true;
    redLEDOn = false;
    playerTwoScore++;
    scoreLEDOn = true;
  }
}