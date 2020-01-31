import datetime
from scipy.stats import norm
from numpy import log
from numpy import sqrt
from numpy import exp


def find_vol(target_value, call_put, S, K, T, r):
    MAX_ITERATIONS = 100
    PRECISION = 1.0e-5

    sigma = 0.5
    for i in range(0, MAX_ITERATIONS):
        price = bs_price(call_put, S, K, T, r, sigma)
        vega = bs_vega(call_put, S, K, T, r, sigma)

        price = price
        diff = target_value - price  # our root

        print (i, sigma, diff)

        if (abs(diff) < PRECISION):
            return sigma
        sigma = sigma + diff/vega # f(x) / f'(x)

    # value wasn't found, return best guess so far
    return sigma

n = norm.pdf
N = norm.cdf

def bs_price(cp_flag,S,K,T,r,v,q=0.0):
    d1 = (log(S/K)+(r+v*v/2.)*T)/(v*sqrt(T))
    d2 = d1-v*sqrt(T)
    if cp_flag == 'c':
        price = S*exp(-q*T)*N(d1)-K*exp(-r*T)*N(d2)
    else:
        price = K*exp(-r*T)*N(-d2)-S*exp(-q*T)*N(-d1)
    return price

def bs_vega(cp_flag,S,K,T,r,v,q=0.0):
    d1 = (log(S/K)+(r+v*v/2.)*T)/(v*sqrt(T))
    return S * sqrt(T)*n(d1)
''''
V_market = 17.5
K = 585
T = (datetime.date(2014,10,18) - datetime.date(2014,9,8)).days / 365.
S = 586.08
r = 0.0002
cp = 'c' # call option
'''
'''
V_market = 77.38
K = 1040.00
T = (datetime.date(2019,2,22) - datetime.date(2019,2,18)).days / 365.
S = 1113.65
r = 0.0243
cp = 'c' # call option
''''
V_market = 5.54
K = 250.00
T = (datetime.date(2019,3,8) - datetime.date(2019,3,1)).days / 365.
S = 243.52
r = 0.0243
cp = 'c' # call option

implied_vol = find_vol(V_market, cp, S, K, T, r)

print ('Implied vol: ' , (implied_vol * 100))
print ('Market price = ',  V_market)
print ('Model price = ' , bs_price(cp, S, K, T, r, implied_vol))





