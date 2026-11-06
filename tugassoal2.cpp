#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cctype>
using namespace std;

const int N = 6;
const int INF = INT_MAX;

int graph[N][N] = {0};

void tambahJalan(char a, char b, int jarak) {
    int u = a - 'A', v = b - 'A';
    graph[u][v] = jarak;
    graph[v][u] = jarak;
}

void dijkstra(int src, int dist[], int parent[]) {
    bool done[N];
    for (int i = 0; i < N; i++) {
        dist[i] = INF;
        parent[i] = -1;
        done[i] = false;
    }
    dist[src] = 0;

    for (int count = 0; count < N - 1; count++) {
        int u = -1;
        for (int i = 0; i < N; i++)
            if (!done[i] && (u == -1 || dist[i] < dist[u])) u = i;

        if (u == -1 || dist[u] == INF) break;
        done[u] = true;

        for (int v = 0; v < N; v++) {
            if (graph[u][v] > 0 && !done[v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }
}

void printRute(int parent[], int tujuan) {
    vector<int> rute;
    for (int v = tujuan; v != -1; v = parent[v]) rute.push_back(v);
    reverse(rute.begin(), rute.end());

    for (size_t i = 0; i < rute.size(); i++) {
        cout << char('A' + rute[i]);
        if (i + 1 < rute.size()) cout << " -> ";
    }
}

int main() {
    system("cls");
    tambahJalan('A', 'B', 4);
    tambahJalan('A', 'C', 2);
    tambahJalan('B', 'C', 1);
    tambahJalan('B', 'D', 5);
    tambahJalan('B', 'E', 3);
    tambahJalan('C', 'D', 8);
    tambahJalan('C', 'E', 6);
    tambahJalan('D', 'E', 2);
    tambahJalan('D', 'F', 4);
    tambahJalan('E', 'F', 3);

    int dist[N], parent[N];

    dijkstra(0, dist, parent);
    cout << "=== Rute terpendek dari lokasi A ke semua lokasi ===\n";
    for (int i = 1; i < N; i++) {
        cout << "A ke " << char('A' + i) << " : ";
        printRute(parent, i);
        cout << "  (total jarak: " << dist[i] << " km)\n";
    }

    char asal, tujuan;
    cout << "\n=== Rekomendasi Rute ===\n";
    cout << "Masukkan lokasi asal (A-F): "; cin >> asal;
    cout << "Masukkan lokasi tujuan (A-F): "; cin >> tujuan;
    asal = toupper(asal);
    tujuan = toupper(tujuan);

    if (asal < 'A' || asal > 'F' || tujuan < 'A' || tujuan > 'F') {
        cout << "Lokasi tidak valid.\n";
        return 1;
    }

    int s = asal - 'A', t = tujuan - 'A';
    dijkstra(s, dist, parent);

    cout << "Rute tercepat: ";
    printRute(parent, t);
    cout << "\nTotal jarak  : " << dist[t] << " km\n";
    return 0;
}