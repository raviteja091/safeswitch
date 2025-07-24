#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

const int switchPin = 1;      // Pushbutton (GPIO1)
const int ledPin    = 2;      // LED indicator / TRIAC gate drive

BLECharacteristic* pCharacteristic;
bool relayState = false;

class RelayCallback : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic* pChar) override {
    std::string value = pChar->getValue();
    if (value == "ON") {
      relayState = true;
      digitalWrite(ledPin, HIGH);
      Serial.println("🔆 BLE: Relay ON");
    } else if (value == "OFF") {
      relayState = false;
      digitalWrite(ledPin, LOW);
      Serial.println("💤 BLE: Relay OFF");
    }
  }
};

void setup() {
  Serial.begin(115200);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.println("🔌 SafeSwitch ESP32-S3 Started");

  BLEDevice::init("ESP32_SafeSwitch");
  BLEServer* pServer = BLEDevice::createServer();
  BLEService* pService = pServer->createService("12345678-1234-1234-1234-1234567890ab");

  pCharacteristic = pService->createCharacteristic(
    "abcd1234-5678-90ab-cdef-1234567890ab",
    BLECharacteristic::PROPERTY_WRITE
  );
  pCharacteristic->setCallbacks(new RelayCallback());
  pCharacteristic->addDescriptor(new BLE2902());

  pService->start();
  BLEDevice::getAdvertising()->start();

  Serial.println("📡 BLE Advertising...");
}

void loop() {
  if (digitalRead(switchPin) == LOW) {
    relayState = !relayState;
    digitalWrite(ledPin, relayState);
    Serial.println(relayState
      ? "🔘 Button: Relay ON"
      : "🔘 Button: Relay OFF");
    delay(300);
  }
}
