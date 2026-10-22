#include <stdio.h>
#include <stdlib.h>

#include "../include/completed.h"

void addCompletedParcel(CompletedNode **head, Parcel parcel) {

    if (head == NULL) {
        return;
    }

    CompletedNode *newNode =
        (CompletedNode *)malloc(sizeof(CompletedNode));

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    newNode->parcel = parcel;
    newNode->next = NULL;

    /*
     * Add the newest completed parcel
     * at the beginning of the history.
     */
    newNode->next = *head;
    *head = newNode;
}

void displayCompletedParcels(const CompletedNode *head) {

    printf("\n========== COMPLETED PARCELS ==========\n");

    if (head == NULL) {
        printf("No completed parcels found.\n");
        printf("=======================================\n");
        return;
    }

    const CompletedNode *current = head;

    while (current != NULL) {
        displayParcel(&current->parcel);
        current = current->next;
    }

    printf("=======================================\n");
}

int countCompletedParcels(const CompletedNode *head) {

    int count = 0;

    const CompletedNode *current = head;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

void freeCompletedParcels(CompletedNode **head) {

    if (head == NULL) {
        return;
    }

    CompletedNode *current = *head;

    while (current != NULL) {

        CompletedNode *next = current->next;

        free(current);

        current = next;
    }

    *head = NULL;
}