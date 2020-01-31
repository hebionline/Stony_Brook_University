

import random
import matplotlib.pyplot as plt
import numpy as np

# time scale -> i range (1,1000)
# step size -> +/- 1

random_walk_1 = list()
random_walk_1.append(-1 if random.random() < 0.5 else 1)
#%%
for i in range(1,10000):
    movement = -1 if random.random() < 0.5 else 1
    # value preserves the previous step value
    value = random_walk_1[i - 1] + movement
    # append the most recent position to the list
    random_walk_1.append(value)
mean1 = sum(random_walk_1)/len(random_walk_1)
var1 = np.var(random_walk_1)
print('Mean of the 1st sample is: ',mean1)
print('Variance of 1st sample is:', var1)
print('\n')

#%%
random_walk_2 = list()
random_walk_2.append(-1 if random.random() < 0.5 else 1)
for i in range(1,10000):
    movement = -1 if random.random() < 0.5 else 1
    value = random_walk_2[i - 1] + movement
    random_walk_2.append(value)
mean2 = sum(random_walk_2)/len(random_walk_2)
var2 = np.var(random_walk_2)
print('Mean of the 2nd sample is: ',mean2)
print('Variance of 2nd sample is:', var2)
print('\n')
#%%
random_walk_3 = list()
random_walk_3.append(-1 if random.random() < 0.5 else 1)

for i in range(1,10000):
    movement = -1 if random.random() < 0.5 else 1
    value = random_walk_2[i - 1] + movement
    random_walk_3.append(value)

mean3 = sum(random_walk_3)/len(random_walk_3)
var3 = np.var(random_walk_3)
print('Mean of the 3rd sample is: ',mean3)
print('Variance of 3rd sample is:', var3)
print('\n')
#%%
random_walk_4 = list()
random_walk_4.append(-1 if random.random() < 0.5 else 1)

for i in range(1,10000):
    movement = -1 if random.random() < 0.5 else 1
    value = random_walk_4[i - 1] + movement
    random_walk_4.append(value)

mean4 = sum(random_walk_4)/len(random_walk_4)
var4 = np.var(random_walk_4)
print('Mean of the 4th sample is: ',mean4)
print('Variance of 4th sample is:', var4)
print('\n')
#%%
random_walk_5 = list()
random_walk_5.append(-1 if random.random() < 0.5 else 1)

for i in range(1,10000):
    movement = -1 if random.random() < 0.5 else 1
    value = random_walk_5[i - 1] + movement
    random_walk_5.append(value)
mean5 = sum(random_walk_5)/len(random_walk_5)
var5 = np.var(random_walk_5)
print('Mean of the 5th sample is: ', mean5)
print('Variance of 5th sample is:', var5)
print('\n')
#%%

print("Sample mean is: ", (mean1+mean2+mean3+mean4+mean5)/5)
print('Sample variance is:', 1/len(random_walk_1)*(var1+var2+var3+var4+var5) )

plt.plot(random_walk_1)
plt.plot(random_walk_2)
plt.plot(random_walk_3)
plt.plot(random_walk_4)
plt.plot(random_walk_5)
plt.show()

