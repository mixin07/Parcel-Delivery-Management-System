#ifndef QUEUE_H
#define QUEUE_H

#include "parcel.h"


typedef struct QueueNode {
    Parcel parcel;
    struct QueueNode *next;
} QueueNode;


typedef struct {
    QueueNode *front;
    QueueNode *rear;
    int size;
} Queue;


/* Queue initialization */
void initializeQueue(Queue *queue);


/* Check whether queue is empty */
int isQueueEmpty(const Queue *queue);


/* Add parcel to rear */
void enqueue(Queue *queue, Parcel parcel);


/* Remove parcel from front */
int dequeue(Queue *queue, Parcel *parcel);


/* View parcel at front */
int peekQueue(const Queue *queue, Parcel *parcel);


/* Remove a specific parcel by ID */
int removeParcelFromQueue(
    Queue *queue,
    int parcelId
);


/* Display queue */
void displayQueue(const Queue *queue);


/* Get number of parcels */
int getQueueSize(const Queue *queue);


/* Free queue memory */
void freeQueue(Queue *queue);

#endif