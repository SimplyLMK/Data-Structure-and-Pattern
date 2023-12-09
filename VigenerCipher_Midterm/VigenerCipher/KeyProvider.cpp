#include"KeyProvider.h"
#include<iostream>
#include<algorithm>

KeyProvider::KeyProvider(const std::string& aKeyword): fKeyword(nullptr), fsize(0), fIndex(0)
{

	fsize = aKeyword.size();
	//memcpy(fKeyword, aKeyword.c_str(), fsize);

	fKeyword = new char[fsize]; // allocate heap memory the size of fsize 

	for (int i = 0; i < fsize; i++)
	{
		fKeyword[i] = std::toupper(aKeyword[i]);
	}
	fIndex = 0;
	
}

KeyProvider::~KeyProvider()
{
	delete[] fKeyword;
}

void KeyProvider::initialize(const std::string& aKeyword)
{
	delete[] fKeyword;

	fsize = aKeyword.size();

	fKeyword = new char[fsize];

	for (int i = 0; i < fsize; i++)
	{
		fKeyword[i] = std::toupper(aKeyword[i]);
	}
	fIndex = 0;

}

char KeyProvider :: operator*() const
{
	return fKeyword[fIndex];
};


KeyProvider& KeyProvider::operator<<(char aKeyCharacter)
{
	if (std::isalpha(aKeyCharacter))
	{
		// Convert the input character to uppercase and store it in the keyword array
		fKeyword[fIndex] = std::toupper(aKeyCharacter);

		// Modulus to wrap it around if it reaches fsize
		fIndex = (fIndex + 1) % fsize;
	}
	return *this;
}
