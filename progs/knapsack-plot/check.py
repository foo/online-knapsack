from math import *
import numpy
#from bigfloat import *

R =  1. / (1. + log(2.))
F =  (1. - 2. * log( 3./2. )) / ( 3 * log( 4./3. ) )
G = R + (2. / 3.) * (R * log( 4./3. ) - 1.)

def f(x):
    if x <= R:
        return 1./2.
    else:
        return (2 * e) ** (x - 1.0)

def g(x):
    if x > 1./3.:
        return -18.*G*x + 9.*G
    else:
        return G/x

def P(x):
    return x - R*x*log(2.*x)

def Q(x):
    return R*x*log(2.*x)

def T(a,b):
    return (g(b) - g(a))*(a+b-0.5)


def acc(a):
    return max(2.0/3.0, 2.0*a)
########################################


def G6(x, b):
    return Q(1. - x) + P(acc(b)) - acc(b)*g(x) + x*g(x) + T(x, b)


def G6estim(x, b):
    pestim = R + 6.0*G*x - 3.0*G
    return Q(1. - x) + pestim - acc(b)*g(x) + x*g(x) + T(x, b)

step = 300


for x in numpy.linspace(1.0/3.0, 0.5, step):
    for b in numpy.linspace(1.0/3.0, 0.5, step):
        if(b < x and G6estim(x, b) < R):
            print("FAIL", x, b)

print("END")