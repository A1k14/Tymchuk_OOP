

#include <iostream>

int main()
{
    std::cout << " a, b, d, c = \n";
	int a, b, d, c;
    std::cin >> a >> b >> d >> c;

	// (18*a + 312*d)/512 - b * 122 + c * 123

	int resultat;

	resultat = (a + a +  (a<< 4) + (8 << d) + (6 << d) + d+ d) / 512 - b * 122 + c * 123;


	return 0;

}