#!/bin/bash
avrdude -c usbtiny -p m168p -D -Uflash:w:./.build/atmega168/firmware.hex
