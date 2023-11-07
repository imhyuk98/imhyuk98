// 적외선 센서 핀 정의
#define leftLineSensor 10
#define centerLineSensor 11
#define rightLineSensor 1

// 모터 핀 정의
#define EN1 A4                 // 우측 모터 속도
const int rightMotorPin1 = 2; // 우측 모터 핀 1
const int rightMotorPin2 = 3; // 우측 모터 핀 2
#define EN2 A3                 // 좌측 모터 속도
const int leftMotorPin1 = 4;  // 좌측 모터 핀 1
const int leftMotorPin2 = 5;  // 좌측 모터 핀 2
#define fsp_1 255
#define fsp_2 200
#define ssp_1 100
#define ssp_2 80
#define ssp_3 0

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
    pinMode(leftLineSensor, INPUT);
    pinMode(rightLineSensor, INPUT);
    pinMode(centerLineSensor, INPUT);
    pinMode(EN1, OUTPUT);
    pinMode(EN2, OUTPUT);
    Serial.begin(9600); // 시리얼 통신 초기화
}
void loop()
{
    int la = digitalRead(leftLineSensor);
    int ca = digitalRead(centerLineSensor);
    int ra = digitalRead(rightLineSensor);
    
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
}