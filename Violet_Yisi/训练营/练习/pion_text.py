#%%
import numpy as np
import matplotlib.pyplot as plt

# %%
data = np.loadtxt('pion_gamma15_p0_t0_1.txt')
print(data)
# %%
data_points = []
for i in range(32*100):
    data_points.append(data[i][7])
data_points = np.array(data_points)
data_points = np.reshape(data_points,(100,32))
print(data_points)
# %%
time = np.arange(31)
print(time)
# %%
data_test = []
for i in range(100):
    for j in range(31):
        data_test.append(np.log(data_points[i][j]/data_points[i][j+1])*0.197/0.97)
data_test = np.array(data_test)
data_test = np.reshape(data_test,(100,31))
# %%
data_mean = data_test.mean(0)
data_error = data_test.std(0)
# %%
plt.plot(time,data_mean)

# %%
print(data_mean[10])
print(data_error[10])
# %%
