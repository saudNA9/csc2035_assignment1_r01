cmake_minimum_required(VERSION 3.29)
project(csc2035_assignment1_r01 C)

set(CMAKE_C_STANDARD 11)

include_directories(csc2035-assignment1-r01)
include_directories(csc2035-assignment1-r01/test)
include_directories(csc2035-assignment1-r01/test/munit)

add_executable(csc2035_assignment1_r01
    csc2035-assignment1-r01/test/munit/munit.c
    csc2035-assignment1-r01/test/munit/munit.h
    csc2035-assignment1-r01/test/munit.c
    csc2035-assignment1-r01/test/munit.h
    csc2035-assignment1-r01/test/procs4tests.c
    csc2035-assignment1-r01/test/procs4tests.h
    csc2035-assignment1-r01/test/test_ipc.c
    csc2035-assignment1-r01/test/test_ipc.h
    csc2035-assignment1-r01/test/test_ipc_jobqueue.c
    csc2035-assignment1-r01/test/test_ipc_jobqueue.h
    csc2035-assignment1-r01/test/test_job.c
    csc2035-assignment1-r01/test/test_job.h
    csc2035-assignment1-r01/test/test_joblog.c
    csc2035-assignment1-r01/test/test_joblog.h
    csc2035-assignment1-r01/test/test_jobqueue_common.c
    csc2035-assignment1-r01/test/test_jobqueue_common.h
    csc2035-assignment1-r01/test/test_pri_jobqueue.c
    csc2035-assignment1-r01/test/test_pri_jobqueue.h
    csc2035-assignment1-r01/test/test_proc.c
    csc2035-assignment1-r01/test/test_proc.h
    csc2035-assignment1-r01/test/test_sem_jobqueue.c
    csc2035-assignment1-r01/test/test_sem_jobqueue.h
    csc2035-assignment1-r01/test/test_shobject_name.c
    csc2035-assignment1-r01/test/test_shobject_name.h
    csc2035-assignment1-r01/ipc.c
    csc2035-assignment1-r01/ipc.h
    csc2035-assignment1-r01/ipc_jobqueue.c
    csc2035-assignment1-r01/ipc_jobqueue.h
    csc2035-assignment1-r01/job.c
    csc2035-assignment1-r01/job.h
    csc2035-assignment1-r01/joblog.c
    csc2035-assignment1-r01/joblog.h
    csc2035-assignment1-r01/pri_jobqueue.c
    csc2035-assignment1-r01/pri_jobqueue.h
    csc2035-assignment1-r01/proc.c
    csc2035-assignment1-r01/proc.h
    csc2035-assignment1-r01/rmsho.c
    csc2035-assignment1-r01/sem_jobqueue.c
    csc2035-assignment1-r01/sem_jobqueue.h
    csc2035-assignment1-r01/shobject_name.c
    csc2035-assignment1-r01/shobject_name.h
    csc2035-assignment1-r01/sim_config.h)
