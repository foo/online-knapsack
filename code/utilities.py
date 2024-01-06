#!/usr/bin/env python3

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

def H(a,b):
	return Q(1-a) + P(2/3) - 3*G*(2*b - 2/3) + (a-2*b) * g(a) + T(a,b)

def H2(a,b):
	return P(2*b) - P(2/3) - 3*G*(2*b - 2/3) 

def H3(a,b):
	return Q(1-a) + P(2*a) - a*g(a)

def H4(a,b):
	return Q(1-a) + P(2/3) + 3*G*(2*a-2/3) - a*g(a)


def verify(H, thresh):
	a = 0.333333
	while a < 0.5:
		b = 0.333333
		while b < a:
			#print (H(a,b))
			if H(a,b) < thresh - 0.0000001:
				print('error: ', a, b, H(a,b))
			b += 0.001
		a += 0.001

def G6(x,y):
  	return P(2 * y) + Q(1-x) + (x - 2*y) * g(x) + T(x,y)

def G6a(x,y):
	return R + Q(1-x) + 6 * G * y - 3 * G + (0.5 - 3*y) * g(x) + (x+y-0.5) * g(y)
