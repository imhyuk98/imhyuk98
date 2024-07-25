// 초음파 센서 핀 정의
const int trigPin1 = 9;  // 중앙 센서 트리거 핀
const int echoPin1 = 8;  // 중앙 센서 에코 핀
const int trigPin2 = 13;  // 우측 센서 트리거 핀
const int echoPin2 = 12;  // 우측 센서 에코 핀
const int trigPin3 = 10;  // 좌측 센서 트리거 핀
const int echoPin3 = 11;  // 좌측 센서 에코 핀

// 모터 핀 정의
const int leftMotorPin1 = 5;   // // 좌측 모터 핀 1
const int leftMotorPin2 = 6;   // 좌측 모터 핀 2
const int rightMotorPin1 = 1; // 우측 모터 핀 1
const int rightMotorPin2 = 3; // 우측 모터 핀 2

// 장애물 감지 거리 설정 (단위: 센티미터)
const int obstacleDistance = 20;

void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  Serial.begin(9600);  // 시리얼 통신 초기화
}

void loop() {
  // 중앙 센서로부터 거리 측정
  long duration1, distance1;
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1 / 2) / 29.1;

  // 좌측 센서로부터 거리 측정
  long duration2, distance2;
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2 / 2) / 29.1;

  // 우측 센서로부터 거리 측정
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

  // 장애물 감지 시 모터 제어
    if (distance1 <= obstacleDistance) {
    // 중앙에 장애물이 있을 때
    // 원하는 동작 수행 (좌회전, 우회전 등)
    // 예: 좌회전
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  } else if (distance2 <= obstacleDistance) {
    // 좌측에 장애물이 있을 때
    // 원하는 동작 수행 (우회전 등)
    // 예: 좌회전 (좌측 모터 천천히 회전)
    analogWrite(leftMotorPin1, 100);
    digitalWrite(leftMotorPin2, LOW);
    analogWrite(rightMotorPin1, 255);
    digitalWrite(rightMotorPin2, LOW);
  } else if (distance3 <= obstacleDistance) {
    // 우측에 장애물이 있을 때
    // 원하는 동작 수행 (좌회전 등)
    // 예: 우회전 (우측 모터 빠르게 회전)
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(leftMotorPin1, HIGH);
    analogWrite(rightMotorPin2, 100);
    digitalWrite(rightMotorPin1, LOW);
  } else {
    // 장애물이 없을 때
    // 원하는 동작 수행 (직진 등)
    // 예: 직진
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  }

  delay(500);  // 감지 주기 설정
}