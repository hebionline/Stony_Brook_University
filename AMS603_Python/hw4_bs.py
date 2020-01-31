from scipy.stats import norm
from numpy import log
from numpy import sqrt
from numpy import exp

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

cp = 'c' # call option
cur_value = bs_price(cp, 100, 100, 30/365, 0.015, 0.01333)
print ('cur_price = ' , cur_value)


