
#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>

// ==========================================
// ESP32 COMPLETE VOICE + BUZZER SYSTEM
// ==========================================

// FRONT ULTRASONIC
#define FRONT_TRIG 5
#define FRONT_ECHO 18

// LEFT ULTRASONIC
#define LEFT_TRIG 19
#define LEFT_ECHO 21

// RIGHT ULTRASONIC
#define RIGHT_TRIG 22
#define RIGHT_ECHO 23

// RAIN SENSOR
#define RAIN_PIN 26

// BUZZER
#define BUZZER_PIN 25

// DFPLAYER MINI
#define DF_RX 16
#define DF_TX 17

// SETTINGS
#define DETECTION_DISTANCE 20
#define RAIN_ACTIVE LOW

// BUZZER SETTINGS
#define BUZZER_INTERVAL 250

// DFPLAYER
HardwareSerial dfSerial(2);
DFRobotDFPlayerMini player;

bool playerReady = false;

// ALERT STATES
// 0 = CLEAR
// 1 = FRONT
// 2 = LEFT
// 3 = RIGHT
// 4 = RAIN

int currentAlert = -1;

// BUZZER TIMING
unsigned long previousBuzzerMillis = 0;
bool buzzerState = false;

// ==========================================
// ULTRASONIC DISTANCE
// ==========================================

float getDistance(int trigPin, int echoPin) {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 25000);

  if (duration == 0) {
    return 999;
  }

  return duration * 0.0343 / 2;
}

// ==========================================
// VOICE ALERT
// ==========================================

void playAlert(int direction) {

  if (!playerReady) return;

  switch (direction) {

    case 1:
      Serial.println("FRONT ALERT - FS");
      player.playMp3Folder(1);
      break;

    case 2:
      Serial.println("LEFT ALERT - LS");
      player.playMp3Folder(2);
      break;

    case 3:
      Serial.println("RIGHT ALERT - RS");
      player.playMp3Folder(3);
      break;

    case 4:
      Serial.println("RAIN ALERT");
      player.playMp3Folder(4);
      break;
  }
}

// ==========================================
// BUZZER CONTROL
// ==========================================

void buzzerControl(bool alert) {

  if (alert) {

    unsigned long now = millis();

    if (now - previousBuzzerMillis >= BUZZER_INTERVAL) {

      previousBuzzerMillis = now;

      buzzerState = !buzzerState;

      digitalWrite(BUZZER_PIN, buzzerState);
    }

  } else {

    digitalWrite(BUZZER_PIN, LOW);

    buzzerState = false;
    previousBuzzerMillis = millis();
  }
}

// ==========================================
// SETUP
// ==========================================

void setup() {

  Serial.begin(115200);

  // Ultrasonic pins
  pinMode(FRONT_TRIG, OUTPUT);
  pinMode(FRONT_ECHO, INPUT);

  pinMode(LEFT_TRIG, OUTPUT);
  pinMode(LEFT_ECHO, INPUT);

  pinMode(RIGHT_TRIG, OUTPUT);
  pinMode(RIGHT_ECHO, INPUT);

  // Rain sensor
  pinMode(RAIN_PIN, INPUT_PULLUP);

  // Buzzer
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // DFPlayer
  dfSerial.begin(9600, SERIAL_8N1, DF_RX, DF_TX);

  Serial.println("Initializing DFPlayer...");

  if (player.begin(dfSerial)) {

    playerReady = true;

    player.volume(25);
    player.EQ(DFPLAYER_EQ_NORMAL);

    Serial.println("DFPlayer READY!");

  } else {

    Serial.println("DFPlayer ERROR!");
  }

  Serial.println("==============================");
  Serial.println("COMPLETE WARNING SYSTEM READY");
  Serial.println("==============================");
}

// ==========================================
// MAIN LOOP
// ==========================================

void loop() {

  // READ FRONT
  float frontDistance =
    getDistance(FRONT_TRIG, FRONT_ECHO);

  delay(40);

  // READ LEFT
  float leftDistance =
    getDistance(LEFT_TRIG, LEFT_ECHO);

  delay(40);

  // READ RIGHT
  float rightDistance =
    getDistance(RIGHT_TRIG, RIGHT_ECHO);

  delay(40);

  // READ RAIN
  bool rainDetected =
    (digitalRead(RAIN_PIN) == RAIN_ACTIVE);

  // DETECTION
  bool frontDetected =
    frontDistance <= DETECTION_DISTANCE;

  bool leftDetected =
    leftDistance <= DETECTION_DISTANCE;

  bool rightDetected =
    rightDistance <= DETECTION_DISTANCE;

  // ========================================
  // SERIAL MONITOR
  // ========================================

  Serial.println("\n------ SENSOR STATUS ------");

  Serial.print("FRONT: ");
  Serial.print(frontDistance);
  Serial.println(" cm");

  Serial.print("LEFT: ");
  Serial.print(leftDistance);
  Serial.println(" cm");

  Serial.print("RIGHT: ");
  Serial.print(rightDistance);
  Serial.println(" cm");

  Serial.print("RAIN: ");
  Serial.println(rainDetected ? "DETECTED" : "CLEAR");

  // ========================================
  // ALERT PRIORITY
  // RAIN > FRONT > LEFT > RIGHT
  // ========================================

  int detectedDirection = 0;

  if (rainDetected) {

    detectedDirection = 4;

  } else if (frontDetected) {

    detectedDirection = 1;

  } else if (leftDetected) {

    detectedDirection = 2;

  } else if (rightDetected) {

    detectedDirection = 3;

  }

  // ========================================
  // VOICE ALERT
  // ========================================

  if (detectedDirection != currentAlert) {

    currentAlert = detectedDirection;

    if (currentAlert == 0) {

      Serial.println("SYSTEM CLEAR");

    } else {

      playAlert(currentAlert);
    }
  }

  // ========================================
  // BUZZER ALERT
  // ========================================

  buzzerControl(detectedDirection != 0);

  delay(20);
}
