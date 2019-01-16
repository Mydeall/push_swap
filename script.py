#!/usr/bin/env python
# coding: utf-8

import os
import sys
import subprocess
import re
from itertools import permutations

def test_all_permutations_for_n_elem(nbr):
    x = permutations(range(0, nbr))
    result = []
    for elem in x:
        lst = re.findall("\d+", str(elem))
        output = subprocess.check_output([os.path.realpath("push_swap")] + lst)
        result.append(len(output.split()))
    print "All permutations for " + str(nbr) + " elements"
    print result
    print "---------------------"

def test_n_time_x_elem(nbr, x):
    result = []
    i = 0
    while i < nbr:
        output = subprocess.check_output(['ruby', '-e', "puts (0.." + str(x - 1) + ").to_a.shuffle.join(' ')"])
        lst = re.findall("\d+", str(output))
        output = subprocess.check_output([os.path.realpath("push_swap")] + lst)
        nbr_op = len(output.split())
        if i == 0:
            min_op = max_op = nbr_op
        result.append(nbr_op)
        if nbr_op > max_op:
            max_op = nbr_op
        if nbr_op < min_op:
            min_op = nbr_op
        i = i + 1
    print str(nbr) + " tests for " + str(x) + " elements"
    print result
    print "minimum d'operations: " + str(min_op)
    print "maximum d'operations: " + str(max_op)
    print "---------------------"

if (len(sys.argv) == 2):
    test_all_permutations_for_n_elem(5)
    test_n_time_x_elem(int(sys.argv[1]), 100)
    test_n_time_x_elem(int(sys.argv[1]), 500)
else:
    print "usage: ./script argument"
