# Hotplate

<p align="left">
  <img src="https://img.shields.io/badge/KiCad-PCB%20Design-314CB0?style=flat&logo=kicad&logoColor=white" alt="KiCad PCB Design"/>
  <img src="https://img.shields.io/badge/LTspice-Circuit%20Simulation-blue?style=flat" alt="LTspice Circuit Simulation"/>
  <img src="https://img.shields.io/badge/Arduino-Firmware-00979D?style=flat&logo=arduino&logoColor=white" alt="Arduino Firmware"/>
  <img src="https://img.shields.io/badge/Status-Work%20in%20Progress-orange?style=flat" alt="Work in Progress"/>
</p>

**An open-source hotplate project for electronics and PCB work.**

> **Work in Progress** — This project is currently under development. Hardware designs, PCB revisions, documentation, and other project files may change.

## Overview

Hotplate is a DIY electronics project focused on the design and development of a hotplate and its associated control electronics.

This repository is intended to collect the hardware designs, PCB documentation, and project resources as development progresses.

## PCB Designs

### Hotplate Resistor

The custom PCB designed for the hotplate heating element.

<p align="center">
  <img src="img/hotplate-resistor.png" alt="Hotplate Resistor PCB" width="700">
</p>

### Hotplate Control Board v1.1

The control electronics PCB, revision v1.1.

<p align="center">
  <img src="img/hotplate-control-board-v1.1.png" alt="Hotplate Control Board v1.1 PCB" width="700">
</p>

## Repository Structure

```text
Hotplate/
├── img/
│   ├── hotplate-control-board-v1.1.png
│   └── hotplate-resistor.png
├── Kicad/
│   ├── Control board/
│   │   ├── Control board v1.0/
│   │   ├── Control board v1.1/
│   │   └── Control board v1.2/
│   ├── Resistor 10x10/
│   └── Resistor 15x15/
├── Program/
│   ├── lib/
│   ├── Master/
│   ├── Master_prova/
│   ├── backup1/
│   └── backup 2/
├── Simulation and circuits/
└── README.md
```

This tree shows the main project directories. Individual KiCad libraries, 3D models, backup files, and simulation outputs are omitted for readability

