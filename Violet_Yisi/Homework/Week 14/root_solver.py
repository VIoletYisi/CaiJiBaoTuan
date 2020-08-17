def bisection(f, x_L, x_R, eps):
# apply Newton-Raphson method to solve f(x)=0
# input - 
# f: defined function, 
# x_L, x_R: double, initial guess of the interval, in which the function changes the sign
# eps: double， the defined tolerance
# output - 
# x_M: double， the numerical approximation of the root
# iteration_counter: integer, the total number of iterations

    f_L = f(x_L)
    if f_L*f(x_R) > 0:
        print("""Error! Function does not have opposite 
                 signs at interval endpoints!""")
        sys.exit(1)
    x_M = (x_L + x_R)/2.0
    f_M = f(x_M)
    iteration_counter = 1

    while abs(x_L - x_R) > eps:
        if f_L*f_M > 0:   # i.e. same sign
            x_L = x_M
            f_L = f_M
        else:
            x_R = x_M
            f_R = f_M
        x_M = (x_L + x_R)/2
        f_M = f(x_M)
        iteration_counter = iteration_counter + 1

    return x_M, iteration_counter
    
def Newton(f, dfdx, x, eps):
# apply Newton-Raphson method to solve f(x)=0
# input - 
# f: defined function, 
# dfdx: defined function, which is the 1st-order derivative of f(x)
# x: double, initial guess of the root
# eps: double， the defined tolerance
# output - 
# x: double， the numerical approximation of the root
# iteration_counter: integer, the total number of iterations, when equals -1, no root can be found!

    f_value = f(x)
    iteration_counter = 0
    dx = 1
    while abs(dx) > eps and iteration_counter < 100:
        try:
            dx = - f_value/dfdx(x)
        except ZeroDivisionError:
            print('Error! - derivative zero for x = ', x)
            sys.exit(1)     # Abort with error

        x = x + dx
        f_value = f(x)
        iteration_counter = iteration_counter + 1

    # Here, either a solution is found, or too many iterations
    if abs(dx) > eps:
        iteration_counter = -1
    return x, iteration_counter

def secant(f, x0, x1, eps):
    f_x0 = f(x0)
    f_x1 = f(x1)
    iteration_counter = 0
    while abs(x0 - x1) > eps and iteration_counter < 100:
        try:
            denominator = (f_x1 - f_x0)/(x1 - x0)
            x = x1 - f_x1/denominator
        except ZeroDivisionError:
            print('Error! - denominator zero for x = ', x)
            sys.exit(1) # Abort with error
        x0 = x1
        x1 = x
        f_x0 = f_x1
        f_x1 = f(x1)
        iteration_counter = iteration_counter + 1
    # Here, either a solution is found, or too many iterations
    if abs(x0 - x1) > eps:
        iteration_counter = -1
    return x, iteration_counter
    
def root_app(): 
    def f(x):
        return x**2 - 9
    def dfdx(x):
        return 2*x

    a = 0;   b = 1000
    
    solution, no_iterations = bisection(f, a, b, eps=1.0e-10)
    print('bisection method: \tnumber of function calls: {:d}, \t\
        the root is {:f}'.format(2 + no_iterations, solution))

    solution, no_iterations = Newton(f, dfdx, 1, eps=1.0e-10)
    print('Newton-Raphson method: \tnumber of function calls: {:d}, \t\
        the root is {:f}'.format(2*no_iterations, solution))

    solution, no_iterations = secant(f, 1, 2, eps=1.0e-10)
    print('secant method: \t\tnumber of function calls: {:d}, \t\
        the root is {:f}'.format(1 + no_iterations, solution))

if __name__ == '__main__':
    root_app()