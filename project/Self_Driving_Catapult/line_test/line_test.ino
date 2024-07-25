// 적외선 센서 핀 정의
#define leftLineSensor 11
#define centerLineSensor 12
#define rightLineSensor 13

// 모터 핀 정의
#define EN1 3                 // 우측 모터 속도
const int rightMotorPin1 = 2; // 우측 모터 핀 1
const int rightMotorPin2 = 4; // 우측 모터 핀 2
#define EN2 5                 // 좌측 모터 속도
const int leftMotorPin1 = 6;  // 좌측 모터 핀 1
const int leftMotorPin2 = 7;  // 좌측 모터 핀 2
#define fsp_1 255
#define fsp_2 200
#define ssp_1 100
#define ssp_2 0
#define ssp_3 80


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
void left()
{ // 좌회전 : 오른쪽 모터만 정회전 시킴

    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
    analogWrite(EN1, ssp_1);
    analogWrite(EN2, ssp_3);
}

void leftTurn()
{ // 좌회전 : 오른쪽 모터만 정회전 시킴

    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
    analogWrite(EN1, ssp_1);
    analogWrite(EN2, ssp_1);
}

void right()
{ // 우회전 : 왼쪽 모터만 정회전 시킴

    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
    analogWrite(EN1, ssp_3);
    analogWrite(EN2, ssp_1);
}

void rightTurn()
{ // 우회전 : 왼쪽 모터만 정회전 시킴

    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
    analogWrite(EN1, ssp_1);
    analogWrite(EN2, ssp_1);
}

void stop()
{ // 정지 : 2개의 모터 모두 회전 멈춤

    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
    analogWrite(EN1, 0);
    analogWrite(EN2, 0);
}

void back()
{ // 정지 : 2개의 모터 모두 회전 멈춤

    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
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


    // 양쪽 미감지 중앙 감지 : 전진 XOX
    if (la == LOW && ca == HIGH && ra == LOW)
    { // 거리 값 출력
        forward();
    }
    
    // 좌측 감지 :  좌회전 OXX
    else if (la == HIGH && ca == LOW && ra == LOW)
    {
        LEFT();
        delay(100);
    }
/*
    // 좌측, 중앙 감지 :  좌회전 OOX
    else if (la == HIGH && ca == HIGH && ra == LOW)
    {
        leftTurn();
    }
*/
    // 우측 감지 :  우회전 XXO
    else if (la == LOW && ca == LOW && ra == HIGH)
    {
        RIGHT();
        delay(100);
    }
/*
    // 우측 감지 :  우회전 XOO
    else if (la == LOW && ca == HIGH && ra == HIGH)
    {
        rightTurn();
    }

    // 모든 센서 감지 :  정지 OOO
    else if (la == LOW && ca == LOW && ra == LOW)
    {
        rightTurn();
    }
*/
    /*else{
      forward();
    }
    // 거리 값 출력
    /*Serial.print("Distance 1: ");
    Serial.print(distance1);
    Serial.print(" cm\t");
    Serial.print("Distance 2: ");
    Serial.print(distance2);
    Serial.print(" cm\t");
    Serial.print("Distance 3: ");
    Serial.print(distance3);
    Serial.println(" cm");*/
}