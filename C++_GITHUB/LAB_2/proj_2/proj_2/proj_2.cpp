
/* ������ �����, ���� ���������� � 16 ����� �� 4 ������� � �����. ��������� �������� �����
�� 16 �������. ��������� ������ ����� �����, ��� ������ ������ ������ ����������� � ���
�����. ��� ����� ����� ���� ���������:
� ���� 0-3 ����������� ����� ����� ������� (4 ���),
� ���� 4-7 ������� ������� ASCII - ���� ������� (4 ���),
8 �� � �� ������� ������ ���� ���� (1 ��)
� ���� 9-12 ������ ������� ASCII - ���� ������� (4 ���),
� ���� 13-14 ������� ������� � ����� (2 ���),
15 �� - �� ������� ��������� ���� ���� (1 ��). */

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

struct TextCode {
    unsigned short schkb : 4;   // ������� ������� ASCII
    unsigned short posrow : 4;  // ����� �����
    unsigned short bitp : 1;     // �� �������
    unsigned short mchkb : 4;    // ������ ������� ASCII
    unsigned short poscol : 4;   // ������� ������� � �����
};


int main() {
    char S[16][5]; 
    TextCode Rez[64];

    
    ifstream ifs("tsk.txt");
    if (!ifs) {
        cout << "���� tsk.txt �� ��������" << endl;
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

    // ������ ������� ����������
    

   
    ofstream ofsb("outbs.bin", ios::out | ios::binary);
    if (!ofsb) {
        cout << "���� outbs.bin �� ��������" << endl;
        return 1;
    }
    ofsb.write((char*)Rez, 64 * sizeof(TextCode));
    ofsb.close();
    cout << "��� ������� � outbs.bin" << endl;

    return 0;
}