#ifndef SEARCH_H
#define SEARCH_H

#include "linked_list.h"

/* Search for a parcel by its ID */
ParcelNode* searchParcelById(ParcelNode *head, int parcelId);

/* Display the result of a parcel search */
void displaySearchResult(ParcelNode *head, int parcelId);

#endif