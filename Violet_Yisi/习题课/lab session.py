#%%
import numpy as np
import math
import matplotlib.pyplot as plt

# %%
def f(x):
    return x ** 4 - 6.4 * x ** 3 + 6.45 * x ** 2 + 20.538 * x -31.752

x = np.arange(0 , 5 ,0.1)
y = f(x)
plt.plot(x, y, label = 'zero of even function')
plt.xlabel('x')
plt.ylabel('y')
plt.title('y-x')
plt.axhline(y=0,color='red')
plt.ylim(-1,5)
plt.show()

# %%
