#include <iostream>
#include "knapsack.h"
using namespace std;

void knapsack(Order orders[], int n, int capacity) {

    int load = 0;

    cout << "\nOptimized Delivery (Knapsack):\n";
    cout << "Capacity = " << capacity << " items\n\n";

    for(int i = 0; i < n; i++) {

        if(orders[i].delivered == 1)
            continue;

        int weight = 0;

        for(int j = 0; j < orders[i].itemCount; j++) {
            weight += orders[i].qty[j];
        }

        cout << "Checking Order ID: " << orders[i].id
             << " (Items: " << weight << ")... ";

        if(load + weight <= capacity) {

            cout << "SELECTED\n";

            orders[i].delivered = 1;

            cout << "   -> Order ID: " << orders[i].id
                 << " | Location: " << orders[i].location
                 << endl;

            load += weight;
        }
        else {
            cout << "SKIPPED (Capacity Exceeded)\n";
        }
    }

    cout << "\nTotal Loaded: " << load << endl;
}