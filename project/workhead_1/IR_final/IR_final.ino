#include <IRremote.h>
#include <Servo.h>

#define irReceiverPin A4  // IR 수신기 핀
#define servoPin A3       // 서보 모터 핀

#define EN1 3                 // 우측 모터 속도
#define EN2 5                 // 좌측 모터 속도
const int rightMotorPin1 = 2; // 우측 모터 핀 1
const int rightMotorPin2 = 4; // 우측 모터 핀 2
const int leftMotorPin1 = 6;  // 좌측 모터 핀 1
const int leftMotorPin2 = 7;  // 좌측 모터 핀 2

// 모터 속도 정의
#define fsp_1 255
#define fsp_2 200
#define ssp_1 255
#define ssp_2 200
#define ssp_3 0

IRrecv irReceiver(irReceiverPin);  // IR 수신 객체
decode_results irResults;           // 수신된 IR 신호를 저장하는 객체
Servo servoMotor;                   // 서보 모터 객체

bool buttonPressed = false;  // 버튼이 눌렸는지 여부를 저장하는 변수
int angle = 50;        // 서보 모터의 시작 각도

void setup() {
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);    
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  irReceiver.enableIRIn();  // IR 수신기 초기화
  servoMotor.attach(servoPin);  // 서보 모터 핀 초기화
  servoMotor.write(angle); // 시작 각도로 서보 모터 설정
  Serial.begin(9600);
}
void forward()
{ // 전진 : 모터 두 개를 모두 정회전 시킴
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
    analogWrite(EN1, ssp_1);
    analogWrite(EN2, ssp_1);
}
void LEFT()
{ // 좌회전 : 우측 모터 정회전, 좌측 모터 역회전
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
    analogWrite(EN1, ssp_1);
    analogWrite(EN2, ssp_1);
}
void RIGHT()
{ // 우회전 : 좌측 모터 정회전, 우측 모터 역회전
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
    analogWrite(EN1, ssp_1);
    analogWrite(EN2, ssp_1);
}
void BACK()
{ // 전진 : 모터 두 개를 모두 정회전 시킴
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
    analogWrite(EN1, ssp_1);
    analogWrite(EN2, ssp_1);
}
void STOP()
{ // 정지 : 모터 두 개를 정지
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
    analogWrite(EN1, ssp_3);
    analogWrite(EN2, ssp_3);
}

void loop() {
  if (irReceiver.decode(&irResults)) {  // IR 신호를 수신했을 때
    if (irResults.value == 0xFFA25D) {  // 1번
      buttonPressed = true;  // 버튼이 눌렸음을 표시
      angle = -10;     // 서보 모터 각도를 180도로 설정
      servoMotor.write(angle);  // 서보 모터를 설정한 각도로 회전
      delay(1000);  // 1초 동안 유지
      
           
    }
    if (irResults.value == 0xFF629D) {  // 2번
      buttonPressed = true;  // 버튼이 눌렸음을 표시
      angle = 50;     // 서보 모터 각도를 180도로 설정
      servoMotor.write(angle);  // 서보 모터를 설정한 각도로 회전
      delay(1000);  // 1초 동안 유지
          
    }
    
    else if (irResults.value == 0xFF18E7) {
      Serial.println("forward");
      forward();
      delay(900);
      STOP(); 
    }
    else if (irResults.value == 0xFF5AA5) {
      Serial.println("right");
      RIGHT();
      delay(400);
      STOP(); 
    }
    
   else if (irResults.value == 0xFF10EF) {
     Serial.println("left");
      LEFT();
      delay(400);
      STOP(); 
    }
    else if (irResults.value == 0xFF4AB5) {
      Serial.println("back");
      BACK();
      delay(400);
      STOP(); 
    }
   else if (irResults.value == 0xFF38C7) {
     Serial.println("stop");
      STOP();
      delay(1000);
    }
    irReceiver.resume();  // IR 신호 수신 재개
  }
}