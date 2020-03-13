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
