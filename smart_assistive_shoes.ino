#define TRIG_FRONT 9
#define ECHO_FRONT 10
#define TRIG_SIDE 6
#define ECHO_SIDE 7
#define BUZZER_PIN 8
#define VIB_FRONT_PIN 3
#define VIB_SIDE_PIN 4

void setup() {
  pinMode(TRIG_FRONT, OUTPUT);
  pinMode(ECHO_FRONT, INPUT);
  pinMode(TRIG_SIDE, OUTPUT);
  pinMode(ECHO_SIDE, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(VIB_FRONT_PIN, OUTPUT);
  pinMode(VIB_SIDE_PIN, OUTPUT);

  digitalWrite(VIB_FRONT_PIN, LOW);
  digitalWrite(VIB_SIDE_PIN, LOW);

  Serial.begin(9600);
}

long readDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 60000);
  if (duration == 0) return -1;

  long distance = duration * 0.034 / 2;
  return distance;
}

void loop() {
  long frontDist = readDistance(TRIG_FRONT, ECHO_FRONT);
  long sideDist  = readDistance(TRIG_SIDE, ECHO_SIDE);

  if (frontDist > 0 && frontDist <= 50) {
    digitalWrite(VIB_FRONT_PIN, HIGH);
    digitalWrite(VIB_SIDE_PIN, LOW);
    tone(BUZZER_PIN, 1500);
  }
  else if (sideDist > 6 && sideDist <= 50) {
    digitalWrite(VIB_FRONT_PIN, LOW);
    digitalWrite(VIB_SIDE_PIN, HIGH);
    tone(BUZZER_PIN, 600);
  }
  else {
    digitalWrite(VIB_FRONT_PIN, LOW);
    digitalWrite(VIB_SIDE_PIN, LOW);
    noTone(BUZZER_PIN);
  }

  delay(80);
}
