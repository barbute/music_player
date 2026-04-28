# See https://docs.arduino.cc/arduino-cli/getting-started/#compile-and-upload-the-sketch
# for more. Could probably turn this into a script that accepts different args
# but lowk that sounds like a lot of work.

# Exit if anything errors
set -e

main_path="src/mp/mp.ino"

# Compile for Arduino Uno board
arduino-cli compile --fqbn arduino:avr:uno $main_path

# Deploy to board (port assumes deploying from my MacBook Air connected via
# a USB dongle)
arduino-cli upload -p /dev/cu.usbmodem1301 --fqbn arduino:avr:uno $main_path