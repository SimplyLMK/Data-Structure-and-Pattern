#include "VigenereForwardIterator.h"

VigenereForwardIterator::VigenereForwardIterator(iVigenereStream& aIStream)
	:fIStream(aIStream), fCurrentChar(0), fEOF(aIStream.eof())
{
	if (!fEOF)
		fIStream >> fCurrentChar;
}

// overload the dereference operator to get value iterator is pointing at
char VigenereForwardIterator::operator*() const
{
	return fCurrentChar;
}

// overload the  pre-fix increment operator (++i) 
// returns the original value before incrementing
VigenereForwardIterator& VigenereForwardIterator::operator++()
{
	fIStream >> fCurrentChar;
	fEOF = fIStream.eof();
	return *this;
}

// also increment overload, but for the post-fix increment (i++)
// returns the updated value
VigenereForwardIterator VigenereForwardIterator::operator++(int)
{
	VigenereForwardIterator tmp = *this;
	++(*this);
	return tmp;
}

// compare two iterators to see if they're pointing to the same position or not.
// {
bool VigenereForwardIterator::operator==(const VigenereForwardIterator& aOther) const
{
	return (&fIStream == &aOther.fIStream) && (fEOF == aOther.fEOF);
}

bool VigenereForwardIterator::operator!=(const VigenereForwardIterator& aOther) const
{
	return !(*this == aOther);
}
// }

//returns an iterator pointing to the beginning of the stream
VigenereForwardIterator VigenereForwardIterator::begin() const
{
	VigenereForwardIterator lResult = *this; //copy the current iterator using the copy constructor
	lResult.fIStream.reset();
	lResult.fEOF = lResult.fIStream.eof(); // end of the stream has been reached
	if (!lResult.fEOF)
		lResult.fIStream >> lResult.fCurrentChar; // else reads the first character
	return lResult;
}
//returns an iterator pointing to the end of the stream
VigenereForwardIterator VigenereForwardIterator::end() const
{
	VigenereForwardIterator lResult = *this;
	lResult.fEOF = true;
	return lResult;
}