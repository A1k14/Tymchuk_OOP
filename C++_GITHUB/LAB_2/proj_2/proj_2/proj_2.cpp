
/* Задано текст, який складається з 16 рядків до 4 символів у рядку. Доповнити пробілами рядки
до 16 символів. Шифрувати тексти таким чином, щоб кожний символ тексту записувався у два
байти. Два байти мають таку структуру:
у бітах 0-3 знаходиться номер рядка символу (4 біти),
у бітах 4-7 молодша частина ASCII - коду символу (4 біти),
8 біт – біт парності перших двох полів (1 біт)
у бітах 9-12 старша частина ASCII - коду символу (4 біти),
у бітах 13-14 позиція символу в рядку (2 біти),
15 біт - біт парності попередніх двох полів (1 біт). */

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

struct TextCode {
    unsigned short schkb : 4;   // молодша частина ASCII
    unsigned short posrow : 4;  // номер рядка
    unsigned short bitp : 1;     // біт парності
    unsigned short mchkb : 4;    // старша частина ASCII
    unsigned short poscol : 4;   // позиція символу в рядку
};


int main() {
    char S[16][5]; 
    TextCode Rez[64];

    
    ifstream ifs("tsk.txt");
    if (!ifs) {
        cout << "Файл tsk.txt не відкритий" << endl;
        return 1;
    }

    
    for (int i = 0; i < 16; i++) {
        ifs.getline(S[i], 5); 
        for (int j = strlen(S[i]); j < 4; j++) {
            S[i][j] = ' ';
        }
        S[i][4] = '\0'; 
    }
    ifs.close(); 

    // Виклик функції шифрування
    

   
    ofstream ofsb("outbs.bin", ios::out | ios::binary);
    if (!ofsb) {
        cout << "Файл outbs.bin не відкритий" << endl;
        return 1;
    }
    ofsb.write((char*)Rez, 64 * sizeof(TextCode));
    ofsb.close();
    cout << "Дані записані у outbs.bin" << endl;

    return 0;
}