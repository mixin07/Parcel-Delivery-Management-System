#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/file_handler.h"
#include "../include/search.h"

int loadParcelsFromFile(
    ParcelNode **parcelList,
    Queue *normalQueue,
    PriorityQueue *priorityQueue,
    CompletedNode **completedList
) {
    FILE *file = fopen(DATA_FILE_PATH, "r");
    if (file == NULL) {
        return 0;
    }

    char line[256];
    int loadedCount = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0) {
            continue;
        }

        int parcelId;
        char customerName[NAME_SIZE];
        char destination[DESTINATION_SIZE];
        int priority;
        int status;

        int parsed = sscanf(line, "%d|%49[^|]|%49[^|]|%d|%d",
                           &parcelId, customerName, destination, &priority, &status);

        if (parsed != 5) {
            continue;
        }

        if (priority < 1 || priority > 3) {
            continue;
        }

        if (status < 0 || status > 3) {
            continue;
        }

        if (searchParcelById(*parcelList, parcelId) != NULL) {
            continue;
        }

        Parcel parcel;
        initializeParcel(&parcel, parcelId, customerName, destination, (Priority)priority);
        parcel.status = (ParcelStatus)status;

        insertParcel(parcelList, parcel);

        if (parcel.status == PENDING) {
            if (parcel.priority == NORMAL) {
                enqueue(normalQueue, parcel);
            } else {
                insertPriorityParcel(priorityQueue, parcel);
            }
        } else if (parcel.status == DELIVERED) {
            addCompletedParcel(completedList, parcel);
        }

        loadedCount++;
    }

    fclose(file);
    return loadedCount;
}

int saveParcelsToFile(const ParcelNode *parcelList) {
    FILE *file = fopen(DATA_FILE_PATH, "w");
    if (file == NULL) {
        return 0;
    }

    const ParcelNode *current = parcelList;
    int savedCount = 0;

    while (current != NULL) {
        fprintf(file, "%d|%s|%s|%d|%d\n",
                current->parcel.parcelId,
                current->parcel.customerName,
                current->parcel.destination,
                current->parcel.priority,
                current->parcel.status);
        savedCount++;
        current = current->next;
    }

    fclose(file);
    return savedCount;
}