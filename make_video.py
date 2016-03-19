import sys
import os
import numpy as np
import matplotlib.animation as anim
import matplotlib.pyplot as plt
from StringIO import StringIO as strio
from os.path import abspath

video_fname = "GOL_video.mp4"

def get_data(input_fname):
    with open(input_fname) as data_file:
        line = data_file.readline()
        header = np.genfromtxt(strio(line),delimiter=",",dtype=int)
        xsize, ysize, frames = header
        data = np.fromfile(data_file, int, xsize*ysize*frames, ",")
    return data.reshape([frames,xsize,ysize])

def create_video(data,video_fname):
    fig = plt.figure()
    def _animate(frame_id):
        plt.imshow(data[frame_id],interpolation="none",cmap='Greys_r')


    video = anim.FuncAnimation(fig, _animate, len(data), interval=100)
    video.save(video_fname)

input_fname = sys.argv[1]

data = get_data(input_fname)
create_video(data,video_fname)
print "Video of GameOfLife output created and save to:\n{}".format(abspath(video_fname))
