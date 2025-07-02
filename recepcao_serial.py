import serial

ser = serial.Serial(port="/dev/ttyUSB0", baudrate=115200)

ser.reset_input_buffer()

print("Escutando")

while True:
    char = ser.read()
    print(char.decode('utf-8'))
    print(char)

