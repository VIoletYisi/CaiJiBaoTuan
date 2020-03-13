#%%
matrix_list=[[1,2,3],[4,5,6],[7,8,9]]
matrix_1 = []
for row_1 in matrix_list:
    matrix_1.append(row_1[-1])
print(matrix_1)

#%%
matrix_2=[]
for row_2 in matrix_list:
    value = row_2[1]
    matrix_2.append(2*value**2)
print(matrix_2)


# %%
import numpy as np

x = np.ones((8,8))
x[1:-1,1:-1] = 0
print(x)

# %%
y = np.ones((8,8))
y[::2,1::2] = 0
y[1::2,::2] = 0
print(y)


# %%
c = np.arange(2,50,5)
c[c%3!=0] = -c[c%3!=0]
print(c)

# %%
total = {'x' : x,'y' : y,'c' : c}
np.set_printoptions(precision=2)
for i, k in total.items():
    print(f'''matrix name is : {i}\n
    size:\t{k.size}\n
    shape:\t{k.shape}\n
    mean:\t{k.mean(0)}\n
    std:\t{k.std(0)}\n''')

# %%
import math as mt
a = [3, 4, 5, 100, 10000, 1000000]
print('n\tp\t\t\t' + 'n p')
for j in range(3):
    p_1 = a[j] * mt.sqrt((0.25 + 0.25 - 2 * 0.5 * 0.5 * mt.cos(2 * mt.pi / a[j])))
    p_2 = a[3+j] * mt.sqrt((0.25 + 0.25 - 2 * 0.5 * 0.5 * mt.cos(2 * mt.pi / a[3+j])))
    print('{:}\t{:.11f}'.format(a[j],p_1) + '{:>12} {:<.11f}'.format(a[j+3],p_2))

# %%
import matplotlib.pyplot as plt

n = np.linspace(0, 1000000, 1000)
p = n * np.sqrt(0.25 + 0.25 - 2 * 0.5 * 0.5 * np.cos(2 * np.pi / n))
plt.plot(n,p)

# %%
np.set_printoptions(precision=8)
y = np.empty((1,21))
t = np.empty((1,21))
y[0,0] = 10
t[0,0] = 0
for i in range(0,30):
    y[0,i + 1] = (y[0,i] - 0.5)
    t[0,i + 1] = mt.sqrt(2 * (10 - y[0,i + 1]) / 9.8) 
    if y[0,i + 1] == 0:
        break
    else:
        continue
print(y)
print(t)
list(zip(t,y))
# %%
v_average = np.zeros((1,20))
for i in range(20):
    v_average[0, i] = (y[0,i] - y[0,i + 1]) / (t[0,i + 1] - t[0,i])
print(v_average)

# %%
t_mid = np.zeros((1,20))
a_average = np.zeros((1,19)) 
for i in range(20):
    t_mid[0,i] = (t[0,i] + t[0,i + 1]) / 2

for i in range(19):
    a_average[0,i] = (v_average[0,i + 1] - v_average[0,i]) / (t_mid[0,i + 1] - t_mid[0,i]) 
print(a_average)

# %%
t = np.arange(0, 1.5, 0.2)
v = 9.8 * t
plt.plot(t,v)


# %%
t = np.arange(0, 1.5, 0.2)
a = 9.8+0 * t
plt.plot(t,a)

# %%
