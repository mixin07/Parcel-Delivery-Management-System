#include <stdio.h>
#include <stdlib.h>

#include "../include/linked_list.h"

ParcelNode* createNode(Parcel parcel) {
    ParcelNode *newNode = (ParcelNode*)malloc(sizeof(ParcelNode));

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    newNode->parcel = parcel;
    newNode->next = NULL;

    return newNode;
}

void insertParcel(ParcelNode **head, Parcel parcel) {
    ParcelNode *newNode = createNode(parcel);

    if (newNode == NULL) {
        return;
    }

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    ParcelNode *current = *head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
}

void displayParcels(const ParcelNode *head) {
    if (head == NULL) {
        printf("\nNo parcels found.\n");
        return;
    }

    const ParcelNode *current = head;

    printf("\n========== PENDING PARCELS ==========\n");

    while (current != NULL) {
        displayParcel(&current->parcel);
        current = current->next;
    }
}

ParcelNode* searchParcel(ParcelNode *head, int parcelId) {
    ParcelNode *current = head;

    while (current != NULL) {
        if (current->parcel.parcelId == parcelId) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

int deleteParcel(ParcelNode **head, int parcelId) {
    if (*head == NULL) {
        return 0;
    }

    ParcelNode *current = *head;
    ParcelNode *previous = NULL;

    while (current != NULL) {

        if (current->parcel.parcelId == parcelId) {

            if (previous == NULL) {
                *head = current->next;
            } else {
                previous->next = current->next;
            }

            free(current);
            return 1;
        }

        previous = current;
        current = current->next;
    }

    return 0;
}

int countParcels(const ParcelNode *head) {
    int count = 0;
    const ParcelNode *current = head;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

void freeList(ParcelNode **head) {
    ParcelNode *current = *head;

    while (current != NULL) {
        ParcelNode *next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}