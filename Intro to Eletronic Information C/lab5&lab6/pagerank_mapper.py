#!/usr/bin/env python

import sys

# input comes from STDIN (standard input)
for line in sys.stdin:
    # remove leading and trailing whitespace
    line = line.strip()
    # split the line into words
    elements = line.split('\t')
    # increase counters
    linknodes=eval(elements[2])
    length=len(linknodes)
    node_id=elements[0].strip()
    pr=elements[1]
    link=list()
    just_for_bug=list()
    just_for_bug.append(node_id)
    just_for_bug.append(0)
    print node_id,'\t',just_for_bug
    for l in linknodes:
        # write the results to STDOUT (standard output);
        # what we output here will be the input for the
        # Reduce step, i.e. the input for reducer.py
        #
        # tab-delimited; the trivial word count is 1
	average=float(pr)/length
	assemble=list()
	assemble.append(node_id)
	assemble.append(average)
        print l,'\t',assemble
