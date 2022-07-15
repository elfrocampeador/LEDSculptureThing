strip_lengths = [10, 12, 15, 12, 10]
strip_start_addresses = [2, 1, 0, 1, 2]
num_strips = 5
longest_strip_length = 15

def GetLED(x, y):
    column_max = strip_lengths[x] + strip_start_addresses[x]
    column_start = 0
    true_y = y - strip_start_addresses[x]

    is_even = x % 2
    
    if y < strip_start_addresses[x] or y >= column_max:
        return None
    
    for i in range(0, x, 1):
        column_start += strip_lengths[i]

    led_index = 0;
    if is_even != 0:
        led_index = (column_start + strip_lengths[x] - 1) - (y - strip_start_addresses[x])
    else:
        led_index = column_start + (y - strip_start_addresses[x])

    
    return led_index
    

for x in range(0, num_strips, 1):
    line = []
    for y in range(0, longest_strip_length, 1):
        index = GetLED(x, y)
        line.append(index)
    print("{}".format(line))
    line = []