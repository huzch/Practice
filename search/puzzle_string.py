from heapq import heappush, heappop
from time import perf_counter

cur = "01020304050607080910111200131415"
goal = "01020304050607080910111213141500"
dx = [1, -1, 0, 0]
dy = [0, 0, 1, -1]
n = 4
m = 4


def h(st):
    dist = 0
    rows = [[] for _ in range(n)]  # 记录每行的(当前列, 目标列)
    cols = [[] for _ in range(n)]  # 记录每列的(当前行, 目标行)
    
    # 第一次遍历：计算曼哈顿距离，并记录行列信息
    for pos in range(0, n*m*2, 2):
        grid_pos = pos // 2
        i, j = grid_pos // m, grid_pos % m
        num = st[pos:pos+2]
        
        if num == "00":  # 空格不计距离
            continue
            
        # 在目标状态中找到该数字的位置
        gpos = goal.find(num)
            
        ggrid_pos = gpos // 2
        gi, gj = ggrid_pos // m, ggrid_pos % m
        
        # 曼哈顿距离
        dist += 1.7 * (abs(i - gi) + abs(j - gj))
        
        # 记录行列冲突信息
        if i == gi:  # 同一行
            rows[i].append((j, gj))
        if j == gj:  # 同一列
            cols[j].append((i, gi))
    
    # 第二次遍历：计算线性冲突
    for i in range(n):
        # 行冲突检测
        row = rows[i]
        for a in range(len(row)):
            for b in range(a+1, len(row)):
                aj, agj = row[a]
                bj, bgj = row[b]
                if (aj < bj and agj > bgj) or (aj > bj and agj < bgj):
                    dist += 2  # 每对冲突额外+2
    
    for j in range(n):
        # 列冲突检测
        col = cols[j]
        for a in range(len(col)):
            for b in range(a+1, len(col)):
                ai, agi = col[a]
                bi, bgi = col[b]
                if (ai < bi and agi > bgi) or (ai > bi and agi < bgi):
                    dist += 2
    
    return dist

def A_star(puzzle):
    open = []
    vis = set()

    pos = puzzle.find("00")
    heappush(open, (h(puzzle), 0, pos, puzzle))
    vis.add(puzzle)
    while open:
        _, g, pos, st = heappop(open)
        if st == goal:
            print(f"{g} ")
            return

        grid_pos = pos // 2  # 转换为网格坐标（0, 1, 2,...）
        i, j = grid_pos // m, grid_pos % m
        for k in range(n):
            x = i + dx[k]
            y = j + dy[k]
            if 0 <= x < n and 0 <= y < m:
                tpos = x * m + y # 转换为网格坐标（0, 1, 2,...）
                tpos *= 2
                tmp = list(st)
                tmp[pos:pos+2], tmp[tpos:tpos+2] = tmp[tpos:tpos+2], tmp[pos:pos+2]
                newst = "".join(tmp)
                if newst not in vis:
                    heappush(open, (h(newst) + g + 1, g + 1, tpos, newst))
                    vis.add(newst)


p1 = "01020408050711101315000314060912"  # [[1,2,4,8],[5,7,11,10],[13,15,0,3],[14,6,9,12]]
p2 = "14100600040901080203051112130715"  # [[14,10,6,0],[4,9,1,8],[2,3,5,11],[12,13,7,15]]
p3 = "05010304020708120906111500131014"  # [[5,1,3,4],[2,7,8,12],[9,6,11,15],[0,13,10,14]]
p4 = "06100315140807110501000213120904"  # [[6,10,3,15],[14,8,7,11],[5,1,0,2],[13,12,9,4]]
p5 = "11030107040608021509101314120500"  # [[11,3,1,7],[4,6,8,2],[15,9,10,13],[14,12,5,0]]
p6 = "00051514070906130102121008110403"  # [[0,5,15,14],[7,9,6,13],[1,2,12,10],[8,11,4,3]]

start_time = perf_counter()
A_star(p2)
end_time = perf_counter()
print(f"代码运行时间: {end_time - start_time:.6f} 秒")
