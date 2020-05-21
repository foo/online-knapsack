import math

R =  1. / (1. + math.log(2.))
F =  (1. - 2. * math.log( 3./2. )) / ( 3 * math.log( 4./3. ) )
G = R + (2. / 3.) * (R * math.log( 4./3. ) - 1.)


def fajna(a, b):
    pierwsza = 1. - F - R * (1. - F) * math.log( 2. - 2.*F ) + R * (1. - a) * math.log( 2. - 2. * a ) + (-18. * G * a + 9 * G) * (a - 1. + F)
    if (b < 1. / 3.) :
        druga = (G / b + 18. * G * a - 9. * G) * (a + b - 1. / 2.)
    else:
        druga = (-18. * G * b + 18. * G * a) * (a + b - 1. / 2.)
    return pierwsza + druga

print fajna(2.*F, F)
print fajna(2.*F, 1. / ( 3. * math.sqrt(2.) ))
print fajna(2.*F, 1. / 3.)
print fajna(2.*F, 2. * F)

print fajna(1./2., F)
print fajna(1./2., 1. / ( 3. * math.sqrt(2.) ))
print fajna(1./2., 1. / 3.)
print fajna(1./2., 2. * F)