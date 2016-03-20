#!/bin/bash -l
#$ -S /bin/bash
#$ -l h_rt=0:10:0
#$ -N GameOfLife
#$ -wd /home/rmapofb/Scratch/GoL/output
module unload compilers
module unload mpi
module load compilers/gnu/4.9.2
module load mpi/openmpi/1.10.1/gnu-4.9.2
/home/rmapofb/code/GoL/GameOfLife/build/src/game_of_life config.yml
