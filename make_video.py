import sys
import os
import numpy as np
import matplotlib.animation as anim
import matplotlib.pyplot as plt
from StringIO import StringIO as strio
from os.path import abspath, dirname, join
from glob import glob

video_fname = "GoL_video.mp4"

def get_data(input_fname):
    with open(input_fname) as data_file:
        line = data_file.readline()
        header = np.genfromtxt(strio(line),delimiter=",",dtype=int)
        xsize, ysize, frames, mpi_row_coord, mpi_col_coord, mpi_rows, mpi_cols = header
        data = np.fromfile(data_file, int, xsize*ysize*frames, ",")
    return data.reshape([frames,xsize,ysize]), mpi_row_coord, mpi_col_coord, mpi_rows, mpi_cols

def create_video(data,video_fname):
    fig = plt.figure()
    def _animate(frame_id):
        plt.imshow(data[frame_id],interpolation="none",cmap='Greys_r')

    video = anim.FuncAnimation(fig, _animate, len(data), interval=100)
    video.save(video_fname)

print "Making video from output..."
input_dir =  "results/latest_results/legion.rc.ucl.ac.uk/" # sys.argv[1]
video_path = join(input_dir,video_fname)
files = glob(input_dir+'*output.txt')

n = 0
for f in files:
    n+=1
    data, mpi_row_coord, mpi_col_coord, mpi_rows, mpi_cols = get_data(f)
    if(n==1):
        temp = [0 for i in range(mpi_cols)]
        data_collection = [temp for i in range(mpi_rows)]
    data_collection[mpi_row_coord][mpi_col_coord] = data
data_array = np.array(data_collection)
data_array = np.concatenate(data_array,axis=3)
data_array = np.concatenate(data_array,axis=1)

create_video(data_array,video_path)
print "Video of GameOfLife output created and saved to:\n{}".format(video_path)
