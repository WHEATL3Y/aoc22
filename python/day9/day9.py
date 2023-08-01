def move_head(direction: str, distance: int):
    pass

if __name__ == '__main__':
    with open('input.txt', 'r') as file:
        file = file.readlines()

file = [
    (instruction.strip().split()[0], int(instruction.strip().split()[1]))
    for instruction in file
]

print(file)