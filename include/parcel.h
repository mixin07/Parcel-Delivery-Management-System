#ifndef PARCEL_H
#define PARCEL_H

#define NAME_SIZE 50
#define DESTINATION_SIZE 50

typedef enum {
    NORMAL = 1,
    EXPRESS = 2,
    URGENT = 3
} Priority;

typedef enum {
    PENDING,
    IN_TRANSIT,
    DELIVERED,
    CANCELLED
} ParcelStatus;

typedef struct {
    int parcelId;
    char customerName[NAME_SIZE];
    char destination[DESTINATION_SIZE];
    Priority priority;
    ParcelStatus status;
} Parcel;

void initializeParcel(
    Parcel *parcel,
    int id,
    const char *customerName,
    const char *destination,
    Priority priority
);

const char* getPriorityName(Priority priority);
const char* getStatusName(ParcelStatus status);

void displayParcel(const Parcel *parcel);

#endif