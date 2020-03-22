#%%
s = 0
e = 14 
f = 1.625
p = e - 127
A = (-1) ** s * f * 2 ** p
print(A)

# %%
import sys
max = float('inf')
over = 1.
while over != max:
    over = over * 2.
print(over) 
# %%
eps = 1.
one = 1
while one + eps != 1:
    eps = eps / 2.
    one = 1
print(eps)


# %%