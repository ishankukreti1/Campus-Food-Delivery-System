#include <iostream>
#include <cstring>
#include "order.h"
using namespace std;

int calculatePriority(int price, int urgency) {
    return price + urgency;
}

void placeOrder(Order orders[], int *n) {
    Order o;

    
    cin.ignore();
    cout << "Enter Name: ";
    cin.getline(o.name, 50);

    int locChoice;
    cout << "\nSelect Delivery Location:\n";
    cout << "1. Canteen\n2. BlockB\n3. HostelA\n4. Library\n";
    cin >> locChoice;

    if(locChoice == 1) strcpy(o.location, "Canteen");
    else if(locChoice == 2) strcpy(o.location, "BlockB");
    else if(locChoice == 3) strcpy(o.location, "HostelA");
    else if(locChoice == 4) strcpy(o.location, "Library");

    o.price = 0;
    o.itemCount = 0;

    int choice;

    do {
        cout << "\n------ MENU ------\n";
        cout << "1. Burger      - 50\n";
        cout << "2. Pizza       - 120\n";
        cout << "3. Sandwich    - 40\n";
        cout << "4. Coffee      - 60\n";
        cout << "5. Done\n";

        cout << "Select Item: ";
        cin >> choice;

        if(choice >= 1 && choice <= 4) {
            o.items[o.itemCount] = choice;

            cout << "Enter Quantity: ";
            cin >> o.qty[o.itemCount];

            if(choice == 1) o.price += 50 * o.qty[o.itemCount];
            if(choice == 2) o.price += 120 * o.qty[o.itemCount];
            if(choice == 3) o.price += 40 * o.qty[o.itemCount];
            if(choice == 4) o.price += 60 * o.qty[o.itemCount];

            o.itemCount++;
        }

    } while(choice != 5);

    cout << "\nItems Ordered:\n";
    for(int i = 0; i < o.itemCount; i++) {
        if(o.items[i] == 1) cout << "Burger x " << o.qty[i] << endl;
        if(o.items[i] == 2) cout << "Pizza x " << o.qty[i] << endl;
        if(o.items[i] == 3) cout << "Sandwich x " << o.qty[i] << endl;
        if(o.items[i] == 4) cout << "Coffee x " << o.qty[i] << endl;
    }

    cout << "Total Bill: " << o.price << endl;

    int urgency;
    cout << "Enter Urgency (10-50): ";
    cin >> urgency;

    o.priority = calculatePriority(o.price, urgency);
    o.delivered = 0;
    o.id = *n + 1;
    orders[*n] = o;
    (*n)++;

    cout << "Order Placed! ID: " << o.id << endl;
}