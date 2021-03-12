# A Python program to print all  
# permutations using library function  
from itertools import permutations  
  
# Get all permutations of [1, 2, 3]  
perm = permutations([0, 1, 2, 3, 4, 5, 6, 7, 8, 9], 8)  
  
# Print the obtained permutations  
for i in list(perm):  
    print (i)  
