#include<SoftwareSerial.h>
#include<TinyGPS++.h>
//# define pwm 2
//# define ip1 3
//# define ip2 4
//# define buzz 5
# define IR 6
SoftwareSerial Serial1(3, 2);
int count = 0;
char tag1[12] = "26002E8F1691";
char tag2[12] = "26002DD4825D";
char newtag[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int i = 0;
int c = 0;
int co = 0;
int flag;
void setup() {
  // put your setup code here, to run once:
  // pinMode(0, INPUT);
  //pinMode(pwm, OUTPUT);
  // pinMode(ip1, OUTPUT);
  // pinMode(ip2, OUTPUT);
  //pinMode(buzz, OUTPUT);
  pinMode(IR, INPUT);
  attachInterrupt(1, sensor, CHANGE);
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //clockwise motion
  //digitalWrite(ip1, HIGH);      // motor starts to rotate
  //digitalWrite(ip2, LOW);
  //  digitalWrite(pwm, 255);
  //tagreader

  if (Serial.available() && i < 12) {
    while (Serial.available()) {
      newtag[i] = Serial.read();
      i++;
      delay(5);
    }
    Serial.println(newtag);
    Serial1.write(newtag);
    for (i = 0; i < 12; i++) {
      if (tag1[i] == newtag[i]) {
        c = c + 1;
      }
    }
    for (i = 0; i < 12; i++) {
      if (tag2[i] == newtag[i]) {
        co = co + 1;
      }
    }
    if (c == 12) {
      Serial.println("CANDY");
    }
    else if (co == 12) {
      Serial.println("COOKIES");
    }
    else {
      Serial.println("Access Denied");
    }
  }

  if (flag == 1) {
    if (digitalRead(3) == LOW) {
      while (digitalRead(3) == LOW);
      count = count + 1;
      Serial.println(count);
    }
  }
  flag = 0;
  newtag[12] = {0};
  c = 0;
  co = 0;


}


void sensor()

{
  flag = 1;
}
