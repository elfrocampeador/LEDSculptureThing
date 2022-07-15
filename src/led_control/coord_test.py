strip_lengths = [10, 10, 10, 10, 10]
strip_start_addresses = [0, 0, 0, 0, 0]
num_strips = 5
longest_strip_length = 10

def GetLED(x, y):
    column_max = strip_lengths[x] + strip_start_addresses[x]
    column_start = 0
    true_y = y - strip_start_addresses[x]

    is_even = x % 2
    
    if y < strip_start_addresses[x] or y > column_max:
        return None
    
    for i in range(0, x, 1):
        column_start += strip_lengths[i]
    
    led_index = 0;
    if is_even != 0:
        led_index = ((column_start + strip_lengths[x]) - strip_start_addresses[x]) - y - 1
    else:
        led_index = column_start + y

    
    return led_index
    

for x in range(0, 5, 1):
    line = []
    for y in range(0, 10, 1):
        index = GetLED(x, y)
        line.append(index)
    print("{}".format(line))
    line = []