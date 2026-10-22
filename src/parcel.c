#include <stdio.h>
#include <string.h>

#include "../include/parcel.h"

void initializeParcel(
    Parcel *parcel,
    int id,
    const char *customerName,
    const char *destination,
    Priority priority
) {
    if (parcel == NULL) {
        return;
    }

    parcel->parcelId = id;

    strncpy(parcel->customerName, customerName, NAME_SIZE - 1);
    parcel->customerName[NAME_SIZE - 1] = '\0';

    strncpy(parcel->destination, destination, DESTINATION_SIZE - 1);
    parcel->destination[DESTINATION_SIZE - 1] = '\0';

    parcel->priority = priority;
    parcel->status = PENDING;
}

const char* getPriorityName(Priority priority) {
    switch (priority) {
        case NORMAL:
            return "Normal";

        case EXPRESS:
            return "Express";

        case URGENT:
            return "Urgent";

        default:
            return "Unknown";
    }
}

const char* getStatusName(ParcelStatus status) {
    switch (status) {
        case PENDING:
            return "Pending";

        case IN_TRANSIT:
            return "In Transit";

        case DELIVERED:
            return "Delivered";

        case CANCELLED:
            return "Cancelled";

        default:
            return "Unknown";
    }
}

void displayParcel(const Parcel *parcel) {
    if (parcel == NULL) {
        return;
    }

    printf("\n----------------------------------------\n");
    printf("Parcel ID    : %d\n", parcel->parcelId);
    printf("Customer     : %s\n", parcel->customerName);
    printf("Destination  : %s\n", parcel->destination);
    printf("Priority     : %s\n", getPriorityName(parcel->priority));
    printf("Status       : %s\n", getStatusName(parcel->status));
    printf("----------------------------------------\n");
}