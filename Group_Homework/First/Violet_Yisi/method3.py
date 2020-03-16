'''

Method 3

'''
#%%
import numpy as np

origin_time = np.datetime64('1900-01-01')
raw_input = input('Please input a calendar date after January 1, 1900 in year-month-day form (2000-01-01) : ')
given_time = np.datetime64(raw_input)
switch_input = [1900,1,1]
for i in range(3):
    switch_input[i] = int(raw_input.split('-')[i])
    
passed_days = str(given_time - origin_time)
days = int(passed_days.split()[0])
weekdays = days % 7

month = ['January','February','March','April','May','June','July','Augest','September','October','November','December'] 
weekday = ['Monday','Tuesday','Wednesday','Thursday','Friday','Saturday','Sunday']

print(month[switch_input[1]-1] + ' ' + str(switch_input[-1]) +', ' + str(switch_input[0]), end='')
print('\t\t' + weekday[weekdays])

# %%
