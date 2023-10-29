with open('input.txt', 'r') as f:
    f = f.readlines()

pairs: list = []
full_overlap_counter: int = 0
overlap_counter: int = 0

def convert_pair_to_int(pairs: list):
    new = []
    for i in pairs:
        new.append(int(i))
    return new

for i in f:
    assignments = convert_pair_to_int(i.strip().replace('-', ',').split(','))
    pair1, pair2 = assignments[0:2], assignments[2::]

    # Test for no overlap
    if (
        ((pair2[0] > pair1[1]) or (pair1[0] > pair2[1]))         
    ):
        continue
    # Test for complete overlap
    elif (
        ((pair1[0] >= pair2[0]) and (pair1[1] <= pair2[1])) or
        ((pair2[0] >= pair1[0]) and (pair2[1] <= pair1[1]))
    ):
        full_overlap_counter += 1
        overlap_counter += 1
    # Everything else will be partial overlap
    else:
        overlap_counter += 1

        
print(full_overlap_counter, overlap_counter)


