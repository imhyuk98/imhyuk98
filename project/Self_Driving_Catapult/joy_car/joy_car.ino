#include <SoftwareSerial.h>
SoftwareSerial HC06(2, 3); // BTSerial(Rx, Tx)
int A_1A = 10;
int A_1B = 11;
int B_1A = 8;
int B_1B = 9;
int speed = 180;   // speed: 0~ 255
char joyBT;

void setup() {
  //핀을 초기화 하고, 출력설정
  pinMode(A_1A, OUTPUT);
  pinMode(A_1B, OUTPUT);
  pinMode(B_1A, OUTPUT);
  pinMode(B_1B, OUTPUT);
  digitalWrite(A_1A, LOW);
  digitalWrite(A_1B, LOW);
  digitalWrite(B_1A, LOW);
  digitalWrite(B_1B, LOW);
  Serial.begin(9600);  
  HC06.begin(9600);
}

void loop() {
  if (HC06.available()) {      
    joyBT = HC06.read();
    HC06.println(joyBT);        
    switch (joyBT) { 
     case 'f' :        // 모터 전진        
        //모터A
        analogWrite(A_1A, speed);
        analogWrite(A_1B, 0);    
        //모터B
        analogWrite(B_1A, speed);
        analogWrite(B_1B, 0);
        break;
     
    case 'b' :        // 모터 후진                
        analogWrite(A_1A, 0);
        analogWrite(A_1B, speed);            
        analogWrite(B_1A, 0);
        analogWrite(B_1B, speed);  
        break;
       
    case 'l' :        // 모터 좌회전                
        analogWrite(A_1A, speed);
        analogWrite(A_1B, 0);            
        analogWrite(B_1A, 0);
        analogWrite(B_1B, speed);        
        break;    
    
    case 'r' :        //모터 우회전                
        analogWrite(A_1A, 0);
        analogWrite(A_1B, speed);            
        analogWrite(B_1A, speed);
        analogWrite(B_1B, 0);
        break;
    
    case 's' :        // 모터 정지      
      analogWrite(A_1A, 0);  
      analogWrite(A_1B, 0);    
      analogWrite(B_1A, 0);
      analogWrite(B_1B, 0);
      break;    
    }
  }
}