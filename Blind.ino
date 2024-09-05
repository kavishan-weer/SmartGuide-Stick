#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>

HardwareSerial GPS(2); // Using Serial2 on ESP32
TinyGPSPlus gps; // Create a TinyGPSPlus object

// Wi-Fi network SSID and password
const char* ssid = "xxxxxxxxxxx";
const char* password = "xxxxxxxxxxxx";

// Bot's API token and chat ID
#define BOTtoken "7071642843:AAE43T0_m8dAxDyUeNfNmZWYhIbI6ulK-kQ"
#define CHAT_ID "7123518219"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

#define TRIG_PIN_1 2  // Trigger pin for Sensor 1
#define ECHO_PIN_1 4  // Echo pin for Sensor 1
#define TRIG_PIN_2 12 // Trigger pin for Sensor 2
#define ECHO_PIN_2 14 // Echo pin for Sensor 2
#define TRIG_PIN_3 26 // Trigger pin for Sensor 3
#define ECHO_PIN_3 27 // Echo pin for Sensor 3

#define VIBRATOR_PIN_1 5   // Vibrator pin for Sensor 1
#define VIBRATOR_PIN_2 18  // Vibrator pin for Sensor 2
#define VIBRATOR_PIN_3 19  // Vibrator pin for Sensor 3

#define BUTTON_PIN 21  // Change to your specific pin
#define BUZZER_PIN 22  // Buzzer pin

#define DISTANCE_THRESHOLD 30
#define SOUND_SPEED 0.0343

void setup() {
  Serial.begin(115200); // Start serial communication for debugging
  pinMode(BUTTON_PIN, INPUT); // Configure push button
  pinMode(BUZZER_PIN, OUTPUT); // Configure buzzer

  GPS.begin(9600, SERIAL_8N1, 16, 17); // GPS communication (RX, TX)

  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected!");

  // Ensure the SSL certificate verification is off for the client
  client.setInsecure(); // Avoid certificate validation

  // Set pin modes for ultrasonic sensors and vibrator modules
  pinMode(TRIG_PIN_1, OUTPUT);
  pinMode(ECHO_PIN_1, INPUT);
  pinMode(TRIG_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);
  pinMode(TRIG_PIN_3, OUTPUT);
  pinMode(ECHO_PIN_3, INPUT);

  pinMode(VIBRATOR_PIN_1, OUTPUT);
  pinMode(VIBRATOR_PIN_2, OUTPUT);
  pinMode(VIBRATOR_PIN_3, OUTPUT);
}

float getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  return (duration / 2.0) * SOUND_SPEED; // Distance in cm
}

void loop() {
  // Declare latitude and longitude at the top of the loop for broad scope
  float latitude = 0.0;
  float longitude = 0.0;

  // Ensure GPS data is available and decode it
  while (GPS.available() > 0) {
    gps.encode(GPS.read());
  }

  if (gps.location.isValid()) { 
    latitude = gps.location.lat(); // Get latitude
    longitude = gps.location.lng(); // Get longitude

    Serial.print("Latitude: ");
    Serial.print(latitude, 6); // Print with 6 decimal places
    Serial.print(" Longitude: ");
    Serial.println(longitude, 6); // Print with 6 decimal places
  } else {
    Serial.println("Waiting for GPS signal...");
  }

  // Get distances from ultrasonic sensors
  float distance1 = getDistance(TRIG_PIN_1, ECHO_PIN_1);
  float distance2 = getDistance(TRIG_PIN_2, ECHO_PIN_2);
  float distance3 = getDistance(TRIG_PIN_3, ECHO_PIN_3);

  digitalWrite(VIBRATOR_PIN_1, (distance1 <= DISTANCE_THRESHOLD) ? HIGH : LOW);
  digitalWrite(VIBRATOR_PIN_2, (distance2 <= DISTANCE_THRESHOLD) ? HIGH : LOW);
  digitalWrite(VIBRATOR_PIN_3, (distance3 <= DISTANCE_THRESHOLD) ? HIGH : LOW);

  Serial.print("Distance 1: ");
  Serial.print(distance1);
  Serial.print(" cm, ");

  Serial.print("Distance 2: ");
  Serial.print(distance2);
  Serial.print(" cm, ");

  Serial.print("Distance 3: ");
  Serial.print(distance3);
  Serial.println(" cm");

  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == 1) {
    String googleMapsLink = "https://www.google.com/maps/search/?api=1&query=" + 
                            String(6.88498) + "," + 
                            String(79.85839);

    // Send the Google Maps link via Telegram
    bot.sendMessage(CHAT_ID, "Here is your location: " + googleMapsLink);
    // Buzzer sound pattern for alert
    for (int i = 0; i < 3; i++) {
      digitalWrite(BUZZER_PIN, HIGH);
      delay(250);
      digitalWrite(BUZZER_PIN, LOW);
      delay(250);
    }
  }

  delay(100); // Slight delay to stabilize readings
}
