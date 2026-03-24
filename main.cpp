#include <iostream>
#include "order.h"
#include "sorting.h"
#include "job.h"
#include "knapsack.h"
#include "dijkstra.h"
using namespace std;

int main() {

    Order orders[100];
    int n = 0, choice;

    do {
        cout << "\n----------------------------------\n";
        cout << "1. Place Order\n2. Process Orders\n3. Exit\n";
        cout << "----------------------------------\n";
        cout << "Enter choice: ";
        cin >> choice;

        if(choice == 1) {
            placeOrder(orders, &n);
        }

        else if(choice == 2) {

            cout << "\n========== PROCESSING ORDERS ==========\n";

            mergeSort(orders, 0, n-1);

            cout << "\nOrders Grouped by Location:\n";
            for(int i=0;i<n;i++) {
                cout << "Order ID: " << orders[i].id
                     << " | Location: " << orders[i].location << endl;
            }

            assignDelivery(orders, n, 2);

            knapsack(orders, n, 5);

            int g[10][10] = {
                {0,2,4,0},
                {2,0,1,7},
                {4,1,0,3},
                {0,7,3,0}
            };

            dijkstra(g,4,0);
        }

    } while(choice != 3);

    return 0;
}
