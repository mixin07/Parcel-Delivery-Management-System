#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "parcel.h"
#include "linked_list.h"
#include "queue.h"
#include "priority_queue.h"
#include "completed.h"

#define DATA_FILE_PATH "data/parcels.txt"

int loadParcelsFromFile(
    ParcelNode **parcelList,
    Queue *normalQueue,
    PriorityQueue *priorityQueue,
    CompletedNode **completedList
);

int saveParcelsToFile(const ParcelNode *parcelList);

#endif