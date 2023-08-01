def convert_to_matrix(input_file: list[str]) -> list[list[int]]:

    """Convert input list into a matrix, with each 'cell' containing exactly 1 value"""

    matrix: list = []

    for _ in input_file:
        row = [[int(tree)] for tree in _.strip()]
        matrix.append(row)

    return matrix

def check_all_cells(grid: list[list]) -> int:

    visible_trees: int = 0
    width: int = len(grid[0])
    height: int = len(grid)

    def scan(x: int, y: int):

        tree_height: int = grid[y][x]
        offset: int = 1
        left = right = up = down = 'scanning'
        right_offset = down_offset = 0
        scenic_score = 1

        while True:

            left_offset = x - offset
            right_offset = x + offset
            up_offset = y - offset
            down_offset = y + offset

            if not left and not right and not up and not down:
                return False, scenic_score
            if 'scanning' not in (left, right, up, down):
                return True, scenic_score

            if left_offset >= 0 and grid[y][left_offset] >= tree_height and left == 'scanning':
                scenic_score *= offset
                left = False
            elif left_offset == 0 and grid[y][left_offset] < tree_height and left == 'scanning':
                scenic_score *= offset
                left = True

            if right_offset <= width - 1 and grid[y][right_offset] >= tree_height and right == 'scanning':
                scenic_score *= offset
                right = False
            elif right_offset == width - 1 and grid[y][right_offset] < tree_height and right == 'scanning':
                scenic_score *= offset
                right = True

            if up_offset >= 0 and grid[up_offset][x] >= tree_height and up == 'scanning':
                scenic_score *= offset
                up = False
            elif up_offset == 0 and grid[up_offset][x] < tree_height and up == 'scanning':
                scenic_score *= offset
                up = True

            if down_offset <= height - 1 and grid[down_offset][x] >= tree_height and down == 'scanning':
                scenic_score *= offset
                down = False
            elif down_offset == height - 1 and grid[down_offset][x] < tree_height and down == 'scanning':
                scenic_score *= offset
                down = True

            offset += 1

    scenic_scores: list = []

    for y in range(width):
        for x in range(height):
            if x == 0 \
                    or y == 0 \
                    or x == width - 1 \
                    or y == height - 1:
                
                visible_trees += 1

            else:
                visible, score = scan(x, y)
                if visible:
                    visible_trees += 1
                # print(f'({x}, {y}): {score}')
                scenic_scores.append(score)
                
    return visible_trees, max(scenic_scores)

if __name__ == '__main__':

    with open('input.txt', 'r') as input_file:
        input_file = input_file.readlines()

    print(check_all_cells(convert_to_matrix(input_file)))