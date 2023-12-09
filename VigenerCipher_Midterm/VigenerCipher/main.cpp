#include <string>
#include "KeyProvider.h"
#include <iostream>
#include "Vigenere.h"
#include "iVigenereStream.h"
#include "VigenereForwardIterator.h"

//#define P1
//#define P2
//#define P3
#define P4

using namespace std;
#ifdef P1

using namespace std;
int runP1(string argv[2])
{
	cout << "Testing KeyProvider with \"" << argv[0]
		<< "\" and \"" << argv[1] << "\"" << endl;
	KeyProvider lKeyWord(argv[0]);
	string& lMessage = argv[1];
	for (char c : lMessage)
	{
		if (isalpha(c))
		{
			cout << *lKeyWord;
			lKeyWord << c;
		}
		else
		{
			cout << ' ';
		}
	}
	cout << "\n";
	for (char c : lMessage)
	{
		cout << (isalpha(c) ? static_cast<char>(toupper(c)) : c);
	}
	cout << "\nCompleted" << endl;
	return 0;
}
#endif

#ifdef P2
int runP2(string argv[2])
{
	Vigenere lSrambler(argv[0]);
	string lMessage = argv[1];
	// Test encoding
	cout << "Encoding \"" << lMessage
		<< "\" using \"" << lSrambler.getCurrentKeyword() << "\"" << endl;
	for (char c : lMessage)
	{
		cout << (isalpha(c) ? static_cast<char>(toupper(c)) : c);
	}
	cout << "\n";
	string lEncodedMessage;
	for (char c : lMessage)
	{
		lEncodedMessage += lSrambler.encode(c);
	}
	cout << lEncodedMessage << "\nCompleted" << endl;
	// Test decoding
	lSrambler.reset();
	cout << "Decoding \"" << lEncodedMessage
		<< "\" using \"" << lSrambler.getCurrentKeyword() << "\"" << endl;
	for (char c : lEncodedMessage)
	{
		cout << (isalpha(c) ? static_cast<char>(toupper(c)) : c);
	}
	cout << "\n";
	string lDecodedMessage;
	for (char c : lEncodedMessage)
	{
		lDecodedMessage += lSrambler.decode(c);
	}
	cout << lDecodedMessage << "\nCompleted" << endl;
	return 0;
}
#endif 

#ifdef P3
int runP3(string argv[2])
{
	iVigenereStream lInput([](Vigenere& aCipherProvider, char aCharacter)
		{
			return aCipherProvider.decode(aCharacter);
		}, argv[0], argv[1].c_str());
	if (!lInput.good())
	{
		cerr << "Cannot open input file: " << argv[1] << endl;
		return 2;
	}
	cout << "Decoding \"" << argv[1] << "\" using \"" << argv[0] << "\"." << endl;
	char lCharacter;
	while (lInput >> lCharacter)
	{
		cout << lCharacter;
	}
	lInput.close();
	cout << "Completed." << endl;
	return 0;
}
#endif

#ifdef P4
int runP4(string argv[2])
{
	iVigenereStream lInput([](Vigenere& aCipherProvider, char aCharacter)
		{
			return aCipherProvider.encode(aCharacter);
		}, argv[0], argv[1].c_str());
	if (!lInput.good())
	{
		cerr << "Cannot open input file: " << argv[1] << endl;
		return 2;
	}
	cout << "Forward Iterator Decoding \"" << argv[1]
		<< "' using \"" << argv[0] << "\"." << endl;
	for (char c : VigenereForwardIterator(lInput))
	{
		cout << c;
	}
	lInput.close();
	cout << "Completed." << endl;
	return 0;
}
#endif

int main()
{
#ifdef P1
	string lArgv1[] = { "Relations", "To be, or not to be: that is the question:" };

	return runP1(lArgv1);
#endif

#ifdef P2
	string lArgv2[] = { "Relations", "To be, or not to be: that is the question:" };

	return runP2(lArgv2);
#endif

#ifdef P3
	string lArgv3[] = { "Relations", "sample_3.txt" };

	return runP3(lArgv3);
#endif

#ifdef P4
	string lArgv4[] = { "Relations", "sample_4.txt" };

	return runP4(lArgv4);
#endif
}
