#ifndef ORDER_H
#define ORDER_H

#include <cstring>

struct Order {
    int id;
    char name[50];
    char location[50];
    
    int delivered; 
    int items[10];
    int qty[10];
    int itemCount;

    int price;
    int priority;
};

void placeOrder(Order orders[], int *n);

#endif
