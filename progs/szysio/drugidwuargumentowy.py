import math

R =  1. / (1. + math.log(2.))
F =  (1. - 2. * math.log( 3./2. )) / ( 3 * math.log( 4./3. ) )
G = R + (2. / 3.) * (R * math.log( 4./3. ) - 1.)


def fajna(a, b):
    if (b < 1. / 3.):
        acc_b = 2. / 3.
        g_b = G / b
    else:
        acc_b = 2. * b
        g_b = -18. * G * b + 9. * G
    return R * (1. - a) * math.log(2. * (1. - a)) + acc_b - R * acc_b * math.log(2. * acc_b) + (18. * G * a - 9. * G) * acc_b + (-18. * G * a + 9. * G) * a + (g_b + 18. * G * a - 9. * G) * (a + b - 0.5)
    
    
print fajna(1./2., F)
print fajna(1./2., 1./3.)
print fajna(1./2., 5./12.)
print fajna(1./2., 1./2.)

print fajna(1./3., F)
print fajna(1./3., 1./(3.*math.sqrt(2)))
print fajna(1./3., 1./3.)