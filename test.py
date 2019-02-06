import os 
import subprocess

output = os.popen("./push_swap 2 1 0").readlines()
print"ok\n" 
print output
