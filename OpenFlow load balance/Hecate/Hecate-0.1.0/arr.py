#!/usr/bin/python
import random

def array():
	# the weight of controller
	controller_list = []
	for i in range(0,100):
		controller_list.append(0)
	# the weight of switch
	switch_list = []
	for i in range(0,10000):
		switch_list.append(random.paretovariate(3))
	# the potential relationship of controller and switch
	potential_matrix = [[0 for col in range(100)] for row in range(10000)]
	for swit in range(10000):
		swit_x = swit / 100
		swit_y = swit % 100
		for ctrl in range(100):
			ctrl_x = (ctrl /10) * 10 + 5
			ctrl_y = (ctrl % 10) * 10 + 5
			dist = (swit_x - ctrl_x) * (swit_x - ctrl_x) + (swit_y - ctrl_y) * (swit_y - ctrl_y)
			if (dist <= 30 * 30):
				potential_matrix[swit][ctrl] = 1
			else:
				potential_matrix[swit][ctrl] = 0
	# the matrix of adjacent controller
	adjacent_controller = [[0 for col in range(100)] for row in range(100)]
	for ctrl1 in range(100):
		ctrl_x1 = (ctrl1 / 10) * 10 + 5
		ctrl_y1 = (ctrl1 % 10) * 10 + 5
		for ctrl2 in range(100):
			ctrl_x2 = (ctrl2 / 10) * 10 + 5
			ctrl_y2 = (ctrl2 % 10) * 10 + 5
			dist = (ctrl_x1 - ctrl_x2) * (ctrl_x1 - ctrl_x2) + (ctrl_y1 - ctrl_y2) * (ctrl_y1 - ctrl_y2)
			if (dist <= 40 * 40):
				if (ctrl1 != ctrl2):
					adjacent_controller[ctrl1][ctrl2] = 1
				else:
					adjacent_controller[ctrl1][ctrl2] = 2
			else:
				adjacent_controller[ctrl1][ctrl2] = 0
	
	for i in range(100):
		for j in range(100):
			print adjacent_controller[i][j],
		print('\n')

	"""
	createVar = globals()
	for i in range(0,100):
		createVar['arr%s' % i] = []
		list1.append(createVar['arr%s' % i])
	arr0.append(1)
	print len(list1)
	print len(arr0)
	print (arr13)
	print (list1[99])
	"""


if __name__ == "__main__" :
	array()
