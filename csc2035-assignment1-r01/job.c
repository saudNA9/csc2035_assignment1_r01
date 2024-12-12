/*
 * Replace the following string of 0s with your student number
 * 230266960
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "job.h"

/* 
 * DO NOT EDIT the job_new functicmake ..
on.
 */
job_t* job_new(pid_t pid, unsigned int id, unsigned int priority, 
    const char* label) {
    return job_set((job_t*) malloc(sizeof(job_t)), pid, id, priority, label);
}

/* 
 * TODO: you must implement this function
 */
job_t* job_copy(job_t* src, job_t* dst) {
    if (!src || strlen(src->label) != MAX_NAME_SIZE - 1) {
        return NULL;
    }

    if (src == dst) {
        return dst;
    }

    if (!dst) {
        dst = malloc(sizeof(job_t));
        if (!dst) {
            return NULL;
        }
    }

    dst->pid = src->pid;
    dst->id = src->id;
    dst->priority = src->priority;
    strncpy(dst->label, src->label, MAX_NAME_SIZE - 1);
    dst->label[MAX_NAME_SIZE - 1] = '\0';

    return dst;
}




/* 
 * TODO: you must implement this function
 */
void job_init(job_t* job) {
    if (!job) {
        return;
    }

    job->pid = 0;
    job->id = 0;
    job->priority = 0;
    strncpy(job->label, PAD_STRING, MAX_NAME_SIZE - 1);
    job->label[MAX_NAME_SIZE - 1] = '\0';
}


/* 
 * TODO: you must implement this function
 */
bool job_is_equal(job_t* j1, job_t* j2) {
    if (j1 == NULL && j2 == NULL) {
        return true;
    }
    if (j1 == NULL || j2 == NULL) {
        return false;
    }

    if (j1->label[MAX_NAME_SIZE - 1] != '\0' || j2->label[MAX_NAME_SIZE - 1] != '\0') {
        return false;
    }

    return (j1->pid == j2->pid &&
            j1->id == j2->id &&
            j1->priority == j2->priority &&
            strncmp(j1->label, j2->label, MAX_NAME_SIZE - 1) == 0);
}



/*
 * TODO: you must implement this function.
 * Hint:
 * - read the information in job.h about padding and truncation of job
 *      labels
 */
job_t* job_set(job_t* job, pid_t pid, unsigned int id, unsigned int priority,
    const char* label) {
    if (job == NULL) {
        return NULL;
    }

    job->pid = pid;
    job->id = id;
    job->priority = priority;

    if (label == NULL || label[0] == '\0') {
        snprintf(job->label, MAX_NAME_SIZE, "%-*s", MAX_NAME_SIZE - 1, PAD_STRING);
    } else {
        size_t len = strlen(label);
        if (len < MAX_NAME_SIZE - 1) {
            snprintf(job->label, MAX_NAME_SIZE, "%-*.*s", MAX_NAME_SIZE - 1, MAX_NAME_SIZE - 1, label);
            memset(job->label + len, '*', MAX_NAME_SIZE - 1 - len);
        } else {
            snprintf(job->label, MAX_NAME_SIZE, "%.*s", MAX_NAME_SIZE - 1, label);
        }
    }

    job->label[MAX_NAME_SIZE - 1] = '\0';

    return job;
}


/*
 * TODO: you must implement this function.
 * Hint:
 * - see malloc and calloc system library functions for dynamic allocation, 
 *      and the documentation in job.h for when to do dynamic allocation
 */
char* job_to_str(job_t* job, char* str) {
    if (job == NULL || strlen(job->label) != MAX_NAME_SIZE - 1) {
        return NULL;
    }

    if (str == NULL) {
        str = (char*)calloc(JOB_STR_SIZE, sizeof(char));
        if (str == NULL) {
            return NULL;
        }
    }

    snprintf(
        str,
        JOB_STR_SIZE,
        JOB_STR_FMT,
        job->pid,
        job->id,
        job->priority,
        job->label
    );

    return str;
}


/*
 * TODO: you must implement this function.
 * Hint:
 * - see the hint for job_to_str
 */
job_t* str_to_job(char* str, job_t* job) {
    if (!str || strlen(str) != JOB_STR_SIZE - 1) {
        return NULL;
    }

    bool allocated = false;
    if (!job) {
        job = malloc(sizeof(job_t));
        if (!job) {
            return NULL;
        }
        allocated = true;
    }

    int parsed = sscanf(str, JOB_STR_FMT, &job->pid, &job->id, &job->priority, job->label);
    if (parsed != 4) {
        if (allocated) free(job);
        return NULL;
    }

    size_t label_len = strlen(job->label);
    if (label_len < MAX_NAME_SIZE - 1) {
        memset(job->label + label_len, '*', MAX_NAME_SIZE - 1 - label_len);
    }
    job->label[MAX_NAME_SIZE - 1] = '\0';

    return job;
}



/* 
 * TODO: you must implement this function
 * Hint:
 * - look at the allocation of a job in job_new
 */
void job_delete(job_t* job) {
    if (job != NULL) {
        free(job);
    }
}