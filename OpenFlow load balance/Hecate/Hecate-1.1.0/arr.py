#!/usr/bin/python
import random

def array():
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

	# sort the switch array and keep an array to store its position
	switch_pos = []
	for i in range(10000):
		switch_pos.append(i)
	for i in range(10000):
		for j in range(i+1, 10000):
			if (switch_list[j] > switch_list[i]):
				tmp_value = switch_list[i]
				switch_list[i] = switch_list[j]
				switch_list[j] = tmp_value
				tmp_pos = switch_pos[i]
				switch_pos[i] = switch_pos[j]
				switch_pos[j] = tmp_pos

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


	# initialization of controllers and switches
	real_controller = []
	for n in range(100):
		real_controller.append([])
	for i in range(10000):
		current_seq = switch_pos[i]
		if (num_pot_ctrl[current_seq] == 1):
			for j in range(100):
				if (potential_matrix[current_seq][j] == 1):
					real_controller[j].append(current_seq)
					controller_list[j] += switch_list[i]
					break
		else:
			flag_rand = random.uniform(0,99)
			tmp_min = 10000
			tmp_ctrl = 0
			tmp_minus_rand = flag_rand
			for k in range(100):
				if (potential_matrix[current_seq][k] == 1):
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
			real_controller[tmp_ctrl].append(current_seq)
			controller_list[tmp_ctrl] += switch_list[i]

	arr_sum = 0
	for i in range(100):
		arr_sum += controller_list[i]
	aver_last = arr_sum / 100

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
	

	# the migration part
	alpha = 0.8
	beta = 1.0
	thd = aver_now * alpha + aver_last * (1 - alpha)
	efn = beta * thd
	#print aver_last
	#print aver_now
	#print thd
	overlist = []
	pendlist = []
	for i in range(100):
		if (controller_list[i] > efn):
			overlist.append(i)
	#print overlist
	while (len(overlist) != 0):
		cmax = 0
		cnum = 0
		for i in range(len(overlist)):
			if (controller_list[overlist[i]] > cmax):
				cmax = controller_list[overlist[i]]
				cnum = overlist[i]
		
		for i in range(len(real_controller[cnum])):
			for j in range(i+1, len(real_controller[cnum])):
				if (switch_list[real_controller[cnum][j]] > switch_list[real_controller[cnum][i]]):
					tmp_value = real_controller[cnum][i]
					real_controller[cnum][i] = real_controller[cnum][j]
					real_controller[cnum][j] = tmp_value

		tmp_controller = []
		for i in range(len(real_controller[cnum])):
			tmp_controller.append(real_controller[cnum][i])

		for j in range(100):
			if (adjacent_controller[cnum][j] == 1 and controller_list[j] < thd):
				# everytime finding an adjacent controller, resort the real controller-switch list
				for s in range(len(real_controller[cnum])):
					for t in range(s+1, len(real_controller[cnum])):
						if (switch_list[real_controller[cnum][t]] > switch_list[real_controller[cnum][s]]):
							tmp_value = real_controller[cnum][s]
							real_controller[cnum][s] = real_controller[cnum][t]
							real_controller[cnum][t] = tmp_value

				tmp_controller = []
				for s in range(len(real_controller[cnum])):
					tmp_controller.append(real_controller[cnum][s])
				
				# the second step of the algorithm
				for k in range(len(tmp_controller)):
					snum = tmp_controller[k]
					if (potential_matrix[snum][j] == 1 and controller_list[j] < thd):
						real_controller[j].append(snum)
						controller_list[j] += switch_list[snum]
						controller_list[cnum] = controller_list[cnum] - switch_list[snum]
						real_controller[cnum].remove(snum)
					if (controller_list[cnum] <= thd):
						break
					if (controller_list[j] >= thd):
						break
				if (controller_list[cnum] <= thd):
					overlist.remove(cnum)
					break
		if (controller_list[cnum] > efn):
			overlist.remove(cnum)
			pendlist.append(cnum)
	
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