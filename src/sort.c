#include <stdio.h>
#include <stdlib.h>

#include "../include/sort.h"


/*
 * Sort parcels by priority for display purposes.
 *
 * Priority:
 * 3 -> Urgent
 * 2 -> Express
 * 1 -> Normal
 *
 * The original linked list is NOT modified.
 *
 * Insertion Sort is performed on an array
 * of pointers to the parcels.
 */
void sortParcelsByPriority(ParcelNode *head) {

    if (head == NULL || head->next == NULL) {
        printf("\nNot enough parcels to sort.\n");
        return;
    }


    /*
     * Count the parcels in the linked list.
     */
    int count = countParcels(head);

    if (count <= 1) {
        printf("\nNot enough parcels to sort.\n");
        return;
    }


    /*
     * Create a temporary array of Parcel pointers.
     */
    Parcel **parcels =
        (Parcel **)malloc(count * sizeof(Parcel *));

    if (parcels == NULL) {
        printf("\nMemory allocation failed.\n");
        return;
    }


    /*
     * Store addresses of parcels from
     * the linked list into the array.
     */
    ParcelNode *current = head;

    int index = 0;

    while (current != NULL) {

        parcels[index] = &current->parcel;

        index++;

        current = current->next;
    }


    /*
     * Insertion Sort
     *
     * Higher priority values come first.
     *
     * Urgent  -> 3
     * Express -> 2
     * Normal  -> 1
     *
     * Equal priorities retain their
     * original order.
     */
    for (int i = 1; i < count; i++) {

        Parcel *key = parcels[i];

        int j = i - 1;


        while (
            j >= 0 &&
            parcels[j]->priority < key->priority
        ) {

            parcels[j + 1] = parcels[j];

            j--;
        }


        parcels[j + 1] = key;
    }


    /*
     * Display the sorted result.
     */
    printf("\n========== SORTED PARCELS ==========\n");

    for (int i = 0; i < count; i++) {

        displayParcel(parcels[i]);
    }

    printf("====================================\n");


    /*
     * Free the temporary array.
     *
     * The original linked list remains unchanged.
     */
    free(parcels);
}


/*
 * Display sorted parcels.
 *
 * This function is kept as part of the
 * sorting module interface.
 */
void displaySortedParcels(ParcelNode *head) {

    sortParcelsByPriority(head);
}