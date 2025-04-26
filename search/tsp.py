import numpy as np
import matplotlib.pyplot as plt
import random
import time

CHROMOSOME_SIZE = 38  # 染色体大小，即一个染色体的基因数 = 城市数 = N
POPULATION_SIZE = 400 # 种群大小，即一个种群中的染色体数 ≈ 5N∼10N
CROSSOVER_RATE = 0.7  # 交叉率
MUTATION_RATE = 0.3   # 变异率
GENERATIONS = 1000    # 迭代次数

# 读取TSP数据集
def read_tsp_file(filename):
    """
    读取TSP文件格式的数据
    格式:
        NAME: <name>
        TYPE: TSP
        DIMENSION: <n>
        EDGE_WEIGHT_TYPE: EUC_2D
        NODE_COORD_SECTION
        1 x1 y1
        2 x2 y2
        ...
        n xn yn
        EOF
    """
    cities = []
    with open(filename, 'r') as f:
        # 跳过文件头直到NODE_COORD_SECTION
        line = f.readline()
        while line.strip() != "NODE_COORD_SECTION":
            line = f.readline()
        
        # 读取城市坐标
        line = f.readline()
        while line.strip() != "EOF":
            parts = line.strip().split()
            cities.append((float(parts[1]), float(parts[2])))
            line = f.readline()
    return cities


# 初始化种群
def init_population():
    population = []
    for _ in range(POPULATION_SIZE):
        chromosome = list(range(CHROMOSOME_SIZE))
        random.shuffle(chromosome)
        population.append(chromosome)
    return population

def distance(city1, city2):
    x1, y1 = city1
    x2, y2 = city2
    return np.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2)

# 适应度（与总路径长度呈现负相关）
def fitness(cities, path):
    total_distance = 0.0
    for i in range(CHROMOSOME_SIZE):
        j = (i + 1) % CHROMOSOME_SIZE
        total_distance += distance(cities[path[i]], cities[path[j]])
    return 1 / total_distance


# 选择父代
def selection(population, fitness_values):
    # 轮盘赌
    total_fitness = sum(fitness_values)
    probabilities = [fitness_value / total_fitness for fitness_value in fitness_values]

    cur = 0.0
    r = random.random()
    for chromosome, probability in zip(population, probabilities):
        cur += probability
        if cur >= r:
            return chromosome


# 交叉
# def crossover(parent1, parent2):
#     if random.random() > CROSSOVER_RATE:
#         return parent1, parent2
#     
#     # 顺序交叉
#     start, end = sorted(random.sample(range(CHROMOSOME_SIZE), 2))
#     child1 = [-1] * CHROMOSOME_SIZE
#     child2 = [-1] * CHROMOSOME_SIZE
#     child1[start:end + 1] = parent1[start:end + 1]
#     child2[start:end + 1] = parent2[start:end + 1]
#
#     def assign(parent, child):
#         pos = 0
#         for gene in parent:
#             if gene not in child:
#                 for i in range(pos, CHROMOSOME_SIZE):
#                     if child[i] == -1:
#                         child[i] = gene
#                         pos = i + 1
#                         break
#
#     assign(parent2, child1)
#     assign(parent1, child2)
#     return child1, child2
def crossover(parent1, parent2):
    # 构建邻接表
    adjacency = {city: set() for city in parent1}
    for i in range(CHROMOSOME_SIZE):
        for parent in [parent1, parent2]:
            left = parent[i-1] if i > 0 else parent[-1]
            right = parent[i+1] if i < CHROMOSOME_SIZE-1 else parent[0]
            adjacency[parent[i]].update({left, right})
    
    # 生成子代
    child = []
    current = random.choice([parent1[0], parent2[0]])
    while len(child) < CHROMOSOME_SIZE:
        child.append(current)
        # 移除当前城市的所有引用
        for neighbors in adjacency.values():
            if current in neighbors:
                neighbors.remove(current)
        # 概率化选择下一个城市
        if adjacency[current]:
            if random.random() < 0.8:
                next_city = min(adjacency[current], key=lambda x: len(adjacency[x]))
            else:
                next_city = random.choice(list(adjacency[current]))
        else:
            remaining = [c for c in parent1 if c not in child]
            next_city = random.choice(remaining) if remaining else None
        current = next_city
    return child


# 变异
def mutation(chromosome):
    if random.random() > MUTATION_RATE:
        return chromosome
    
    # 50%概率使用倒置变异，50%概率使用交换变异
    if random.random() < 0.5:
        start, end = sorted(random.sample(range(CHROMOSOME_SIZE), 2))
        chromosome[start:end+1] = chromosome[end:start-1:-1]
    else:
        i, j = random.sample(range(CHROMOSOME_SIZE), 2)
        chromosome[i], chromosome[j] = chromosome[j], chromosome[i]
    return chromosome


def two_opt(route, cities):
    improved = True
    while improved:
        improved = False
        for i in range(1, len(route)-1):
            for j in range(i+1, len(route)):
                # 计算交换前后的距离差
                a, b, c, d = route[i-1], route[i], route[j-1], route[j]
                before = distance(cities[a], cities[b]) + distance(cities[c], cities[d])
                after = distance(cities[a], cities[c]) + distance(cities[b], cities[d])
                if after < before:
                    route[i:j] = route[j-1:i-1:-1]
                    improved = True
    return route


# 遗传算法主函数
def genetic_algorithm(cities):
    population = init_population()

    most_best_fitness = 0.0
    best_solution = []
    for generation in range(GENERATIONS):
        fitness_values = [fitness(cities, chromosome) for chromosome in population]
        new_population = []
        for _ in range(POPULATION_SIZE // 2):
            parent1 = selection(population, fitness_values)
            parent2 = selection(population, fitness_values)
            child1 = crossover(parent1, parent2)
            parent3 = selection(population, fitness_values)
            parent4 = selection(population, fitness_values)
            child2 = crossover(parent3, parent4)
            new_population.extend([child1, child2])

        population = new_population
        if generation % 50 == 0:
            population = [two_opt(ind, cities) for ind in population]

        fitness_values = [fitness(cities, chromosome) for chromosome in population]
        best_fitness = max(fitness_values)
        # print(f"Generation {generation}: Best Fitness = {best_fitness}")

        if best_fitness > most_best_fitness:
            most_best_fitness = best_fitness
            best_index = fitness_values.index(best_fitness)
            best_solution = population[best_index]

    print(f"Best Solution: {best_solution}")
    print(f"Best Fitness = {most_best_fitness} Best Distance = {1 / most_best_fitness}")
    plot_solution(cities, best_solution, 1 / most_best_fitness)


def plot_solution(cities, path, distance):
    """
    可视化TSP解决方案路径
    :param cities: 城市坐标列表
    :param path: 城市访问顺序
    :param distance: 路径总距离
    """
    # 提取x和y坐标
    x = [cities[i][0] for i in path]
    y = [cities[i][1] for i in path]
    
    # 添加起点以闭合路径
    x.append(x[0])
    y.append(y[0])
    
    plt.figure(figsize=(10, 6))
    
    # 绘制路径
    plt.plot(x, y, 'o-', markersize=8, linewidth=1, label=f'Path (Distance: {distance:.2f})')
    
    # 标记城市编号
    for i, (xi, yi) in enumerate(cities):
        plt.text(xi, yi, str(i), fontsize=8, ha='center', va='center')
    
    # 设置图形属性
    plt.title('TSP Solution Path')
    plt.xlabel('X Coordinate')
    plt.ylabel('Y Coordinate')
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    cities = read_tsp_file("dj38.tsp")

    start_time = time.perf_counter()
    genetic_algorithm(cities)
    end_time = time.perf_counter()
    print(f"代码运行时间: {end_time - start_time:.6f} 秒")

