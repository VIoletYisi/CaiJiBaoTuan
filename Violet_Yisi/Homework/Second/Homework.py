#%%
matrix_list=[[1,2,3],[4,5,6],[7,8,9]]
matrix_1=[]
for row_1 in matrix_list:
    matrix_1.append(row_1[-1])
print(matrix_1)

#%%
matrix_2=[]
for row_2 in matrix_list:
    value=row_2[1]
    matrix_2.append(2*value**2)
print(matrix_2)


# %%
