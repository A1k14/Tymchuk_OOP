

#include <iostream>

int main()
{
    std::cout << " a, b, d, c = \n";
	int a, b, d, c;
    std::cin >> a >> b >> d >> c;

	// (18*a + 312*d)/512 - b * 122 + c * 123

	int resultat1, resultat2;

	resultat1 = (((a << 4) + (a << 1) + (d << 8) + (d << 5) + (d << 3)) >> 9)- ((b << 7) - (b << 2) - (b << 1)) + ((c << 7) - (c << 2) - c);
	resultat2 = (18 * a + 312 * d) / 512 - b * 122 + c * 123;




	std::cout << "Resultat = " << resultat1 << std::endl;
	std::cout << "Resultat = " << resultat2 << std::endl;


	return 0;

}