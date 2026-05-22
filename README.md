# arduino-serial-comms

A structured serial command/response interface for controlling and monitoring Arduino hardware from a PC over USB.

## Components

- **`arduino/HardwareCommandBridge/`** — Arduino sketch that receives serial commands, dispatches handlers, and sends responses.
- **`pc/`** — C++17 application that opens the serial port and sends commands.

## Quick Start

1. Flash `arduino/HardwareCommandBridge/HardwareCommandBridge.ino` to your Arduino via the Arduino IDE.
2. Build and run the PC application — see [`pc/README.md`](pc/README.md).

## Protocol

See [`arduino/HardwareCommandBridge/README.md`](arduino/HardwareCommandBridge/README.md) for the full command reference.
