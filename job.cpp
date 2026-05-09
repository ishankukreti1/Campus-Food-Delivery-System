#include <iostream>
#include <cstring>
#include "job.h"
using namespace std;

int getLocationIndex(char location[]) {

    if(strcmp(location, "Canteen") == 0) return 0;
    if(strcmp(location, "HostelB") == 0) return 1;
    if(strcmp(location, "HostelA") == 0) return 2;
    if(strcmp(location, "HostelC") == 0) return 3;

    return -1;
}

void assignDelivery(Order orders[], int n, int boys) {

    cout << "\n=====================================\n";
    cout << "        DELIVERY ASSIGNMENT\n";
    cout << "=====================================\n";

    int used[100] = {0};
    int boy = 1;
    int capacity = 5;

    int g[4][4] = {
        {0,2,4,6},
        {2,0,1,7},
        {4,1,0,3},
        {0,7,3,0}
    };

    for(int i = 0; i < n; i++) {

        if(used[i] == 1)
            continue;

        int currentLoad = 0;

        cout << "\n-------------------------------------\n";
        cout << "Delivery Boy : " << boy << endl;

        // FIRST ORDER
        int weight = 0;
        for(int k = 0; k < orders[i].itemCount; k++) {
            weight += orders[i].qty[k];
        }
        cout << "Batching orders for location: " << orders[i].location << endl;

        cout << "Assigned Orders:\n";
        cout << "Order ID : " << orders[i].id << endl;

        currentLoad += weight;
        used[i] = 1;

        // GROUP SAME LOCATION
        for(int j = i + 1; j < n; j++) {

            if(strcmp(orders[i].location, orders[j].location) == 0 && used[j] == 0) {

                int w = 0;
                for(int k = 0; k < orders[j].itemCount; k++) {
                    w += orders[j].qty[k];
                }

                if(currentLoad + w <= capacity) {
                    cout << "Order ID : " << orders[j].id << endl;
                    currentLoad += w;
                    used[j] = 1;
                }
            }
        }

        // DISTANCE + TIME
        int locIndex = getLocationIndex(orders[i].location);
        int distance = 0;

        if(locIndex != -1)
            distance = g[0][locIndex];

        int time = distance * 2;

        cout << "-------------------------------------\n";
        cout << "Location : " << orders[i].location << endl;
        cout << "Distance : " << distance << endl;
        cout << "Time     : " << time << " mins\n";
        cout << "Load     : " << currentLoad << endl;
        cout << "-------------------------------------\n";

        boy++;

        if(boy > boys)
            boy = 1;
    }

    cout << "\n=====================================\n";
}