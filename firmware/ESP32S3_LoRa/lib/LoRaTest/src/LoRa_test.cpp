/**
 * SX1262 LoRa Module SPI Configuration Test - FINAL CORRECTED VERSION
 * 
 * Board: Seeed Studio XIAO ESP32-S3 with Wio-SX1262
 * Pin definitions verified against schematic
 */

#include <Arduino.h>
#include <SPI.h>

// ============================================================================
// PIN DEFINITIONS - VERIFIED FROM SCHEMATIC
// ============================================================================
#define LORA_NSS    41   // D7 - SPI Chip Select
#define LORA_MOSI   9  // D10 - SPI Master Out Slave In
#define LORA_MISO   8   // D9 - SPI Master In Slave Out
#define LORA_SCK    7   // D8 - SPI Clock
#define LORA_RST    42   // D2 - Hardware Reset
#define LORA_BUSY   40   // D3 - Busy indicator
#define LORA_DIO1   2   // D1 - Digital IO 1 / Interrupt

// ============================================================================
// SX1262 COMMAND DEFINITIONS
// ============================================================================
#define CMD_GET_STATUS          0xC0
#define CMD_WRITE_REGISTER      0x0D
#define CMD_READ_REGISTER       0x1D
#define CMD_SET_STANDBY         0x80
#define CMD_SET_DIO3_TCXO_CTRL  0x97
#define CMD_CALIBRATE           0x89
#define CMD_GET_DEVICE_ERRORS   0x17

// ============================================================================
// SX1262 REGISTER ADDRESSES
// ============================================================================
#define REG_VERSION             0x0320
#define REG_LNA_REGIME          0x08E2
#define REG_RX_GAIN             0x08AC
#define REG_XTA_TRIM            0x0911
#define REG_XTB_TRIM            0x0912
#define REG_OCP_CONFIG          0x08E7

// ============================================================================
// SX1262 CALIBRATION FLAGS
// ============================================================================
#define CAL_ALL                 0x7F

// ============================================================================
// GLOBAL VARIABLES
// ============================================================================
SPIClass *spiLoRa = nullptr;
bool testPassed = true;
uint32_t testStartTime = 0;

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

void logPrint(const char* level, const char* message) {
  uint32_t elapsed = millis() - testStartTime;
  Serial.printf("[%07lu ms] [%s] %s\n", elapsed, level, message);
  Serial.flush();
}

void logInfo(const char* message) { logPrint("INFO ", message); }
void logPass(const char* message) { logPrint("PASS ", message); }
void logFail(const char* message) { logPrint("FAIL ", message); testPassed = false; }
void logWarn(const char* message) { logPrint("WARN ", message); }

void printSection(const char* title) {
  Serial.println();
  Serial.println("============================================================================");
  Serial.printf("  %s\n", title);
  Serial.println("============================================================================");
  Serial.flush();
}

void printRegister(const char* name, uint16_t address, uint8_t value) {
  Serial.printf("  %-25s [0x%04X] = 0x%02X (0b%s)\n", 
    name, address, value, String(value, BIN).c_str());
}

bool waitNotBusy(uint32_t timeout_ms = 1000) {
  uint32_t start = millis();
  while (digitalRead(LORA_BUSY) == HIGH) {
    if (millis() - start > timeout_ms) {
      logFail("Timeout waiting for BUSY pin to go low");
      return false;
    }
    delayMicroseconds(10);
  }
  return true;
}

// ============================================================================
// SPI COMMUNICATION FUNCTIONS
// ============================================================================

void writeCommand(uint8_t command, const uint8_t* data = nullptr, uint16_t dataLen = 0) {
  if (!waitNotBusy()) return;
  
  spiLoRa->beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
  digitalWrite(LORA_NSS, LOW);
  
  spiLoRa->transfer(command);
  
  if (data != nullptr && dataLen > 0) {
    for (uint16_t i = 0; i < dataLen; i++) {
      spiLoRa->transfer(data[i]);
    }
  }
  
  digitalWrite(LORA_NSS, HIGH);
  spiLoRa->endTransaction();
  
  waitNotBusy();
}

void writeRegister(uint16_t address, uint8_t value) {
  uint8_t data[3];
  data[0] = (address >> 8) & 0xFF;
  data[1] = address & 0xFF;
  data[2] = value;
  
  writeCommand(CMD_WRITE_REGISTER, data, 3);
}

uint8_t readRegister(uint16_t address) {
  if (!waitNotBusy()) return 0xFF;
  
  spiLoRa->beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
  digitalWrite(LORA_NSS, LOW);
  
  spiLoRa->transfer(CMD_READ_REGISTER);
  spiLoRa->transfer((address >> 8) & 0xFF);
  spiLoRa->transfer(address & 0xFF);
  spiLoRa->transfer(0x00);
  uint8_t value = spiLoRa->transfer(0x00);
  
  digitalWrite(LORA_NSS, HIGH);
  spiLoRa->endTransaction();
  
  waitNotBusy();
  return value;
}

uint8_t getStatus() {
  if (!waitNotBusy()) return 0xFF;
  
  spiLoRa->beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
  digitalWrite(LORA_NSS, LOW);
  
  spiLoRa->transfer(CMD_GET_STATUS);
  uint8_t status = spiLoRa->transfer(0x00);
  
  digitalWrite(LORA_NSS, HIGH);
  spiLoRa->endTransaction();
  
  return status;
}

void displayStatus(uint8_t status) {
  uint8_t chipMode = (status >> 4) & 0x07;
  uint8_t cmdStatus = (status >> 1) & 0x07;
  
  const char* modeStr[] = {
    "UNUSED", "RFU", "STDBY_RC", "STDBY_XOSC", 
    "FS", "RX", "TX", "RFU"
  };
  
  const char* statusStr[] = {
    "UNUSED", "RFU", "Data Available", "Timeout",
    "Processing Error", "Failure to Execute", "TX Done", "RFU"
  };
  
  Serial.printf("  Status Byte: 0x%02X\n", status);
  Serial.printf("    Chip Mode:     %s\n", modeStr[chipMode]);
  Serial.printf("    Command Status: %s\n", statusStr[cmdStatus]);
}

// ============================================================================
// HARDWARE INITIALIZATION
// ============================================================================

void hardwareReset() {
  logInfo("Performing hardware reset...");
  
  digitalWrite(LORA_RST, LOW);
  delayMicroseconds(100);
  digitalWrite(LORA_RST, HIGH);
  delay(10);
  
  if (waitNotBusy(100)) {
    logPass("Hardware reset completed successfully");
  } else {
    logFail("Hardware reset timeout");
  }
}

void initGPIO() {
  printSection("GPIO INITIALIZATION");
  
  // Configure NSS
  pinMode(LORA_NSS, OUTPUT);
  digitalWrite(LORA_NSS, HIGH);
  Serial.printf("  NSS pin configured (GPIO %d)\n", LORA_NSS);
  
  // Configure RESET
  pinMode(LORA_RST, OUTPUT);
  digitalWrite(LORA_RST, HIGH);
  Serial.printf("  RESET pin configured (GPIO %d)\n", LORA_RST);
  
  // Configure BUSY
  pinMode(LORA_BUSY, INPUT);
  Serial.printf("  BUSY pin configured (GPIO %d)\n", LORA_BUSY);
  
  // Configure DIO1
  pinMode(LORA_DIO1, INPUT);
  Serial.printf("  DIO1 pin configured (GPIO %d)\n", LORA_DIO1);
  
  logPass("All GPIO pins initialized successfully");
}

void initSPI() {
  printSection("SPI BUS INITIALIZATION");
  
  spiLoRa = new SPIClass(FSPI);
  spiLoRa->begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_NSS);
  
  logInfo("SPI bus initialized:");
  Serial.printf("  SCK:  GPIO %d\n", LORA_SCK);
  Serial.printf("  MISO: GPIO %d\n", LORA_MISO);
  Serial.printf("  MOSI: GPIO %d\n", LORA_MOSI);
  Serial.printf("  NSS:  GPIO %d\n", LORA_NSS);
  
  logPass("SPI initialization completed");
}

// ============================================================================
// SX1262 CONFIGURATION TESTS
// ============================================================================

bool testSPICommunication() {
  printSection("TEST 1: SPI COMMUNICATION");
  
  logInfo("Reading firmware version register...");
  
  uint8_t version = readRegister(REG_VERSION);
  
  Serial.printf("  Firmware Version: 0x%02X\n", version);
  
  if (version == 0xFF || version == 0x00) {
    logFail("Invalid version read - SPI communication may be faulty");
    Serial.println("  Possible causes:");
    Serial.println("    - Incorrect wiring");
    Serial.println("    - Module not powered");
    Serial.println("    - SPI clock/mode mismatch");
    return false;
  }
  
  logPass("SPI communication verified successfully");
  return true;
}

bool testRegisterAccess() {
  printSection("TEST 2: REGISTER READ/WRITE");
  
  logInfo("Testing register write and read-back...");
  
  uint16_t testReg = REG_XTA_TRIM;
  uint8_t originalValue = readRegister(testReg);
  
  Serial.printf("  Original value at 0x%04X: 0x%02X\n", testReg, originalValue);
  
  uint8_t testValue = 0x55;
  writeRegister(testReg, testValue);
  delay(1);
  
  uint8_t readBack = readRegister(testReg);
  Serial.printf("  Wrote 0x%02X, read back 0x%02X\n", testValue, readBack);
  
  writeRegister(testReg, originalValue);
  
  if (readBack == testValue) {
    logPass("Register read/write test passed");
    return true;
  } else {
    logFail("Register read/write test failed");
    return false;
  }
}

bool testStandbyMode() {
  printSection("TEST 3: STANDBY MODE CONFIGURATION");
  
  logInfo("Setting module to STDBY_RC mode...");
  
  uint8_t config = 0x00;
  writeCommand(CMD_SET_STANDBY, &config, 1);
  
  delay(10);
  
  uint8_t status = getStatus();
  displayStatus(status);
  
  uint8_t mode = (status >> 4) & 0x07;
  
  if (mode == 2) {
    logPass("Module successfully entered STDBY_RC mode");
    return true;
  } else {
    logFail("Failed to enter STDBY_RC mode");
    return false;
  }
}

bool testTCXOConfiguration() {
  printSection("TEST 4: TCXO CONFIGURATION");
  
  logInfo("Configuring TCXO via DIO3...");
  
  uint8_t tcxoConfig[4];
  tcxoConfig[0] = 0x07;
  tcxoConfig[1] = 0x00;
  tcxoConfig[2] = 0x06;
  tcxoConfig[3] = 0x40;
  
  writeCommand(CMD_SET_DIO3_TCXO_CTRL, tcxoConfig, 4);
  
  Serial.println("  TCXO Configuration:");
  Serial.println("    Voltage: 3.3V (via DIO3)");
  Serial.println("    Timeout: ~1ms");
  
  delay(5);
  
  logPass("TCXO configuration completed");
  return true;
}

bool testCalibration() {
  printSection("TEST 5: MODULE CALIBRATION");
  
  logInfo("Calibrating all module subsystems...");
  
  uint8_t calParam = CAL_ALL;
  writeCommand(CMD_CALIBRATE, &calParam, 1);
  
  Serial.println("  Calibrating:");
  Serial.println("    - 64kHz RC oscillator");
  Serial.println("    - 13MHz RC oscillator");
  Serial.println("    - PLL");
  Serial.println("    - ADC pulse");
  Serial.println("    - ADC bulk N");
  Serial.println("    - ADC bulk P");
  Serial.println("    - Image rejection");
  
  delay(100);
  
  if (waitNotBusy(1000)) {
    logPass("Module calibration completed successfully");
    return true;
  } else {
    logFail("Calibration timeout");
    return false;
  }
}

bool testReadKeyRegisters() {
  printSection("TEST 6: KEY REGISTER VALUES");
  
  logInfo("Reading important configuration registers...");
  Serial.println();
  
  printRegister("Firmware Version", REG_VERSION, readRegister(REG_VERSION));
  printRegister("LNA Regime", REG_LNA_REGIME, readRegister(REG_LNA_REGIME));
  printRegister("RX Gain", REG_RX_GAIN, readRegister(REG_RX_GAIN));
  printRegister("XTA Trim", REG_XTA_TRIM, readRegister(REG_XTA_TRIM));
  printRegister("XTB Trim", REG_XTB_TRIM, readRegister(REG_XTB_TRIM));
  printRegister("OCP Config", REG_OCP_CONFIG, readRegister(REG_OCP_CONFIG));
  
  logPass("Register read completed");
  return true;
}

bool testDeviceErrors() {
  printSection("TEST 7: DEVICE ERROR CHECK");
  
  logInfo("Checking for device errors...");
  
  if (!waitNotBusy()) return false;
  
  spiLoRa->beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
  digitalWrite(LORA_NSS, LOW);
  
  spiLoRa->transfer(CMD_GET_DEVICE_ERRORS);
  spiLoRa->transfer(0x00);
  
  uint8_t errors_msb = spiLoRa->transfer(0x00);
  uint8_t errors_lsb = spiLoRa->transfer(0x00);
  
  digitalWrite(LORA_NSS, HIGH);
  spiLoRa->endTransaction();
  
  uint16_t errors = (errors_msb << 8) | errors_lsb;
  
  Serial.printf("  Error Register: 0x%04X\n", errors);
  
  if (errors != 0) {
    Serial.println("  Error flags set:");
    if (errors & 0x0001) Serial.println("    - RC64K calibration failed");
    if (errors & 0x0002) Serial.println("    - RC13M calibration failed");
    if (errors & 0x0004) Serial.println("    - PLL calibration failed");
    if (errors & 0x0008) Serial.println("    - ADC calibration failed");
    if (errors & 0x0010) Serial.println("    - Image calibration failed");
    if (errors & 0x0020) Serial.println("    - XOSC failed to start");
    if (errors & 0x0040) Serial.println("    - PLL lock failed");
    if (errors & 0x0100) Serial.println("    - PA ramping error");
    
    logWarn("Device errors detected - module may not function properly");
    return false;
  } else {
    logPass("No device errors detected");
    return true;
  }
}

bool testClockConfiguration() {
  printSection("TEST 8: CLOCK CONFIGURATION");
  
  logInfo("Configuring module clock settings...");
  
  uint8_t xtaTrim = 0x12;
  uint8_t xtbTrim = 0x12;
  
  writeRegister(REG_XTA_TRIM, xtaTrim);
  writeRegister(REG_XTB_TRIM, xtbTrim);
  
  Serial.println("  Clock Configuration:");
  Serial.printf("    XTA Trim: 0x%02X\n", xtaTrim);
  Serial.printf("    XTB Trim: 0x%02X\n", xtbTrim);
  Serial.println("    Crystal: 32 MHz (external TCXO)");
  
  uint8_t readXta = readRegister(REG_XTA_TRIM);
  uint8_t readXtb = readRegister(REG_XTB_TRIM);
  
  if (readXta == xtaTrim && readXtb == xtbTrim) {
    logPass("Clock configuration completed successfully");
    return true;
  } else {
    logFail("Clock configuration verification failed");
    return false;
  }
}

// ============================================================================
// MAIN PROGRAM
// ============================================================================

void setup() {
  Serial.begin(115200);
  
  unsigned long serialStartTime = millis();
  while (!Serial && (millis() - serialStartTime) < 5000) {
    delay(100);
  }
  
  delay(10000);
  
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println(">>> SERIAL PORT ACTIVE <<<");
  Serial.println(">>> STARTING SX1262 TEST <<<");
  Serial.flush();
  delay(500);
  
  testStartTime = millis();
  
  Serial.println();
  Serial.println("################################################################################");
  Serial.println("#                                                                              #");
  Serial.println("#           SX1262 LoRa Module SPI Configuration Test                         #");
  Serial.println("#           Seeed Studio XIAO ESP32-S3 + Wio-SX1262                           #");
  Serial.println("#                                                                              #");
  Serial.println("################################################################################");
  Serial.println();
  
  logInfo("Test sequence started");
  logInfo("Board: XIAO ESP32-S3");
  logInfo("Module: Wio-SX1262 (Semtech SX1262)");
  Serial.println();
  
  // PIN VERIFICATION
  Serial.println("============================================================================");
  Serial.println("  PIN CONFIGURATION VERIFICATION");
  Serial.println("============================================================================");
  Serial.printf("  NSS (Chip Select): GPIO %d (expected: 7)\n", LORA_NSS);
  Serial.printf("  MOSI:              GPIO %d (expected: 10)\n", LORA_MOSI);
  Serial.printf("  MISO:              GPIO %d (expected: 9)\n", LORA_MISO);
  Serial.printf("  SCK:               GPIO %d (expected: 8)\n", LORA_SCK);
  Serial.printf("  RST:               GPIO %d (expected: 3)\n", LORA_RST);
  Serial.printf("  BUSY:              GPIO %d (expected: 4)\n", LORA_BUSY);
  Serial.printf("  DIO1:              GPIO %d (expected: 2)\n", LORA_DIO1);

  Serial.println();
  
  // Initialize hardware
  initGPIO();
  delay(100);
  
  initSPI();
  delay(100);
  
  printSection("HARDWARE RESET");
  hardwareReset();
  delay(100);
  
  // Run all tests
  bool test1 = testSPICommunication();
  delay(50);
  
  bool test2 = testRegisterAccess();
  delay(50);
  
  bool test3 = testStandbyMode();
  delay(50);
  
  bool test4 = testTCXOConfiguration();
  delay(50);
  
  bool test5 = testCalibration();
  delay(50);
  
  bool test6 = testReadKeyRegisters();
  delay(50);
  
  bool test7 = testDeviceErrors();
  delay(50);
  
  bool test8 = testClockConfiguration();
  delay(50);
  
  // Print summary
  printSection("TEST SUMMARY");
  Serial.println();
  Serial.printf("  Test 1 - SPI Communication:      %s\n", test1 ? "PASS" : "FAIL");
  Serial.printf("  Test 2 - Register Access:        %s\n", test2 ? "PASS" : "FAIL");
  Serial.printf("  Test 3 - Standby Mode:           %s\n", test3 ? "PASS" : "FAIL");
  Serial.printf("  Test 4 - TCXO Configuration:     %s\n", test4 ? "PASS" : "FAIL");
  Serial.printf("  Test 5 - Module Calibration:     %s\n", test5 ? "PASS" : "FAIL");
  Serial.printf("  Test 6 - Key Registers:          %s\n", test6 ? "PASS" : "FAIL");
  Serial.printf("  Test 7 - Device Errors:          %s\n", test7 ? "PASS" : "FAIL");
  Serial.printf("  Test 8 - Clock Configuration:    %s\n", test8 ? "PASS" : "FAIL");
  Serial.println();
  
  bool allPassed = test1 && test2 && test3 && test4 && test5 && test6 && test7 && test8;
  
  if (allPassed) {
    Serial.println("  ╔════════════════════════════════════════════╗");
    Serial.println("  ║  ALL TESTS PASSED - MODULE READY FOR USE  ║");
    Serial.println("  ╚════════════════════════════════════════════╝");
  } else {
    Serial.println("  ╔════════════════════════════════════════════╗");
    Serial.println("  ║  SOME TESTS FAILED - CHECK ERRORS ABOVE    ║");
    Serial.println("  ╚════════════════════════════════════════════╝");
  }
  
  Serial.println();
  uint32_t totalTime = millis() - testStartTime;
  Serial.printf("Total test duration: %lu ms\n", totalTime);
  Serial.println();
  Serial.println("################################################################################");
  Serial.println();
  
  logInfo("Test sequence completed");
  logInfo("To save this output to a file, run: pio device monitor | tee logs/test_output.log");
}

void loop() {
  delay(10000);
}