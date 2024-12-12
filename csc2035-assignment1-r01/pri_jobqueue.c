/*
 * Replace the following string of 0s with your student number
 * 230266960
 */
#include <stdlib.h>
#include <stdbool.h>
#include "pri_jobqueue.h"

/*
 * TODO: you must implement this function that allocates a job queue and
 * initialise it.
 * Hint:
 * - see job_new in job.c
 */
pri_jobqueue_t* pri_jobqueue_new() {
    pri_jobqueue_t* pjq = malloc(sizeof(pri_jobqueue_t));
    if (!pjq) {
        return NULL;
    }

    pri_jobqueue_init(pjq);

    return pjq;
}

/*
 * TODO: you must implement this function.
 */
void pri_jobqueue_init(pri_jobqueue_t* pjq) {

    pjq->buf_size = JOB_BUFFER_SIZE;
    pjq->size = 0;

    for (int i = 0; i < pjq->buf_size; i++) {
        job_init(&pjq->jobs[i]);
    }
}

/*
 * TODO: you must implement this function.
 * Hint:
 *      - if a queue is not empty, and the highest priority job is not in the
 *      last used slot on the queue, dequeueing a job will result in the
 *      jobs on the queue having to be re-arranged
 *      - remember that the job returned by this function is a copy of the job
 *      that was on the queue
 */
job_t* pri_jobqueue_dequeue(pri_jobqueue_t* pjq, job_t* dst) {
    if (!pjq || pri_jobqueue_is_empty(pjq)) {
        return NULL;
    }

    int highest_priority_index = 0;

    for (int i = 1; i < pjq->size; i++) {
        if (pjq->jobs[i].priority < pjq->jobs[highest_priority_index].priority) {
            highest_priority_index = i;
        }
    }

    job_t highest_priority_job = pjq->jobs[highest_priority_index];

    if (dst) {
        *dst = highest_priority_job;
    } else {
        dst = job_new(highest_priority_job.pid, highest_priority_job.id,
                      highest_priority_job.priority, highest_priority_job.label);
        if (!dst) {
            return NULL;
        }
    }

    for (int i = highest_priority_index; i < pjq->size - 1; i++) {
        pjq->jobs[i] = pjq->jobs[i + 1];
    }


    pjq->size--;
    job_init(&pjq->jobs[pjq->size]);

    return dst;
}

/*
 * TODO: you must implement this function.
 * Hints:
 * - if a queue is not full, and if you decide to store the jobs in
 *      priority order on the queue, enqueuing a job will result in the jobs
 *      on the queue having to be re-arranged. However, it is not essential to
 *      store jobs in priority order (it simplifies implementation of dequeue
 *      at the expense of extra work in enqueue). It is your choice how
 *      you implement dequeue (and enqueue) to ensure that jobs are dequeued
 *      by highest priority job first (see pri_jobqueue.h)
 * - remember that the job passed to this function is copied to the
 *      queue
 */
void pri_jobqueue_enqueue(pri_jobqueue_t* pjq, job_t* job) {
    if (!pjq || !job || pri_jobqueue_is_full(pjq) || job->priority == 0) {
        return;
    }

    int insert_pos = pjq->size;
    for (int i = 0; i < pjq->size; i++) {
        if (job->priority < pjq->jobs[i].priority) {
            insert_pos = i;
            break;
        }
    }

    for (int i = pjq->size; i > insert_pos; i--) {
        pjq->jobs[i] = pjq->jobs[i - 1];
    }

    pjq->jobs[insert_pos] = *job;
    pjq->size++;
}

/*
 * TODO: you must implement this function.
 */
bool pri_jobqueue_is_empty(pri_jobqueue_t* pjq) {

    if (!pjq) {
        return true;
    }

    return pjq->size == 0;
}


/*
 * TODO: you must implement this function.
 */
bool pri_jobqueue_is_full(pri_jobqueue_t* pjq) {

    if (!pjq) {
        return true;
    }

    return pjq->size >= pjq->buf_size;
}


/*
 * TODO: you must implement this function.
 * Hints:
 *      - remember that the job returned by this function is a copy of the
 *      highest priority job on the queue.
 *      - both pri_jobqueue_peek and pri_jobqueue_dequeue require copying of
 *      the highest priority job on the queue
 */
job_t* pri_jobqueue_peek(pri_jobqueue_t* pjq, job_t* dst) {
    if (!pjq || pri_jobqueue_is_empty(pjq)) {
        return NULL;
    }

    int highest_priority_index = 0;
    for (int i = 1; i < pjq->size; i++) {
        if (pjq->jobs[i].priority < pjq->jobs[highest_priority_index].priority) {
            highest_priority_index = i;
        }
    }

    job_t* result = dst;
    if (dst) {
        *dst = pjq->jobs[highest_priority_index];
    } else {
        result = job_new(
            pjq->jobs[highest_priority_index].pid,
            pjq->jobs[highest_priority_index].id,
            pjq->jobs[highest_priority_index].priority,
            pjq->jobs[highest_priority_index].label
        );
    }

    return result;
}


/*
 * TODO: you must implement this function.
 */
int pri_jobqueue_size(pri_jobqueue_t* pjq) {
    if (!pjq) {
        return 0;
    }
    return pjq->size;
}


/*
 * TODO: you must implement this function.
 */
int pri_jobqueue_space(pri_jobqueue_t* pjq) {
    if (!pjq) {
        return 0;
    }
    return pjq->buf_size - pjq->size;
}


/*
 * TODO: you must implement this function.
 *  Hint:
 *      - see pri_jobqeue_new
 */
void pri_jobqueue_delete(pri_jobqueue_t* pjq) {
    if (pjq) {
        free(pjq);
    }
}
