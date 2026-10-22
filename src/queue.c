#include <stdio.h>
#include <stdlib.h>

#include "../include/queue.h"


void initializeQueue(Queue *queue) {

    if (queue == NULL) {
        return;
    }

    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}


int isQueueEmpty(const Queue *queue) {

    return queue == NULL ||
           queue->front == NULL;
}


void enqueue(
    Queue *queue,
    Parcel parcel
) {

    if (queue == NULL) {
        return;
    }


    QueueNode *newNode =
        (QueueNode *)malloc(
            sizeof(QueueNode)
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
     * If queue is empty,
     * new node becomes both
     * front and rear.
     */
    if (isQueueEmpty(queue)) {

        queue->front = newNode;
        queue->rear = newNode;

    } else {

        /*
         * Add new node at the rear.
         */
        queue->rear->next = newNode;

        queue->rear = newNode;
    }


    queue->size++;
}


int dequeue(
    Queue *queue,
    Parcel *parcel
) {

    if (isQueueEmpty(queue)) {
        return 0;
    }


    QueueNode *temp =
        queue->front;


    if (parcel != NULL) {

        *parcel =
            temp->parcel;
    }


    queue->front =
        queue->front->next;


    /*
     * If the queue becomes empty,
     * rear must also become NULL.
     */
    if (queue->front == NULL) {

        queue->rear = NULL;
    }


    free(temp);

    queue->size--;


    return 1;
}


int peekQueue(
    const Queue *queue,
    Parcel *parcel
) {

    if (isQueueEmpty(queue)) {
        return 0;
    }


    if (parcel != NULL) {

        *parcel =
            queue->front->parcel;
    }


    return 1;
}


int removeParcelFromQueue(
    Queue *queue,
    int parcelId
) {

    if (isQueueEmpty(queue)) {
        return 0;
    }


    QueueNode *current =
        queue->front;

    QueueNode *previous = NULL;


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


            /*
             * If the removed node was
             * the rear node, update rear.
             */
            if (current == queue->rear) {

                queue->rear =
                    previous;
            }


            free(current);

            queue->size--;


            /*
             * Keep front/rear consistent
             * if queue became empty.
             */
            if (queue->front == NULL) {

                queue->rear = NULL;
            }


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


void displayQueue(
    const Queue *queue
) {

    if (isQueueEmpty(queue)) {

        printf(
            "\nQueue is empty.\n"
        );

        return;
    }


    const QueueNode *current =
        queue->front;


    printf(
        "\n========== NORMAL PARCEL QUEUE ==========\n"
    );


    while (current != NULL) {

        displayParcel(
            &current->parcel
        );

        current =
            current->next;
    }


    printf(
        "=========================================\n"
    );
}


int getQueueSize(
    const Queue *queue
) {

    if (queue == NULL) {
        return 0;
    }


    return queue->size;
}


void freeQueue(
    Queue *queue
) {

    if (queue == NULL) {
        return;
    }


    QueueNode *current =
        queue->front;


    while (current != NULL) {

        QueueNode *next =
            current->next;

        free(current);

        current = next;
    }


    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}