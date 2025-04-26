import numpy as np
import matplotlib.pyplot as plt
import scipy.signal as sg

# 差分方程系统分析
a_coeff = 0.2
b = [1]  # 分子系数
a = [1, -a_coeff]  # 分母系数

# 计算频率响应
w, h = sg.freqz(b, a, worN=512, whole=True)

# 绘制幅频和相频特性
plt.figure(figsize=(12, 5))

plt.rcParams['font.family']=['WenQuanYi Micro Hei'] # 显示中文
plt.rcParams['axes.unicode_minus']=False # 用来正常显示负号

plt.subplot(121)
plt.plot(w, 20*np.log10(np.abs(h)))
plt.title('幅频特性')
plt.xticks([-2*np.pi, -np.pi, 0, np.pi, 2*np.pi], ['-2π', '-π', '0', 'π', '2π'])
plt.ylabel('幅度 (dB)')
plt.grid()

plt.subplot(122)
plt.plot(w, np.angle(h))
plt.title('相频特性')
plt.xticks([-2*np.pi, -np.pi, 0, np.pi, 2*np.pi], ['-2π', '-π', '0', 'π', '2π'])
plt.ylabel('相位 (rad)')
plt.grid()

# 计算单位脉冲响应
n_imp = np.arange(0, 30)
imp = (a_coeff**n_imp) * (n_imp >= 0)  # 解析解

plt.figure()
plt.stem(n_imp, imp)
plt.title('单位脉冲响应h[n]')
plt.xlabel('n')
plt.grid()

plt.tight_layout()
plt.show()
