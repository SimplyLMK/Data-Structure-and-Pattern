#include"Vigenere.h"
#include<string>


void Vigenere::initializeTable()
{
	for (char row = 0; row < CHARACTERS; row++)
	{
		char lChar = 'B' + row;
		for (char column = 0; column < CHARACTERS; column++)
		{
			if (lChar > 'Z')
				lChar = 'A';
			fMappingTable[row][column] = lChar++;
		}
	}
}

Vigenere::Vigenere(const std::string& aKeyword) : fKeyword(aKeyword), fKeywordProvider(aKeyword)
{
   initializeTable();
}

std::string Vigenere::getCurrentKeyword()
{
	std::string result;

	for (size_t i = 0;i < fKeyword.length();i++)
	{
		result += *fKeywordProvider;
		fKeywordProvider << *fKeywordProvider;
	}

	return result;
}


void Vigenere::reset()
{
	fKeywordProvider.initialize(fKeyword);
}


// my approach is uppercasing the input, encode and return the lowercase version
// well the original state of a character should also be checked to return correct case
char Vigenere::encode(char aCharacter)
{
	char upperChar = static_cast<char>(toupper(aCharacter));

	// only perform the encryption if its a valid character.
	if (isalpha(upperChar))
	{
		// Get the encoded character from the mapping table using the current keyword character and the input character
		char encodedChar = fMappingTable[*fKeywordProvider - 'A'][upperChar - 'A'];

		// Append the input character to the keyword provider
		fKeywordProvider << upperChar;

		// Check if the OG character was lowercase
		if (islower(aCharacter))
		{
			// If the OG character was lowercase, convert the encoded character to lowercase
			return char(tolower(encodedChar));
		}
		else
		{
			// leave the encoded character as uppercase
			return encodedChar;
		}
	}
	else
	{
		return aCharacter;
	}
}


// similar to encode
char Vigenere::decode(char aCharacter)
{
	if (isalpha(aCharacter))
	{
		char upperChar = static_cast<char>(toupper(aCharacter));
		char decoded = 0;

		// Check if the input character matches any character in the mapping table for the current keyword character
		for (char col = 0; col < CHARACTERS; col++)
		{
			if (fMappingTable[*fKeywordProvider - 'A'][col] == upperChar)
			{
				decoded = char(col + 'A');
				break;
			}
		}
		fKeywordProvider << decoded;

		if (islower(aCharacter))
		{
			return char(tolower(decoded));
		}
		else
		{
			return decoded;
		}
		
	}
	else
	{
		return aCharacter;
	}
}
