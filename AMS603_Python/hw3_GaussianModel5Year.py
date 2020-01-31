import datetime as dt
import matplotlib.pyplot as plt
from matplotlib import style
import pandas as pd
import numpy as np
import scipy.stats as ss

style.use('ggplot')

df = pd.read_csv('tsla.csv', parse_dates=True, index_col=0)
df['adj_close_prev'] = df['Adj Close'].shift(1)
df['return'] = np.log(df['Adj Close']/df['adj_close_prev'])
df = df[~df['return'].isnull()]
df['return'].plot()
plt.show()

#print(df['return'].mean())
#print(df['return'].std())

mu = df['return'].mean()
sigma = df['return'].std()

df.sort_values(['return'])
print(df['return'])
returnsPDF = ss.norm.pdf(mu,sigma,df['return'])

plt.plot(df['return'],returnsPDF,label="PDF")
plt.show()
print(df['return'].mean())
print(df['return'].std())

s = np.random.normal(mu,sigma,1250)
count, bins, ignored = plt.hist(s,20,normed=True)
plt.plot(bins, 1/(sigma * np.sqrt(2 * np.pi)) *
    np.exp( - (bins - mu)**2 / (2 * sigma**2) ), linewidth=3, color='y')
plt.show()
