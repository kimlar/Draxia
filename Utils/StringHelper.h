#ifndef __STRINGHELPER_H__
#define __STRINGHELPER_H__

#include <string>         // std::string
#include <locale>         // std::locale, std::toupper

//
// Prototypes
//
//std::string ToUpper(std::string text);	// Converts a string to upper case
//std::string ToLower(std::string text);	// Converts a string to lower case
//
//#else // For the implementation

// Converts a string to upper case
inline std::string ToUpper(std::string text)
{
	std::locale loc;
	for (std::string::size_type i = 0; i < text.length(); ++i)
		text[i] = std::toupper(text[i], loc);

	return text;
}

// Converts a string to lower case
inline std::string ToLower(std::string text)
{
	std::locale loc;
	for (std::string::size_type i = 0; i < text.length(); ++i)
		text[i] = std::tolower(text[i], loc);

	return text;
}

#endif // __STRINGHELPER_H__
