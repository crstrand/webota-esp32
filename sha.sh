#!/bin/bash
# ESP32 SHA256 sum is the SHA256 sum of the firmware binary with the 32 byte SHA256 footer removed
# command to get SHA256 sum with Espressif tool
# python esptool.py --chip esp32 image_info ./firmware.bin | grep Hash | awk '{ print toupper($3) }'
if [ "$1" != "-nc" ]; then
  firmware_path=$(find ./.pio -name firmware.bin)
  cp $firmware_path ./firmware.bin
fi
# ./.pio/build/nodemcu-32s/firmware.bin
cp ./firmware.bin ./temp.bin
truncate -s -32 ./temp.bin
sha256sum temp.bin | awk '{print toupper($1)}' > sha256.txt
rm temp.bin
ls -l ./firmware.bin ./sha256.txt
cat sha256.txt
