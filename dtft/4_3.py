import numpy as np
import matplotlib.pyplot as plt
import scipy.signal as sg

# 设置中文显示和字体
plt.rcParams['font.family']=['WenQuanYi Micro Hei']
plt.rcParams['axes.unicode_minus'] = False

# 定义DTFT函数
def DTFT(xn, n0=0, a=-2*np.pi, b=2*np.pi):
    num = np.array(xn)
    den = np.array([1])
    ws, Hw = sg.freqz(num, a=den, whole=True, worN=np.linspace(a, b, 512))
    return ws, Hw/np.exp(-1j*ws*n0)

# 定义双边指数信号
n = np.arange(-16, 17)
x = np.exp(-2*np.abs(n))
n0 = len(n[n<0])  # 信号起始点n=0的位置

# 1. 计算DTFT和频域乘积
w, Xw = DTFT(x, n0)  # 计算x[n]的DTFT
Yw = Xw * Xw  # 频域相乘得到Y(e^jω)

# 2. 频域方法：通过逆DTFT计算y[n]
y_freq = np.zeros_like(n, dtype=complex)
for i in range(len(n)):
    y_freq[i] = np.trapz(Yw * np.exp(1j*w*n[i]), w) / (2*np.pi)
y_freq = np.real(y_freq)  # 取实数部分

# 3. 时域方法：直接卷积计算
y_time = np.convolve(x, x, mode='same')  # 保持输出长度与输入相同

# 创建画布
plt.figure(figsize=(15, 10))

# 子图1：原始信号x[n]
plt.subplot(3, 2, 1)
plt.stem(n, x, linefmt='b-', markerfmt='bo', basefmt=' ')
plt.title(r'(a) 原始信号 $x[n] = e^{-2|n|}$')
plt.xlabel(r'$n$')
plt.grid()

# 子图2：|Y(e^jω)| 幅频特性
plt.subplot(3, 2, 2)
plt.plot(w, np.abs(Yw))
plt.title(r'(b) 频域响应 $|Y(e^{j\omega})| = |X(e^{j\omega})|^2$')
plt.xticks(
    [-2*np.pi, -np.pi, 0, np.pi, 2*np.pi], 
    [r'$-2\pi$', r'$-\pi$', r'$0$', r'$\pi$', r'$2\pi$']
)
plt.xlabel(r'$\omega$')
plt.grid()

# 子图3：频域方法得到的y[n]
plt.subplot(3, 2, 3)
plt.stem(n, y_freq, linefmt='g-', markerfmt='go', basefmt=' ')
plt.title('(c) 频域方法得到的 y[n]')
plt.xlabel('n')
plt.grid()

# 子图4：时域方法得到的y[n]
plt.subplot(3, 2, 4)
plt.stem(n, y_time, linefmt='m-', markerfmt='mo', basefmt=' ')
plt.title('(d) 时域卷积得到的 y[n]')
plt.xlabel('n')
plt.grid()

# 子图5：两种方法比较
plt.subplot(3, 2, 5)
plt.stem(n, y_freq, linefmt='b-', markerfmt='bo', basefmt=' ', label='频域方法')
plt.stem(n, y_time, linefmt='r--', markerfmt='rx', basefmt=' ', label='时域方法')
plt.title('(e) 两种方法结果比较')
plt.xlabel('n')
plt.legend()
plt.grid()

# 子图6：误差分析
plt.subplot(3, 2, 6)
error = np.abs(y_freq - y_time)
plt.stem(n, error, linefmt='r-', markerfmt='ro', basefmt=' ')
plt.title('(f) 两种方法差异')
plt.xlabel('n')
plt.ylabel('绝对误差')
plt.grid()

plt.tight_layout()
plt.show()
