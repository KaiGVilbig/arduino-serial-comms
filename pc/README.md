# pc

C++17 application that connects to the Arduino over serial and sends commands.

## Requirements

```bash
sudo apt-get install liblog4cxx-dev libgtest-dev valgrind
```

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

## Test

```bash
./build/arduino-serial-comms-tests
```

## Valgrind

```bash
cmake --build build --target valgrind
```

## Notes

- The Arduino resets when the serial port is opened. A 2 second delay is built in before commands are sent.
- The Arduino must be flashed and connected before running.
- Commands are entered as comma-delimited strings matching the protocol format, e.g. `SET,LED,1` or `STATUS,ALL`.
