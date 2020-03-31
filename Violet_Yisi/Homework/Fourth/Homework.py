#%%
from sympy import *
pi_inf = symbols('x')
c_1 = symbols('y')
c_2 = symbols('z')
c_3 = symbols('g')
pi_8 = pi_inf + c_1 / 8 + c_2 / (8 ** 2) + c_3 /(8 ** 3) - 3.061467
pi_16 = pi_inf + c_1 / 16 + c_2 / (16 ** 2) + c_3 /(16 ** 3) - 3.121445
pi_32 = pi_inf + c_1 / 32 + c_2 / (32 ** 2) + c_3 /(32 ** 3) - 3.136548
pi_64 = pi_inf + c_1 / 64 + c_2 / (64 ** 2) + c_3 /(64 ** 3) - 3.140331
solve([pi_8,pi_16,pi_32,pi_64],[pi_inf,c_1,c_2,c_3])

# %%
import numpy as np
from scipy.special import *
from decimal import *
tv = [0.1 , 1 , 10] #values used to test my program
# Get datas by using upward method
j_u = np.empty((26,3))
for i in range (3):
    j_u[0][i] = spherical_jn(0,tv[i])
    j_u[1][i] = spherical_jn(1,tv[i])
for i in range(1,25):
    for k in range(3):
        j_u[i + 1][k] = (2 * i + 1) / Decimal (tv[k]) * Decimal (j_u[i][k] ) - Decimal (j_u[i-1][k]) 
print('The values what we get by using upward method')
print('l\t\t\t0.1\t\t\t\t\t1\t\t\t\t\t10')
print('------------------------------------------------------------------------------------------------------------------------------------')
for i in range(26):
    print('{}\t\t\t{:<20}\t\t\t{:<20}\t\t\t{:<20}'.format(i,j_u[i][0],j_u[i][1],j_u[i][2]))

# %%
