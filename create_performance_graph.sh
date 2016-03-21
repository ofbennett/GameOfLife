#!/bin/bash -l
pip install fabric
fab legion.cold:branch=OpenMP

for i in 1 8
do
  fab legion.sub:processes=${i},config=config_graph.yml
  fab legion.wait
  fab legion.fetch_time:dir_name=${i}_processes
  fab legion.cleanup_results
done

#python make_graph.py
