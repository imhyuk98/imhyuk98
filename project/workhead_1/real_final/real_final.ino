// 적외선 센서 핀 정의
#define leftLineSensor 10
#define centerLineSensor 11
#define rightLineSensor 12

// 초음파 센서 핀 정의
const int trigPin1 = 8;  // 중앙 센서 트리거 핀
const int echoPin1 = A0;  // 중앙 센서 에코 핀
const int trigPin2 = 9; // 우측 센서 트리거 핀
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
#define fsp_1 255
#define fsp_2 200
#define ssp_1 100
#define ssp_2 80
#define ssp_3 0

// 장애물 감지 거리 설정 (단위: 센티미터)
const int obstacleDistance1 = 10;
const int obstacleDistance2 = 20;

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
{ // 전진 : 모터 두 개를 모두 정회전 시킴
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
    analogWrite(EN1, ssp_1);
    analogWrite(EN2, ssp_1);
}
void RIGHT()
{ // 전진 : 모터 두 개를 모두 정회전 시킴
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
    analogWrite(EN1, ssp_1);
    analogWrite(EN2, ssp_1);
}
void setup()
{
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
    int la = digitalRead(leftLineSensor);
    int ca = digitalRead(centerLineSensor);
    int ra = digitalRead(rightLineSensor);
    //적외선 시작
    if (la == LOW && ca == HIGH && ra == LOW)
    { // 거리 값 출력
        forward();
    }
    else if (la == HIGH && ca == LOW && ra == LOW)
    {
        LEFT();
        delay(100);
    }
    else if (la == LOW && ca == LOW && ra == HIGH)
    {
        RIGHT();
        delay(100);
        
    }
    else if (la == HIGH && ca == HIGH && ra == LOW)
    {
        LEFT();
        delay(100);
    }
    else if (la == LOW && ca == HIGH && ra == HIGH)
    {
        RIGHT();
        delay(100);
    }
    else
    {
      forward();
    }
    
    // 초음파 시작
    if (distance1 <= obstacleDistance1)
    {
        // 중앙에 장애물이 있을 때
        digitalWrite(leftMotorPin1, LOW);
        digitalWrite(leftMotorPin2, HIGH);
        digitalWrite(rightMotorPin1, LOW);
        digitalWrite(rightMotorPin2, HIGH);
        analogWrite(EN1, 100);
        analogWrite(EN2, 100);
    }
    else if (distance1 <= obstacleDistance1 && distance2 <= obstacleDistance1)
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
        analogWrite(EN1, 100);
        analogWrite(EN2, 100);
    }
}