# -*- coding: utf-8 -*-
"""
Created on Wed Oct 30 10:28:03 2019

@author: bin lu, student id: 112-101-275
"""
import numpy as np
import pandas as pd
from numpy.linalg import inv
from numpy.linalg import det

def xConsistToNormal1(val):
    return val * 2.8469

def xConsistToNormal2(val):
    return val * 1.58686

def xOneCStep(new_mnData, nNumofComponents, vnCurrentMean, mnCurrentCov):
    A = np.matrix(new_mnData)
    A -= vnCurrentMean
    mnCurCovInv = inv(mnCurrentCov)
    
    def add_calu_func(x):
        return x*mnCurCovInv*(x.transpose())

    test_list = np.apply_along_axis(add_calu_func, axis=1, arr=A)
    C = np.array(test_list)
    D = C.flatten()
    ser = pd.Series(D)
    temp = ser.sort_values()
    vnDistanceOrderings = temp.index
    vnIndex = vnDistanceOrderings[range(nNumofComponents)]
    ret_mean = new_mnData[vnIndex].mean(0)
    ret_cov = np.cov(new_mnData[vnIndex].transpose()) 
  
    return ret_mean, ret_cov

#oringinal data
mnData = np.array([[0.4, 53., 64.], [0.4, 23., 60.], [3.1, 19., 71.],
                  [0.6, 34., 61.], [4.7, 24., 54.], [1.7, 65., 77.],
                  [9.4, 44., 81.], [10.1, 31., 93.], [11.6, 29., 93.], 
                  [12.6, 58., 51.], [10.9, 37., 76.], [23.1, 46., 96.], 
                  [23.1, 50., 77.], [21.6, 44., 93.], [23.1, 56., 95.], 
                  [1.9, 36., 54.], [26.8, 58., 168.], [29.9, 51., 99.]])
    
mnData2 = np.array([[3.83, 28.87, 7.2, 26.6, 6.19, 37.01], 
                   [2.89, 20.1, -11.71, 24.4, 5.17, 26.51], 
                   [2.86, 69.05, 12.32, 25.7, 7.04, 36.51], 
                   [2.92, 65.4, 14.28, 25.7, 7.1, 40.7], 
                   [3.06, 29.59, 6.31, 25.4, 6.15, 37.1],
                   [2.07, 44.82, 6.16, 21.6, 6.41, 33.9], 
                   [2.52, 77.37, 12.7, 24.9, 6.86, 41.8], 
                   [2.45, 24.67, -0.17, 25.01, 5.78, 33.4], 
                   [3.13, 65.01, 9.85, 26.6, 6.51, 41.01], 
                   [2.44, 9.99, -0.05, 28.01, 5.57, 37.2], 
                   [2.09, 12.2, -12.86, 23.51, 5.62, 23.3], 
                   [2.52, 22.55, 0.92, 23.6, 5.34, 35.2], 
                   [2.22, 14.3, 4.77, 24.51, 5.8, 34.9], 
                   [2.67, 31.79, -0.96, 25.8, 6.19, 33.1], 
                   [2.71, 11.6, -16.04, 25.2, 5.62, 22.7], 
                   [3.14, 68.47, 10.62, 25.01, 6.94, 39.7], 
                   [3.54, 42.64, 2.66, 25.01, 6.33, 31.8], 
                   [2.52, 16.7, -10.99, 24.8, 6.01, 31.7], 
                   [2.68, 86.27, 15.03, 25.51, 7.51, 43.1],
                   [2.37, 76.73, 12.77, 24.51, 6.96, 41.01]])

new_mnData = np.delete(mnData2, -1, axis=1)

#step 1
nDataLength = len(new_mnData)
nNumofComp = len(new_mnData.transpose())
nPointsInPartition = int((nDataLength + nNumofComp + 1)/2)

#Step 4.1 and 4.2
mxCandEstMean = []
mxCandEstCov = []
i = 500
while i > 0:
    vnIntSubSet = np.random.choice(nDataLength, size=nDataLength)
    nIntSubSetSize = nNumofComp
    nIntSubSetSize = 3
    newSubSet = new_mnData[vnIntSubSet[range(nIntSubSetSize)]]
    
    vnCurMean = newSubSet.mean(0)
    mnCurCov = np.cov(newSubSet.T)
    
    while det(mnCurCov) < (0.00001):
        nIntSubSetSize += 1
        newSubSet = new_mnData[vnIntSubSet[range(nIntSubSetSize)]]
        vnCurMean = newSubSet.mean(0)
        mnCurCov = np.cov(newSubSet.T)
    
    vn1stEstMean, mx1stEstCov = xOneCStep(new_mnData, nPointsInPartition, vnCurMean, mnCurCov)
    vn2ndEstMean, mx2ndEstCov = xOneCStep(new_mnData, nPointsInPartition, vn1stEstMean, mx1stEstCov)
    
    mxCandEstMean.append(vn2ndEstMean)
    mxCandEstCov.append(mx2ndEstCov)
    
    i -= 1

mxCandEstCovDet = []
for i in mxCandEstCov:
    mxCandEstCovDet.append(det(i))

C = np.array(mxCandEstCovDet)
D = C.flatten()
ser = pd.Series(D)
temp = ser.sort_values()
vnDistanceOrderings = temp.index.values
vnIndex = vnDistanceOrderings[range(10)]
#step 4.3 and 4.4
min10_mxCandEstMean = []
min10_mxCandEstCov = []
i = 0
for i in range(10):
    min10_mxCandEstMean.append(mxCandEstMean[vnIndex[i]])
    min10_mxCandEstCov.append(mxCandEstCov[vnIndex[i]])

#Report solution with lowest det
print ('NewMean = ', min10_mxCandEstMean[0])
print ('FullCov = ', min10_mxCandEstCov[0])
















