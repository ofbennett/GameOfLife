#!/bin/bash -l
pip install fabric
fab legion.cold:branch=MPI
fab legion.sub_test:processes=4
fab legion.wait
fab legion.fetch_all
fab legion.cleanup_all
