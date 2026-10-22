#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parcel.h"
#include "../include/linked_list.h"
#include "../include/queue.h"
#include "../include/priority_queue.h"
#include "../include/search.h"
#include "../include/sort.h"
#include "../include/completed.h"
#include "../include/file_handler.h"


void clearInputBuffer(void) {

    int c;

    while (
        (c = getchar()) != '\n' &&
        c != EOF
    ) {
        /* Clear remaining input */
    }
}


void readString(
    const char *prompt,
    char *buffer,
    int size
) {

    printf("%s", prompt);

    if (
        fgets(buffer, size, stdin) != NULL
    ) {

        buffer[
            strcspn(buffer, "\n")
        ] = '\0';
    }
}


int readInteger(
    const char *prompt
) {

    int value;


    while (1) {

        printf("%s", prompt);


        if (
            scanf("%d", &value) == 1
        ) {

            clearInputBuffer();

            return value;
        }


        printf(
            "Invalid input. Please enter a number.\n"
        );


        clearInputBuffer();
    }
}


void displayMenu(void) {

    printf("\n");

    printf(
        "===============================================\n"
    );

    printf(
        "       PARCEL DELIVERY MANAGEMENT SYSTEM       \n"
    );

    printf(
        "===============================================\n"
    );

    printf("  1. Add Parcel\n");

    printf(
        "  2. Display Pending Parcels\n"
    );

    printf(
        "  3. Process Next Parcel\n"
    );

    printf(
        "  4. Search Parcel\n"
    );

    printf(
        "  5. Cancel Parcel\n"
    );

    printf(
        "  6. Display Completed Parcels\n"
    );

    printf(
        "  7. Sort Parcels by Priority\n"
    );

    printf(
        "  8. Display All Parcels\n"
    );

    printf("  9. Exit\n");

    printf(
        "===============================================\n"
    );
}


void addNewParcel(
    ParcelNode **parcelList,
    Queue *normalQueue,
    PriorityQueue *priorityQueue
) {

    Parcel parcel;


    printf(
        "\n========== ADD NEW PARCEL ==========\n"
    );


    parcel.parcelId =
        readInteger(
            "Enter Parcel ID: "
        );


    /*
     * Prevent duplicate Parcel IDs.
     */
    if (
        searchParcelById(
            *parcelList,
            parcel.parcelId
        ) != NULL
    ) {

        printf(
            "\nParcel ID already exists.\n"
        );

        return;
    }


    readString(
        "Enter Customer Name: ",
        parcel.customerName,
        NAME_SIZE
    );


    readString(
        "Enter Destination: ",
        parcel.destination,
        DESTINATION_SIZE
    );


    printf("\nSelect Priority:\n");

    printf("1. Normal\n");

    printf("2. Express\n");

    printf("3. Urgent\n");


    int priorityChoice =
        readInteger(
            "Enter Priority: "
        );


    while (
        priorityChoice < 1 ||
        priorityChoice > 3
    ) {

        printf(
            "Invalid priority.\n"
        );


        priorityChoice =
            readInteger(
                "Enter Priority: "
            );
    }


    parcel.priority =
        (Priority)priorityChoice;


    parcel.status =
        PENDING;


    /*
     * Add parcel to master linked list.
     */
    insertParcel(
        parcelList,
        parcel
    );


    /*
     * Normal parcels use FIFO queue.
     *
     * Express and Urgent parcels use
     * the priority queue.
     */
    if (
        parcel.priority == NORMAL
    ) {

        enqueue(
            normalQueue,
            parcel
        );

    } else {

        insertPriorityParcel(
            priorityQueue,
            parcel
        );
    }


    printf(
        "\nParcel added successfully!\n"
    );


    displayParcel(
        &parcel
    );
}


void displayPendingParcels(
    ParcelNode *parcelList
) {

    printf(
        "\n========== PENDING PARCELS ==========\n"
    );


    if (parcelList == NULL) {

        printf(
            "No parcels found.\n"
        );

        printf(
            "=====================================\n"
        );

        return;
    }


    ParcelNode *current =
        parcelList;


    int count = 0;


    while (current != NULL) {

        if (
            current->parcel.status ==
            PENDING
        ) {

            displayParcel(
                &current->parcel
            );

            count++;
        }


        current =
            current->next;
    }


    if (count == 0) {

        printf(
            "No pending parcels.\n"
        );
    }


    printf(
        "=====================================\n"
    );
}


void processNextParcel(
    ParcelNode *parcelList,
    Queue *normalQueue,
    PriorityQueue *priorityQueue,
    CompletedNode **completedList
) {

    Parcel nextParcel;

    ParcelNode *masterNode =
        NULL;


    /*
     * Process Express/Urgent parcels first.
     */
    while (
        !isPriorityQueueEmpty(
            priorityQueue
        )
    ) {

        if (
            !removeHighestPriority(
                priorityQueue,
                &nextParcel
            )
        ) {

            break;
        }


        masterNode =
            searchParcelById(
                parcelList,
                nextParcel.parcelId
            );


        /*
         * Only pending parcels can be delivered.
         */
        if (
            masterNode != NULL &&
            masterNode->parcel.status ==
            PENDING
        ) {

            masterNode->parcel.status =
                DELIVERED;


            nextParcel.status =
                DELIVERED;


            addCompletedParcel(
                completedList,
                nextParcel
            );


            printf(
                "\n========== PROCESSING NEXT PARCEL ==========\n"
            );


            displayParcel(
                &nextParcel
            );


            printf(
                "\nParcel delivered successfully!\n"
            );


            return;
        }
    }


    /*
     * If no Express/Urgent parcel is available,
     * process Normal parcels using FIFO.
     */
    while (
        !isQueueEmpty(
            normalQueue
        )
    ) {

        if (
            !dequeue(
                normalQueue,
                &nextParcel
            )
        ) {

            break;
        }


        masterNode =
            searchParcelById(
                parcelList,
                nextParcel.parcelId
            );


        /*
         * Only pending parcels can be delivered.
         */
        if (
            masterNode != NULL &&
            masterNode->parcel.status ==
            PENDING
        ) {

            masterNode->parcel.status =
                DELIVERED;


            nextParcel.status =
                DELIVERED;


            addCompletedParcel(
                completedList,
                nextParcel
            );


            printf(
                "\n========== PROCESSING NEXT PARCEL ==========\n"
            );


            displayParcel(
                &nextParcel
            );


            printf(
                "\nParcel delivered successfully!\n"
            );


            return;
        }
    }


    printf(
        "\nNo pending parcels available for processing.\n"
    );
}


void searchParcelMenu(
    ParcelNode *parcelList
) {

    int parcelId =
        readInteger(
            "\nEnter Parcel ID to search: "
        );


    displaySearchResult(
        parcelList,
        parcelId
    );
}


void cancelParcel(
    ParcelNode *parcelList,
    Queue *normalQueue,
    PriorityQueue *priorityQueue
) {

    int parcelId =
        readInteger(
            "\nEnter Parcel ID to cancel: "
        );


    ParcelNode *node =
        searchParcelById(
            parcelList,
            parcelId
        );


    if (node == NULL) {

        printf(
            "\nParcel not found.\n"
        );

        return;
    }


    /*
     * Only pending parcels can be cancelled.
     */
    if (
        node->parcel.status != PENDING
    ) {

        printf(
            "\nParcel cannot be cancelled.\n"
        );


        printf(
            "Current Status: %s\n",
            getStatusName(
                node->parcel.status
            )
        );


        return;
    }


    /*
     * Remove the parcel from the
     * appropriate processing queue.
     */
    int removedFromQueue = 0;


    if (
        node->parcel.priority == NORMAL
    ) {

        removedFromQueue =
            removeParcelFromQueue(
                normalQueue,
                parcelId
            );

    } else {

        removedFromQueue =
            removeParcelFromPriorityQueue(
                priorityQueue,
                parcelId
            );
    }


    /*
     * Change status only after the
     * parcel has been found as pending.
     */
    node->parcel.status =
        CANCELLED;


    printf(
        "\nParcel cancelled successfully.\n"
    );


    if (removedFromQueue) {

        printf(
            "Parcel removed from processing queue.\n"
        );

    } else {

        /*
         * This should normally not happen,
         * but the system remains safe if
         * the parcel was not found in its queue.
         */
        printf(
            "Parcel was not present in the processing queue.\n"
        );
    }


    displayParcel(
        &node->parcel
    );
}


void displayAllParcels(
    ParcelNode *parcelList
) {

    printf(
        "\n========== ALL PARCELS ==========\n"
    );


    if (parcelList == NULL) {

        printf(
            "No parcels available.\n"
        );


        printf(
            "================================\n"
        );


        return;
    }


    ParcelNode *current =
        parcelList;


    while (current != NULL) {

        displayParcel(
            &current->parcel
        );


        current =
            current->next;
    }


    printf(
        "================================\n"
    );
}


int main(void) {

    /*
     * Master linked list.
     *
     * Contains all registered parcels:
     *
     * Pending
     * Delivered
     * Cancelled
     */
    ParcelNode *parcelList =
        NULL;


    Queue normalQueue;


    PriorityQueue priorityQueue;


    CompletedNode *completedList =
        NULL;


    initializeQueue(
        &normalQueue
    );


initializePriorityQueue(
        &priorityQueue
    );

    loadParcelsFromFile(
        &parcelList,
        &normalQueue,
        &priorityQueue,
        &completedList
);

    int choice;

    do {

        displayMenu();


        choice =
            readInteger(
                "Enter your choice: "
            );


        switch (choice) {


            case 1:

                addNewParcel(
                    &parcelList,
                    &normalQueue,
                    &priorityQueue
                );

                break;


            case 2:

                displayPendingParcels(
                    parcelList
                );

                break;


            case 3:

                processNextParcel(
                    parcelList,
                    &normalQueue,
                    &priorityQueue,
                    &completedList
                );

                break;


            case 4:

                searchParcelMenu(
                    parcelList
                );

                break;


            case 5:

                cancelParcel(
                    parcelList,
                    &normalQueue,
                    &priorityQueue
                );

                break;


            case 6:

                displayCompletedParcels(
                    completedList
                );

                break;


            case 7:

                /*
                 * Sorting only displays the
                 * sorted order.
                 *
                 * Master linked list remains unchanged.
                 */
                sortParcelsByPriority(
                    parcelList
                );

                break;


            case 8:

                displayAllParcels(
                    parcelList
                );

                break;


            case 9:

                printf(
                    "\nExiting Parcel Delivery "
                    "Management System...\n"
                );

                saveParcelsToFile(parcelList);

                break;


            default:

                printf(
                    "\nInvalid choice. "
                    "Please try again.\n"
                );
        }


    } while (
        choice != 9
    );


    /*
     * Free all dynamically allocated memory.
     */
    freeList(
        &parcelList
    );


    freeQueue(
        &normalQueue
    );


    freePriorityQueue(
        &priorityQueue
    );


    freeCompletedParcels(
        &completedList
    );


    return 0;
}