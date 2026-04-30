#!/usr/bin/env bash

# See https://docs.arduino.cc/arduino-cli/getting-started/#compile-and-upload-the-sketch
# for more. Could probably turn this into a script that accepts different args
# but lowk that sounds like a lot of work.

# Exit if anything errors
set -e

main_path="music_player.ino"
board_name="arduino:avr:uno"
port="/dev/cu.usbmodem1301"

# Compile for Arduino Uno board
arduino-cli compile --fqbn $board_name $main_path

# Deploy to board (port assumes deploying from my MacBook Air connected via
# a USB dongle)
arduino-cli upload -p $port --fqbn $board_name $main_path

# Open communication with the board
# See https://arduino.github.io/arduino-cli/dev/commands/arduino-cli_monitor/
arduino-cli monitor -p $port -b $board_name