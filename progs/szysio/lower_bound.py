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

def alg1(n):
    max = 0.
    sum = 0.
    for i in xrange(1, n):
        item = f(float(i) / n)
        # print("item: ", item)
        ratio = sum / (item)
        if ratio > max:
            max = ratio
        # print("ratio: ", ratio)
        sum += item / n
    # nie licze jednego z ratio, bo nie ma sensu!
    ratio = (sum + 0.5 / n)
    if ratio > max:
        max = ratio
    # print("ratio: ", ratio)
    print("max alg1: ", max)
    
def alg2(n):
    max = 0.
    sum = 0.
    for i in xrange(1, n):
        item = f((i-1.) / n)
        # print("item: ", item)
        ratio = sum / (item)
        if ratio > max:
            max = ratio
        # print("ratio: ", ratio)
        sum += item / n
    # nie licze jednego z ratio, bo nie ma sensu!
    ratio = (sum + 0.5 / n)
    if ratio > max:
        max = ratio
    # print("ratio: ", ratio)
    print("max alg2: ", max)

for i in xrange(2,21):
    print("i: ", i)
    alg1(i)
