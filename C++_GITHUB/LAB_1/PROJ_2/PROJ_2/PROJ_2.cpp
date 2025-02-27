#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;

    cout << "Ak = ";
    cin >> n;
    int ak = n;

    cout << "bk = ";
    cin >> m;
    int bk = m;

    if (ak > bk) {
        cout << "Ak must < bk." << endl;
        return 1;
    }

    int mas1;
    cout << "Element: ";
    cin >> mas1;

    vector<int> mas(mas1);

    for (int i = 0; i < mas1; ) {
        cout << "write number (max: " << mas1 << ") for masive: ";
        cin >> mas[i];

        if (mas[i] < ak || mas[i] > bk) {
            cout << "It`m can`t be." << endl;
        }
        else {
            i++;
        }
    }

    int num = 0;
    for (int i = 0; i < mas1; i++) {
        if (mas[i] > 0) {
            num = i + 1;
            break;
        }
    }

    int max = 0;

    for (int i = num; i < mas1; i++) {
        if (mas[i] > max) {
            max = mas[i];
        }
    }

    cout << "This your max: " << max << endl;
    return 0;
}
