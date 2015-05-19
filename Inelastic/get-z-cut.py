##############################################################################
# get-z-cut.py
##############################################################################
# Python script for analysis of inelastic scatterers
# Date: 2015/03/18
# Author: Gaudenz Kessler <gaudenz.kessler@physik.uzh.ch>
##############################################################################
import csv
import numpy as np
from math import cos, sin


ellfile = open("2DGauss.csv")
thereader = csv.reader(ellfile)
thereader.next()
thereader.next()
x1 = float(thereader.next()[1])
y1 = float(thereader.next()[1])
sx = float(thereader.next()[1])
sy = float(thereader.next()[1])
theta = float(thereader.next()[1])
cth = cos(theta)
sth = -sin(theta)

z = 3.
print z
cutstring = "((" + str(cth) + "*(cxS1sTot[0]-" + str(x1) + ")+(" + str(sth) + ")*(cS2sTotBottom[0]-" + str(y1) + "))**2/" + str(z*z*sx*sx) + "+(-" + str(sth) + "*(cxS1sTot[0]-" + str(x1) + ")+" + str(cth) + "*(cS2sTotBottom[0]-" + str(y1) + "))**2/" + str(z*z*sy*sy) + ")<1"
print cutstring
print
