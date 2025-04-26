from heapq import heappush, heappop
from time import perf_counter
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

# 目标状态
goal = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,0]]

# 方向向量
dx = [1, -1, 0, 0]
dy = [0, 0, 1, -1]
dir_names = ['下', '上', '右', '左']  # 用于显示移动方向

def find_pos(board, num):
    """找到数字num在板子上的位置"""
    for i in range(4):
        for j in range(4):
            if board[i][j] == num:
                return (i, j)
    return (-1, -1)

# 预计算目标位置
goal_pos = {num: (i, j) for i, row in enumerate(goal) for j, num in enumerate(row)}

def heuristic(board):
    """计算启发式函数（曼哈顿距离 + 线性冲突）"""
    dist = 0
    rows = [[] for _ in range(4)]
    cols = [[] for _ in range(4)]

    # 计算曼哈顿距离
    for i in range(4):
        for j in range(4):
            num = board[i][j]
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

def A_star(initial_board):
    """使用A*算法求解15拼图"""
    open_set = []
    visited = set()
    parent = {}  # 记录父状态和移动信息
    
    initial_tuple = tuple(tuple(row) for row in initial_board)
    parent[initial_tuple] = (None, None, None)  # (父状态, 移动的数字, 方向)
    
    zero_i, zero_j = find_pos(initial_board, 0)
    heappush(open_set, (heuristic(initial_board), 0, zero_i, zero_j, 0, initial_board))
    visited.add(initial_tuple)
    
    while open_set:
        _, g, i, j, moved_num, current_board = heappop(open_set)
        current_tuple = tuple(tuple(row) for row in current_board)
        
        if current_board == goal:
            # 回溯路径
            path = []
            while current_tuple in parent and parent[current_tuple][0] is not None:
                prev_state, num, direction = parent[current_tuple]
                path.append((prev_state, num, direction))
                current_tuple = prev_state
            path.reverse()
            
            # 收集所有状态用于动画
            states = [initial_board]
            for state, num, dir in path:
                states.append([list(row) for row in state])
            states.append(goal)
            
            return states, path  # 返回所有状态和路径信息
        
        for direction in range(4):
            x = i + dx[direction]
            y = j + dy[direction]
            if 0 <= x < 4 and 0 <= y < 4:
                new_board = [list(row) for row in current_board]
                num = new_board[x][y]
                new_board[i][j], new_board[x][y] = new_board[x][y], new_board[i][j]
                new_tuple = tuple(tuple(row) for row in new_board)
                
                if new_tuple not in visited:
                    heappush(open_set, (heuristic(new_board) + g + 1, g + 1, x, y, num, new_board))
                    visited.add(new_tuple)
                    parent[new_tuple] = (current_tuple, num, direction)
    
    return None, None  # 无解

def IDA_star(initial_board):
    """使用IDA*算法求解15拼图"""
    initial_tuple = tuple(tuple(row) for row in initial_board)
    threshold = heuristic(initial_board)
    
    # 用于记录路径
    path = []
    parent = {initial_tuple: (None, None, None)}  # (父状态, 移动的数字, 方向)
    
    while True:
        # 每次迭代增加阈值
        result, new_threshold = dfs(initial_board, 0, threshold, path, parent)
        if result == "FOUND":
            # 构建状态序列
            states = [initial_board]
            current_tuple = tuple(tuple(row) for row in goal)
            path_info = []
            
            # 回溯路径
            while current_tuple in parent and parent[current_tuple][0] is not None:
                prev_state, num, direction = parent[current_tuple]
                path_info.append((prev_state, num, direction))
                current_tuple = prev_state
            path_info.reverse()
            
            # 构建状态序列
            for state, num, dir in path_info:
                states.append([list(row) for row in state])
            states.append(goal)
            
            return states, path_info
        elif result == float('inf'):
            return None, None  # 无解
        threshold = new_threshold

def dfs(board, g, threshold, path, parent):
    """深度优先搜索辅助函数"""
    h = heuristic(board)
    f = g + h
    
    if f > threshold:
        return f, f  # 超过阈值，返回新的阈值候选
    
    if board == goal:
        return "FOUND", threshold
    
    min_cost = float('inf')
    zero_i, zero_j = find_pos(board, 0)
    
    for direction in range(4):
        x = zero_i + dx[direction]
        y = zero_j + dy[direction]
        if 0 <= x < 4 and 0 <= y < 4:
            new_board = [list(row) for row in board]
            num = new_board[x][y]
            new_board[zero_i][zero_j], new_board[x][y] = new_board[x][y], new_board[zero_i][zero_j]
            new_tuple = tuple(tuple(row) for row in new_board)
            
            if new_tuple not in parent:
                parent[new_tuple] = (tuple(tuple(row) for row in board), num, direction)
                path.append((new_board, num, direction))
                
                # 递归搜索
                result, new_threshold = dfs(new_board, g + 1, threshold, path, parent)
                
                if result == "FOUND":
                    return "FOUND", threshold
                if new_threshold < min_cost:
                    min_cost = new_threshold
                
                # 回溯
                path.pop()
                del parent[new_tuple]
    
    return min_cost, min_cost

def create_animation(states):
    """创建拼图解法的动画"""
    fig, ax = plt.subplots(figsize=(6, 6))
    ax.set_xlim(0, 4)
    ax.set_ylim(0, 4)
    ax.set_xticks(np.arange(0, 5, 1))
    ax.set_yticks(np.arange(0, 5, 1))
    ax.grid(True)
    ax.set_title('15-Puzzle Solution')
    
    # 初始空图像
    patches = []
    for i in range(4):
        for j in range(4):
            num = states[0][i][j]
            if num != 0:
                rect = plt.Rectangle((j, 3-i), 1, 1, fill=True, edgecolor='black', facecolor='skyblue')
                ax.add_patch(rect)
                text = ax.text(j+0.5, 3-i+0.5, str(num), ha='center', va='center', fontsize=14)
                patches.append((rect, text))
    
    def update(frame):
        """更新动画帧"""
        for patch, text in patches:
            patch.remove()
            text.remove()
        patches.clear()
        
        for i in range(4):
            for j in range(4):
                num = states[frame][i][j]
                if num != 0:
                    rect = plt.Rectangle((j, 3-i), 1, 1, fill=True, edgecolor='black', facecolor='skyblue')
                    ax.add_patch(rect)
                    text = ax.text(j+0.5, 3-i+0.5, str(num), ha='center', va='center', fontsize=14)
                    patches.append((rect, text))
        
        ax.set_title(f'Step {frame}/{len(states)-1}')
        return patches
    
    ani = animation.FuncAnimation(fig, update, frames=len(states), interval=800, blit=False)
    plt.close()
    return ani

# 测试拼图
p1 = [[1,2,4,8],[5,7,11,10],[13,15,0,3],[14,6,9,12]]
p2 = [[14,10,6,0],[4,9,1,8],[2,3,5,11],[12,13,7,15]]
p3 = [[5,1,3,4],[2,7,8,12],[9,6,11,15],[0,13,10,14]]
p4 = [[6,10,3,15],[14,8,7,11],[5,1,0,2],[13,12,9,4]]
p5 = [[11,3,1,7],[4,6,8,2],[15,9,10,13],[14,12,5,0]]
p6 = [[0,5,15,14],[7,9,6,13],[1,2,12,10],[8,11,4,3]]

# 解决拼图
start_time = perf_counter()
solution_states, path = IDA_star(p6)
end_time = perf_counter()

if solution_states:
    print(f"找到解！总步数: {len(solution_states)-1}")
    print(f"求解时间: {end_time - start_time:.4f}秒")
    
    # 打印移动步骤
    print("\n移动步骤:")
    for step, (state, num, dir) in enumerate(zip(solution_states[:-1], [p[1] for p in path], [p[2] for p in path]), 1):
        print(f"步骤 {step}: 移动数字 {num} {dir_names[dir]}")
    
    # 创建动画
    ani = create_animation(solution_states)
    ani.save('puzzle_solution.gif', writer='pillow', fps=2)
else:
    print("无解")
