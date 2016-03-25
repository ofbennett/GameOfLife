#!/bin/bash -l
pip install fabric
fab legion.cold:branch=CUDA
fab legion.sub:config=config.yml
fab legion.wait
fab legion.fetch_all
fab legion.cleanup_all
python make_video.py results/latest_results/legion.rc.ucl.ac.uk/output.txt
