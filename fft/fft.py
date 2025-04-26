import numpy as np
import matplotlib.pyplot as plt
from math import cos, sin, pi

def fft(a, invert=False):
    n = len(a)
    if n == 1:
        return a
    a0 = fft(a[::2], invert)
    a1 = fft(a[1::2], invert)
    ang = 2 * pi / n * (-1 if invert else 1)
    w, wn = 1, complex(cos(ang), sin(ang))
    a = [0] * n
    for i in range(n//2):
        a[i] = a0[i] + w * a1[i]
        a[i + n//2] = a0[i] - w * a1[i]
        if invert:
            a[i] /= 2
            a[i + n//2] /= 2
        w *= wn
    return a

# 待插值函数
def f(x):
    return x**2 * np.cos(x)

# 参数设置
N = 32       # 采样点数（需为 2 的幂）

# 采样
x_samples = np.linspace(-pi, pi, N, endpoint=False)
y_samples = f(x_samples)

# 利用IFFT计算插值多项式的系数
coeffs = fft(y_samples, invert=True)

# 三角插值多项式
def p(x):
    result = np.zeros_like(x, dtype=complex)
    # 将[-pi,pi]映射到[0,2*pi]
    x = (x + pi) % (2 * pi)
    # 正负频率合一
    for k in range(-N//2, N//2):
        result += coeffs[k] * np.exp(1j * k * x)
    # # 正频率分量
    # for k in range(N//2):
    #     result += coeffs[k] * np.exp(1j * k * x)
    # # 负频率分量
    # for k in range(N//2, N):
    #     result += coeffs[k] * np.exp(1j * (k - N) * x)
    return result.real

# 绘图
x_fine = np.linspace(-pi, pi, 1000)
plt.figure(figsize=(10, 6))
plt.plot(x_fine, f(x_fine), label="True function: $f(x) = x^2 \cos(x)$", color='blue')
plt.plot(x_fine, p(x_fine), label=f"{N}-term interpolation", linestyle='--', color='red')
plt.scatter(x_samples, y_samples, color='green', label="Sampling points")
plt.xlabel("x")
plt.ylabel("f(x)")
plt.legend()
plt.grid()
plt.show()
