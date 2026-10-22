#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "parcel.h"

typedef struct ParcelNode {
    Parcel parcel;
    struct ParcelNode *next;
} ParcelNode;

/* Create a new node */
ParcelNode* createNode(Parcel parcel);

/* Add a parcel to the end of the list */
void insertParcel(ParcelNode **head, Parcel parcel);

/* Display all parcels */
void displayParcels(const ParcelNode *head);

/* Search for a parcel by ID */
ParcelNode* searchParcel(ParcelNode *head, int parcelId);

/* Delete a parcel by ID */
int deleteParcel(ParcelNode **head, int parcelId);

/* Count the number of parcels */
int countParcels(const ParcelNode *head);

/* Free the linked list */
void freeList(ParcelNode **head);

#endif