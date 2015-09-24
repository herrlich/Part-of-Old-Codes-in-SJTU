#!/usr/bin/env python

from operator import itemgetter
import sys

current_node = None
current_pr = 0
node = None
a=0.85
num=4
flag=0
total_link=[[2,3,4],[3,4],[4],[2]]

# input comes from STDIN
for line in sys.stdin:
    # remove leading and trailing whitespace
    line = line.strip()

    # parse the input we got from mapper.py
    line= line.split('\t')
    node=line[0]
    add_list=line[1]
    add_list=eval(add_list)
    add_pr=add_list[1]

    # convert count (currently a string) to int
    try:
        add_pr = float(add_pr)
    except ValueError:
        # count was not a number, so silently
        # ignore/discard this line
        continue

    # this IF-switch only works because Hadoop sorts map output
    # by key (here: word) before it is passed to the reducer
    if current_node == node:
        current_pr += add_pr
    else:
        if current_node:
            # write result to STDOUT
	    final_pr=a*current_pr+(1-a)/num
	    final_pr=float('%.4f' % final_pr)
            print current_node,'\t',final_pr,'\t',total_link[flag]
	    flag+=1
        current_node = node
        current_pr = add_pr

# do not forget to output the last word if needed!
if current_node == node:
    final_pr=a*current_pr+(1-a)/num
    final_pr=float('%.4f' % final_pr)
    print current_node,'\t',final_pr,'\t',total_link[flag]
