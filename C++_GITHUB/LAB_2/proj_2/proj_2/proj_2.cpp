#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>

using namespace std;

struct TextCode {
    unsigned short schkb : 4;   // Lower nibble of ASCII
    unsigned short posrow : 4;  // Row number (0-15)
    unsigned short bitp : 1;    // Parity bit (0/1)
    unsigned short mchkb : 4;   // Upper nibble of ASCII
    unsigned short poscol : 2;  // Column number (0-3)
};

static_assert(sizeof(TextCode) == 2, "TextCode must be 2 bytes!");

static unsigned char pbit(unsigned char c) {
    unsigned char parity = 0;
    for (int j = 0; j < 8; j++) {
        if (c & (1 << j)) {
            parity ^= 1;
        }
    }
    return parity;
}

static void MyEncryption(char InS[16][5], TextCode OutCoding[64]) {
    for (int row = 0; row < 16; row++) {
        for (int col = 0; col < 4; col++) {
            char c = InS[row][col];
            if (c == '\0') c = ' ';

            OutCoding[row * 4 + col].schkb = c & 0x0F;
            OutCoding[row * 4 + col].mchkb = (c >> 4) & 0x0F;

            OutCoding[row * 4 + col].posrow = row;
            OutCoding[row * 4 + col].poscol = col;

            unsigned char pos = row * 4 + col;
            OutCoding[row * 4 + col].bitp = pbit(c) ^ pbit(pos);
        }
    }
}

static void MyDecryption(TextCode InCoding[64], char OutS[16][5]) {
    for (int i = 0; i < 64; i++) {
        unsigned char c = (InCoding[i].mchkb << 4) | InCoding[i].schkb;
        OutS[InCoding[i].posrow][InCoding[i].poscol] = c;
    }
    for (int row = 0; row < 16; row++) {
        OutS[row][4] = '\0';
    }
}

int main() {
    char S[16][5] = { 0 };
    TextCode Rez[64];

    while (true) {
        cout << "Choose an option:\n1. Encrypt\n2. Decrypt\n3. Exit\n";
        int choice;
        cin >> choice;

        if (choice == 1) {
            ifstream infile("tsk.txt");
            if (!infile) {
                cout << "File tsk.txt not open" << endl;
                return 1;
            }

            for (int i = 0; i < 16; i++) {
                infile.getline(S[i], 5);
                int len = strlen(S[i]);
                for (int j = len; j < 4; j++) {
                    S[i][j] = ' ';
                }
                S[i][4] = '\0';
            }
            infile.close();

            MyEncryption(S, Rez);

            
            ofstream ofsb("outb.bin", ios::out | ios::binary);
            if (!ofsb) {
                cout << "File outb.bin not open" << endl;
            }
            else {
                ofsb.write((char*)Rez, 64 * sizeof(TextCode));
                ofsb.close();
                cout << "Data written to outb.bin" << endl;
            }

            cout << "\nEncrypted data:\n";
            for (int i = 0; i < 64; i++) {
                unsigned short encoded = (Rez[i].mchkb << 12) | (Rez[i].bitp << 11) | (Rez[i].posrow << 7) | (Rez[i].poscol << 5) | (Rez[i].schkb);
                cout << hex << setw(4) << setfill('0') << encoded << endl;
            }

        }
    
            else if (choice == 2) {

        ifstream ifsb("outb.bin", ios::in | ios::binary);
        if (!ifsb) {
            cout << "File outb.bin not open" << endl;
            return 1;
        }

        ifsb.read((char*)Rez, 64 * sizeof(TextCode));
        ifsb.close();

        char Decrypted[16][5] = { 0 };
        MyDecryption(Rez, Decrypted);

        cout << "Data read from outb.bin" << endl;
        cout << "String  ";
        for (int i = 0; i < 16; i++) {
            cout << Decrypted[i] << " ";
        }
        cout << endl;
        }
        
        else if (choice == 3) {
            cout << "Exiting the program." << endl;
            break; 
        }
        else {
            cout << "Invalid choice. Please select 1 for encryption, 2 for decryption, or 3 to exit." << endl;
        }
    }

    return 0;
}