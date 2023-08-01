# A, X = Rock (1 Point)
# B, Y = Paper (2 Points)
# C, Z = Scissors (3 Points)

WIN_MAP = {'A': 'Y', 'B': 'Z', 'C': 'X'}
DRAW_MAP = {'A': 'X', 'B': 'Y', 'C': 'Z'}
LOSS_MAP = {'A': 'Z', 'B': 'X', 'C': 'Y'}
POINT_MAP = {'X': 1, 'A': 1, 'Y': 2, 'B': 2, 'Z': 3, 'C': 3}
score: int = 0
score1: int = 0

with open('input.txt', 'r') as f:
    games: list = f.readlines()

games = [_.split() for _ in games]

for game in games:
    if WIN_MAP[game[0]] == game[1]:
        score += (POINT_MAP[game[1]] + 6)
    elif DRAW_MAP[game[0]] == game[1]:
        score += (POINT_MAP[game[1]] + 3)
    else:
        score += (POINT_MAP[game[1]])

    match game[1]:
        case 'Z':       # Win
            score1 += (POINT_MAP[WIN_MAP[game[0]]] + 6)
        case 'Y':       # Draw
            score1 += (POINT_MAP[DRAW_MAP[game[0]]] + 3)
        case 'X':       # Lose
            score1 += (POINT_MAP[LOSS_MAP[game[0]]])

print(score, score1)