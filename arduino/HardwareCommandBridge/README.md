# arduino-serial-comms

A structured serial command/response interface for Arduino, designed to control and monitor hardware over a USB serial connection from a PC-side C++ application.

---

## Setup

- **Baud rate:** 9600
- **Line ending:** Newline (`\n`) terminated
- Flash the sketch to your Arduino via the Arduino IDE before connecting from the PC side

---

## Protocol Format

All messages follow a comma-delimited format:

**Command (PC → Arduino)**
```
TYPE,ACTION,PARAM1,PARAM2,...\n
```

**Response (Arduino → PC)**
```
TYPE,ACTION,STATUS,RESPONSE
```

Where `STATUS` is either `OK` or `FAIL`, and `RESPONSE` contains the result value or error reason.

---

## Commands

### `IDENTIFY`
Returns the board model.

**Format:**
```
IDENTIFY
```

**Response:**
```
IDENTIFY,OK,Uno
```

---

### `SET,LED,<value>`
Sets the built-in LED (pin 13) on or off.

**Params:**
- `value` — `1` for ON, `0` for OFF

**Examples:**
```
SET,LED,1
SET,LED,0
```

**Response:**
```
SET,LED,OK,
SET,LED,FAIL,BAD_PARAM
```

---

### `SET,PIN,<pin>,<value>`
Sets a digital pin as output and writes a PWM value to it. Valid pins are 2–12.

Pin numbers are offset from `LED_BUILTIN` — pass the offset value, not the raw pin number (e.g. pass `0` for the first pin above LED_BUILTIN).

Optionally, if `value` is `-1`, pass a third param as an analog pin offset to read from — the output value will be read from that analog pin instead.

**Params:**
- `pin` — target pin offset
- `value` — PWM value (0–255), or `-1` to read from analog pin
- `analogPin` *(optional)* — analog pin offset to read from if `value` is `-1`

**Examples:**
```
SET,PIN,2,128
SET,PIN,3,-1,1
```

**Response:**
```
SET,PIN,OK,128
SET,PIN,FAIL,BAD_PARAM
```

---

### `READ,A,<pin>`
Reads an analog value from an analog pin (A0–A6). Returns a value between 0–1023.

Pin is passed as an offset — `0` maps to A0, `1` to A1, etc.

**Examples:**
```
READ,A,0
READ,A,3
```

**Response:**
```
READ,A,OK,512
READ,A,FAIL,BAD_PARAM
```

---

### `READ,D,<pin>`
Reads the digital state of a pin. Returns `0` or `1`.

**Examples:**
```
READ,D,0
```

**Response:**
```
READ,D,OK,1
READ,D,FAIL,BAD_PARAM
```

---

### `STATUS,PIN,<pin>`
Returns the current digital state of a specific pin via `digitalRead`.

**Params:**
- `pin` — raw pin number (13–A7 range)

**Examples:**
```
STATUS,PIN,13
```

**Response:**
```
STATUS,PIN,OK,1
STATUS,PIN,FAIL,BAD_PARAM
```

---

### `STATUS,ALL`
Returns the shadow register state of all tracked pins (0–13). Values reflect what was last **set** via `SET` commands, not physical pin reads. PWM values are preserved as-set since they cannot be read back from hardware registers.

**Format:**
```
STATUS,ALL
```

**Response:**
```
STATUS,ALL,OK,0,0,128,0,0,0,0,0,0,0,0,0,0,1,
```

Each comma-separated value corresponds to pin 0 through 13 in order.

---

### `RUN,BLINK,<count>,<rate>`
Blinks the built-in LED a specified number of times at a given rate, then returns the number of blinks completed.

**Params:**
- `count` — number of blinks
- `rate` *(optional)* — delay in milliseconds between on/off (default: 500ms)

**Examples:**
```
RUN,BLINK,5
RUN,BLINK,10,250
```

**Response:**
```
RUN,BLINK,OK,5
RUN,BLINK,FAIL,UNKNOWN_PROGRAM
```

---

## Error Responses

All commands respond with `FAIL` and a reason string on error:

| Reason | Meaning |
|---|---|
| `BAD_PARAM` | Parameter out of range or wrong type |
| `UNKNOWN_PROGRAM` | `RUN` called with unrecognized program name |

---

## Shadow Register

Pin states set via `SET` commands are tracked in a software array (`D_PINS[14]`) rather than read back from hardware. This is intentional — PWM duty cycle values are not stored in a readable AVR register after being written, so the firmware maintains its own mirror of pin state. `STATUS,ALL` reads from this mirror.

---

## Supported Boards

Automatically detected at compile time via preprocessor macros. Supports all standard Arduino AVR boards (Uno, Nano, Mega, Leonardo, etc.) and Teensy boards.
