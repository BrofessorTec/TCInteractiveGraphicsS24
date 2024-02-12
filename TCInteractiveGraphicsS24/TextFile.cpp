#include "TextFile.h"
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>


TextFile::TextFile()
{

}


void TextFile::ReadFile(std::string filePath)
{
	std::stringstream ss;
	std::ifstream fin{};
	fin.open(filePath.c_str());
	if (fin.fail()) {
		ss << "Could not open: " << filePath << std::endl;
		//return false; 
		return;
	}

	std::string line;
	while (!fin.eof()) {
		getline(fin, line);
		Trim(line);
		if (line != "") { // Skip blank lines
			ss << line << std::endl;
		}
	}
	fin.close();

	// You can get the data as a string by calling ss.str()
	data = ss.str();
}

void TextFile::Trim(std::string& str)
{
	const std::string delimiters = " \f\n\r\t\v";
	str.erase(str.find_last_not_of(delimiters) + 1);
	str.erase(0, str.find_first_not_of(delimiters));
}

const std::string& TextFile::GetString() const
{
	return data;
}
