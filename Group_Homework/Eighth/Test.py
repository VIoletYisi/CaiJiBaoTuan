#%%
import numpy as np
n = 5
xData = np.array([-1.5,-0.75,0,0.75,1.5])
yData = np.array([-14.1014,-0.931596,0,0.931596,14.1014])
m = n 
a = yData.copy()
for k in range(1,m): # m = n + 1: number of data points
    for i in range(k,m):
        a[i] = (a[i] - a[k-1])/(xData[i] - xData[k-1])
    print(a)

# %%
