#include <iostream>
#include "knapsack.h"
using namespace std;

void knapsack(Order orders[], int n, int capacity, int dist[]) {

    int load = 0;

    cout << "\n=====================================\n";
    cout << "       KNAPSACK OPTIMIZATION\n";
    cout << "=====================================\n";

    cout << "Capacity : " << capacity << " items\n";
    cout << "-------------------------------------\n\n";

    for(int i = 0; i < n; i++) {

        if(orders[i].delivered == 1)
            continue;

        int totalWeight = 0;

        cout << "Batch Location : " << orders[i].location << endl;

        
        for(int j = i; j < n; j++) {
            if(orders[j].delivered == 0 &&
               strcmp(orders[i].location, orders[j].location) == 0) {

                for(int k = 0; k < orders[j].itemCount; k++) {
                    totalWeight += orders[j].qty[k];
                }
            }
        }

        if(load + totalWeight <= capacity) {

            cout << "Status          : SELECg++ main.cpp food_delivery.cpp dijkstra.cpp huffman.cpp job.cpp order.cpp sorting.cpp -o appTED (BATCHED)\n";

            
            for(int j = i; j < n; j++) {
                if(orders[j].delivered == 0 &&
                   strcmp(orders[i].location, orders[j].location) == 0) {

                    orders[j].delivered = 1;
                }
            }

            load += totalWeight;

            cout << "Batch Load      : " << totalWeight << endl;
            cout << "Current Load    : " << load << endl;

            
            int locIndex = -1;

            if(strcmp(orders[i].location, "Canteen") == 0) locIndex = 0;
            else if(strcmp(orders[i].location, "HostelB") == 0) locIndex = 1;
            else if(strcmp(orders[i].location, "HostelA") == 0) locIndex = 2;
            else if(strcmp(orders[i].location, "HostelC") == 0) locIndex = 3;

            if(locIndex != -1) {
                cout << "Delivery Time   : " << dist[locIndex] << " mins\n";
            }

        } else {
            cout << "Status          : SKIPPED (Capacity Exceeded)\n";
            cout << "Current Load    : " << load << endl;
        }

        cout << "-------------------------------------\n";
    }

    cout << "\nTotal Loaded Items : " << load << " / " << capacity << endl;
    cout << "=====================================\n";
}
