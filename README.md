Arduno WiFly UDP sensor data blaster
=====
Loop forever

  Read a sensor


  Send sensor data via broadcast UDP packets at an interval

End


 sudo tcpdump -i eth1 udp dst port 12345 -X


Uses inotool from http://inotool.org


------------
$ avr-size -C --mcu=atmega328p .build/uno/firmware.elf 
AVR Memory Usage
----------------
Device: atmega328p

Program:   12164 bytes (37.1% Full)
(.text + .data + .bootloader)

Data:       1279 bytes (62.5% Full)
(.data + .bss + .noinit)

