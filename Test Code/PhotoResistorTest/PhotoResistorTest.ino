#include <Servo.h>
Servo ser1;
int serPin = 2;
int serVal = 180;
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
  ser1.attach(serPin);
  ser1.write(serVal);
}

void loop() {
  // put your main code here, to run repeatedly:


  lvFront = analogRead(photoPin1);
  lvRight = analogRead(photoPin2);
  lvLeft = analogRead(photoPin3);
  lvBack = analogRead(photoPin4);

  if(isGreatest(lvFront,lvRight,lvLeft,lvBack)){
    Serial.println("Tilt Front");    
  }
  else if(isGreatest(lvRight,lvLeft,lvBack,lvFront)){
    Serial.println("Tilt Right");
  }
  else if(isGreatest(lvLeft,lvBack,lvFront,lvRight)){
    Serial.println("Tilt Left");
  }
  else if(isGreatest(lvBack,lvFront,lvRight,lvLeft)){
    Serial.println("Tilt Back");
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
  //  ser1.write(serVal);
  delay(250);

}

bool isGreatest(int a, int b, int c, int d) {
  int bound = 100;
  int vars[] = {a, (b+bound), (c+bound), (d+bound)};
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






