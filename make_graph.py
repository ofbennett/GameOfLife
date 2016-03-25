import matplotlib.pyplot as plt
from os.path import join, dirname, abspath
from glob import glob

proc_nums = [1,2,4,6,8,10,12]

fname_list = []
for i in proc_nums:
    fname = './results/{}_processes/legion.rc.ucl.ac.uk/time.txt'
    fname_list.append(fname)

time_list = []
for files in fname_list:
    with open(files) as f:
        time = float(f.readline())
        time_list.append(time)

plt.plot(proc_nums,time_list,marker='o')
ymin, ymax = plt.ylim()
plt.ylim(0,ymax)
plt.title('Run Time vs MPI Process Number')
plt.xlabel('MPI Process number')
plt.ylabel('Run time / sec')

plt.show()
