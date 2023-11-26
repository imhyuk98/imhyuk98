// 적외선 센서 핀 정의
#define leftLineSensor 8
#define centerLineSensor 9
#define rightLineSensor 10

// 모터 핀 정의
#define EN1 2                 // 우측 모터 속도
const int rightMotorPin1 = 3; // 우측 모터 핀 1
const int rightMotorPin2 = 4; // 우측 모터 핀 2
#define EN2 5                 // 좌측 모터 속도
const int leftMotorPin1 = 6;  // 좌측 모터 핀 1
const int leftMotorPin2 = 7;  // 좌측 모터 핀 2

void forward()
{ // 전진 : 모터 두 개를 모두 정회전 시킴
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, MOTOR_SPEED);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, MOTOR_SPEED);
}

void back()
{ // 후진 : 모터 두 개를 모두 역회전 시킴

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, MOTOR_SPEED);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENB, MOTOR_SPEED);
}

void left()
{ // 좌회전 : 오른쪽 모터만 정회전 시킴

    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
    analogWrite(EN1, 255);
    analogWrite(EN2, 150);
}

void right()
{ // 우회전 : 왼쪽 모터만 정회전 시킴

    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
    analogWrite(EN1, 150);
    analogWrite(EN2, 255);
}

void stop()
{ // 정지 : 2개의 모터 모두 회전 멈춤

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

void setup()
{

    pinMode(IN1, OUTPUT); // A 모터 1
    pinMode(IN2, OUTPUT); // A 모터 2
    pinMode(IN3, OUTPUT); // B 모터 1
    pinMode(IN4, OUTPUT); // B 모터 2
    pinMode(leftLineSensor, INPUT);
    pinMode(rightLineSensor, INPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
}

void loop()
{

    // 만약 양쪽 센서가 모두 선 ‘미감지’(반사신호’OK’) 경우 : 전진
    if (!digitalRead(leftLineSensor) && !digitalRead(rightLineSensor))
    {
        forward();
    }

    // 만약 왼쪽 센서만 ‘선감지(반사신호X)’ 경우 :  좌회전
    else if (!digitalRead(leftLineSensor) && digitalRead(rightLineSensor))
    {
        left();
    }

    // 만약 오른쪽 센서만 ‘선감지(반사신호X)’ 경우 :  우회전
    else if (digitalRead(leftLineSensor) && !digitalRead(rightLineSensor))
    {
        right();
    }

    // 만약 양쪽 센서 모두 ‘선감지(반사신호X)’ 경우 :  정지
    else if (digitalRead(leftLineSensor) && digitalRead(rightLineSensor))
    {
        stop();
    }
}
