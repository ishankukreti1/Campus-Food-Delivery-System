#include <iostream>
#include <cstring>
#include <limits>
#include "order.h"
#include "huffman.h"
using namespace std;

int calculatePriority(int price, int urgency){
    return price + urgency;
}

void placeOrder(Order orders[], int *n){

    Order o;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n=====================================\n";
    cout << "            PLACE ORDER\n";
    cout << "=====================================\n";

    cout << "Enter Name: ";
    cin.getline(o.name, 50);

    // LOCATION
    cout << "\nSelect Delivery Location:\n";
    cout << "-------------------------------------\n";
    cout << "1. Canteen\n";
    cout << "2. HostelB\n";
    cout << "3. HostelA\n";
    cout << "4. HostelC\n";
    cout << "-------------------------------------\n";
    cout << "Enter choice: ";

    int c;
    cin >> c;

    if(c==1) strcpy(o.location,"Canteen");
    else if(c==2) strcpy(o.location,"HostelB");
    else if(c==3) strcpy(o.location,"HostelA");
    else strcpy(o.location,"HostelC");

    o.price = 0;
    o.itemCount = 0;

    int ch;

    // MENU LOOP
    do{
        cout << "\n=====================================\n";
        cout << "                MENU\n";
        cout << "=====================================\n";

        cout << "1. Burger      - Rs 50\n";
        cout << "2. Pizza       - Rs 120\n";
        cout << "3. Sandwich    - Rs 40\n";
        cout << "4. Coffee      - Rs 60\n";
        cout << "5. Done\n";

        cout << "-------------------------------------\n";
        cout << "Select Item: ";
        cin >> ch;

        if(ch >= 1 && ch <= 4){

            o.items[o.itemCount] = ch;

            cout << "Enter Quantity: ";
            cin >> o.qty[o.itemCount];

            if(ch==1) o.price += 50 * o.qty[o.itemCount];
            if(ch==2) o.price += 120 * o.qty[o.itemCount];
            if(ch==3) o.price += 40 * o.qty[o.itemCount];
            if(ch==4) o.price += 60 * o.qty[o.itemCount];

            o.itemCount++;
        }

    } while(ch != 5);



    cout << "-------------------------------------\n";
    cout << "Total Bill : Rs " << o.price << endl;

    int u;
    cout << "\nEnter Urgency (10-50): ";
    
    cin >> u;
    if(u<10)
    {
        cout<<"Invalid Urgency, should be between 10-50. Enter Again: ";
        cin>>u;
    }
    

    o.priority = calculatePriority(o.price, u);
    o.delivered = 0;
    o.id = *n + 1;

    // HUFFMAN SUMMARY (WITH SPACES)
    strcpy(o.summary, o.name);
    strcat(o.summary, " ");

    for(int i=0;i<o.itemCount;i++){
        if(o.items[i]==1) strcat(o.summary,"Burger ");
        if(o.items[i]==2) strcat(o.summary,"Pizza ");
        if(o.items[i]==3) strcat(o.summary,"Sandwich ");
        if(o.items[i]==4) strcat(o.summary,"Coffee ");
    }

    strcat(o.summary, o.location);



    // COMPRESS
    compress(o.summary, o.compressed);

    orders[*n] = o;
    (*n)++;

    cout << "\n-------------------------------------\n";
    cout << "Order Placed Successfully!\n";
    cout << "Order ID : " << o.id << endl;
    cout << "-------------------------------------\n";
}


// VIEW ORDERS
void displayOrders(Order orders[], int n){

    cout << "\n=====================================\n";
    cout << "             ALL ORDERS\n";
    cout << "=====================================\n";

    for(int i = 0; i < n; i++){

        cout << "\nOrder ID : " << orders[i].id << endl;

        cout << "-------------------------------------\n";

        char out[200];
        decompress(orders[i].compressed, out);

        cout << "Order Summary:\n";
        cout << out << endl;

        cout << "-------------------------------------\n";

    }
}
