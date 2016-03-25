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
input_dir = sys.argv[1]
video_path = join(input_dir,video_fname)
files = glob(input_dir+'*output.txt')

n = 0
for f in files:
    n+=1
    data, mpi_row_coord, mpi_col_coord, mpi_rows, mpi_cols = get_data(f)
    temp = []
    if(n==1):
        for j in range(mpi_cols):
            temp.append([0 for i in range(mpi_cols)])
        data_collection = [temp[i] for i in range(mpi_rows)]
    data_collection[mpi_row_coord][mpi_col_coord] = data

for row in range(mpi_rows):
    data_collection[row] = np.concatenate(data_collection[row][:],axis=1)
data_collection = np.concatenate(data_collection[:],axis=2)

create_video(data_collection,video_path)
print "Video of GameOfLife output created and saved to:\n{}".format(video_path)
