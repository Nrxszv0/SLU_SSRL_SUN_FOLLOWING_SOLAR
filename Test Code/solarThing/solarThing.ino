/***************************************************
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 8 servos, one after the other on the
  first 8 pins of the PCA9685

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These drivers use I2C to communicate, 2 pins are required to
  interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);

// Depending on your servo make, the pulse width min and max may vary, you
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2300 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

int lvFront;
int lvRight;
int lvLeft;
int lvBack;

int photoPin1 = A0;
int photoPin2 = A1;
int photoPin3 = A2;
int photoPin4 = A3;

int FL = 90;
int FR = 90;
int BL = 90;
int BR = 90;

int FLSer = 0;
int FRSer = 1;
int BLSer = 2;
int BRSer = 3;
void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);
  setAngle(FLSer, FL);
  setAngle(FRSer, FR);
  setAngle(BLSer, BL);
  setAngle(BRSer, BR);
}

void setAngle(int servo, int degree) {
  int microsec = map(degree, 0, 180, USMIN, USMAX);
  pwm.writeMicroseconds(servo, microsec);
}

void loop() {
  lvFront = analogRead(photoPin1);
  lvRight = analogRead(photoPin2);
  lvLeft = analogRead(photoPin3);
  lvBack = analogRead(photoPin4);

  if (isGreatest(lvFront, lvRight, lvLeft, lvBack)) {
    tiltFront();
  }
  else if (isGreatest(lvRight, lvLeft, lvBack, lvFront)) {
    tiltRight();
  }
  else if (isGreatest(lvLeft, lvBack, lvFront, lvRight)) {
    tiltLeft();
  }
  else if (isGreatest(lvBack, lvFront, lvRight, lvLeft)) {
    tiltBack();
  }
  else{
    lcd.clear();
  }

  String str = "Front: ";
  str += lvFront;
  str += "\tRight: ";
  str += lvRight;
  str += "\tLeft: ";
  str += lvLeft;
  str += "\tBack: ";
  str += lvBack;

  Serial.println(str);
  delay(250);
}

//Left Tighten +, Loosen -
//Right Tighten -, Loosen +

void tiltFront() {
  //Left Tighten +, Loosen -
  //Right Tighten -, Loosen +
  //Tighten FL and FR
  //Loosen BL and BR
  if (checkServos()) {
    Serial.println("Tilting Front");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tilt Front");
    FL++;
    FR--;
    BL--;
    BR++;
    setAngle(FLSer, FL);
    setAngle(FRSer, FR);
    setAngle(BLSer, BL);
    setAngle(BRSer, BR);

  }
}

void tiltLeft() {
  //Left Tighten +, Loosen -
  //Right Tighten -, Loosen +
  //Tighten FL and BL
  //Loosen FR and BR
  if (checkServos()) {
    Serial.println("Tilting Left");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tilt Left");
    FL++;
    FR++;
    BL++;
    BR++;
    setAngle(FLSer, FL);
    setAngle(FRSer, FR);
    setAngle(BLSer, BL);
    setAngle(BRSer, BR);
  }
}

void tiltRight() {
  //Left Tighten +, Loosen -
  //Right Tighten -, Loosen +
  //Tighten FR and BR
  //Loosen FL and BL
  if (checkServos()) {
    Serial.println("Tilting Right");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tilt Right");
    FL--;
    FR--;
    BL--;
    BR--;
    setAngle(FLSer, FL);
    setAngle(FRSer, FR);
    setAngle(BLSer, BL);
    setAngle(BRSer, BR);
  }
}

void tiltBack() {
  //Left Tighten +, Loosen -
  //Right Tighten -, Loosen +
  //Tighten BL and BR
  //Loosen FL and FR
  if (checkServos()) {
    Serial.println("Tilting Back");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tilt Back");
    FL--;
    FR++;
    BL++;
    BR--;
    setAngle(FLSer, FL);
    setAngle(FRSer, FR);
    setAngle(BLSer, BL);
    setAngle(BRSer, BR);
  }
}


bool checkServos() {
  int currFL = FL;
  int currFR = FR;
  int currBL = BL;
  int currBR = BR;
  int minV = 2;
  int maxV = 178;
  if (currFL > 2 && currFL < 178 && currFR > 2 && currFR < 178 && currBL > 2 && currBL < 178 && currBR > 2 && currBR < 178) {
    return true;
  }
  return false;
}


bool isGreatest(int a, int b, int c, int d) {
  int bound = 100;
  int vars[] = {a, (b + bound), (c + bound), (d + bound)};
  int greatest = vars[0];
  for (int i = 0; i < 4; i++) {
    if (vars[i] > greatest) {
      greatest = vars[i];
    }
  }
  if ( greatest == vars[0]) {
    return true;
  }
  else {
    return false;
  }
}
