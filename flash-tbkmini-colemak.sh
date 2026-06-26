#!/usr/bin/env bash
#
# Compile and flash the bastardkb/tbkmini colemak layout.
#
# Compiles the keymap with the local qmk venv, then flashes the resulting
# .hex to the atmega32u4 (Elite-C) via dfu-programmer. Waits for you to put
# the board into bootloader mode (reset it) before flashing.
#
# Usage: ./flash-tbkmini-colemak.sh
set -euo pipefail

KB="bastardkb/tbkmini/promicro"
KM="colemak"
MCU="atmega32u4"
DFU_USB="03eb:2ff4"   # Atmel atmega32u4 DFU bootloader

REPO_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
QMK="$REPO_DIR/.venv-qmk/bin/qmk"
HEX="$REPO_DIR/$(echo "${KB}_${KM}" | tr '/' '_').hex"

cd "$REPO_DIR"

# 1. Compile
if [[ -x "$QMK" ]]; then
    echo ">> Compiling $KB:$KM ..."
    "$QMK" compile -kb "$KB" -km "$KM"
elif command -v qmk >/dev/null 2>&1; then
    echo ">> Compiling $KB:$KM (system qmk) ..."
    qmk compile -kb "$KB" -km "$KM"
else
    echo "!! qmk not found (looked for $QMK and 'qmk' on PATH)" >&2
    exit 1
fi

if [[ ! -f "$HEX" ]]; then
    echo "!! Build did not produce $HEX" >&2
    exit 1
fi

# 2. Wait for the board to be in bootloader mode
echo ">> Put the keyboard into bootloader mode (reset it) ..."
until lsusb | grep -qi "$DFU_USB"; do
    sleep 0.5
done
echo ">> DFU bootloader detected."

# 3. Flash (needs root for raw USB access; remove sudo if you have udev rules)
echo ">> Erasing ..."
sudo dfu-programmer "$MCU" erase --force
echo ">> Flashing $HEX ..."
sudo dfu-programmer "$MCU" flash "$HEX"
echo ">> Resetting ..."
sudo dfu-programmer "$MCU" reset || true   # reset disconnects the device -> non-zero is normal

echo ">> Done."
