#!/bin/bash

# Verify no device forwarded
echo -e "$(tput bold)Verifying no forwarded device...$(tput sgr0)"


# ls /dev/ttyUSB*
ls /dev/ttyUSB* 1>/dev/null 2>&1
USB_EXISTS=$?

ls /dev/ttyACM* 1>/dev/null 2>&1
ACM_EXISTS=$?

echo "$USB_EXISTS"
echo "$ACM_EXISTS"

# Get the directory where this bash script is located
SCRIPT_DIR=$(dirname "$(realpath "$0")")

# Convert WSL path to Windows path
WIN_SCRIPT_DIR=$(wslpath -w "$SCRIPT_DIR")

SCRIPT_NAME="WSL_usb_setup.ps1"

# Path to the PowerShell script
POWERSHELL_SCRIPT="$WIN_SCRIPT_DIR\\$SCRIPT_NAME"

# Open PowerShell in administrator mode and run the PowerShell script
powershell.exe -Command "Start-Process powershell -ArgumentList '-ExecutionPolicy Bypass -File \"$POWERSHELL_SCRIPT\"' -Verb RunAs"

# Verify device forwarding
echo -e "$(tput bold)Verifying forwarded device...$(tput sgr0)"
ls /dev/ttyUSB*
ls /dev/ttyACM*
