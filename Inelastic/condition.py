##############################################################################
# condition.py
##############################################################################
# Python script for analysis of inelastic scatterers
# Date: 2015/03/18
# Author: Gaudenz Kessler <gaudenz.kessler@physik.uzh.ch>
##############################################################################
from math import cos, sin

x1 = 115.212065483
y1 = 9095.13287722
sx = 15.8988080142
sy = 1351.03724707
theta = -0.00557282352456
cth = cos(theta)
sth = -sin(theta)

S1 = 80.
S2 = 10000.

z = 3.


# Or in a long line
if ((cth*(S1-x1)+sth*(S2-y1))**2/(z*z*sx*sx)+(-sth*(S1-x1)+cth*(S2-y1))**2/(z*z*sy*sy))<1:
    print "yes"

