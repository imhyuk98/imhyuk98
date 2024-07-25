#include <IRremote.h>
#include <Servo.h>

// IR리모컨 / 모터 핀 정의
#define irReceiverPin A4  // IR 수신기 핀
#define servoPin A3       // 서보 모터 핀

// 적외선 센서 핀 정의
#define leftLineSensor 11   // 좌측 라인 센서
#define centerLineSensor 12 // 중앙 라인 센서
#define rightLineSensor 13  // 우측 라인 센서

// 초음파 센서 핀 정의
const int trigPin1 = 8;  // 중앙 센서 트리거 핀
const int echoPin1 = A0; // 중앙 센서 에코 핀
const int trigPin2 = 9;  // 우측 센서 트리거 핀
const int echoPin2 = A1; // 우측 센서 에코 핀
const int trigPin3 = 10; // 좌측 센서 트리거 핀
const int echoPin3 = A2; // 좌측 센서 에코 핀

// 모터 핀 정의
#define EN1 3                 // 우측 모터 속도
#define EN2 5                 // 좌측 모터 속도
const int rightMotorPin1 = 2; // 우측 모터 핀 1
const int rightMotorPin2 = 4; // 우측 모터 핀 2
const int leftMotorPin1 = 6;  // 좌측 모터 핀 1
const int leftMotorPin2 = 7;  // 좌측 모터 핀 2

// 모터 속도 정의
#define fsp_1 255
#define fsp_2 200
#define ssp_1 100
#define ssp_2 80
#define ssp_3 0

// 장애물 감지 거리 설정 (단위: 센티미터)
const int obstacleDistance1 = 10;
const int obstacleDistance2 = 20;

IRrecv irReceiver(irReceiverPin);  // IR 수신 객체
decode_results irResults;           // 수신된 IR 신호를 저장하는 객체
Servo servoMotor;                   // 서보 모터 객체

bool buttonPressed = false;  // 버튼이 눌렸는지 여부를 저장하는 변수
int angle = 45;        // 서보 모터의 시작 각도

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

void STOP()
{ // 정지 : 모터 두 개를 정지
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
    analogWrite(EN1, ssp_3);
    analogWrite(EN2, ssp_3);
}

void setup()
{
    irReceiver.enableIRIn();  // IR 수신기 초기화
    servoMotor.attach(servoPin);  // 서보 모터 핀 초기화
    servoMotor.write(angle); // 시작 각도로 서보 모터 설정
    pinMode(leftMotorPin1, OUTPUT);
    pinMode(leftMotorPin2, OUTPUT);
    pinMode(rightMotorPin1, OUTPUT);
    pinMode(rightMotorPin2, OUTPUT);
    pinMode(EN1, OUTPUT);
    pinMode(EN2, OUTPUT);
    pinMode(leftLineSensor, INPUT);
    pinMode(rightLineSensor, INPUT);
    pinMode(centerLineSensor, INPUT);
    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
    pinMode(trigPin3, OUTPUT);
    pinMode(echoPin3, INPUT);
    Serial.begin(9600); // 시리얼 통신 초기화
}
void loop()
{
    // 중앙 센서로부터 거리 측정
    long duration1, distance1;
    digitalWrite(trigPin1, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin1, LOW);
    duration1 = pulseIn(echoPin1, HIGH);
    distance1 = (duration1 / 2) / 29.1;

    // 우측 센서로부터 거리 측정
    long duration2, distance2;
    digitalWrite(trigPin2, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);
    duration2 = pulseIn(echoPin2, HIGH);
    distance2 = (duration2 / 2) / 29.1;

    // 좌측 센서로부터 거리 측정
    long duration3, distance3;
    digitalWrite(trigPin3, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin3, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin3, LOW);
    duration3 = pulseIn(echoPin3, HIGH);
    distance3 = (duration3 / 2) / 29.1;

    // 거리 값 출력
    Serial.print("Distance 1: ");
    Serial.print(distance1);
    Serial.print(" cm\t");
    Serial.print("Distance 2: ");
    Serial.print(distance2);
    Serial.print(" cm\t");
    Serial.print("Distance 3: ");
    Serial.print(distance3);
    Serial.println(" cm");
    // 감지값을 HIGH/LOW로 입력
    int la = digitalRead(leftLineSensor);
    int ca = digitalRead(centerLineSensor);
    int ra = digitalRead(rightLineSensor);

    // 적외선 시작
    // 전진 : 중앙 적외선 센서만 감지
    if (la == LOW && ca == HIGH && ra == LOW)
    {
        forward();
    }
    // 좌회전(1) : 좌측 적외선 센서만 감지
    else if (la == HIGH && ca == LOW && ra == LOW)
    {
        LEFT();
        delay(100);
    }
    // 좌회전(2) : 좌측, 중앙 적외선 센서 감지
    else if (la == LOW && ca == LOW && ra == HIGH)
    {
        RIGHT();
        delay(100);
    }
    // 우회전(1) : 우측 적외선 센서만 감지
    else if (la == HIGH && ca == HIGH && ra == LOW)
    {
        LEFT();
        delay(100);
    }
    // 우회전(2) : 우측, 중앙 적외선 센서 감지
    else if (la == LOW && ca == HIGH && ra == HIGH)
    {
        RIGHT();
        delay(100);
    }

    // 초음파 시작
    else if (la == LOW && ca == LOW && ra == LOW)
    {
        if (distance1 <= obstacleDistance1 && distance2 <= obstacleDistance1)
        {
            // 우측에 장애물이 가까이 있을 때
            digitalWrite(leftMotorPin1, LOW);
            digitalWrite(leftMotorPin2, HIGH);
            digitalWrite(rightMotorPin1, LOW);
            digitalWrite(rightMotorPin2, HIGH);
            analogWrite(EN1, 150);
            analogWrite(EN2, 0);
        }
        else if (distance1 <= obstacleDistance2 && distance2 <= obstacleDistance2)
        {
            // 우측에 장애물이 멀리 있을 때
            digitalWrite(leftMotorPin1, LOW);
            digitalWrite(leftMotorPin2, HIGH);
            digitalWrite(rightMotorPin1, LOW);
            digitalWrite(rightMotorPin2, HIGH);
            analogWrite(EN1, 150);
            analogWrite(EN2, 100);
        }
        else if (distance1 <= obstacleDistance1 && distance3 <= obstacleDistance1)
        {
            // 좌측에 장애물이 가까이 있을 때
            digitalWrite(leftMotorPin1, LOW);
            digitalWrite(leftMotorPin2, HIGH);
            digitalWrite(rightMotorPin1, LOW);
            digitalWrite(rightMotorPin2, HIGH);
            analogWrite(EN1, 0);
            analogWrite(EN2, 150);
        }
        else if (distance1 <= obstacleDistance2 && distance3 <= obstacleDistance2)
        {
            // 우측에 장애물이 멀리 있을 때
            digitalWrite(leftMotorPin1, LOW);
            digitalWrite(leftMotorPin2, HIGH);
            digitalWrite(rightMotorPin1, LOW);
            digitalWrite(rightMotorPin2, HIGH);
            analogWrite(EN1, 100);
            analogWrite(EN2, 150);
        }
        else
        {
            // 장애물이 없을 때
            digitalWrite(leftMotorPin1, LOW);
            digitalWrite(leftMotorPin2, HIGH);
            digitalWrite(rightMotorPin1, LOW);
            digitalWrite(rightMotorPin2, HIGH);
            analogWrite(EN1, 200);
            analogWrite(EN2, 200);
        }
    }
    // 정지 : 모든 적외선 센서가 감지했을 때
    else if (la == HIGH && ca == HIGH && ra == HIGH)
    {
        STOP();
        delay(100);
    }

    else
    {
        forward();
    }

    /*if (irReceiver.decode(&irResults)) {  // IR 신호를 수신했을 때
    if (irResults.value == 0xFFB04F) {  // 수신된 IR 신호가 0xFFB04F일 때 동작
      buttonPressed = true;  // 버튼이 눌렸음을 표시
      angle = 50;     // 서보 모터 각도를 180도로 설정
      servoMotor.write(angle);  // 서보 모터를 설정한 각도로 회전
      delay(100);  // 1초 동안 유지
      angle = 115;  // 서보 모터 각도를 45도로 설정
      servoMotor.write(angle);  // 서보 모터를 설정한 각도로 회전
    }
    irReceiver.resume();  // IR 신호 수신 재개
  }*/
}
