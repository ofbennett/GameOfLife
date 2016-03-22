import matplotlib.pyplot as plt
from os.path import join, dirname, abspath
from glob import glob

proc_nums = [1,8]

fname_list = []
for i in proc_nums:
    fname = glob('./results/{}_processes/legion.rc.ucl.ac.uk/*'.format(i))[0]
    fname_list.append(fname)

time_list = []
for files in fname_list:
    with open(files) as f:
        time = float(f.readline())
        time_list.append(time)

graph = plt.plot(proc_nums,time_list)

plt.show(graph)
