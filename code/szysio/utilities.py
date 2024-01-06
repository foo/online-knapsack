from math import *

R =  1. / (1. + log(2.))
F =  (1. - 2. * log( 3./2. )) / ( 3 * log( 4./3. ) )
G = R + (2. / 3.) * (R * log( 4./3. ) - 1.)

def f(x):
    if x <= R:
        return 1./2.
    else:
        return (2 * e) ** (x - 1)

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


########################################


def Gf(a, b):
    return P(1. - F) + Q(1. - a) - (1. - F - a) * g(a) + T(a, b)


value = ((- 2. / 3.) * (R - P(2. / 3.))) / (P(2. / 3.) - 2. / 3.)
print value
