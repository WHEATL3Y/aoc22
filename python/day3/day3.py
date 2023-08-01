LOWERCASE_OFFSET = -96
UPPERCASE_OFFSET = -38
priority_sum: int = 0

with open('input.txt', 'r') as f:
    f = f.readlines()

for rucksack in f:
    compartment1, compartment2 = rucksack[:(len(rucksack) // 2)], rucksack[(len(rucksack) // 2):]
    for i in compartment1:
        if i in compartment2 and i.isupper():
            priority = ord(i) + UPPERCASE_OFFSET
            priority_sum += priority
            break
        elif i in compartment2 and i.islower():
            priority = ord(i) + LOWERCASE_OFFSET
            priority_sum += priority
            break

print(priority_sum)
slice_counter: int = 0
priority_sum: int = 0

while (slice_counter + 3) <= len(f):
    group = f[slice_counter:(slice_counter + 3)]
    for i in group[0]:
        if i in group[1] and i in group[2] and i.isupper():
            priority = ord(i) + UPPERCASE_OFFSET
            priority_sum += priority
            break
        elif i in group[1] and i in group[2] and i.islower():
            priority = ord(i) + LOWERCASE_OFFSET
            priority_sum += priority
            break

    slice_counter += 3

print(priority_sum)