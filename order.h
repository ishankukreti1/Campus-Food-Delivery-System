#ifndef ORDER_H
#define ORDER_H
#include <iostream>
using namespace std;

struct Order {
    int id;
    char name[50];
    char location[50];
    int items[10], qty[10], itemCount;
    int price, priority, delivered;
    char summary[200], compressed[500];
};

void placeOrder(Order orders[], int *n);
void displayOrders(Order orders[], int n);
int calculatePriority(int price, int urgency);

#endif
