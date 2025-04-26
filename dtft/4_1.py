import numpy as np
import matplotlib.pyplot as plt
import scipy.signal as sg

def DTFT(xn, n0=0, a=-2*np.pi, b=2*np.pi):
    num = np.array(xn)
    den = np.array([1])
    ws, Hw = sg.freqz(num, a=den, whole=True, worN=np.linspace(a, b, 512))
    return ws, Hw/np.exp(-1j*ws*n0)

# 双边指数衰减信号
n = np.arange(-16, 17)
x = np.exp(-2*np.abs(n))

# 内插信号(k=3)
k = 3
xk = np.zeros(len(n)*k)
xk[::k] = x  # 每隔k点取x的值，其余为零

# 计算DTFT
n0_x = len(n[n<0])
w_x, Xw = DTFT(x, n0_x)

n0_xk = len(xk[np.arange(len(xk)) < (len(xk)//2)])
w_xk, Xkw = DTFT(xk, n0_xk)

# 绘制结果
plt.figure(figsize=(12, 10))

plt.rcParams['font.family']=['WenQuanYi Micro Hei'] # 显示中文
plt.rcParams['axes.unicode_minus']=False # 用来正常显示负号

# 原始信号及其频谱
plt.subplot(321)
plt.stem(n, x)
plt.title(r'原始信号 $x[n]$')
plt.grid()

plt.subplot(322)
plt.plot(w_x, np.abs(Xw))
plt.title(r'$|X(e^{j\omega})|$')
plt.xticks(
    [-2*np.pi, -np.pi, 0, np.pi, 2*np.pi],
    [r'$-2\pi$', r'$-\pi$', r'$0$', r'$\pi$', r'$2\pi$']
)
plt.grid()

plt.subplot(323)
plt.plot(w_x, np.angle(Xw))
plt.title(r'$\angle X(e^{j\omega})$')
plt.xticks(
    [-2*np.pi, -np.pi, 0, np.pi, 2*np.pi],
    [r'$-2\pi$', r'$-\pi$', r'$0$', r'$\pi$', r'$2\pi$']
)
plt.grid()

# 内插信号及其频谱
plt.subplot(324)
plt.stem(np.arange(len(xk)), xk)
plt.title(rf'内插信号 $x[{k}n]$')
plt.grid()

plt.subplot(325)
plt.plot(w_xk, np.abs(Xkw))
plt.title(rf'$|X_k(e^{{j\omega}})|\quad (k={k})$')
plt.xticks(
    [-2*np.pi, -np.pi, 0, np.pi, 2*np.pi],
    [r'$-2\pi$', r'$-\pi$', r'$0$', r'$\pi$', r'$2\pi$']
)
plt.grid()

plt.subplot(326)
plt.plot(w_xk, np.angle(Xkw))
plt.title(rf'$\angle X_k(e^{{j\omega}})\quad (k={k})$')
plt.xticks(
    [-2*np.pi, -np.pi, 0, np.pi, 2*np.pi],
    [r'$-2\pi$', r'$-\pi$', r'$0$', r'$\pi$', r'$2\pi$']
)
plt.grid()

plt.tight_layout()
plt.show()
