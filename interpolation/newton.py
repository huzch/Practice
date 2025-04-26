x = [0.2, 0.4, 0.6, 0.8, 1.0]
y = [0.98, 0.92, 0.81, 0.64, 0.38]

def newton_interpolation(x, y, xi):
    n = len(y)
    divided_diff = y.copy() # 初始化差商表
    # 枚举阶数
    for j in range(1, n):
        # 计算每阶差商时原地更新(从后往前，防止被覆盖)
        for i in range(n - 1, j - 1, -1):
            divided_diff[i] = (divided_diff[i] - divided_diff[i - 1]) / (x[i] - x[i - j])

    m = len(xi)
    yi = [0.0] * m
    for k in range(m):
        for i in range(n):
            term = divided_diff[i]
            for j in range(i):
                term *= (xi[k] - x[j])
            yi[k] += term

    return yi

import numpy as np

# xi = [0.20, 0.28, 1.00, 1.08]
xi = np.linspace(0, 2, 100)
yi = newton_interpolation(x, y, xi)

import matplotlib.pyplot as plt
# 绘制图像
plt.figure(figsize=(10, 6))
plt.plot(x, y, 'o', label='Data Points')
plt.plot(xi, yi, label='Newton Interpolation')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Interpolation Comparison')
plt.legend()
plt.grid(True)
plt.show()
