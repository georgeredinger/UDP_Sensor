#!/bin/bash
 avrdude -P usb -c usbtiny -p m168p  -U lfuse:w:0xce:m -U hfuse:w:0xdf:m -U efuse:w:0xf9:m

