#define TRIG1 9   // 중앙 센서 TRIG 핀 설정 (초음파 보내는 핀)
#define ECHO1 8   // 중앙 센서 ECHO 핀 설정 (초음파 받는 핀)
#define TRIG2 11   // 좌측 센서 TRIG 핀 설정
#define ECHO2 10  // 좌측 센서 ECHO 핀 설정
#define TRIG3 13   // 우측 센서 TRIG 핀 설정
#define ECHO3 12   // 우측 센서 ECHO 핀 설정


void setup() {
  Serial.begin(9600); 

  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);
  pinMode(TRIG3, OUTPUT);
  pinMode(ECHO3, INPUT);
}

void loop() {
  long duration1, distance1;  // 중앙 센서 측정 변수
  long duration2, distance2;  // 좌측 센서 측정 변수
  long duration3, distance3;  // 우측 센서 측정 변수

  // 중앙 센서로부터 거리 측정
  digitalWrite(TRIG1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG1, LOW);
  duration1 = pulseIn(ECHO1, HIGH);
  distance1 = duration1 * 17 / 1000;

  // 좌측 센서로부터 거리 측정
  digitalWrite(TRIG2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG2, LOW);
  duration2 = pulseIn(ECHO2, HIGH);
  distance2 = duration2 * 17 / 1000;

  // 우측 센서로부터 거리 측정
  digitalWrite(TRIG3, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG3, LOW);
  duration3 = pulseIn(ECHO3, HIGH);
  distance3 = duration3 * 17 / 1000;

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

  delay(1000);
}
