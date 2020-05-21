from math import *

R =  1. / (1. + log(2.))
F =  (1. - 2. * log( 3./2. )) / ( 3 * log( 4./3. ) )
G = R + (2. / 3.) * (R * log( 4./3. ) - 1.)

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

#print -3. * G - 2. * R * log( 2./3.)
s = 0.414760281780679
#print s * g(s) + P(2 * s)


A = -36. * G
B = -2.*R
C = 9.*G-2.*R*log(2.)
#print (A*exp(-C/B)/B)


a = 0.5
b = 0.414760281780679

print Q(1. - a) + P(2.*b) - g(a) * 2.*b + g(a)*a + T(a,b)

#print s * g(s) + P(2.*s)

#a = (-math.sqrt(R*R - 8. * R * G + 144. * G * G) + R + 12. * G) / ( 24. * G )

#a = 1. / 2.

#print -1. - R * math.log(1. - a) - 2. * R * math.log(2. * a) + 36. * G * a - 9 * G

#b = 1./3.
#a = 1. - math.exp(( -1. + 3. * G + 18. * b * G + G / b) / R)

#print 5. / 8. * R + 5. / 12. - 5. / 6. * R * math.log(5.) + 5. / 12. * R * math.log(4.) + 5. / 12. * R * math.log(3.)

#print a

#b = R / (36. * G)

#print F
#print 1. / (3. * math.sqrt(2.))

#print R * math.log (2 * b) / (18. * G) + b + 1. / 4.

#print (1. + R * math.log(1. - 1./2.)) / (36. * G)
#print (R / (36. * G))
#print (1. + R * math.log(1. - 1./3.)) / (36. * G)

#print 1 - F - R * (1 - F) * math.log(2 - 2 * F) + G

#print 1 - math.exp((6 * math.sqrt(2) * G + 9 * G - 18 * G * F - 1) / R )

#print 1 - math.exp((F/G + 9 * G - 1) / R)

#print 1 - math.exp((18 * G - 18 * G * F - 1) / R)

#print 1 - math.exp((18 * G - 18 * G * F - 1) / R)