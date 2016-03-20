from fabric.api import *
from mako.template import Template
import mako
import os
from contextlib import nested
import time

env.run_at="/home/rmapofb/Scratch/GoL/output"
env.deploy_to="/home/rmapofb/code/GoL"
env.clone_url="https://github.com/ofbennett/GameOfLife.git"
env.hosts=['legion.rc.ucl.ac.uk']
env.user='rmapofb'

modules = nested(
    prefix('module load cmake'),
    prefix('module swap compilers compilers/gnu/4.9.2'),
    prefix('module swap mpi mpi/openmpi/1.10.1/gnu-4.9.2')
)

@task
def cold(branch='master'):
    run('rm -rf '+env.deploy_to)
    run('mkdir -p '+env.deploy_to)
    run('mkdir -p '+env.run_at)
    with cd(env.deploy_to):
        with modules:
            run('git clone '+env.clone_url)
            with cd('GameOfLife'):
                run('git checkout '+branch)
                run('mkdir build')
                with cd('build'):
                    run('cmake .. -DCMAKE_CXX_COMPILER=mpiCC -DCMAKE_C_COMPILER=mpicc')
                    run('make')
                    run('test/test_GoL')

@task
def warm(branch='master'):
  with cd(env.deploy_to+'/GameOfLife/build'):
        with modules:
            run('git checkout '+branch)
            run('git reset --hard HEAD')
            run('git pull')
            run('cmake ..')
            run('make')
            run('test/test_GoL')

@task
def sub(processes=4):
    env.processes=processes
    template_file_path=os.path.join(os.path.dirname(__file__),'legion.sh.mko')
    script_local_path=os.path.join(os.path.dirname(__file__),'legion.sh')
    config_file_path=os.path.join(os.path.dirname(os.path.dirname(__file__)),'config.yml')
    run('mkdir -p '+env.run_at)
    with open(template_file_path) as template:
        script=Template(template.read()).render(**env)
        with open(script_local_path,'w') as script_file:
            script_file.write(script)
    with cd(env.run_at):
       put(config_file_path,'config.yml')
    with cd(env.deploy_to):
        put(script_local_path,'legion.sh')
        run('qsub legion.sh')

@task
def stat():
    run('qstat')

@task
def wait():
  while "job-ID" in run('qstat'):
	time.sleep(20)

@task
def fetch_all(dir_name = 'latest_results'):
    with lcd(os.path.join(os.path.dirname(os.path.dirname(__file__)),'results',dir_name)):
      with cd(env.run_at):
        get('*')

@task
def fetch_time(dir_name = 'latest_results'):
    with lcd(os.path.join(os.path.dirname(os.path.dirname(__file__)),'results',dir_name)):
      with cd(env.run_at):
        get('GameOfLife.o*')

@task
def cleanup_results():
    run('rm -rf /home/rmapofb/Scratch/GoL')

@task
def cleanup_code():
    run('rm -rf /home/rmapofb/code/GoL')

@task
def cleanup_all():
    run('rm -rf /home/rmapofb/Scratch/GoL')
    run('rm -rf /home/rmapofb/code/GoL')

@task
def patch():
  with cd(env.deploy_to+'/GameOfLife'):
    local('git diff > patch.diff')
    put('patch.diff','patch.diff')
    with modules:
        run('git checkout .')
        run('git apply patch.diff')
        with cd('build'):
            run('cmake ..')
            run('make')
            run('test/test_GoL')
