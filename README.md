# SNIPS - Scalable Node Interfacing and Processing System

> A novel integrated positioning and communication system for LoRa-based mesh networks, featuring specialized anchor nodes for positioning infrastructure, relay coordination, and mobile user communication endpoints.

## 📋 Table of Contents

- [Project Overview](#-project-overview)
- [Key Features](#-key-features)
- [System Architecture](#-system-architecture)
- [Node Configurations](#-node-configurations)
- [Hardware Design](#-hardware-design)
- [Protocol Innovation](#-protocol-innovation)
- [Documentation Structure](#-documentation-structure)
- [Quick Start](#-quick-start)
- [Contributing](#-contributing)
- [License](#-license)

## 🌐 Project Overview

SNIPS (Scalable Node Interfacing and Processing System) is a comprehensive final year engineering project that implements a sophisticated custom communication and positioning protocol for LoRa-based mesh networks. The system addresses the dual challenge of reliable multi-node communication and real-time positioning through a unified architecture.

### Vision & Goals

- Create a unified LoRa mesh system that seamlessly integrates positioning and communication
- Enable simultaneous positioning of multiple mobile nodes within an active communication mesh
- Demonstrate professional-grade hardware design within educational project constraints (₹15,000)
- Contribute novel research in LoRa mesh networking and positioning systems

## ⭐ Key Features

### 🔄 Technical Innovations

- **Unified Architecture**: First-of-its-kind integration of positioning, TDMA scheduling, and store-and-forward routing in a single LoRa mesh system
- **Multi-Mobile Positioning**: Simultaneous positioning of multiple mobile nodes within an active communication mesh
- **Hybrid Protocol**: Combines structured TDMA scheduling with opportunistic store-and-forward for resilience
- **Role-Based Hierarchy**: Specialized 5-node configuration (3 Anchors + 1 Relay + 2 Mobile) with distinct capabilities

### 🎯 Core Capabilities

```yaml
Network Configuration:
  Total Nodes: 5 (3 Anchor + 1 Relay + 2 Mobile)
  Topology: Star-of-Stars with hybrid mesh capabilities
  Communication: Custom MAC and routing protocol
  Positioning: TDMA-scheduled trilateration measurements

Key Features:
  - Integrated positioning + communication mesh
  - Multi-mobile node positioning capability
  - Hybrid TDMA + Store-and-forward protocol
  - QoS with positioning traffic prioritization
  - Professional PCB design within budget constraints
```

### 🏆 Novelty Assessment

Based on comprehensive literature review, SNIPS demonstrates **significant technical novelty with a score of 2.67/4.0**:

- ✅ **No prior work** integrates positioning, TDMA, and store-and-forward routing in a single LoRa mesh
- ✅ **First system** to support multi-mobile positioning within active communication mesh
- ✅ **Unique hybrid protocol** combining deterministic TDMA access with opportunistic forwarding
- ✅ **Novel star-of-stars topology** with specific role specialization

## 🏗️ System Architecture

The SNIPS network implements a **star-of-stars topology** with role-based specialization:

```
        [A1] ---- [A2] ---- [A3]     (Anchor Nodes - Positioning Infrastructure)
         |         |         |
         |        [R1]       |        (Relay Node - Communication Coordinator)
         |       /    \      |
        [M1] ------------ [M2]        (Mobile Nodes - End User Devices)
```

### Communication Patterns

| Pattern          | Route                  | Use Case                |
| ---------------- | ---------------------- | ----------------------- |
| Direct           | M1 ↔ M2                | Nodes within LoRa range |
| Single-hop Relay | M1 → R1 → M2           | Standard communication  |
| Multi-hop Mesh   | M1 → A1 → R1 → A2 → M2 | Extended range          |
| Broadcast        | Any → All              | Network announcements   |

### TDMA Superframe Structure

| Phase     | Duration | Purpose                  | Priority |
| --------- | -------- | ------------------------ | -------- |
| Sync      | 100ms    | Network synchronization  | Critical |
| Control   | 200ms    | Management + Positioning | High     |
| Data      | 600ms    | User communications      | Medium   |
| Emergency | 100ms    | High-priority traffic    | Critical |

📖 **[Detailed Architecture Documentation →](docs/conceptual/overview.md)**

## ⚙️ Node Configurations

### 🔗 Anchor Nodes (A1, A2, A3)

- **Hardware**: Seeed XIAO ESP32S3 + Wio-SX1262 LoRa Module
- **Power**: Mains-powered (100% duty cycle)
- **Role**: Positioning reference infrastructure, mesh backbone
- **Features**: Always active, precise timing, fixed coordinates

### 🛡️ Relay Node (R1)

- **Hardware**: Arduino Uno R4 WiFi + Custom Shield
- **Power**: High-capacity battery (5000 mAh, 2-4 weeks operation)
- **Role**: Communication coordinator, TDMA master, routing hub
- **Features**: Traffic management, synchronization, protocol enforcement

### 📱 Mobile User Nodes (M1, M2)

- **Hardware**: Arduino Nano + Custom Shield
- **Power**: Battery-optimized (2500 mAh, 6-12 months)
- **Role**: End-user devices, data origination/consumption
- **Features**: Power efficient, portable, adaptive protocols

📖 **[Detailed Node Specifications →](docs/circuit-diagrams/README.md)**

## 🔩 Hardware Design

All nodes feature custom-designed PCBs emphasizing modularity, efficiency, and professional-grade reliability within project constraints.

### Core Hardware Modules

- **Voltage Regulation**: TPS61088 boost + TLV75533 LDO (>85% efficiency)
- **Battery Protection**: DW01A + TP4056 with multi-layer safety
- **LoRa Transceiver**: Seeed Wio-SX1262 (Semtech SX1262, -148dBm sensitivity)
- **PCB Architecture**: 4-layer design with controlled impedance RF paths
- **Environmental Protection**: IP65-rated enclosures for outdoor deployment

### Design Philosophy

```yaml
Principles:
  - Modular architecture for easy maintenance
  - Professional-grade reliability
  - Budget-conscious component selection (₹15,000 total)
  - Thermal management for outdoor deployment
  - RF design best practices for LoRa
```

📖 **[Detailed Hardware Documentation →](docs/practical/README.md)**

## 🔄 Protocol Innovation

SNIPS implements a custom protocol stack that uniquely integrates positioning and communication functionalities.

### Protocol Architecture

- **Integration Philosophy**: _"Positioning is not an add-on, but a native protocol function"_
- **TDMA-Scheduled Positioning**: Measurements integrated into 1-second superframe
- **Hybrid MAC Protocol**: Structured TDMA + opportunistic store-and-forward
- **Multi-Metric Routing**: Route cost based on hops, link quality, latency, energy

### Development Phases

1. **Foundation** (Weeks 1-4): Basic LoRa communication, frame structure
2. **MAC Layer** (Weeks 5-8): TDMA superframe, synchronization
3. **Routing** (Weeks 9-14): Route discovery, multi-hop forwarding
4. **Positioning** (Weeks 15-17): TDOA measurements, trilateration
5. **Optimization** (Weeks 18-20): Power management, QoS, field testing

📖 **[Detailed Protocol Documentation →](docs/protocol/README.md)**

## 📚 Documentation Structure

This repository follows a structured documentation approach:

```
docs/
├── README.md                 # Documentation overview & navigation
├── conceptual/               # Theory and conceptual explanations
│   ├── README.md             # Index for conceptual docs
│   ├── overview.md           # System overview and architecture
│   └── domain-specific.md    # LoRa mesh and positioning theory
├── practical/                # Practical aspects and applications
│   ├── README.md             # Index for practical docs
│   ├── application.md        # Use cases and applications
│   └── troubleshooting.md    # Common issues and solutions
├── protocol/                 # Custom communication protocol
│   ├── README.md             # Protocol overview & specifications
│   ├── specification.md      # Detailed protocol specs
│   ├── implementation.md     # Implementation guidelines
│   └── examples.md           # Protocol usage examples
└── circuit-diagrams/         # Hardware schematics and PCB designs
    ├── README.md             # Hardware documentation index
    ├── node-configurations.md # Detailed node specifications
    └── pcb-designs/          # Schematic files and layouts

resources/
├── README.md                 # Resource index and guidance
├── ics/                      # IC datasheets and specifications
├── components/               # Component datasheets
└── external/                 # Links to external documentation
```

## 🚀 Quick Start

### Prerequisites

- Arduino IDE or PlatformIO
- LoRa development boards
- Basic understanding of embedded systems

### Setup Instructions

1. **Clone Repository**:

   ```bash
   git clone https://github.com/Adiaparmar/SNIPS-Scalable_Node_Interfacing_Processing_System.git
   cd SNIPS-Scalable_Node_Interfacing_Processing_System
   ```

2. **Hardware Setup**: Follow [Hardware Assembly Guide](docs/practical/application.md)

3. **Software Setup**: See [Implementation Guide](docs/protocol/implementation.md)

4. **Testing**: Run [Test Procedures](test/README.md)

### Project Status

- **Current Phase**: Design and Documentation
- **Hardware**: PCB designs in progress
- **Software**: Protocol development ongoing
- **Target Completion**: Academic session end

## 🤝 Contributing

We welcome contributions to SNIPS! This project is part of an academic research effort, and community input helps improve the system.

### How to Contribute

- 📖 **Documentation**: Help improve clarity and completeness
- 🐛 **Issues**: Report bugs or suggest enhancements
- 💡 **Ideas**: Share optimization strategies or use cases
- 🔬 **Research**: Contribute to protocol analysis and validation

Please read our [Contributing Guidelines](CONTRIBUTING.md) and [Code of Conduct](docs/CONTRIBUTING.md).

### Academic Use

- ✅ **Free for educational and research purposes**
- ✅ **Attribution required for academic publications**
- ✅ **Commercial derivative works permitted under MIT terms**

## 🎓 Credits

- Mayank Sharma (Team Leader) |  **Contact**: Shar.mayankofficial@gmail.com |  **GitHub**: https://github.com/Shar-mayank0
- Aditya Kumar Singh (Software) |  **Contact**: adiaparmar@gmail.com |  **GitHub**: https://github.com/Adiaparmar
- Aayush Jha (Communication) |  **Contact**: aayushjha1911@gmail.com |  **GitHub**: https://github.com/aayushjha19
- Abhishek Prajapat (Hardware) |  **Contact**: abhishekprajapati6350@gmail.com |  **GitHub**: https://github.com/Abhii-prajapat
- Harsh Kumar () |  **Contact**:  |  **GitHub**: 

---

 | **🔗 Project Repository**: [Repository URL]

_Last Updated: October 16, 2025_

## Last Updated

[Insert last updated date here]
