#!/bin/bash -l
pip install fabric
fab legion.cold:branch=OpenMP
fab legion.sub:processes=1
fab legion.wait
fab legion.fetch_time
fab legion.cleanup_all
python make_video.py results/latest_results/legion.rc.ucl.ac.uk/output.txt
