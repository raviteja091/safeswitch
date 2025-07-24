# SafeSwitch

Industrial-grade AC load controller using ESP32-S3 and opto-isolated TRIAC drivers.

## Features

- BLE command “ON”/“OFF” to switch AC loads via MOC3021M + BTA136 TRIAC.
- Manual push-button override.
- LED indication of relay state.
- Safe isolated control: HLK-5M05 power module + opto-isolator.

## Hardware

- **MCU**: Seeed XIAO ESP32-S3
- **Driver**: MOC3021M (opto-isolator) + BTA136 TRIAC
- **Power**: HLK-5M05 AC-DC
- **Input**: Push-button on GPIO1
- **Output**: TRIAC gate on GPIO2

See `hardware/schematic.png` and `hardware/pcb_layout.png`.

## Build & Flash

