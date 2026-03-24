#include <iostream>
#include <climits>
using namespace std;

int minDist(int d[], bool v[], int n) {
    int m = INT_MAX, idx = -1;

    for(int i=0;i<n;i++) {
        if(!v[i] && d[i] < m) {
            m = d[i];
            idx = i;
        }
    }
    return idx;
}

void dijkstra(int g[][10], int n, int src) {

    int d[10];
    bool v[10];

    for(int i=0;i<n;i++) {
        d[i] = INT_MAX;
        v[i] = false;
    }

    d[src] = 0;

    for(int i=0;i<n-1;i++) {
        int u = minDist(d,v,n);
        v[u] = true;

        for(int j=0;j<n;j++) {
            if(!v[j] && g[u][j] && d[u] + g[u][j] < d[j])
                d[j] = d[u] + g[u][j];
        }
    }

    char loc[4][20] = {"Canteen","BlockB","HostelA","Library"};

    cout << "\nShortest Distances:\n";
    for(int i=0;i<n;i++) {
        cout << "Canteen -> " << loc[i]
             << " = " << d[i] << " units\n";
    }
}
