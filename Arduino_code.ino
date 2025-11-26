#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "SLTC_LEARN";
const char* password = "Success@SLTC";

// Motor pins
const int in1 = 15;
const int in2 = 16;
const int in3 = 17;
const int in4 = 18;
const int enA = 22;
const int enB = 23;

// Ultrasonic sensor pins
const int trigFrontLeft = 27;
const int echoFrontLeft = 26;
const int trigFrontRight = 33;
const int echoFrontRight = 25;
const int trigRear = 14;
const int echoRear = 12;

AsyncWebServer server(80);

String currentCommand = ""; // Store the current command
unsigned long lastCommandTime = 0; // Time of the last command
const unsigned long commandTimeout = 200; // Timeout in milliseconds
const int obstacleDistanceThreshold = 20; // Distance threshold in cm

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Motor pin setup
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  ledcSetup(0, 1000, 8);  // Channel 0, 1 kHz, 8-bit
  ledcSetup(1, 1000, 8);  // Channel 1, 1 kHz, 8-bit
  ledcAttachPin(enA, 0);
  ledcAttachPin(enB, 1);

  // Ultrasonic sensor setup
  pinMode(trigFrontLeft, OUTPUT);
  pinMode(echoFrontLeft, INPUT);
  pinMode(trigFrontRight, OUTPUT);
  pinMode(echoFrontRight, INPUT);
  pinMode(trigRear, OUTPUT);
  pinMode(echoRear, INPUT);

  // Web server
  server.on("/move", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (request->hasParam("direction")) {
      currentCommand = request->getParam("direction")->value();
      lastCommandTime = millis(); // Update last command time
      request->send(200, "text/plain", "OK");
    } else {
      request->send(400, "text/plain", "Bad Request");
    }
  });

  server.begin();
}

void loop() {
  // Check for command timeout
  if (millis() - lastCommandTime > commandTimeout) {
    stopMotors();
    return;
  }

  // Execute movement based on command
  if (currentCommand == "up") moveForward();
  else if (currentCommand == "down") moveBackward();
  else if (currentCommand == "left") turnLeft();
  else if (currentCommand == "right") turnRight();
}

// Movement functions
void moveForward() {
  long leftDist = getDistance(trigFrontLeft, echoFrontLeft);
  long rightDist = getDistance(trigFrontRight, echoFrontRight);

  if (leftDist > obstacleDistanceThreshold && rightDist > obstacleDistanceThreshold) {
    Serial.println("Moving Forward");
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    ledcWrite(0, 200);  // Adjust speed
    ledcWrite(1, 200);
  } else {
    stopMotors();
  }
}

void moveBackward() {
  long rearDist = getDistance(trigRear, echoRear);
  if (rearDist > obstacleDistanceThreshold) {
    Serial.println("Moving Backward");
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    ledcWrite(0, 200);
    ledcWrite(1, 200);
  } else {
    stopMotors();
  }
}

void turnLeft() {
  long leftDist = getDistance(trigFrontLeft, echoFrontLeft);
  if (leftDist > obstacleDistanceThreshold) {
    Serial.println("Turning Left");
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    ledcWrite(0, 200);
    ledcWrite(1, 200);
  } else {
    stopMotors();
  }
}

void turnRight() {
  long rightDist = getDistance(trigFrontRight, echoFrontRight);
  if (rightDist > obstacleDistanceThreshold) {
    Serial.println("Turning Right");
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    ledcWrite(0, 200);
    ledcWrite(1, 200);
  } else {
    stopMotors();
  }
}

void stopMotors() {
  Serial.println("Stopping Motors");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  ledcWrite(0, 0);
  ledcWrite(1, 0);
}

// Ultrasonic distance function
long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout
  long distance = duration * 0.034 / 2;
  if (distance == 0) distance = 300; // If no echo, assume max distance
  return distance;
}
