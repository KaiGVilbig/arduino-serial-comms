# pc

C++17 application that connects to the Arduino over serial and sends commands.

## Build

```bash
cmake -B build
cmake --build build
```

## Run

```bash
./build/arduino-serial-comms
```

The serial port and baud rate are configured in `src/main.cpp`. The default is `/dev/ttyUSB0` at 9600 baud — change these to match your setup before building.

## Notes

- The Arduino resets when the serial port is opened. Allow ~2 seconds before sending commands or responses will be missed.
- The Arduino must be flashed and connected before running.
