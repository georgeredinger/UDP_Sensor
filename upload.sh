#!/bin/bash
avrdude -P usb -c usbtiny -p m168p -e -D -Uflash:w:./.build/pro/firmware.hex

