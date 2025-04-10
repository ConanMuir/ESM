# ESM - Electro Shock Module

**ESP32 Muscle Stimulation Firmware** for a compact, custom-designed PCB that delivers precise, configurable DC voltage pulses to stimulate muscles. Built for prototyping, research, biofeedback, and experimental haptics applications.

---

## Overview

The Electro Shock Module (ESM) is a firmware and hardware platform centered around the Seeed Studio Xiao ESP32-C3 microcontroller. It safely generates and controls high-voltage DC pulses to stimulate muscles through electrode contact points.

This system is ideal for:
- Biofeedback and neurostimulation experiments  
- TENS-style prototyping  
- Haptic feedback research  
- Educational demonstrations of electro-muscular control

---

## How It Works

The core architecture of ESM is designed around three main components:

### 1. Voltage Boosting

A custom-designed boost converter steps up the ESP32’s 3.3V input to a controlled maximum of **55V DC**. This is necessary to overcome the natural resistance of human skin and induce muscle contraction. The circuit is intentionally current-limited to remain within safe parameters.

### 2. Pulse Control via MOSFET

A logic-level MOSFET switches the high-voltage DC output on and off in precise, configurable pulses. This mimics the functionality of a TENS (Transcutaneous Electrical Nerve Stimulation) unit, which delivers electrical signals to muscles or nerves through surface electrodes.

> In layman’s terms: it sends tiny "zaps" to your skin that make your muscles twitch. By changing the frequency and length of those zaps, you can create different effects—from a light tingling to a strong flex.

### 3. Firmware Configuration

Stimulation parameters such as:
- Pulse width  
- Frequency  
- Duty cycle  
- Session duration  

...can all be adjusted in the firmware. These allow for fine-grained control to match different use cases or testing scenarios.

---

## Key Features

- Configurable high-voltage DC pulses (up to 55V)
- Safe, limited current output
- Compact design using the Xiao ESP32-C3
- Adjustable pulse parameters via firmware
- USB and wireless capability (ESP32)
- Fully open-source and modifiable

---

## Hardware Diagram

*(Insert photo or diagram here)*  
> _Example: Circuit block diagram or assembled PCB photo._

---

## Repository Structure

