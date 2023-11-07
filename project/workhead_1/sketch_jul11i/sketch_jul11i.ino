// 초음파 센서 핀 정의
const int trigPin1 = 9;  // 중앙 센서 트리거 핀
const int echoPin1 = 8;  // 중앙 센서 에코 핀
const int trigPin2 = 13;  // 좌측 센서 트리거 핀
const int echoPin2 = 12;  // 좌측 센서 에코 핀
const int trigPin3 = 10;  // 우측 센서 트리거 핀
const int echoPin3 = 11;  // 우측 센서 에코 핀

// 모터 핀 정의
const int leftMotorPin1 = 5;   // // 좌측 모터 핀 1
const int leftMotorPin2 = 6;   // 좌측 모터 핀 2
const int rightMotorPin1 = 1; // 우측 모터 핀 1
const int rightMotorPin2 = 3; // 우측 모터 핀 2

// 장애물 감지 거리 설정 (단위: 센티미터)
const int obstacleDistance = 3;

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
  digitalWrite(leftMotorPin1,HIGH);
  digitalWrite(leftMotorPin2,LOW);
  digitalWrite(rightMotorPin1,HIGH);
  digitalWrite(rightMotorPin2,LOW);
}