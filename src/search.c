#include <stdio.h>

#include "../include/search.h"

ParcelNode* searchParcelById(ParcelNode *head, int parcelId) {

    ParcelNode *current = head;

    while (current != NULL) {

        if (current->parcel.parcelId == parcelId) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

void displaySearchResult(ParcelNode *head, int parcelId) {

    ParcelNode *result = searchParcelById(head, parcelId);

    printf("\n========== PARCEL SEARCH ==========\n");

    if (result == NULL) {
        printf("Parcel ID %d was not found.\n", parcelId);
    } else {
        printf("Parcel found successfully!\n");
        displayParcel(&result->parcel);
    }

    printf("===================================\n");
}