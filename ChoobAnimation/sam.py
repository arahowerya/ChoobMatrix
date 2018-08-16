import serial
import time
import binascii


with serial.Serial('/dev/tty.usbserial-FTGYVTNL', 57600, timeout=10) as ser:
            # with serial.Serial('/dev/ttyUSB0', 115200, timeout=10) as ser:
	message = "26 26 26 26 26 26 26 26 26 26 26 26 26 26 26 26 26 26 26 26 26 26 26 26 26 26 \n"
	# "{:<159}".format(message)
	# b = bytearray(message, 'utf-8')
	# b[158] = 10
	ser.write(bytes(str(message), 'utf-8'))# time.sleep(1)
	ser.flushOutput()
	time.sleep(1)

3.
