#ifndef COMPLETED_H
#define COMPLETED_H

#include "parcel.h"

typedef struct CompletedNode {
    Parcel parcel;
    struct CompletedNode *next;
} CompletedNode;

/* Add a completed parcel to the history */
void addCompletedParcel(CompletedNode **head, Parcel parcel);

/* Display all completed parcels */
void displayCompletedParcels(const CompletedNode *head);

/* Count completed parcels */
int countCompletedParcels(const CompletedNode *head);

/* Free completed parcel history */
void freeCompletedParcels(CompletedNode **head);

#endif