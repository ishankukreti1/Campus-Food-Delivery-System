#include <iostream>
#include "job.h"
using namespace std;

void assignDelivery(Order orders[], int n, int boys) {

    for(int i=0;i<n-1;i++) {
        for(int j=0;j<n-i-1;j++) {
            if(orders[j].priority < orders[j+1].priority) {
                Order t = orders[j];
                orders[j] = orders[j+1];
                orders[j+1] = t;
            }
        }
    }

    cout << "\nDelivery Assignment:\n";

    for(int i=0;i<n && i<boys;i++) {
        cout << "Delivery Boy " << i+1
             << " -> Order ID " << orders[i].id
             << " (Priority: " << orders[i].priority << ")\n";
    }

    if(n > boys)
        cout << "Remaining orders will be delivered later\n";
}
