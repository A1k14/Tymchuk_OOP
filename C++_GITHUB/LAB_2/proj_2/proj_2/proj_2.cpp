/*
������ ����� ASCII (��������� �����), ���� ���������� � 64 ����.
�������� ������� ���������� �� ������������� �������� ������.
����� ��� ��������� ����� ������ ���� �������� � �������,
���� ���������� � ���� ����� �� �� ���������:
  -  � ���� 0-3 ������ �������, ����� ��� 4-7 ASCII - ���� ����� (4 ���) - ����,
  -  � ���� 4-10 ������� ����� � ����� (7 ���) - ���,
  -  � ���� 12-15 ������� �������, ����� ��� 0-3 ASCII - ���� ����� (4 ���) - ����,
  -  11 �� � �� ������� ���������� ������ (1 ��)  -��.
  -    15 14 13 12  11  10 09 08 07 06 05 04 03 02 01 00
	   | ����    | |��| |     ���          | |   ����  |
*/

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

int main(char InS[64], unsigned short OutCoding[64])
{
	
		unsigned char c;
		unsigned short r, t, i, b;
		short j;
		for (i = 0; i < 64; i++)            //
		{
			r = 0;                        // 0000 0000 0000 0000
			c = InS[i];                     // s - 0x73 = 0111 0011
			t = c;
			r |= t >> 4;                  // 0000 0000 0000 0111
			r |= i << 4;                  // 0000 0000 0101 0111  if i=5 -> 0000 0000 0000 0101
			t = c;
			r |= t << 12;                 // 0011 0000 0101 0111  if i=5 0000 0000 0000 0101
			t = 1;
			b = 0;
			for (j = 0; j < 16; j++)         // ���������� ��� �������
			{
				if (r & t) {
					if (b == 0) b = 1; else b = 0;
				}
				t <<= 1;
			}
			r |= b << 11;                    // 0011 0000 0101 0111 if i=5 0000 0000 0000 0101
			OutCoding[i] = r;
		}
	}
	struct TextCode {
		unsigned short schkb : 4;
		unsigned short posrow : 7;
		unsigned short bitp : 1;
		unsigned short mchkb : 4;

	};
	unsigned char pbit(unsigned char c)
	{
		unsigned char t = 1, b = 0;
		for (int j = 0; j < 8; j++)         // ���������� ��� �������
		{
			if (c & t) {
				if (b == 0) b = 1; else b = 0;
			}
			t <<= 1;
		}
		return b;
	}
	void MyEncryptionS(char InS[64], TextCode OutCoding[64])
	{
		unsigned char c;
		unsigned short r, t, i;
		short j;
		for (i = 0; i < 64; i++)            //
		{
			c = InS[i];                     // s - 0x73 = 0111 0011
			OutCoding[i].schkb = c >> 4;
			OutCoding[i].mchkb = c & 0x0f;
			OutCoding[i].posrow = i;
			r = pbit(c);
			t = pbit(static_cast<unsigned char>(i));
			OutCoding[i].bitp = r ^ t;
		}
	}

	int MyDecryption(char OutS[64], unsigned short InCoding[64]) {

		unsigned char c;
		unsigned short r, t, i, b, p, w;
		short j;
		for (i = 0; i < 64; i++)            //
		{
			// �������� �������
			r = InCoding[i];
			t = r & 0b1111011111111111;      //  0xf7ff			1111 0111 1111 1111
			p = r & 0b0000100000000000;      //  0x0800			0000 1000 0000 0000
			w = 1;
			b = 0;
			for (j = 0; j < 16; j++)         // ���������� ��� �������
			{
				if (t & w) {
					if (b == 0) b = 1; else b = 0;
				}
				w <<= 1;
			}
			p >>= 11;
			if (p != b)  return -i;
			t = r & 0b1111000000000000;  // 0xf000
			t >>= 12;
			w = r & 0b0000000000001111;  // 0x000f
			w <<= 4;
			t |= w;
			p = r & 0b0000011111110000;  // 0x07f
			p >>= 4;
			OutS[p] = (unsigned char)t;
		}
		return 1;
	
}