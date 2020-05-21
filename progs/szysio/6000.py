import math

R =  1. / (1. + math.log(2.))
F =  (1. - 2. * math.log( 3./2. )) / ( 3 * math.log( 4./3. ) )
G = R + (2. / 3.) * (R * math.log( 4./3. ) - 1.)


a = 1 - math.exp((G/F - 9. * G - 1.) / R)

print a