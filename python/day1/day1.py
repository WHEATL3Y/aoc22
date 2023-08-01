with open('input.txt', 'r') as f:
    elves = f.read().split('\n\n')
    calorie_list = []

    for elf in elves:
        elf_cals = [int(cal) for cal in elf.split()]
        calorie_list.append(sum(elf_cals))

top3 = sorted(calorie_list)[-3::]
print(f'Max:\t{top3[-1]}\nTop 3:\t{sum(top3)}')