#include <AccelStepper.h> // Installed when installing Teensyduino
#include <MultiStepper.h>

// References:
// Accelstepper GitHub: https://github.com/adafruit/AccelStepper
// AccelStepper class/function reference: http://www.airspayce.com/mikem/arduino/AccelStepper/classAccelStepper.html
// Stepper Drivers Big Easy


#define TRAVERSE_STEP_PIN 3                                                                      // Traverse motor controller step pin
#define TRAVERSE_DIR_PIN 2                                                                       // Traverse motor controller direction pin
#define WINDER_STEP_PIN 5                                                                        // Winder motor controller step pin
#define WINDER_DIR_PIN 4                                                                         // Winder motor controller direction pin
#define PAUSE_BUTTON 6                                                                           // Button on pin 6
#define KNOB_1_A 23                                                                              // encoder on pin 23
#define KNOB_2_A 22                                                                              // encoder on pin 22
#define LIMIT_A 7                                                                                // tactile switch on pin 7
#define LIMIT_B 8                                                                                // tactile switch on pin 8

float traverse_speed = 20000;                                                                    // 10,000 ticks per second angular velocity
float traverse_accel = 200000;                                                                   // 100,000 ticks per second^2 angular acceleration
float winder_speed = 20000;                                                                      // 10,000 ticks per second angular velocity
float winder_accel = 200000;                                                                     // 100,000 ticks per second^2 angular acceleration

// Determine the number of ticks needed to traverse the bobbin
int flipper = 1; //change this value if values are all flipped for position
int Ammount = 614;
float bobbin_length = 4.3; // inches
float bobbin_dia = 0.618; // inches
float pully_dia = 0.625; // inches
int ticks_per_rev = 3200;
float bobbin_dist_per_rev = bobbin_dia * PI;
float goal[] = {0, flipper * bobbin_length / (pully_dia * PI / ticks_per_rev)}; // to go from 0 to trav ticks
float Winder_goal = Ammount / (bobbin_dist_per_rev / ticks_per_rev);
volatile uint8_t idx = 0;
boolean test = false;
boolean Start_spinning = false;
boolean Auto_Calibrate = false;
int Yarn_Ammount = 0;
int Ticks_Per_mm = 67;

long winderposition = 0; // winder position
long traverseposition = 0; //traverse position
byte val[6] = {0}; // Data received from the serial port
int ticker = 0;

AccelStepper traverse(AccelStepper::DRIVER, TRAVERSE_STEP_PIN, TRAVERSE_DIR_PIN); //traverse pins
AccelStepper winder(AccelStepper::DRIVER, WINDER_STEP_PIN, WINDER_DIR_PIN); //winder pins
IntervalTimer timer; //precise timing interval

void setup() {
  //Serial Communication
  Serial.begin(115200);
  establishContact();                   // send a byte to establish contact until receiver responds
  // put your setup code here, to run once:
  traverse.moveTo(0);
  traverse.setAcceleration(traverse_accel);
  traverse.setMaxSpeed(traverse_speed);
  traverse.setSpeed(traverse_speed);

  winder.setAcceleration(winder_accel);
  winder.setMaxSpeed(winder_speed);
  winder.setSpeed(winder_speed);

  pinMode(LED_BUILTIN, OUTPUT);         // LED Outputs directiondirection
  pinMode(PAUSE_BUTTON, INPUT_PULLUP);  // Button/ switch (input pullup)
  pinMode(LIMIT_A, INPUT);
  pinMode(LIMIT_B, INPUT);
  pinMode(KNOB_1_A, INPUT);
  pinMode(KNOB_2_A, INPUT);

  timer.begin(pulse, 20);               //timing interval w/ pulse 20
}

union converter {
  byte b[4];
  int ival;
} u;

void loop() {
  if (Serial.available() > 0) {
    while (ticker < 6) {
      val[ticker] = Serial.read();
      ticker++;
    } 
    ticker = 0;
    Serial.flush();
    if (val[0] == 1) {
      Manual_Control();
    }
    else if (val[0] == 2) {
      Speed_Settings();
    }
    else if (val[0] == 3) {
      Bobbin_Setting();
    }
    else if (val[0] == 4) {
      Start_Winding();
    }
    for (int i = 0 ; i < sizeof(val) ; i++) {
      Serial.print(val[i]);
    }
    memset(val, 0, sizeof(val));
  }
  else {
    Serial.println("0");
    delay(10); //I dont know why but accelstepper freaks out without some kind of delay
  }

  // put your main code here, to run repeatedly:
  noInterrupts(); // disables interrupts
  if (test) {
    Test_Run();
  }
  if (Start_spinning) {
    Run();
  }
  if (Auto_Calibrate) {
    traverse.move(flipper * -100);
    traverse.setMaxSpeed(-3000);
    traverse.setSpeed(-3000);
    Auto_Calibrate = Auto();
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("A");   // send a capital A
    delay(1);
  }
}

void pulse () {
  winder.run();
  traverse.run();
}
