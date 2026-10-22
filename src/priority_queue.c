#include <stdio.h>
#include <stdlib.h>

#include "../include/priority_queue.h"


void initializePriorityQueue(
    PriorityQueue *queue
) {

    if (queue == NULL) {
        return;
    }

    queue->front = NULL;
    queue->size = 0;
}


int isPriorityQueueEmpty(
    const PriorityQueue *queue
) {

    return queue == NULL ||
           queue->front == NULL;
}


void insertPriorityParcel(
    PriorityQueue *queue,
    Parcel parcel
) {

    if (queue == NULL) {
        return;
    }


    PriorityQueueNode *newNode =
        (PriorityQueueNode *)malloc(
            sizeof(PriorityQueueNode)
        );


    if (newNode == NULL) {

        printf(
            "Memory allocation failed.\n"
        );

        return;
    }


    newNode->parcel = parcel;
    newNode->next = NULL;


    /*
     * Insert at front if:
     *
     * 1. Queue is empty
     * OR
     * 2. New parcel has higher priority
     */
    if (
        queue->front == NULL ||
        parcel.priority >
        queue->front->parcel.priority
    ) {

        newNode->next =
            queue->front;

        queue->front =
            newNode;

        queue->size++;

        return;
    }


    PriorityQueueNode *current =
        queue->front;


    /*
     * Move through parcels having
     * equal or higher priority.
     *
     * This preserves FCFS order
     * for equal priorities.
     */
    while (
        current->next != NULL &&
        current->next->parcel.priority >=
        parcel.priority
    ) {

        current =
            current->next;
    }


    newNode->next =
        current->next;

    current->next =
        newNode;


    queue->size++;
}


int removeHighestPriority(
    PriorityQueue *queue,
    Parcel *parcel
) {

    if (
        isPriorityQueueEmpty(queue)
    ) {

        return 0;
    }


    PriorityQueueNode *temp =
        queue->front;


    if (parcel != NULL) {

        *parcel =
            temp->parcel;
    }


    queue->front =
        temp->next;


    free(temp);

    queue->size--;


    return 1;
}


int peekHighestPriority(
    const PriorityQueue *queue,
    Parcel *parcel
) {

    if (
        isPriorityQueueEmpty(queue)
    ) {

        return 0;
    }


    if (parcel != NULL) {

        *parcel =
            queue->front->parcel;
    }


    return 1;
}


int removeParcelFromPriorityQueue(
    PriorityQueue *queue,
    int parcelId
) {

    if (
        isPriorityQueueEmpty(queue)
    ) {

        return 0;
    }


    PriorityQueueNode *current =
        queue->front;

    PriorityQueueNode *previous =
        NULL;


    while (current != NULL) {

        if (
            current->parcel.parcelId ==
            parcelId
        ) {

            /*
             * Removing the first node.
             */
            if (previous == NULL) {

                queue->front =
                    current->next;

            } else {

                /*
                 * Removing a middle or
                 * last node.
                 */
                previous->next =
                    current->next;
            }


            free(current);

            queue->size--;


            return 1;
        }


        previous = current;

        current = current->next;
    }


    /*
     * Parcel ID was not found.
     */
    return 0;
}


void displayPriorityQueue(
    const PriorityQueue *queue
) {

    if (
        isPriorityQueueEmpty(queue)
    ) {

        printf(
            "\nPriority queue is empty.\n"
        );

        return;
    }


    const PriorityQueueNode *current =
        queue->front;


    printf(
        "\n========== PRIORITY PARCEL QUEUE ==========\n"
    );


    while (current != NULL) {

        displayParcel(
            &current->parcel
        );

        current =
            current->next;
    }


    printf(
        "===========================================\n"
    );
}


int getPriorityQueueSize(
    const PriorityQueue *queue
) {

    if (queue == NULL) {
        return 0;
    }


    return queue->size;
}


void freePriorityQueue(
    PriorityQueue *queue
) {

    if (queue == NULL) {
        return;
    }


    PriorityQueueNode *current =
        queue->front;


    while (current != NULL) {

        PriorityQueueNode *next =
            current->next;

        free(current);

        current = next;
    }


    queue->front = NULL;
    queue->size = 0;
}