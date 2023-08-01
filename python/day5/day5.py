stacks: list = []
moves: list = []       # [number of crates, from, to]

# Read in initial stacks
with open('input.txt', 'r') as f:
    raw_stacks, raw_moves = f.read().split('\n\n')

# Make stack input usable
raw_stacks = raw_stacks.replace('    ', '[ ]').replace(' ', '').replace('][', '] [')
rows = raw_stacks.split('\n')

# Make move input usable
raw_moves = raw_moves.split('\n')

for move in raw_moves:
    move = move.replace('move ', ' ')
    move = move.replace(' from ', ' ')
    move = move. replace(' to ', ' ')

    count, move_from, move_to = move.split()
    moves.append([int(count), (int(move_from) - 1), (int(move_to) - 1)])
   
# Remove row labels
rows.pop()

# Create all stacks
for _ in rows[0].split(' '):
    stacks.append([])

# Fill Stacks
for row in rows[::-1]:
    row = row.split(' ')
    for stack_number, crate in enumerate(row):
        if crate == '[]':
            continue
        else:
            stacks[stack_number].append(crate)

print(stacks)

# Move Crates
def move_crates1(moves: list, stacks: list) -> None:
    for move in moves:
        for i in range(move[0]):
            stacks[move[2]].append(stacks[move[1]].pop())

    # Get answer (top crate, each stack)
    for i in stacks:
        print(i[-1].strip('[]'), end='')

def move_crates2(moves: list, stacks: list) -> None:
    for move in moves:
        moving_crates = []
        for i in range(move[0]):
            moving_crates.append(stacks[move[1]].pop())

        for i in moving_crates[::-1]:
            stacks[move[2]].append(i)

    # Get answer (top crate, each stack)
    for i in stacks:
        print(i[-1].strip('[]'), end='')

move_crates2(moves, stacks)