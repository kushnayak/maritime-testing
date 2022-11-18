import serial

with serial.Serial('/dev/ttyUSB0', 115200) as ser, open("dvl_data_1.txt", "r") as f:
    for l in f.readlines():
        print(l)
        ser.write(str.encode(l))
