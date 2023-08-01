with open('input.txt', 'r') as f:
    f = f.read()

start_of_packet: list = []
looking_for_packet_start: bool = True
looking_for_message_start: bool = True
i = 0

while looking_for_packet_start:
    start_check = set([i for i in f[(0+i):(4+i)]])
    if len(start_check) == 4:
        packet_start_position = i + 4
        break
    else:
        i += 1

while looking_for_message_start:
    start_check = set([i for i in f[(0+i):(14+i)]])
    if len(start_check) == 14:
        message_start_position = i + 14
        break
    else:
        i += 1

print(packet_start_position, message_start_position)