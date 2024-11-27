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
    // Validate the source job
    if (!src || strlen(src->label) != MAX_NAME_SIZE - 1) {
        return NULL; // Return NULL if src is invalid
    }

    // If source and destination are the same, no copying needed
    if (src == dst) {
        return dst;
    }

    // Dynamically allocate memory for destination if NULL
    if (!dst) {
        dst = malloc(sizeof(job_t));

    }

    // Copy fields
    dst->pid = src->pid;
    dst->id = src->id;
    dst->priority = src->priority;
    strncpy(dst->label, src->label, MAX_NAME_SIZE - 1);
    dst->label[MAX_NAME_SIZE - 1] = '\0'; // Ensure null termination

    return dst;
}



/* 
 * TODO: you must implement this function
 */
void job_init(job_t* job) {
    if (!job) {
        return; // If the job pointer is NULL, do nothing
    }

    // Initialize the fields of the job to their default values
    job->pid = 0;                             // Set process ID to 0
    job->id = 0;                              // Set job ID to 0
    job->priority = 0;                        // Set priority to 0
    strncpy(job->label, PAD_STRING, MAX_NAME_SIZE - 1); // Copy PAD_STRING into label
    job->label[MAX_NAME_SIZE - 1] = '\0';     // Ensure the label is null-terminated
}


/* 
 * TODO: you must implement this function
 */
bool job_is_equal(job_t* j1, job_t* j2) {
    // Handle null cases
    if (j1 == NULL && j2 == NULL) {
        return true;
    }
    if (j1 == NULL || j2 == NULL) {
        return false;
    }

    // Compare all fields
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

    // Set basic fields
    job->pid = pid;
    job->id = id;
    job->priority = priority;

    // Handle label
    if (label == NULL || label[0] == '\0') {
        // Use PAD_STRING if label is NULL or empty
        snprintf(job->label, MAX_NAME_SIZE, "%-*s", MAX_NAME_SIZE - 1, PAD_STRING);
    } else {
        size_t len = strlen(label);
        if (len < MAX_NAME_SIZE - 1) {
            // Copy label and pad with '*'
            snprintf(job->label, MAX_NAME_SIZE, "%-*.*s", MAX_NAME_SIZE - 1, MAX_NAME_SIZE - 1, label);
            memset(job->label + len, '*', MAX_NAME_SIZE - 1 - len);
        } else {
            // Truncate label
            snprintf(job->label, MAX_NAME_SIZE, "%.*s", MAX_NAME_SIZE - 1, label);
        }
    }

    // Ensure null-termination
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
    // Validate the job pointer and label
    if (job == NULL || strlen(job->label) != MAX_NAME_SIZE - 1) {
        return NULL;
    }

    // Dynamically allocate memory if str is NULL
    if (str == NULL) {
        str = (char*)calloc(JOB_STR_SIZE, sizeof(char)); // Zero-initialize memory
        if (str == NULL) {
            return NULL; // Allocation failure
        }
    }

    // Format the job's fields into the string
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
    // Validate the input string
    if (!str || strlen(str) != JOB_STR_SIZE - 1) {
        return NULL;
    }

    // Allocate memory for job if job is NULL
    bool allocated = false;
    if (!job) {
        job = malloc(sizeof(job_t));
        if (!job) {
            return NULL; // Memory allocation failed
        }
        allocated = true;
    }

    // Parse the string into the job fields
    int parsed = sscanf(str, JOB_STR_FMT, &job->pid, &job->id, &job->priority, job->label);
    if (parsed != 4) {
        if (allocated) free(job); // Free allocated memory on failure
        return NULL;
    }

    // Ensure label is correctly padded/truncated
    size_t label_len = strlen(job->label);
    if (label_len < MAX_NAME_SIZE - 1) {
        memset(job->label + label_len, '*', MAX_NAME_SIZE - 1 - label_len);
    }
    job->label[MAX_NAME_SIZE - 1] = '\0'; // Ensure null-termination

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