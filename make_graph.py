import matplotlib.pyplot as plt
from os.path import join, dirname, abspath
from glob import glob

proc_nums = [1,2,3,4,6,8,10,12]

fname_list = []
for i in proc_nums:
    fname = glob('./results/{}_processes/legion.rc.ucl.ac.uk/*'.format(i))[0]
    fname_list.append(fname)

time_list = []
for files in fname_list:
    with open(files) as f:
        time = float(f.readline())
        time_list.append(time)

plt.plot(proc_nums,time_list)
plt.title('Run Time vs Process Number')
plt.xlabel('Process number')
plt.ylabel('Run time / sec')

plt.show()
