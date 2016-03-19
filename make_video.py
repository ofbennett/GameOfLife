import sys
import os
import numpy as np
import matplotlib.animation as anim
import matplotlib.pyplot as plt
from StringIO import StringIO as strio

video_fname = "GOL_video.mp4"

def get_data(fname):
    with open(fname) as data_file:
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

fname = sys.argv[1]

data = get_data(fname)
create_video(data,video_fname)
