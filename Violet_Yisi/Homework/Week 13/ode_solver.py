import numpy as np
import matplotlib.pyplot as plt

def harmoic_oscillator_drive(y,t,args):
    omega = args
    dydt = [y[1], -omega*omega*y[0]]
    return dydt


def forward_euler(f,y0,t,args=None): 
 
    dt = t[1] - t[0]
    y = np.zeros((len(t), y0.size))
    y[0] = y0
    for n in range(0, len(t) - 1):
        y[n+1] = y[n] + dt * np.array(f(y[n], t[n], args))
    return y


def heun(f,y0,t,args=None): 
    # Heun's method
    dt = t[1] - t[0]
    y = np.zeros((len(t), y0.size))
    y[0] = y0
    for n in range(0, len(t) - 1):
        k1 = np.array(f(y[n], t[n],args))
        k2 = np.array(f(y[n] + dt*k1, t[n+1], args))
        y[n+1] = y[n] + dt * (k1 + k2) / 2
    return y


def modified_euler_cauchy(f,y0,t,args=None): 
    # modified Euler-Cauchy method
    dt = t[1] - t[0]
    y = np.zeros((len(t), y0.size))
    y[0] = y0
    for n in range(0, len(t) - 1):
        k1 = np.array(f(y[n], t[n],args))
        k2 = np.array(f(y[n] + dt*k1/2, t[n] + dt/2, args))
        y[n+1] = y[n] + dt * k2
    return y

def Adams_Bashforth_2nd_order(f,y0,t,args=None): 
    # modified Euler-Cauchy method
    dt = t[1] - t[0]
    y = np.zeros((len(t), y0.size))
    y[0] = y0
    
    # forward-euler method
    y[1] = y0 + dt * np.array(f(y[0], t[0], args))  
    #
    
    for n in range(1, len(t) - 1):
        k1 = np.array(f(y[n], t[n], args))
        k2 = np.array(f(y[n-1], t[n-1], args))
        y[n+1] = y[n] + dt * (3*k1 - k2) / 2
    return y

def rk4(f,y0,t,args=None): 
    # Heun's method
    dt = t[1] - t[0]
    y = np.zeros((len(t), y0.size))
    y[0] = y0
    for n in range(0, len(t) - 1):
        k1 = np.array(f(y[n], t[n], args))
        k2 = np.array(f(y[n] + dt*k1/2, t[n] + dt/2, args))
        k3 = np.array(f(y[n] + dt*k2/2, t[n] + dt/2, args))
        k4 = np.array(f(y[n] + dt*k3, t[n+1], args))        
        y[n+1] = y[n] + dt * (k1 + 2*k2 + 2*k3 + k4) / 6
    return y

def ode_app():
    omega = 2 * np.pi
    y0 = np.array([0, 1])
    t = np.linspace(0,10,200)
    
    fig, ax = plt.subplots(1,1,figsize=(10,7))
    
    # forward Euler's method
    y = forward_euler(harmoic_oscillator_drive,y0,t,args=1)
    ax.plot(t,y[:,0],'bs', label='forward Euler\'s method') # 
    
    # Heun's method
    y = heun(harmoic_oscillator_drive,y0,t,args=1)
    ax.plot(t,y[:,0],'ro', label='Heun\'s method') # 
    
    # modified Euler-Cauchy method
    y = modified_euler_cauchy(harmoic_oscillator_drive,y0,t,args=1)
    ax.plot(t,y[:,0],'md', label='modified Euler-Cachy method') # 
    
    # rk4 method
    y = rk4(harmoic_oscillator_drive,y0,t,args=1)
    ax.plot(t,y[:,0],'b.', label='rk4 method') # 
    
    # 2nd-order Adams-Bashforth method
    y = Adams_Bashforth_2nd_order(harmoic_oscillator_drive,y0,t,args=1)
    ax.plot(t,y[:,0],'yd', label='2nd-order Adams-Bashforth method') # 
        
    plt.legend()
    plt.title('$y^{\prime\prime}+y=0$')
    plt.xlabel('Time t')
    plt.ylabel('Position y')
    plt.show()

if __name__ == '__main__':
    ode_app()    
