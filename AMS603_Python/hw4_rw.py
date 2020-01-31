from matplotlib import style
import numpy as np
import scipy.stats

style.use('ggplot')

r = 0.015/365
sigma = 0.4/30
s0=100

def mean_confidence_interval(data, confidence=0.95):
    a = 1.0 * np.array(data)
    n = len(a)
    m, se = np.mean(a), scipy.stats.sem(a)
    h = se * scipy.stats.t.ppf((1 + confidence) / 2., n-1)
    return m, m-h, m+h

option_price = list()

for i in range(1, 10000):
    movement = 0
    y=np.random.normal(0,1,32)
    for j in range(1,32):
        movement += 100* (r + sigma*(y[j-1])/250)
    option_price.append(movement)

x=mean_confidence_interval(option_price)
print ('option_price = ', np.mean(option_price))