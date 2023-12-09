#pragma once
#include<string>

class KeyProvider
{
private: 
	char* fKeyword;
	size_t fsize;
	size_t fIndex;

public:
	KeyProvider(const std::string& aKeyword);
	~KeyProvider();

	void initialize(const std::string& aKeyword);

	char operator*() const;

	KeyProvider& operator<<(char aKeyCharacter);


};