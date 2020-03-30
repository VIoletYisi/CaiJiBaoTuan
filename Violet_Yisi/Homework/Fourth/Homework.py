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
