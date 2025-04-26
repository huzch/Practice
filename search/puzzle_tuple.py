from heapq import heappush, heappop
from time import perf_counter

cur = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[0,13,14,15]]
goal = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,0]]
dx = [1, -1, 0, 0]
dy = [0, 0, 1, -1]

def find(a, x):
    for i in range(4):
        for j in range(4):
            if a[i][j] == x:
                return (i, j)
    return (-1, -1)

# 预计算目标位置
goal_pos = {num: (i, j) for i, row in enumerate(goal) for j, num in enumerate(row)}

def h(st):
    dist = 0
    rows = [[] for _ in range(4)]
    cols = [[] for _ in range(4)]

    # 计算曼哈顿距离
    for i in range(4):
        for j in range(4):
            num = st[i][j]
            if num == 0:
                continue
            x, y = goal_pos[num]
            if i == x:
                rows[i].append((j, y))
            if j == y:
                cols[j].append((i, x))
            dist += 1.7 * (abs(x - i) + abs(y - j))

    # 计算线性冲突
    # 行冲突
    for row in rows:
        n = len(row)
        for i in range(n):
            for j in range(i + 1, n):
                aj, ay = row[i]
                bj, by = row[j]
                if aj < bj and ay > by:
                    dist += 2
    # 列冲突
    for col in cols:
        m = len(col)
        for i in range(m):
            for j in range(i + 1, m):
                ai, ax = col[i]
                bi, bx = col[j]
                if ai < bi and ax > bx:
                    dist += 2

    return dist

def A_star(puzzle):
    open = []
    vis = set()

    a, b = find(puzzle, 0)
    heappush(open, (h(puzzle), 0, a, b, 0, puzzle))
    puzzle_tuple = tuple(tuple(row) for row in puzzle)
    vis.add(puzzle_tuple)
    while open:
        _, g, a, b, x, st = heappop(open)
        # print(f"{x} ")
        if st == goal:
            print(f"{g} ")
            return

        for k in range(4):
            x = a + dx[k]
            y = b + dy[k]
            if 0 <= x <= 3 and 0 <= y <= 3:
                tmp = [list(row) for row in st]
                num = tmp[x][y]
                tmp[a][b], tmp[x][y] = tmp[x][y], tmp[a][b]
                tmp_tuple = tuple(tuple(row) for row in tmp)
                if tmp_tuple not in vis:
                    heappush(open, (h(tmp) + g + 1, g + 1, x, y, num, tmp))
                    vis.add(tmp_tuple)

p1 = [[1,2,4,8],[5,7,11,10],[13,15,0,3],[14,6,9,12]]
p2 = [[14,10,6,0],[4,9,1,8],[2,3,5,11],[12,13,7,15]]
p3 = [[5,1,3,4],[2,7,8,12],[9,6,11,15],[0,13,10,14]]
p4 = [[6,10,3,15],[14,8,7,11],[5,1,0,2],[13,12,9,4]]
p5 = [[11,3,1,7],[4,6,8,2],[15,9,10,13],[14,12,5,0]]
p6 = [[0,5,15,14],[7,9,6,13],[1,2,12,10],[8,11,4,3]]

start_time = perf_counter()
A_star(p2)
end_time = perf_counter()
print(f"代码运行时间: {end_time - start_time:.6f} 秒")
