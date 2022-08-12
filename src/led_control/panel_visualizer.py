import serial
from PIL import Image, ImageDraw

serial_handle = serial.Serial(port='COM3', baudrate=57600, timeout=5)

image = Image.new(mode = 'RGB', size = (9, 29))
pixels = image.load()
y = 0

while True:
    line = str(serial_handle.readline())
    
    if line == 'PANELDUMP':
        y = 0
    else:
        tokens = line.split(" ") # Split on spaces
        
        x = 0
        for token in tokens:
            color_values = token.split("|")
            print("{}".format(token))
            try:
                pixels[x, y] = (color_values[0], color_values[1], color_values[2])
                x += 1
            except:
                print("!")
    y += 1
    image.show()  