#include <cstring>
#include "sorting.h"

void merge(Order arr[], int l, int m, int r) {
    Order temp[100];
    int i=l, j=m+1, k=0;

    while(i<=m && j<=r) {
        if(strcmp(arr[i].location, arr[j].location) < 0)
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while(i<=m) temp[k++] = arr[i++];
    while(j<=r) temp[k++] = arr[j++];

    for(i=l, k=0; i<=r; i++, k++)
        arr[i] = temp[k];
}

void mergeSort(Order arr[], int l, int r) {
    if(l<r) {
        int m=(l+r)/2;
        mergeSort(arr,l,m);
        mergeSort(arr,m+1,r);
        merge(arr,l,m,r);
    }
}