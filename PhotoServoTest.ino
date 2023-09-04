#include <Servo.h>
Servo serFL;
Servo serFR;
Servo serBL;
Servo serBR;

int serPinFL = 2;
int serPinFR = 2;
int serPinBL = 2;
int serPinBR = 2;
int svFL = 0;

int lvFront;
int lvRight;
int lvLeft;
int lvBack;

int photoPin1 = A0;
int photoPin2 = A1;
int photoPin3 = A2;
int photoPin4 = A3;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  serFL.attach(2, 500, 2500);
  serFR.attach(3, 500, 2500);
  serBL.attach(4, 500, 2500);
  serBR.attach(5, 500, 2500);

  serFL.write(90); // 0 -180 to tighten
  serBL.write(90); // 0 -180 to tighten
  serFR.write(90); //180 - 0 to tighten
  serBR.write(90); //180 - 0 to tighten

}

void loop() {
  // put your main code here, to run repeatedly:

  Servo sers[] = {serFL, serFR, serBL, serBR};





  lvFront = analogRead(photoPin1);
  lvRight = analogRead(photoPin2);
  lvLeft = analogRead(photoPin3);
  lvBack = analogRead(photoPin4);

  if (isGreatest(lvFront, lvRight, lvLeft, lvBack)) {
    Serial.println("Tilt Front");
    tiltFront();
  }
  else if (isGreatest(lvRight, lvLeft, lvBack, lvFront)) {
    Serial.println("Tilt Right");
    tiltRight();
  }
  else if (isGreatest(lvLeft, lvBack, lvFront, lvRight)) {
    Serial.println("Tilt Left");
    tiltLeft();
  }
  else if (isGreatest(lvBack, lvFront, lvRight, lvLeft)) {
    Serial.println("Tilt Back");
    tiltBack();
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

//  serFL.write(180); // 0 -180 to tighten +
//  serBL.write(180); // 0 -180 to tighten +
//  serFR.write(0); //180 - 0 to tighten -
//  serBR.write(0); //180 - 0 to tighten -

void tiltFront() {
  //Tighten FL and FR
  //Loosen BL and BR
  if (checkServos()) {
    serFL.write(serFL.read() + 1);
    serBL.write(serBL.read() - 1);
    serFR.write(serFR.read() - 1);
    serBR.write(serBR.read() + 1);
  }
}
void tiltBack() {
  //Tighten BL and BR
  //Loosen FL and FR
  if (checkServos()) {
    serFL.write(serFL.read() - 1);
    serBL.write(serBL.read() + 1);
    serFR.write(serFR.read() + 1);
    serBR.write(serBR.read() - 1);
  }
}
void tiltRight() {
  //Tighten FR and BR
  //Loosen FL and BL
  if (checkServos()) {
    serFL.write(serFL.read() - 1);
    serBL.write(serBL.read() - 1);
    serFR.write(serFR.read() - 1);
    serBR.write(serBR.read() - 1);
  }
}
void tiltLeft() {
  //Tighten FL and BL
  //Loosen FR and BR
  if (checkServos()) {
    serFL.write(serFL.read() + 1);
    serBL.write(serBL.read() + 1);
    serFR.write(serFR.read() + 1);
    serBR.write(serBR.read() + 1);
  }
}

bool checkServos() {
  int currFL = serFL.read();
  int currFR = serFR.read();
  int currBL = serFL.read();
  int currBR = serFR.read();
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









//  for (int s = 0; s < 3; s++) {
//    sers[s].write(0);
//  }
//    for (int i = 0; i < 180; i+=5) {
//      Serial.println(i);
//      for (int s = 0; s < 4; s++) {
//        sers[s].write(i);
//      }
//      delay(500);
//    }
//    for (int i = 180; i > 0; i-=5) {
//      Serial.println(i);
//      for (int s = 0; s < 4; s++) {
//        sers[s].write(i);
//      }
//      delay(500);
//    }
