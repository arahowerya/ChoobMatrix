import serial
import time
import binascii


with serial.Serial('/dev/tty.usbserial-FTGYVTNL', 57600, timeout=10) as ser:
            # with serial.Serial('/dev/ttyUSB0', 115200, timeout=10) as ser:
	message = "31415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174\n"
	# "{:<159}".format(message)
	# b = bytearray(message, 'utf-8')
	# b[158] = 10
	ser.write(bytes(str(message), 'utf-8'))# time.sleep(1)
	ser.flushOutput()
	time.sleep(1)

3.
