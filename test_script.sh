#!/bin/bash -l
pip install fabric
fab legion.cold:branch=CUDA
fab legion.sub_test
fab legion.wait
fab legion.fetch_all
fab legion.cleanup_all
