
//양쪽 모터와 연결된 PWM 핀 번호 배열에 저장
#define EN1 3                // 우측 모터 속도
const int rightMotorPin1 = 2; // 우측 모터 핀 1
const int rightMotorPin2 = 4; // 우측 모터 핀 2
#define EN2 5               // 좌측 모터 속도
const int leftMotorPin1 = 6;  // 좌측 모터 핀 1
const int leftMotorPin2 = 7;  // 좌측 모터 핀 2

void setup() {

}

void loop() {
  //블루투스로 데이터가 전달된다면
  
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
    analogWrite(EN1, 255);
    analogWrite(EN2, 255);     
}
