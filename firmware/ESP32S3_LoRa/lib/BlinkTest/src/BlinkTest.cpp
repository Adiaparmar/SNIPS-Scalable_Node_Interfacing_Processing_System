#include "BlinkTest.h"
#include <Arduino.h>

// Define the built-in LED pin for XIAO ESP32S3
#ifndef LED_BUILTIN
#define LED_BUILTIN 21
#endif

// Variable to track LED state
static bool ledState = false;

// Counter for heartbeat messages
static unsigned long messageCount = 0;

void BlinkTest_setup() {
  Serial.begin(115200);
  // Allow a short delay for Serial initialization
  delay(5000); // reduce to 100ms; 10s is too long for normal use
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.println("\n\n======================================");
  Serial.println("XIAO ESP32S3 - First Upload Test");
  Serial.println("======================================");

  Serial.print("Chip Model: ");
  Serial.println(ESP.getChipModel());
  Serial.print("Chip Revision: ");
  Serial.println(ESP.getChipRevision());
  Serial.print("CPU Frequency: ");
  Serial.print(ESP.getCpuFreqMHz());
  Serial.println(" MHz");
  Serial.print("Flash Size: ");
  Serial.print(ESP.getFlashChipSize() / (1024 * 1024));
  Serial.println(" MB");
  Serial.print("Free Heap Memory: ");
  Serial.print(ESP.getFreeHeap() / 1024);
  Serial.println(" KB");

  Serial.println("======================================");
  Serial.println("Setup complete! Board is ready.");
  Serial.println("LED will blink every second...\n");
}

void BlinkTest_loop() {
  ledState = !ledState;
  digitalWrite(LED_BUILTIN, ledState ? HIGH : LOW);

  messageCount++;

  Serial.print("Heartbeat #");
  Serial.print(messageCount);
  Serial.print(" | LED: ");
  Serial.print(ledState ? "ON " : "OFF");
  Serial.print(" | Uptime: ");
  Serial.print(millis() / 1000);
  Serial.println(" seconds");

  delay(1000);
}
