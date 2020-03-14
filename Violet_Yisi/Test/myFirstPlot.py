# Plot sin(x)

# Environment: VS Code

#%%

import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(0, 20, 100)  # Create a list of evenly-spaced numbers over the range
plt.plot(x, np.sin(x))       # Plot the sine of each x point
plt.show()                   # Display the plot

'''
#Environment: JupyterLab

import matplotlib.pyplot as plt
import numpy as np
%matplotlib inline

x = np.linspace(0, 20, 100)  # Create a list of evenly-spaced numbers over the range
plt.plot(x, np.sin(x))       # Plot the sine of each x point
'''

"""
Author: W.H. Gu
Date: 03.03.2020
the very first python plotting example,
noticing the difference between VS code and JupyterLab
""" 



