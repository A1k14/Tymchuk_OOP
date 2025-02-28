#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, M;

    cout << "N = ";
    cin >> N;

    cout << "M = ";
    cin >> M;

    vector<int> A(N);
    vector<int> B(M);
    int CMAS = N + M;
    vector<int> C(CMAS);

    int c1 = 0;

    for (int i = 0; i < N; i++) {
        cout << "A[" << i + 1 << "] = ";
        cin >> A[i];
    }

    for (int i = 0; i < M; i++) {
        cout << "B[" << i + 1 << "] = ";
        cin >> B[i];
    }

    for (int i = 0; i < N; i++) {
        if (A[i] >= 0) {
            C[c1] = A[i];
            c1++;
        }
    }

    for (int i = 0; i < M; i++) {
        if (B[i] >= 0) {
            C[c1] = B[i];
            c1++;
        }
    }

    for (int i = 0; i < N; i++) {
        if (A[i] < 0) {
            C[c1] = A[i];
            c1++;
        }
    }

    for (int i = 0; i < M; i++) {
        if (B[i] < 0) {
            C[c1] = B[i];
            c1++;
        }
    }

    cout << "Answer: ";

	cout << "C = ";

    for (int i = 0; i < CMAS; i++) {
        cout << C[i] << " ";
    }

    return 0;
}