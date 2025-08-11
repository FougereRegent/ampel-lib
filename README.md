# LibAmpel

LibAmpel is a C library for controlling a USB LED device (Ampel) via `libusb-1.0` communication. It provides a simple and lightweight API to turn on, turn off, and change the color of the LEDs on the Ampel device.

---

## Table of Contents

- [Features](#features)  
- [Dependencies](#dependencies)  
- [Installation](#installation)  
- [Compilation](#compilation)  
- [Project Integration](#project-integration)  
- [API Usage](#api-usage)  
- [Usage Example](#usage-example)  
- [Error Codes and Handling](#error-codes-and-handling)  
---

## Features

- Control LEDs via USB (colors and ON/OFF states)  
- Communication through the `libusb-1.0` library  
- Simple and lightweight API suitable for embedded or desktop use  
- Detailed error handling and clear messages  

---

## Dependencies

- [libusb-1.0](https://libusb.info/) (cross-platform USB library)

### Installation on Debian/Ubuntu

```bash
  sudo apt-get install libusb-1.0-0-dev

```

## Installation

```bash
  git clone https://github.com/FougereRegent/ampel-lib.git
  cd ampel-lib
```

# Compilation

## Compile the static library

```bash
  make
```
## Compile the example

```bash
  make example
```

## Clean

```bash
  make clean
```

## Project Integration

```bash
  gcc -I./include -L./lib -lled -lusb-1.0 <your_source.c> -o your_program
```

# API

## Usage
| Function                                                                               | Description                                       |
| -------------------------------------------------------------------------------------- | ------------------------------------------------- |
| `int init(libampel_ampel_led **ampel_led)`                                             | Initializes connection to the LED device.         |
| `int libampel_apply_value(libampel_ampel_led *ampel_led, struct libampel_state state)` | Applies a state (color + ON/OFF) to the LED.      |
| `struct libampel_state libampel_get_last_led(libampel_ampel_led *ampel_led)`           | Retrieves the last state applied to the LED.      |
| `char *libampel_strerror(int error_code)`                                              | Returns a readable error message.                 |
| `void release_ampel(libampel_ampel_led *ampel_led)`                                    | Releases resources and closes the USB connection. |

## Error Codes and handling

| Code                      | Description                  |
| ------------------------- | ---------------------------- |
| `OK` (0)                  | Operation successful         |
| `ERROR_INIT` (-1)         | libusb initialization failed |
| `ERROR_NOTFOUND` (-2)     | USB device not found         |
| `ERROR_USB_TRANSFER` (-3) | USB transfer error           |
| `ERROR_ACCESS` (-4)       | USB port access denied       |


