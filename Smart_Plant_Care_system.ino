#define BLYNK_TEMPLATE_ID "TMPL3evl9jfap"
#define BLYNK_TEMPLATE_NAME "Quickstart Device"
#define BLYNK_AUTH_TOKEN "KAP_t5A49aTjPh5blx5vr8s410dtDudo"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
// Define pins
#define DHTPIN 15
#define DHTTYPE DHT11
#define LDR_PIN 33
#define SOIL_MOISTURE_PIN 32
#define IN1 14
#define IN2 27
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C LCD 
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "OnePlus 10T 5G";
char pass[] = "guna0404";
bool motorManualControl = false;  // Manual control flag from Blynk
bool motorOn = false;
bool alertTempSent = false;
bool alertHumSent = false;
bool alertLightSent = false;
bool alertSoilSent = false;
// Blynk manual control on watering switch V8
BLYNK_WRITE(V8) {
  motorManualControl = param.asInt();
  Serial.print("Manual watering control: ");
  Serial.println(motorManualControl ? "ON" : "OFF");
}
// Send alerts to Blynk app notifications
void sendAlerts(float temp, float hum, int ldrValue, int soilMoistureValue) {
 if (temp > 30 && !alertTempSent) {
 Blynk.logEvent("high_temp", "High temperature detected!");
 alertTempSent = true;
 }
 else if (temp <= 30) alertTempSent = false;
 if (hum < 40 && !alertHumSent) {
 Blynk.logEvent("low_humidity", "Low humidity detected!");
 alertHumSent = true;
 }
 else if (hum >= 40) alertHumSent = false;
 if (ldrValue < 3000 && !alertLightSent) {
 Blynk.logEvent("low_light", "Low light intensity!");
 alertLightSent = true;
 }
 else if (ldrValue >= 3000) alertLightSent = false;
 if (soilMoistureValue > 2000 && !alertSoilSent) {
 Blynk.logEvent("dry_soil", "Soil moisture low, needs watering!");
 alertSoilSent = true;
 }
 else if (soilMoistureValue <= 2000) alertSoilSent = false;
}
void setup() {
 Serial.begin(115200);
 dht.begin();
 lcd.init();
 lcd.backlight();
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, LOW);
 pinMode(SOIL_MOISTURE_PIN, INPUT);
 // Connect to WiFi with debug
 Serial.print("Connecting to WiFi");
 WiFi.begin(ssid, pass);
 int retries = 0;
 while (WiFi.status() != WL_CONNECTED && retries < 20) {
 delay(500);
 Serial.print(".");
 retries++;
 }
 if (WiFi.status() == WL_CONNECTED) {
 Serial.println("\nWiFi connected!");
 Serial.print("IP address: ");
 Serial.println(WiFi.localIP());
 } else {
 Serial.println("\nFailed to connect to WiFi");
 }
 Blynk.config(auth);
 Blynk.connect();
}
void loop() {
 Blynk.run();
 float temp = dht.readTemperature();
 float hum = dht.readHumidity();
 int ldrValue = analogRead(LDR_PIN);
 int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);
 if (isnan(temp) || isnan(hum)) {
 Serial.println("Failed to read from DHT sensor!");
 delay(2000);
 return;
 }
// Send sensor data to Blynk app
 Blynk.virtualWrite(V5, temp);
 Blynk.virtualWrite(V6, hum);
 Blynk.virtualWrite(V10, ldrValue);
 Blynk.virtualWrite(V11, soilMoistureValue);
 // Decision Logic (Auto Mode)
 bool tempCondition = temp > 30;
 bool humidityCondition = hum < 40;
 bool lightCondition = ldrValue < 3000;
 bool soilDryCondition = soilMoistureValue > 2000;
 bool autoCondition = tempCondition || humidityCondition || lightCondition || soilDryCondition;
 // Final Motor Control Decision: manual override or automatic
 motorOn = motorManualControl || autoCondition;
 if (motorOn) {
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, LOW);
 } else {
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, LOW);
 }
 // Send alerts if conditions met
 sendAlerts(temp, hum, ldrValue, soilMoistureValue);
 // Serial Output for debugging
 Serial.println("------------------------------");
 Serial.print("Motor: ");
 Serial.println(motorOn ? "ON" : "OFF");
 Serial.print("Temperature: ");
 Serial.print(temp);
 Serial.println(" C");
 Serial.print("Humidity : ");
 Serial.print(hum);
 Serial.println(" %");
 Serial.print("LDR Value : ");
 Serial.println(ldrValue);
 Serial.print("Soil Moisture: ");
 Serial.println(soilMoistureValue);
 // LCD Output
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print("T:");
 lcd.print(temp);
 lcd.print("C H:");
 lcd.print(hum);
 lcd.print("%");
 lcd.setCursor(0, 1);
 lcd.print("L:");
 lcd.print(ldrValue);
 lcd.print(" S:");
 lcd.print(soilMoistureValue / 10); // scaled for display
 lcd.print(" M:");
 lcd.print(motorOn ? "ON " : "OFF");
 delay(2000);
}
