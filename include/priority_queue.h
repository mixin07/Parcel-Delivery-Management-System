#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "parcel.h"


typedef struct PriorityQueueNode {
    Parcel parcel;
    struct PriorityQueueNode *next;
} PriorityQueueNode;


typedef struct {
    PriorityQueueNode *front;
    int size;
} PriorityQueue;


/* Priority queue initialization */
void initializePriorityQueue(
    PriorityQueue *queue
);


/* Check whether priority queue is empty */
int isPriorityQueueEmpty(
    const PriorityQueue *queue
);


/* Insert parcel according to priority */
void insertPriorityParcel(
    PriorityQueue *queue,
    Parcel parcel
);


/* Remove highest-priority parcel */
int removeHighestPriority(
    PriorityQueue *queue,
    Parcel *parcel
);


/* View highest-priority parcel */
int peekHighestPriority(
    const PriorityQueue *queue,
    Parcel *parcel
);


/* Remove a specific parcel by ID */
int removeParcelFromPriorityQueue(
    PriorityQueue *queue,
    int parcelId
);


/* Display priority queue */
void displayPriorityQueue(
    const PriorityQueue *queue
);


/* Get number of parcels */
int getPriorityQueueSize(
    const PriorityQueue *queue
);


/* Free priority queue memory */
void freePriorityQueue(
    PriorityQueue *queue
);

#endif