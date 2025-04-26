x = [0.2, 0.4, 0.6, 0.8, 1.0]
y = [0.98, 0.92, 0.81, 0.64, 0.38]

import numpy as np

def calc(y, h, M, i, dx):
    a = y[i]
    b = (y[i + 1] - y[i]) / h[i] - h[i] * (M[i + 1] + 2 * M[i]) / 6
    c = M[i] / 2
    d = (M[i + 1] - M[i]) / (6 * h[i])
    return a + b * dx + c * dx**2 + d * dx**3
        
def spline_interpolation(x, y, xi):
    n = len(x)
    # 区间长度
    h = np.diff(x)
    # 初始化矩阵
    A = np.zeros((n, n))
    b = np.zeros(n)
    # 填充矩阵
    for i in range(1, n - 1):
        A[i, i - 1] = h[i - 1]
        A[i, i] = 2 * (h[i - 1] + h[i])
        A[i, i + 1] = h[i]
        b[i] = 6 * ((y[i + 1] - y[i]) / h[i] - (y[i] - y[i - 1]) / h[i - 1])
    # 自然边界
    A[0, 0] = 2
    A[-1, -1] = 2
    # 求解线性方程组
    M = np.linalg.solve(A, b)

    # m = len(xi)
    # yi = [0.0] * m
    # for k in range(m):
    #     for i in range(n - 1):
    #         if x[i] <= xi[k] <= x[i + 1]:
    #             yi[k] = calc(x, y, h, M, i, xi[k])
    #             break

    m = len(xi)
    yi = [0.0] * m
    # 计算插值点区间的坐标i
    indices = np.searchsorted(x, xi) - 1
    # 将插值点限制在有效区间内，处理异常插值点
    indices = np.clip(indices, 0, n-2)
    for k, i in enumerate(indices):
        dx = xi[k] - x[i]
        yi[k] = calc(y, h, M, i, dx)

    return yi

# xi = [0.20, 0.28, 1.00, 1.08]
xi = np.linspace(0, 2, 100)
yi = spline_interpolation(x, y, xi)

import matplotlib.pyplot as plt
# 绘制图像
plt.figure(figsize=(10, 6))
plt.plot(x, y, 'o', label='Data Points')
plt.plot(xi, yi, label='Spline Interpolation')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Interpolation Comparison')
plt.legend()
plt.grid(True)
plt.show()
