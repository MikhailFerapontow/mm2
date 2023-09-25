import random

value = 1.28

for i in range(1, 5):
  value = value / 4 + random.uniform(0.001, 0.005) - random.uniform(0.001, 0.005)
  print(value)