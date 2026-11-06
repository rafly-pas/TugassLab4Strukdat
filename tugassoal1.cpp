#include <iostream>
#include <queue>
#include <cctype>
using namespace std;

const int N = 6;

int adj[N][N] = {0};
bool visited[N];

int toIndex(char c) {
    return toupper(c) - 'A';
}

void bfs(int start) {
    queue<int> q;
    for (int i = 0; i < N; i++) visited[i] = false;

    visited[start] = true;
    q.push(start);

    cout << "Urutan BFS: ";
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << char('A' + u) << " ";

        for (int v = 0; v < N; v++) {
            if (adj[u][v] == 1 && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    cout << endl;
}

void printMatrix() {
    cout << "\nAdjacency Matrix:\n  ";
    for (int i = 0; i < N; i++) cout << char('A' + i) << " ";
    cout << endl;
    for (int i = 0; i < N; i++) {
        cout << char('A' + i) << " ";
        for (int j = 0; j < N; j++) cout << adj[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

int main() {
    system("cls");
    int jumlahEdge;
    cout << "Masukkan jumlah edge: ";
    cin >> jumlahEdge;

    cout << "Masukkan edge (contoh: A B)\n";
    for (int i = 0; i < jumlahEdge; i++) {
        char a, b;
        cout << "Edge ke-" << i + 1 << ": ";
        cin >> a >> b;
        int u = toIndex(a), v = toIndex(b);

        if (u < 0 || u >= N || v < 0 || v >= N) {
            cout << "Vertex tidak valid (harus A-F), ulangi.\n";
            i--;
            continue;
        }
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    printMatrix();

    char s;
    cout << "Masukkan vertex awal (A-F): ";
    cin >> s;
    int start = toIndex(s);
    if (start < 0 || start >= N) {
        cout << "Vertex awal tidak valid.\n";
        return 1;
    }

    bfs(start);
    return 0;
}