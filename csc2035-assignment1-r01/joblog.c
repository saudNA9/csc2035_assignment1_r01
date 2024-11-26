/*
 * Replace the following string of 0s with your student number
 * 230266960
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include "joblog.h"

/* 
 * DO NOT EDIT the new_log_name function. It is a private helper 
 * function provided for you to create a log name from a process 
 * descriptor for use when reading, writing and deleting a log file.
 * 
 * You must work out what the function does in order to use it properly
 * and to clean up after use.
 */
static char* new_log_name(proc_t* proc) {
    static char* joblog_name_fmt = "%s/%.31s%07d.txt";
                                // string format for the name of a log file
                                // declared static to have only one instance

    if (!proc)
        return NULL;

    char* log_name;
            
    asprintf(&log_name, joblog_name_fmt, JOBLOG_PATH, proc->type_label,
        proc->id);

    return log_name;
}

/* 
 * DO NOT EDIT the joblog_init function that sets up the log directory 
 * if it does not already exist.
 */
int joblog_init(proc_t* proc) {
    if (!proc) {
        errno = EINVAL;
        return -1;
    }
        
    int r = 0;
    if (proc->is_init) {
        struct stat sb;
    
        if (stat(JOBLOG_PATH, &sb) != 0) {
            errno = 0;
            r = mkdir(JOBLOG_PATH, 0777);
        }  else if (!S_ISDIR(sb.st_mode)) {
            unlink(JOBLOG_PATH);
            errno = 0;
            r = mkdir(JOBLOG_PATH, 0777);
        }
    }

    joblog_delete(proc);    // in case log exists for proc
    
    return r;
}

/* 
 * TODO: you must implement this function.
 * Hints:
 * - you have to go to the beginning of the line represented
 *      by entry_num to read the required entry
 * - see job.h for a function to create a job from its string representation
 */
job_t* joblog_read(proc_t* proc, int entry_num, job_t* job) {
    // Preserve the errno value at the start
    int old_errno = errno;

    // Validate parameters
    if (!proc || entry_num < 0) {
        errno = old_errno;
        return NULL;
    }

    // Generate the log file name
    char* log_name = new_log_name(proc);
    if (!log_name) {
        errno = old_errno;
        return NULL;
    }

    // Open the log file
    FILE* log_file = fopen(log_name, "r");
    free(log_name);
    if (!log_file) {
        errno = old_errno;
        return NULL;
    }

    // Allocate job if not provided
    bool dynamically_allocated = false;
    if (!job) {
        job = malloc(sizeof(job_t));
        if (!job) {
            fclose(log_file);
            errno = old_errno;
            return NULL;
        }
        dynamically_allocated = true;
    }

    // Read the log and locate the entry
    char line[JOB_STR_SIZE];
    int current_line = 0;
    while (fgets(line, sizeof(line), log_file)) {
        if (current_line == entry_num) {
            // Convert the string to a job structure
            if (!str_to_job(line, job)) {
                if (dynamically_allocated) free(job);
                fclose(log_file);
                errno = old_errno;
                return NULL;
            }
            fclose(log_file);
            return job; // Successfully read the job
        }
        current_line++;
    }

    // Entry not found
    if (dynamically_allocated) free(job);
    fclose(log_file);
    errno = old_errno;
    return NULL;
}



/* 
 * TODO: you must implement this function.
 * Hints:
 * - remember new entries are appended to a log file
 * - see the hint for joblog_read
 */
void joblog_write(proc_t* proc, job_t* job) {
    // Preserve the current errno value
    int old_errno = errno;

    // Validate parameters
    if (!proc || !job) {
        errno = old_errno;
        return;
    }

    // Generate the log file name
    char* log_name = new_log_name(proc);
    if (!log_name) {
        errno = old_errno;
        return;
    }

    // Open the log file in append mode
    FILE* log_file = fopen(log_name, "a");
    free(log_name); // Clean up dynamically allocated log name
    if (!log_file) {
        errno = old_errno;
        return;
    }

    // Convert the job to its string representation
    char job_str[JOB_STR_SIZE];
    if (!job_to_str(job, job_str)) {
        // If conversion fails, clean up and return
        fclose(log_file);
        errno = old_errno;
        return;
    }

    // Append the job entry to the log file
    fprintf(log_file, "%s\n", job_str);

    // Clean up
    fclose(log_file);

    // Restore the original errno
    errno = old_errno;
}


/* 
 * TODO: you must implement this function.
 */
void joblog_delete(proc_t* proc) {
    if (!proc) {
        return; // Do nothing if proc is NULL
    }

    // Generate the log file name
    char* log_name = new_log_name(proc);
    if (!log_name) {
        return; // Do nothing if log name generation failed
    }

    // Preserve the current value of errno
    int saved_errno = errno;

    // Attempt to delete the file
    unlink(log_name);

    // Restore the previous value of errno
    errno = saved_errno;

    // Free the dynamically allocated log name
    free(log_name);
}
