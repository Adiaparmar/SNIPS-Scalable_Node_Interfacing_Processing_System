# SX1262 LoRa Module Testing Guide

## Overview
This guide explains how to test the SPI communication between your XIAO ESP32-S3 and the Wio-SX1262 LoRa module.

## Pin Configuration
The following pins are used for the B2B connector interface:

| Function | GPIO Pin | Description |
|----------|----------|-------------|
| LORA_CS | 5 | Chip Select (SPI) |
| LORA_DIO1 | 2 | Interrupt pin |
| LORA_RESET | 3 | Hardware reset |
| LORA_BUSY | 4 | Busy indicator |
| LORA_RXEN | 6 | RX Enable |
| LORA_MISO | 9 | SPI MISO |
| LORA_MOSI | 10 | SPI MOSI |
| LORA_SCK | 8 | SPI Clock |

## Test Sequence
The `LoRa_test.cpp` file performs the following tests:

1. **SPI Bus Initialization** - Sets up the SPI interface with correct pins
2. **Module Hardware Reset** - Performs a hardware reset sequence
3. **SPI Communication Verification** - Reads the firmware version register
4. **Register Read/Write Tests** - Verifies register access works correctly
5. **Clock Configuration** - Configures the crystal oscillator trim
6. **Basic Module Configuration** - Sets up TCXO, calibration, and standby mode

## How to Run Tests

### Method 1: Normal Upload (Recommended)
```bash
# Build and upload to the board
pio run -t upload -e seeed_xiao_esp32s3

# Open serial monitor to see test output
pio device monitor -e seeed_xiao_esp32s3
```

### Method 2: PlatformIO Test Framework
```bash
# Run tests (this may have serial port issues)
pio test -e seeed_xiao_esp32s3
```

## Expected Serial Output
When the test runs successfully, you should see:

```
>>> SERIAL PORT ACTIVE <<<
>>> STARTING SX1262 TEST <<<

################################################################################
#                                                                              #
#           SX1262 LoRa Module SPI Configuration Test                         #
#           Seeed Studio XIAO ESP32-S3 + Wio-SX1262                           #
#                                                                              #
################################################################################

[0000001 ms] [INFO ] Test sequence started
[0000002 ms] [INFO ] Board: XIAO ESP32-S3
[0000003 ms] [INFO ] Module: Wio-SX1262 (Semtech SX1262)

============================================================================
  GPIO INITIALIZATION
============================================================================
  CS pin configured (GPIO 5)
  RESET pin configured (GPIO 3)
  BUSY pin configured (GPIO 4)
  DIO1 pin configured (GPIO 2)
[0000150 ms] [PASS ] All GPIO pins initialized successfully

... (more test output) ...

============================================================================
  TEST SUMMARY
============================================================================

  Test 1 - SPI Communication:      PASS
  Test 2 - Register Access:        PASS
  Test 3 - Standby Mode:           PASS
  Test 4 - TCXO Configuration:     PASS
  Test 5 - Module Calibration:     PASS
  Test 6 - Key Registers:          PASS
  Test 7 - Device Errors:          PASS
  Test 8 - Clock Configuration:    PASS

  ╔════════════════════════════════════════════╗
  ║  ALL TESTS PASSED - MODULE READY FOR USE  ║
  ╚════════════════════════════════════════════╝

Total test duration: 1234 ms
```

## Troubleshooting

### No Serial Output
If you see no output in the serial monitor:

1. **Check USB Cable**: Ensure you're using a data+power cable, not just power
2. **Verify COM Port**: Open Device Manager and confirm the board is on COM6
3. **Close Other Programs**: Make sure no other serial monitor or Arduino IDE is open
4. **Reset the Board**: Press the reset button after opening the serial monitor
5. **Wait for USB CDC**: The code waits 5 seconds for USB serial to initialize

### Pin Conflict Issues (GPIO 1 & 3)
GPIO1 and GPIO3 are sometimes used for UART0/USB CDC on ESP32-S3. If you experience issues:

- The current configuration uses GPIO2, 3, 4, 5, 6, 8, 9, 10 which should work
- GPIO3 (LORA_RESET) might conflict on some boards - if so, try remapping to another pin
- To debug serial without touching hardware, compile with `-DDEBUG_SERIAL_ONLY` flag

### SPI Communication Fails
If Test 1 fails:

1. Check all wiring connections on the B2B connector
2. Verify the LoRa module has power (3.3V)
3. Check for loose connections
4. Verify SPI pins match your actual hardware configuration

## Logging Test Output to File
To save the test output to a log file:

```bash
pio device monitor -e seeed_xiao_esp32s3 > logs/test_output_$(date +%Y%m%d_%H%M%S).log
```

Or on Windows PowerShell:
```powershell
pio device monitor -e seeed_xiao_esp32s3 | Tee-Object -FilePath "logs/test_output_$(Get-Date -Format 'yyyyMMdd_HHmmss').log"
```

## Next Steps
Once all tests pass, you can:

1. Implement LoRa transmission/reception functions
2. Test actual RF communication between two modules
3. Integrate into your SNIPS node firmware
4. Add network protocol handling

## Support
If you continue to experience issues:

1. Check the PlatformIO documentation for ESP32-S3
2. Verify your Wio-SX1262 module is functioning (test with known good code)
3. Try the RadioLib examples to verify hardware setup
4. Check the ESP32-S3 datasheet for pin limitations
