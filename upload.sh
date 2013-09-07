#!/bin/bash
avrdude -c usbtiny -p m168p -e -D -Uflash:w:./.build/atmega168/firmware.hex
