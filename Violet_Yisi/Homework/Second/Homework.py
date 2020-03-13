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
