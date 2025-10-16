# Circuit Diagrams & Hardware Documentation

This section contains comprehensive hardware documentation for the SNIPS system, including detailed schematics, PCB designs, component specifications, and assembly instructions.

## 📋 Hardware Documentation Overview

### 🔧 What You'll Find Here

- **Complete hardware specifications** for all 5 node types
- **Professional PCB designs** with 4-layer architecture
- **Component selection rationale** and sourcing information
- **Assembly instructions** and testing procedures
- **Enclosure designs** for outdoor deployment
- **RF performance optimization** guidelines

---

## 📁 Available Documentation

### 🖥️ [Node Configurations](node-configurations.md)

**Detailed hardware specifications for each node type**

- **Anchor Node Architecture**: ESP32S3 + SX1262 platform specifications
- **Relay Node Design**: Arduino R4 WiFi + custom shield architecture
- **Mobile Node Hardware**: Arduino Nano + optimized power management
- **Comparative Analysis**: Platform selection rationale and trade-offs
- **Power Management**: Battery life calculations and optimization strategies

**Target Audience**: Hardware engineers, system integrators, builders

---

### ⚡ [PCB Design Guidelines](pcb-designs/)

**Professional PCB design files and documentation**

#### **Available Files & Documentation**:

- **Schematic Files**: Complete electrical schematics (EasyEDA format)
- **PCB Layouts**: 4-layer board designs with controlled impedance
- **Gerber Files**: Manufacturing-ready production files
- **Assembly Drawings**: Component placement and orientation guides
- **Bill of Materials**: Complete BOM with part numbers and sourcing
- **Design Rules**: PCB manufacturing specifications and constraints

**Target Audience**: PCB designers, manufacturers, advanced builders

---

## 🏗️ Hardware Architecture Overview

### System-Wide Design Philosophy

```yaml
Design Principles:
  - Modular architecture for maintainability
  - Professional-grade reliability within budget constraints
  - RF design best practices for LoRa performance
  - Power efficiency optimization for battery life
  - Environmental protection (IP65) for outdoor use
```

### Node Hardware Summary

| Node Type  | Platform              | Power Source      | Key Features                  |
| ---------- | --------------------- | ----------------- | ----------------------------- |
| **Anchor** | ESP32S3 + SX1262      | Mains (always-on) | High performance, WiFi backup |
| **Relay**  | Arduino R4 + Shield   | 5000mAh battery   | Traffic coordination, routing |
| **Mobile** | Arduino Nano + Shield | 2500mAh battery   | Ultra-low power, portable     |

---

## 🔋 Power Management Architecture

### Universal Power Design

All nodes share a common power architecture optimized for different use cases:

```
18650 Battery → TPS61088 Boost → 5V Rail → TLV75533 LDO → 3.3V Rail
                     ↓                        ↓
               DW01A Protection         SX1262 LoRa Module
                     ↓                        ↓
               TP4056 Charging          Microcontroller
```

#### **Key Components**:

- **TPS61088**: High-efficiency boost converter (85% typical)
- **TLV75533**: Ultra-low noise LDO for RF circuits
- **DW01A**: Multi-layer battery protection
- **TP4056**: Intelligent CC/CV battery charging

### Power Performance Targets

| Component           | Efficiency | Current Draw   | Notes                  |
| ------------------- | ---------- | -------------- | ---------------------- |
| **Boost Converter** | 85%        | -              | 2.5V-5.5V input range  |
| **LDO Regulator**   | 95%        | 500mA max      | Ultra-low noise for RF |
| **SX1262 TX**       | -          | 120mA @ +22dBm | Maximum power output   |
| **SX1262 RX**       | -          | 4.6mA          | Receive mode           |
| **SX1262 Sleep**    | -          | 1.5μA          | Deep sleep mode        |

---

## 📡 RF Design Considerations

### LoRa Module Integration

**Seeed Wio-SX1262 Features**:

- **Chipset**: Semtech SX1262 (latest generation)
- **Sensitivity**: -148dBm (SF12/BW125)
- **Output Power**: +22dBm maximum
- **Interface**: SPI with 3.3V logic levels

### RF Path Optimization

#### **PCB Design Features**:

- **Controlled Impedance**: 50Ω throughout RF path
- **Ground Plane**: Solid ground pour for RF reference
- **Via Stitching**: Ground vias flanking RF traces
- **Component Isolation**: Keep-out zones around antenna connections

#### **Antenna Options**:

- **3dBi Omnidirectional**: Standard deployment
- **5dBi Directional**: Extended range applications
- **PCB Trace**: Compact mobile nodes

---

## 🏭 Manufacturing & Assembly

### PCB Manufacturing Specifications

```yaml
PCB Specifications:
  Layers: 4-layer stackup
  Thickness: 1.6mm standard FR-4
  Copper Weight: 1oz signals, 2oz power
  Surface Finish: ENIG (gold plating)
  Solder Mask: Green or matte black
  Silkscreen: White component references

Design Rules:
  Min Trace Width: 0.15mm (6 mil)
  Min Via Size: 0.3mm drill / 0.6mm pad
  Min Clearance: 0.15mm (6 mil)
  Impedance Control: 50Ω ±10%
```

### Assembly Process

#### **Component Placement Order**:

1. **Power Components**: Regulators, protection circuits
2. **Digital ICs**: Microcontrollers, support logic
3. **RF Components**: LoRa modules, antenna connectors
4. **Passives**: Resistors, capacitors, inductors
5. **Mechanical**: Connectors, switches, indicators

#### **Testing Sequence**:

1. **Visual Inspection**: Component placement and solder quality
2. **Power-On Test**: Verify voltage rails (no load)
3. **Functional Test**: Basic firmware operation
4. **RF Performance**: Range and sensitivity validation
5. **Final Assembly**: Enclosure integration and sealing

---

## 📦 Enclosure & Environmental Protection

### Environmental Requirements

**Target Rating**: IP65 (dust-tight, water jet protected)

| Parameter       | Specification             |
| --------------- | ------------------------- |
| **Temperature** | -20°C to +60°C            |
| **Humidity**    | 5% to 95% non-condensing  |
| **Altitude**    | 0 to 3000m                |
| **Vibration**   | 5-200 Hz, 2g acceleration |

### Enclosure Materials

- **Anchor Nodes**: ABS plastic, UV-stabilized
- **Relay Node**: Polycarbonate with TPE gasket
- **Mobile Nodes**: ASA plastic, drop-resistant

### Sealing Strategy

- **O-ring Gaskets**: All openings sealed
- **Cable Glands**: Weatherproof external connections
- **Conformal Coating**: Optional PCB protection
- **Pressure Vents**: IP65-rated for thermal cycling

---

## 💰 Cost Analysis & Sourcing

### Project Budget Breakdown

**Total Budget**: ₹15,000 (~$180 USD)

| Category             | Cost (₹) | Percentage | Notes                  |
| -------------------- | -------- | ---------- | ---------------------- |
| **Microcontrollers** | 4,500    | 30%        | 5 nodes total          |
| **LoRa Modules**     | 5,000    | 33%        | Wio-SX1262 units       |
| **Power Components** | 2,000    | 13%        | Regulators, protection |
| **PCB Fabrication**  | 1,500    | 10%        | 5 boards, 4-layer      |
| **Enclosures**       | 1,200    | 8%         | IP65 weatherproof      |
| **Miscellaneous**    | 800      | 6%         | Connectors, hardware   |

### Sourcing Strategy

#### **Authorized Distributors**:

- **Critical ICs**: DigiKey, Mouser (genuine parts)
- **LoRa Modules**: Seeed Studio (direct)
- **Microcontrollers**: Arduino, Adafruit (official)

#### **Cost Optimization**:

- **Volume Pricing**: Bulk orders for 5+ units
- **Generic Components**: Local sources for passives
- **PCB Manufacturing**: JLCPCB, PCBWay (cost-effective)
- **Alternative Parts**: Pin-compatible substitutes where available

---

## 🔧 Tools & Equipment Requirements

### Design Tools

- **Schematic Capture**: EasyEDA Professional
- **PCB Layout**: EasyEDA (4-layer capable)
- **3D Modeling**: FreeCAD for enclosures
- **Simulation**: LTSpice (power), Qucs (RF)

### Manufacturing Equipment

#### **Assembly Tools**:

- **Soldering Station**: Temperature-controlled (300-400°C)
- **Hot Air Rework**: For QFN/BGA components
- **Microscope**: 10-40x magnification for inspection
- **Multimeter**: Basic electrical testing

#### **Test Equipment**:

- **Oscilloscope**: Signal integrity verification
- **Spectrum Analyzer**: RF performance testing (optional)
- **Network Analyzer**: Impedance measurements (advanced)
- **Power Supply**: Variable DC source for testing

---

## 📊 Performance Validation

### Hardware Testing Procedures

#### **Power System Validation**:

- [ ] Efficiency measurements across load range
- [ ] Ripple and noise characterization
- [ ] Thermal performance under maximum load
- [ ] Battery charging profile verification

#### **RF Performance Testing**:

- [ ] Sensitivity measurements (range testing)
- [ ] Power output verification and harmonics
- [ ] Antenna SWR and impedance matching
- [ ] Interference susceptibility testing

#### **Environmental Testing**:

- [ ] Temperature cycling validation
- [ ] Humidity exposure testing
- [ ] Vibration and shock resistance
- [ ] IP65 water ingress protection

---

## 🚀 Advanced Topics

### Performance Optimization

#### **RF Enhancements**:

- **Antenna Diversity**: Multiple antennas with switching
- **Power Amplifiers**: External PA for extended range
- **Low Noise Amplifiers**: Improve receiver sensitivity
- **Adaptive Matching**: Tunable antenna matching networks

#### **Power Optimization**:

- **Energy Harvesting**: Solar panels for anchor nodes
- **Advanced Sleep Modes**: Microcontroller-specific optimizations
- **Dynamic Voltage Scaling**: Frequency-dependent power reduction
- **Wake-on-Radio**: Hardware-triggered wake from deep sleep

### Future Hardware Revisions

#### **Version 2.0 Enhancements** (Planned):

- **Integrated Design**: Single-board computer approach
- **Enhanced Protection**: Military-grade environmental specs
- **Advanced Sensors**: Integrated IMU, environmental sensors
- **Modular Expansion**: Standardized sensor interface connectors

---

## 📚 Supporting Resources

### **Component Datasheets**: [../resources/ics/](../../resources/ics/)

- Microcontroller specifications and programming guides
- LoRa module technical documentation
- Power management IC characteristics
- Environmental protection component specs

### **External References**: [../resources/external/](../../resources/external/)

- PCB design guidelines and best practices
- RF design principles for LoRa applications
- Battery management and safety standards
- Environmental testing procedures and standards

### **Design Files**: Available in repository

- Complete EasyEDA project files
- Gerber files for PCB manufacturing
- 3D models for enclosure design
- Assembly documentation and procedures

---

_This hardware documentation provides complete specifications for building professional-grade SNIPS nodes. The modular design allows customization while maintaining compatibility across the mesh network._

**Navigation**: [← Documentation Index](../README.md) | [Node Configurations →](node-configurations.md)
