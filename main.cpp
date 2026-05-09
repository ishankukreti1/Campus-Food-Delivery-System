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
        cout << "\n=====================================\n";
        cout << "   CAMPUS FOOD DELIVERY SYSTEM\n";
        cout << "=====================================\n";
        cout << "1. Place Order\n";
        cout << "2. Process Orders\n";
        cout << "3. View Orders\n";
        cout << "4. Exit\n";
        cout << "-------------------------------------\n";
        cout << "Enter choice: ";
        cin >> choice;

        if(choice == 1) {
            placeOrder(orders, &n);
        }

        else if(choice == 2) {

            if(n == 0) {
                cout << "\nNo orders to process!\n";
                continue;
            }

            cout << "\n========== PROCESSING ORDERS ==========\n";

            
            for(int i = 0; i < n; i++) {
                if(!orders[i].delivered)
                    orders[i].priority += 5;
            }

            
            mergeSort(orders, 0, n - 1);

            
            assignDelivery(orders, n, 5);

            
            int g[10][10] = {
                {0, 2, 4, 6},
                {2, 0, 1, 7},
                {4, 1, 0, 3},
                {6, 7, 3, 0}
            };

            int dist[10];

          
            dijkstra(g, 4, 0, dist);

            
            knapsack(orders, n, 5, dist);
        }

        else if(choice == 3) {
            displayOrders(orders, n);
        }

    } while(choice != 4);

    cout << "\nExiting system...\n";
    return 0;
}