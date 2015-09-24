#!/usr/bin/python
import random

def array():
	# number of changed switch
	ch_swit_num = 0
	
	alpha = 0.8
	beta = 1.0

	# the weight of controller
	controller_list = []
	for i in range(0,100):
		controller_list.append(0)

	# the weight of switch
	switch_list = []
	switch_weight = [] # unchanged
	for i in range(0,10000):
		tmp_weight = random.paretovariate(3)
		switch_list.append(tmp_weight)
		switch_weight.append(tmp_weight)

	# the potential relationship of controller and switch
	potential_matrix = [[0 for col in range(100)] for row in range(10000)]
	for swit in range(10000):
		swit_x = swit / 100
		swit_y = swit % 100
		for ctrl in range(100):
			ctrl_x = (ctrl / 10) * 10 + 5
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


	# the number of potential controllers of each switch
	num_pot_ctrl = []
	tmp_ctrl_num = 0
	for i in range(10000):
		tmp_ctrl_num = 0
		for j in range(100):
			if (potential_matrix[i][j] == 1):
				tmp_ctrl_num += 1
		num_pot_ctrl.append(tmp_ctrl_num)



	# shuffle the switch array
	switch_array = []
	for i in range(10000):
		switch_array.append(i)
	random.shuffle(switch_array)



	# initialization of controllers and switches
	real_controller = []
	for n in range(100):
		real_controller.append([])
	for i in range(10000):
		snum = switch_array[i]
		if (num_pot_ctrl[snum] == 1):
			for j in range(100):
				if (potential_matrix[snum][j] == 1):
					real_controller[j].append(snum)
					controller_list[j] += switch_list[snum]
		else:
			flag_rand = random.uniform(0,99)
			tmp_min = 10000
			tmp_ctrl = 0
			tmp_minus_rand = flag_rand
			for k in range(100):
				if (potential_matrix[snum][k] == 1):
					if (controller_list[k] < tmp_min):
						tmp_min = controller_list[k]
						tmp_ctrl = k
						tmp_minus_rand = abs(flag_rand - k)
					else:
						if (controller_list[k] == tmp_min):
							if (abs(flag_rand - k) < tmp_minus_rand):
								tmp_min = controller_list[k]
								tmp_ctrl = k
								tmp_minus_rand = abs(flag_rand - k)
			real_controller[tmp_ctrl].append(snum)
			controller_list[tmp_ctrl] += switch_list[snum]

	arr_sum = 0
	for i in range(100):
		arr_sum += controller_list[i]
	aver_now = arr_sum / 100

	outcome = 0
	for i in range(100):
		outcome += (controller_list[i] - aver_now) * (controller_list[i] - aver_now)
	outcome = outcome / 100
	print(outcome)

	# two array to store the average load of each controller
	aver_ctrl_last = []
	aver_ctrl_now = []
	
	for i in range(100):
		aver_ctrl_last.append(0)
		aver_ctrl_now.append(0)

	# calculate the average load of last round
	for i in range(100):
		aver_ctrl_last[i] = controller_list[i]
		aver_ctrl_now[i] = controller_list[i]

	
	for i in range(100):
		adj_ctrl_num = 0
		for j in range(100):
			if (adjacent_controller[i][j] == 1):
				aver_ctrl_last[i] += controller_list[j]
				adj_ctrl_num += 1
		aver_ctrl_last[i] = aver_ctrl_last[i] / adj_ctrl_num


	# after running for a while, the load changes
	for i in range(0,10000):
			tmp_weight = random.paretovariate(3)
			switch_list[i] = tmp_weight
			switch_weight[i] = tmp_weight

	for i in range(100):
		controller_list[i] = 0

	for i in range(100):
		for j in range(len(real_controller[i])):
			controller_list[i] += switch_list[real_controller[i][j]]

	"""
	for i in range(100):
		print(real_controller[i])
		print('\n')
		print(controller_list[i])
	"""

	arr_sum = 0
	for i in range(100):
		arr_sum += controller_list[i]
	aver_now = arr_sum / 100
	
	outcome = 0
	for i in range(100):
		outcome += (controller_list[i] - aver_now) * (controller_list[i] - aver_now)
	outcome = outcome / 100
	print(outcome)
"""
	# for each controller, do the migration part without thinking about its rank
	for i in range(100):
		adj_ctrl_num = 0
		for j in range(100):
			if (adjacent_controller[i][j] == 1):
				aver_ctrl_now[i] += controller_list[j]
				adj_ctrl_num += 1
		aver_ctrl_now[i] = aver_ctrl_now[i] / adj_ctrl_num

	for i in range(100):
		print aver_ctrl_now[i]
	print (aver_ctrl_last[0])
	print aver_now
	"""



if __name__ == "__main__" :
	array()
