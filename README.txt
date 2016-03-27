GameOfLife

By Oscar Bennett, UCL
Student Number - 14087294

This project is a C++ implementation of Conway's Game of Life. Different git branches in the repository parallelize the code in different ways (serial, OpenMP, MPI, CUDA). The resulting data files can by converted into a video using the Python script make_video.py. Additionally scripts have been included which automate the process of measuring performance changes with different parellelisation parameters.

NOTE: Using the make_video.py script to generate a video file for visualization requires an installation of ffmpeg on your system.

The project has been setup so that it can be easily run on UCL's cluster called Legion. While all the branches of this repository can be easily run on Legion (or any other cluster in principle), they can only be run locally if your local system has the necessary dependancies. Local building requires CMake, whilst running the scripts to deploy the code on Legion requires the python modules Fabric and Mako.

The execution of the code is controlled by a config.yml file. Modify this file to specify parameter values for the simulation. The variable parameters are:

sizex: The size of the x (or horizontal) dimension of the cell field
sizey: The size of the y (or vertical) dimension of the cell field
EndOfDays: The number of update steps to run the simulation for
Pseudorandom: Initialize the cell field pseudorandomly (set to 1) or truly randomly (set to 0)
verbose: Verbose output (set to 1) or quiet output (set to 0)

Example results from each branch are provided in the folder called example_results. These results include the printed std output from the program along with the video created from the results of the computation. The raw output data has not been included as these files are very large.

******************************************************************************
SERIAL BRANCH:
This can be built and run locally or on Legion.

To build locally:
git clone https://github.com/ofbennett/GameOfLife.git
git checkout serial
cd ..
mkdir build
cd build
ccmake ../GameOfLife
-> Hit c to configure
-> Hit g to generate a make file
make

To run the unit tests:
test/test_GoL

Then to execute the code:
src/game_of_life

Then to create a video from the output:
python ../GameOfLife/make_video.py output.txt

DONE

To build and run the code on Legion:
There are a series of Fabric functions that can be called to carry this out conveniently. However, before you can do this you need to modify the file deploy/legion.py. You need to replace my Legion user name (at the top of the file) with yours.

Commands:
git clone https://github.com/ofbennett/GameOfLife.git
git checkout serial
-> Modify deploy/legion.py file, replacing my Legion user name with yours.
fab legion.cold (Tests are automatically run after the build)
fab legion.sub
fab legion.wait
fab legion.fetch_all
fab legion.cleanup_all (If you want to delete the build and results from your Legion account)
python make_video.py results/latest_results/legion.rc.ucl.ac.uk/output.txt

Alternatively, if you have access to a bash shell you can run this whole pipeline by executing the supplied shell script like this:
bash legion_pipeline.sh

DONE

******************************************************************************
OPENMP BRANCH:
OpenMP is a
