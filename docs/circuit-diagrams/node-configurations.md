# Node Configurations - Detailed Specifications

This document provides comprehensive hardware specifications for each SNIPS node type, including detailed component selection, power analysis, and deployment considerations.

## 📋 Table of Contents

- [Design Overview](#-design-overview)
- [Anchor Nodes (A1, A2, A3)](#-anchor-nodes-a1-a2-a3)
- [Relay Node (R1)](#-relay-node-r1)
- [Mobile Nodes (M1, M2)](#-mobile-nodes-m1-m2)
- [Comparative Analysis](#-comparative-analysis)
- [Power Management Details](#-power-management-details)
- [Assembly Instructions](#-assembly-instructions)

---

## 🎯 Design Overview

### Hardware Design Philosophy

The SNIPS hardware architecture follows a **modular, role-specialized approach** where each node type is optimized for its specific function while maintaining protocol compatibility.

```yaml
Design Principles:
  - Role-based optimization for performance and power
  - Common power architecture for maintainability
  - Professional-grade components within budget constraints
  - Scalable design supporting future enhancements
  - RF best practices for reliable LoRa communication
```

### Common Hardware Elements

All nodes share these core subsystems:

- **Power Management**: TPS61088 boost + TLV75533 LDO architecture
- **LoRa Communication**: Seeed Wio-SX1262 module (SX1262 chipset)
- **Battery Protection**: DW01A + TP4056 safety and charging system
- **Environmental Protection**: IP65-rated enclosures with proper sealing

---

## 🔗 Anchor Nodes (A1, A2, A3)

### Hardware Platform Overview

**Primary Platform**: **Seeed XIAO ESP32S3** + **Wio-SX1262 LoRa Module**

The anchor nodes form the backbone infrastructure of the SNIPS network, providing positioning reference points and always-on connectivity.

### Microcontroller Specifications

#### **Seeed XIAO ESP32S3**

```yaml
Processor:
  CPU: Dual-core Xtensa LX7 @ 240 MHz
  Architecture: 32-bit RISC with DSP extensions
  Performance: 740 DMIPS dual-core

Memory:
  Flash: 8MB built-in (QSPI)
  PSRAM: 2MB built-in (OPI)
  SRAM: 512KB internal
  Cache: 16KB instruction + 16KB data per core

Connectivity:
  WiFi: 802.11 b/g/n (2.4GHz)
  Bluetooth: BLE 5.0 with mesh support
  Interfaces: SPI, I2C, UART, ADC, DAC

Physical:
  Dimensions: 21 × 17.5 × 3.5 mm
  Weight: 4.5g
  Connector: USB-C for programming and power
  Operating Voltage: 3.3V (5V tolerant inputs)
```

**Selection Rationale**:

- ✅ **High Performance**: Dual-core design handles complex routing algorithms
- ✅ **Connectivity Options**: WiFi provides backup communication path
- ✅ **Memory Capacity**: Sufficient for comprehensive routing tables
- ✅ **Development Ecosystem**: Arduino IDE and ESP-IDF support
- ✅ **Size**: Ultra-compact form factor for space-constrained designs

### LoRa Module Integration

#### **Wio-SX1262 Specifications**

```yaml
RF Performance:
  Chipset: Semtech SX1262 (latest generation)
  Frequency Bands:
    - 868 MHz (Europe)
    - 915 MHz (Americas, Asia-Pacific)
  Sensitivity: -148 dBm @ SF12/BW125
  Output Power: +22 dBm maximum (adjustable)

Modulation:
  LoRa: SF5-SF12, BW 7.8-500 kHz
  FSK: 0.6-300 kbps

Interface:
  Communication: SPI (up to 16 MHz)
  Control Pins: NSS, RESET, DIO1, BUSY
  Logic Levels: 3.3V (5V tolerant)

Physical:
  Dimensions: 23 × 28 mm
  Antenna: U.FL connector
  Current Consumption:
    - TX @ +22dBm: 120 mA
    - TX @ +14dBm: 85 mA
    - RX: 4.6 mA
    - Sleep: 1.5 μA
```

### Power System Design

#### **Power Configuration**

**Primary Power**: Mains-powered (5V USB-C or external adapter)
**Backup Power**: Optional 2500mAh 18650 Li-ion battery

```yaml
Power Rails:
  Input: 5V ± 5% (USB-C or external)
  Boost Output: 5V @ 2A (battery mode)
  LDO Output: 3.3V @ 500mA (clean power for RF)

Power Consumption:
  Active Mode (TX): ~150mA @ 5V
  Active Mode (RX): ~80mA @ 5V
  Idle Mode: ~30mA @ 5V
  Sleep Mode: ~5mA @ 5V (ESP32 light sleep)

Duty Cycle: 100% (always active)
Battery Backup Duration: ~16-20 hours (emergency operation)
```

#### **Power Management Features**

- **Automatic Switchover**: Seamless transition from mains to battery
- **Charging Circuit**: TP4056-based intelligent charging when on mains power
- **Over-voltage Protection**: Input protection for external power supplies
- **Thermal Management**: Heat sinks and thermal vias for continuous operation

### Deployment Specifications

#### **Physical Installation**

```yaml
Mounting:
  Type: Fixed installation (permanent or semi-permanent)
  Hardware: 4× M3 mounting holes, DIN rail compatibility
  Height: 2-5 meters above ground (optimal RF coverage)
  Orientation: Vertical antenna polarization preferred

Enclosure:
  Material: ABS plastic, UV-stabilized
  Rating: IP65 (dust-tight, water jet protected)
  Dimensions: 120 × 80 × 60 mm (approximate)
  Windows: Clear polycarbonate for LED indicators

Cable Management:
  Power: IP65-rated cable gland for mains connection
  Antenna: SMA connector with weatherproof seal
  Expansion: Optional sealed connectors for sensors
```

#### **Environmental Requirements**

| Parameter                 | Specification  | Notes                     |
| ------------------------- | -------------- | ------------------------- |
| **Operating Temperature** | -20°C to +60°C | Extended industrial range |
| **Storage Temperature**   | -40°C to +85°C | Non-operating limits      |
| **Humidity**              | 5% to 95% RH   | Non-condensing            |
| **Ingress Protection**    | IP65           | Outdoor deployment ready  |
| **Shock/Vibration**       | IEC 60068-2-27 | Structural installation   |

### Network Functions

#### **Positioning Infrastructure Role**

- **Reference Coordinates**: Precisely surveyed GPS coordinates (±1m accuracy)
- **TDOA Measurements**: Sub-microsecond timestamp recording for positioning
- **Synchronization**: Crystal oscillator-based timing for TDMA coordination
- **Always Available**: 100% uptime for positioning reliability

#### **Communication Backbone Role**

- **Mesh Node**: Full routing table maintenance (up to 255 entries)
- **Range Extension**: Multi-hop relay for network coverage expansion
- **Redundancy**: Multiple anchor paths for communication reliability
- **Protocol Enforcement**: Network management and quality control

---

## 🛡️ Relay Node (R1)

### Hardware Platform Overview

**Primary Platform**: **Arduino Uno R4 WiFi** + **Custom Shield**

The relay node serves as the network coordinator and traffic manager, requiring moderate processing power with high availability.

### Microcontroller Specifications

#### **Arduino Uno R4 WiFi**

```yaml
Main Processor:
  CPU: Renesas RA4M1 (ARM Cortex-M4 @ 48 MHz)
  Architecture: 32-bit ARM with FPU
  Performance: 150 DMIPS

Co-processor:
  WiFi/BLE: ESP32-S3 module
  Communication: UART interface to main MCU

Memory:
  Flash: 256 KB program memory
  SRAM: 32 KB data memory
  EEPROM: Emulated in flash

Connectivity:
  WiFi: 802.11 b/g/n via ESP32-S3
  Bluetooth: BLE via ESP32-S3
  USB: USB-C native support
  Interfaces: SPI, I2C, UART, ADC

Physical:
  Dimensions: 68.6 × 53.4 mm (standard Arduino form factor)
  Weight: 25g
  GPIO: 20 digital pins, 6 analog inputs
  Operating Voltage: 5V (3.3V logic compatible)
```

**Selection Rationale**:

- ✅ **Moderate Performance**: Sufficient for routing and traffic management
- ✅ **WiFi Capability**: Backup communication and configuration access
- ✅ **Arduino Ecosystem**: Extensive library support and community
- ✅ **Standard Form Factor**: Compatible with existing shield designs
- ✅ **Cost Effective**: Good performance/price ratio within budget

### Custom Shield Design

#### **Shield Architecture**

The custom shield provides LoRa connectivity, power management, and expansion capabilities:

```yaml
Shield Components:
  LoRa Module: Wio-SX1262 via SPI interface
  Power Management:
    - TPS61088RHLR boost converter
    - TLV75533PDBVR LDO regulator
    - DW01A battery protection IC
    - TP4056 charging controller

Interfaces:
  SPI: LoRa module communication
  I2C: Sensor expansion bus
  UART: Debug/programming interface
  GPIO: Status LEDs, control signals

Expansion:
  Grove Connectors: 2× I2C, 2× digital I/O
  Sensor Interface: Temperature, humidity, IMU options
  External Antenna: SMA connector with RP-SMA option
```

#### **Shield PCB Specifications**

```yaml
PCB Design:
  Layers: 4-layer controlled impedance
  Dimensions: 68.6 × 53.4 mm (Arduino Uno shield)
  Thickness: 1.6 mm FR-4
  Surface Finish: ENIG for reliability

Signal Integrity:
  RF Traces: 50Ω controlled impedance
  Ground Planes: Solid pour on layers 2&3
  Via Stitching: RF isolation and thermal management
  Component Isolation: Keep-out zones for sensitive circuits
```

### Power System Design

#### **High-Capacity Battery Configuration**

**Primary Power**: 5000mAh 18650 Li-ion battery (parallel configuration)
**Charging**: USB-C PD with optional solar panel support

```yaml
Battery Configuration:
  Cells: 2× 18650 Li-ion in parallel
  Capacity: 5000mAh total @ 3.7V nominal
  Protection: Dual DW01A ICs for redundant safety
  Balancing: Passive balancing for parallel cells

Power Rails:
  Battery: 3.0V - 4.2V (18650 operating range)
  Boost Output: 5V @ 3A continuous
  LDO Output: 3.3V @ 500mA (LoRa and sensors)

Power Consumption:
  Active Mode (TX): ~180mA avg
  Active Mode (RX): ~120mA avg
  Routing Mode: ~100mA avg
  Sleep Mode: ~15mA avg (wake timers active)

Duty Cycle: 95% (near-continuous operation)
Battery Life: 2-4 weeks (typical usage)
```

#### **Charging System Features**

- **USB-C PD**: Up to 15W charging (compatible with phone chargers)
- **Solar Panel Support**: 6V-12V input with MPPT optimization
- **Charge Balancing**: Automatic cell balancing during charging
- **Thermal Protection**: NTC temperature monitoring during charge

### Network Functions

#### **Multi-Point Relay (MPR) Role**

- **TDMA Master**: Controls time slot allocation and synchronization
- **Traffic Coordination**: Manages packet forwarding and routing decisions
- **QoS Enforcement**: Prioritizes positioning traffic over user data
- **Network Monitoring**: Tracks link quality and topology changes

#### **Routing Hub Capabilities**

```yaml
Routing Features:
  Table Size: 255 entries maximum
  Route Metrics: Hop count, link quality, latency, energy
  Discovery: Proactive (anchors) + Reactive (mobiles)
  Maintenance: Hello messages every 30 seconds
  Failover: Sub-5-second route recovery

Buffer Management:
  TX Buffer: 8 packets @ 256 bytes each
  RX Buffer: 16 packets for store-and-forward
  Priority Queues: 4 levels (emergency, positioning, data, management)
```

---

## 📱 Mobile Nodes (M1, M2)

### Hardware Platform Overview

**Primary Platform**: **Arduino Nano** + **Custom Shield**

Mobile nodes are end-user devices optimized for portability and maximum battery life while maintaining full mesh networking capabilities.

### Microcontroller Specifications

#### **Arduino Nano (ATmega328P)**

```yaml
Processor:
  CPU: Atmel ATmega328P (8-bit AVR @ 16 MHz)
  Architecture: Harvard architecture with RISC instruction set
  Performance: 20 MIPS @ 20 MHz

Memory:
  Flash: 32 KB program memory (2KB bootloader)
  SRAM: 2 KB data memory
  EEPROM: 1 KB non-volatile storage

Interfaces:
  Digital I/O: 22 pins (6 PWM capable)
  Analog Inputs: 8 × 10-bit ADC
  Communication: SPI, I2C, UART

Physical:
  Dimensions: 18 × 45 mm (mini form factor)
  Weight: 7g
  Connector: Mini-USB for programming
  Operating Voltage: 5V (3.3V compatible I/O)
```

**Selection Rationale**:

- ✅ **Ultra-Low Power**: Aggressive power management with deep sleep modes
- ✅ **Compact Size**: Minimal form factor for portable applications
- ✅ **Cost Effective**: Lowest-cost option meeting performance requirements
- ✅ **Mature Platform**: Extensive optimization and power management libraries
- ✅ **Sufficient Performance**: Adequate for end-node functionality

### Custom Shield Design

#### **Optimized Mobile Shield**

```yaml
Shield Features:
  LoRa Module: Wio-SX1262 with optimized power switching
  Power Management:
    - TPS61088 boost (high efficiency)
    - TLV75533 LDO (ultra-low noise)
    - Advanced sleep control circuitry
    - Wake-on-radio capability

Mobile Optimizations:
  Power Switches: Load switching for maximum sleep efficiency
  Wake Sources: LoRa interrupt, timer, button, sensor
  Status Indicators: Low-power LEDs with sleep disable
  Sensor Interface: Grove connectors for external sensors

Physical:
  Dimensions: 50 × 35 mm (compact mobile form)
  Thickness: 15 mm including battery
  Mounting: 2× M3 holes for case attachment
  Connectors: Micro-USB charging, external antenna
```

### Power System Design

#### **Battery-Optimized Architecture**

**Primary Power**: 2500mAh 18650 Li-ion battery
**Charging**: Micro-USB with intelligent charge management

```yaml
Battery Specifications:
  Cell: Single 18650 Li-ion
  Capacity: 2500mAh @ 3.7V nominal
  Protection: DW01A IC with dual MOSFET protection
  Charging: TP4056 with CC/CV profile

Power Rails:
  Battery: 3.0V - 4.2V operating range
  Boost Output: 5V @ 1A (active mode)
  LDO Output: 3.3V @ 300mA (LoRa optimized)

Power Consumption Profiles:
  Active TX: ~140mA for 50ms (TDMA slot)
  Active RX: ~35mA for 50ms (listen mode)
  Standby: ~8mA (wake timers, RTC active)
  Deep Sleep: <1mA (all peripherals off)

Duty Cycle: 5-20% (adaptive based on traffic)
Battery Life: 6-12 months (typical personal use)
```

#### **Advanced Power Management**

```yaml
Sleep Management:
  Deep Sleep: ATmega328P power-down mode (<100μA)
  Wake Sources:
    - LoRa interrupt (DIO1)
    - RTC timer (32kHz crystal)
    - External button/sensor
    - USB connection detection

Power Switching:
  LoRa Module: Switchable power rail (complete shutdown)
  Peripherals: Individual control for sensors, LEDs
  Boost Converter: Enable/disable based on activity
  Status Monitoring: Battery voltage with low-power ADC

Adaptive Algorithms:
  Dynamic Duty Cycle: Adjusts based on traffic patterns
  Predictive Wake: Learns usage patterns for efficiency
  Emergency Mode: Extended operation at reduced functionality
```

### User Interface Design

#### **Portable Device Features**

```yaml
User Interaction:
  Power Button: Long-press on/off, short-press status
  Status LED: Multi-color indication (power, network, activity)
  Charging LED: Separate indicator for battery status

Connectivity:
  Micro-USB: Charging and programming interface
  Expansion Port: Grove connector for sensors/accessories
  External Antenna: SMA connector (optional high-gain antenna)

Enclosure:
  Material: ASA plastic (drop-resistant, UV-stable)
  Rating: IP54 (splash-resistant for personal use)
  Form Factor: Handheld device (smartphone-like dimensions)
  Belt Clip: Optional attachment for hands-free carry
```

### Application Examples

#### **Use Case Configurations**

**Personal Tracker**: Basic positioning and messaging

- Battery life: 10-12 months
- Features: Position reporting, emergency messages
- Sensors: None (minimal configuration)

**Environmental Monitor**: Sensor data collection with positioning

- Battery life: 6-8 months
- Features: Periodic sensor readings, data logging
- Sensors: Temperature, humidity, air quality

**Emergency Device**: High-reliability communications

- Battery life: 3-6 months
- Features: Always-on emergency monitoring, GPS backup
- Sensors: Accelerometer for fall detection

**Asset Tracker**: Commercial tracking applications

- Battery life: 8-10 months
- Features: Movement detection, geofencing alerts
- Sensors: IMU, vibration detection

---

## 📊 Comparative Analysis

### Platform Comparison Matrix

| Specification       | Anchor (ESP32S3) | Relay (Arduino R4) | Mobile (Nano) |
| ------------------- | ---------------- | ------------------ | ------------- |
| **CPU Performance** | 740 DMIPS        | 150 DMIPS          | 20 MIPS       |
| **Memory (Flash)**  | 8MB              | 256KB              | 32KB          |
| **Memory (RAM)**    | 2MB+512KB        | 32KB               | 2KB           |
| **Power (Active)**  | 150mA            | 180mA              | 140mA         |
| **Power (Sleep)**   | 5mA              | 15mA               | <1mA          |
| **Battery Life**    | 16h backup       | 2-4 weeks          | 6-12 months   |
| **Connectivity**    | WiFi + LoRa      | WiFi + LoRa        | LoRa only     |
| **Cost**            | ₹2,500           | ₹2,000             | ₹1,500        |

### Role-Specific Optimizations

#### **Anchor Nodes - Infrastructure Focus**

- **High Performance**: Dual-core processing for complex algorithms
- **Always Available**: Mains power eliminates battery constraints
- **Connectivity Options**: WiFi backup for redundant communication
- **Memory Capacity**: Large routing tables and network state

#### **Relay Node - Coordination Focus**

- **Balanced Design**: Moderate performance with extended battery life
- **High Capacity Battery**: Supports near-continuous operation
- **Traffic Management**: Sufficient processing for routing decisions
- **Expansion Capability**: Shield design allows future enhancements

#### **Mobile Nodes - Efficiency Focus**

- **Ultra-Low Power**: Aggressive power management for long battery life
- **Compact Design**: Portable form factor with minimal components
- **Cost Optimized**: Simplest platform meeting functionality requirements
- **User Friendly**: Simple interface suitable for non-technical users

---

## 🔋 Power Management Details

### Universal Power Architecture

All SNIPS nodes use a common power management approach optimized for different duty cycles and power sources:

```
┌─────────────┐    ┌──────────────┐    ┌─────────────┐    ┌──────────────┐
│18650 Battery│────│ DW01A        │────│ TPS61088    │────│ TLV75533     │
│3.7V/2.5-5Ah│    │ Protection   │    │ Boost       │    │ LDO          │
└─────────────┘    └──────────────┘    │ 2.5V-5.5V→5V│    │ 5V→3.3V     │
                                       └─────────────┘    └──────────────┘
                           │                    │                    │
                           ▼                    ▼                    ▼
                    ┌──────────────┐    ┌─────────────┐    ┌──────────────┐
                    │ TP4056       │    │Microcontroller│    │ SX1262 LoRa  │
                    │ Charging     │    │5V Power Rail │    │3.3V Power Rail│
                    └──────────────┘    └─────────────┘    └──────────────┘
```

### Component Selection Rationale

#### **TPS61088RHLR Boost Converter**

- **Efficiency**: 85% typical across load range
- **Input Range**: 2.5V-5.5V (full 18650 discharge range)
- **Output**: 5V @ up to 10A (supports all node configurations)
- **Features**: Synchronous rectification, low quiescent current (45μA)

#### **TLV75533PDBVR LDO Regulator**

- **Ultra-Low Noise**: Critical for LoRa receiver sensitivity
- **High PSRR**: 70dB power supply rejection
- **Fast Transient Response**: Handles LoRa TX current spikes
- **Efficiency**: 95% at typical loads

#### **DW01A Battery Protection**

- **Overcharge Protection**: 4.25V threshold prevents cell damage
- **Overdischarge Protection**: 2.4V threshold preserves cell life
- **Overcurrent Protection**: 3A threshold for short circuit safety
- **Response Time**: <100μs for rapid fault protection

#### **TP4056 Charging Controller**

- **CC/CV Profile**: Optimal charging for Li-ion cells
- **Thermal Regulation**: Prevents overheating during charge
- **Status Indication**: LEDs show charging progress
- **Safety**: Built-in timer and temperature monitoring

### Power Consumption Analysis

#### **Detailed Current Measurements**

| Operating Mode       | Anchor | Relay | Mobile | Duration   |
| -------------------- | ------ | ----- | ------ | ---------- |
| **LoRa TX (+22dBm)** | 120mA  | 120mA | 120mA  | 50ms max   |
| **LoRa RX**          | 4.6mA  | 4.6mA | 4.6mA  | Variable   |
| **CPU Active**       | 80mA   | 45mA  | 20mA   | Variable   |
| **CPU Idle**         | 25mA   | 15mA  | 8mA    | Background |
| **Deep Sleep**       | 5mA    | 15mA  | 0.8mA  | Majority   |

#### **Battery Life Calculations**

**Mobile Node Example** (2500mAh battery):

```
Daily Usage Pattern:
- 8 hours active (10% duty cycle): 8h × 0.1 × 35mA = 28mAh
- 16 hours sleep: 16h × 0.8mA = 12.8mAh
- Total per day: 28 + 12.8 = 40.8mAh

Battery Life: 2500mAh ÷ 40.8mAh = 61 days
Safety Factor (80%): 61 × 0.8 = ~49 days (1.6 months)

Optimized Usage (5% duty cycle): ~3-4 months
Heavy Usage (20% duty cycle): ~1 month
```

---

## 🔧 Assembly Instructions

### General Assembly Process

#### **Phase 1: Component Preparation**

1. **ESD Precautions**: Use anti-static wrist strap and mat
2. **Component Inspection**: Verify all parts against BOM
3. **Tool Setup**: Prepare soldering station (350°C), flux, solder
4. **PCB Inspection**: Check for manufacturing defects

#### **Phase 2: Power Circuit Assembly**

1. **Install Protection Components**: DW01A, MOSFETs, fuses
2. **Add Power Management**: TPS61088, TLV75533, supporting passives
3. **Power-On Test**: Verify voltage rails (no load)
4. **Load Testing**: Confirm regulation under typical loads

#### **Phase 3: Digital Circuit Assembly**

1. **Install Microcontroller**: Handle with care, verify orientation
2. **Add Support Components**: Crystals, bypass capacitors, reset circuits
3. **Programming Test**: Upload basic firmware, verify communication
4. **Interface Testing**: Confirm SPI, I2C, UART functionality

#### **Phase 4: RF Circuit Assembly**

1. **Install LoRa Module**: Handle with anti-static precautions
2. **RF Path Components**: Antenna connector, matching network, filters
3. **SPI Interface**: Connect to microcontroller with proper routing
4. **RF Testing**: Basic transmit/receive verification

#### **Phase 5: Final Assembly**

1. **Enclosure Preparation**: Install gaskets, cable glands
2. **PCB Installation**: Secure with standoffs, ensure grounding
3. **External Connections**: Antenna, power, programming interfaces
4. **Sealing**: Apply conformal coating if required, seal enclosure

### Node-Specific Considerations

#### **Anchor Nodes**

- **Heat Management**: Ensure thermal interface to enclosure
- **Antenna Mounting**: External antenna with weatherproof connector
- **Power Connection**: Strain relief for mains power cable
- **Mounting Hardware**: DIN rail clips or wall mount brackets

#### **Relay Nodes**

- **Battery Installation**: Secure 18650 cells with protection
- **Shield Alignment**: Careful Arduino shield connection
- **Status Indicators**: LEDs visible through enclosure window
- **Expansion Ports**: Sealed connectors for future sensors

#### **Mobile Nodes**

- **Compact Assembly**: Minimize thickness for portability
- **User Interface**: Button and LED accessibility
- **Charging Port**: Micro-USB with dust cover
- **Drop Protection**: Shock-absorbing enclosure design

---

_This detailed specification provides complete information for building and deploying professional-grade SNIPS nodes. Each node type is optimized for its specific role while maintaining system compatibility and professional reliability standards._

**Navigation**: [← Hardware Documentation](README.md) | [PCB Design Guidelines →](pcb-designs/)
