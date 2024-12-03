#include <WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Wi-Fi settings
const char* ssid = "<YOUR_NETWORK>";
const char* password = "<PASSPHRASE>";

// MQTT settings
const char* mqtt_server = "<IP_ADDRESS>"; // Mosquitto server address // If running locally, use your IPv4 where Mosquitto is running
const int mqtt_port = 1883;               // Default MQTT port
const char* mqtt_topic = "test";

WiFiClient espClient;
PubSubClient client(espClient);

// Temperature sensor pin
#define TEMP_SENSOR_PIN 15

// Setup a OneWire instance to communicate with any OneWire devices
OneWire oneWire(TEMP_SENSOR_PIN);

// Pass the OneWire reference to the Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

void connectToWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected!");
  Serial.println("IP Address: " + WiFi.localIP().toString());
}

void reconnectMQTT() {
  while (!client.connected()) {
    Serial.println("Connecting to the MQTT broker...");
    if (client.connect("mosquitto")) { // MQTT client ID
      Serial.println("Connected to the MQTT broker!");
    } else {
      Serial.print("MQTT connection failed, rc=");
      Serial.print(client.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  connectToWiFi();

  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();

  // Read temperature from the sensor
  sensors.requestTemperatures(); 
  float c_temperature = sensors.getTempCByIndex(0);
  float f_temperature = sensors.getTempFByIndex(0);

  // Create the JSON message
  String payload = "{\"temp_sensor_pin\":"+String(TEMP_SENSOR_PIN)+",";
  payload += "\"c_temperature\":"+String(c_temperature)+",";
  payload += "\"f_temperature\":"+String(f_temperature)+"}";

  // Publish to the MQTT topic
  if (client.publish(mqtt_topic, payload.c_str())) {
    Serial.println("Message published to topic: " + String(mqtt_topic));
  } else {
    Serial.println("Failed to publish the message.");
  }
  
  delay(5000); // 5-second interval between readings
}
