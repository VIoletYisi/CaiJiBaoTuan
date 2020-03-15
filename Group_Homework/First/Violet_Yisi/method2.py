'''

 Method 2

'''
#%%
import numpy as np
import datetime 

origin_time = datetime.date(1900,1,1)
raw_input = input('Please input a calendar date after January 1, 1900 in year-month-day form (2000-1-1) : ')
switch_input = [1900,1,1]
''' switch_input 是个中间变量，用来将输入进行转换，赋予初值是为了便于处理，以及避免
出现一些未知的错误'''
for i in range(3):
    switch_input[i] = int(raw_input.split('-')[i])

given_time = datetime.date(switch_input[0],switch_input[1],switch_input[-1])
passed_days = str(given_time - origin_time)
if passed_days == '0:00:00':
    days = 0
    weekdays = 0
else:
    days = int(passed_days.split()[0])
    weekdays = days % 7

month = ['January','February','March','April','May','June','July','Augest','September','October','November','December'] 
weekday = ['Monday','Tuesday','Wednesday','Thursday','Friday','Saturday','Sunday']

print(month[switch_input[1]-1] + ' ' + str(switch_input[-1]) +', ' + str(switch_input[0]), end='')
print('\t\t' + weekday[weekdays])

# %%
