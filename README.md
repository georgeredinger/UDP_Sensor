Arduno WiFly UDP sensor data blaster
=====
Loop forever

  Read a sensor


  Send sensor data via broadcast UDP packets at an interval

End

in src/WiFly_helpers.cpp
change the host IP address and the port number to suit:

  SpiSerial.print("set ip host 192.168.1.100\r");echo();

  SpiSerial.print("set ip remote 12345\r");echo();

For a WiFly static ip address,add something like this 

 SpiSerial.print("set ip address 192.168.1.123");echo();

 SpiSerial.print("set ip netmask 255.255.255.0");echo();

set ip dhcp 0
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

