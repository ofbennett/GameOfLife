#!/bin/bash -l
fab legion.cold
fab legion.sub
fab legion.wait
fab legion.fetch_all
fab legion.cleanup_all
python make_video.py results/latest_results/legion.rc.ucl.ac.uk/output.txt
