import serial
import time
import binascii
from time import gmtime, strftime
from random import randint

with serial.Serial('/dev/tty.usbserial-FTGYVTNL', 57600, timeout=10) as ser:
            # with serial.Serial('/dev/ttyUSB0', 115200, timeout=10) as ser:
	while True:
		message = ''
		for i in range(0,randint(0,8)):
			message = message + "          "
		message = message + strftime(" %H:%M:%S", time.localtime()) + "                                        \n"
		# "{:<159}".format(message)
		# b = bytearray(message, 'utf-8')
		# b[158] = 10
		ser.write(bytes(str(message), 'utf-8'))# time.sleep(1)
		ser.flushOutput()
		time.sleep(1)
