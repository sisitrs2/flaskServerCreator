//
// Copyright(c) 2018 Daniel Arad.
//
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
// ---------------------------------------------------------------------
// File: FileEdit.cpp
// ---------------------------------------------------------------------

#include "FileEdit.h"


FileEdit::FileEdit(const std::string &file) : _file(file), _isReplaced(true)
{
	initFileType(); //Unnecessary yet.
	initLines();
}

FileEdit::FileEdit(const std::string &src, const std::string &dst) : _file(src), _newFile(dst), _isReplaced(false)
{
	initFileType(); //Unnecessary yet.
	initLines();
}

FileEdit::~FileEdit()
{
	saveChanges();
}

void FileEdit::replaceAll(const std::string &toRemove, const std::string &newStr)
{
	for(Line& line : _lines)
	{
		line.replace(toRemove, newStr);
	}
}

void FileEdit::replaceAll(const std::string &toRemove, const std::string &newStr, const std::string &var)
{
	unsigned long beforeSize; //toRemove length of part before var.
	unsigned long afterSize;
	unsigned long varSize; //length of var
	unsigned int beforeStart; //start of before part in toRemove (0)
	unsigned long afterStart; //start of after part in toRemove
	long beforePos; //position of part before var in Line.
	long afterPos; //position of part after var in Line.
	unsigned long toRemoveSize;

	unsigned int newBeforeStart;
	unsigned long newBeforeSize;
	unsigned long newAfterStart;
	unsigned long newAfterSize;
	unsigned long newStrSize;

	varSize = var.length();
	newStrSize = newStr.length();
	newBeforeStart = 0;
	newBeforeSize = newStr.find(var);
	newAfterSize = newStrSize - newBeforeSize - varSize;
	newAfterStart = newStrSize - newAfterSize;

	toRemoveSize = toRemove.length();
	beforeSize = toRemove.find(var);
	afterSize = toRemoveSize - beforeSize - varSize;
	beforeStart = 0;
	afterStart = toRemoveSize - afterSize;


	for(Line& line : _lines)
	{
		beforePos = line.find(toRemove.substr(0, beforeSize));
		if(beforePos != std::string::npos)
		{
			afterPos = line.find(toRemove.substr(afterStart, toRemoveSize), beforePos + beforeSize);
			if(afterPos != std::string::npos)
			{
				line.replace(toRemove.substr(afterStart, afterSize), newStr.substr(newAfterStart, newAfterSize), beforePos + beforeSize);
				line.replace(toRemove.substr(beforeStart, beforeSize), newStr.substr(newBeforeStart, newBeforeSize));
			}
		}
	}
}

void FileEdit::initFileType()
{
	unsigned int dotPos;
	unsigned int fileNameLength;

	dotPos = _file.find_last_of('.');

	if(dotPos != std::string::npos)
	{
		fileNameLength = _file.length();
		_fileType = _file.substr(dotPos, fileNameLength);
	}
	else
	{
		_fileType = "";
	}
}

void FileEdit::initLines()
{
	std::ifstream file(_file);
	std::string line;

	while(std::getline(file, line))
	{
		_lines.emplace_back(Line(line));
	}
	file.close();
}

void FileEdit::saveChanges() const
{
	std::ofstream file;
	if(_isReplaced)
	{
		remove(_file.c_str());
		file.open(_file);
	}
	else
	{
		file.open(_newFile);
	}
	if (file.is_open())
	{
		for(const Line& line : _lines)
		{
			file << line.getLine() << '\n';
		}
		file.close();
	}
}

std::vector<Line> &FileEdit::getLines()
{
	return _lines;
}

void FileEdit::operator<<(const std::string &str)
{
	this->_lines.emplace_back(Line(str));
}



Line::Line(const std::string &str) : _line(str){}

Line::Line(const Line &line) : _line(line.getLine()) {}

const std::string &Line::getLine() const
{
	return _line;
}

void Line::setLine(const std::string &str)
{
	_line = str;
}

void Line::setLine(const Line line)
{
	_line = line.getLine();
}

unsigned long Line::length() const
{
	return _line.length();
}

unsigned long Line::find(const std::string &str) const
{
	return _line.find(str);
}

unsigned long Line::find(const std::string &str, const unsigned long &pos) const
{
	return _line.find(str, pos);
}

void Line::append(const std::string &str)
{
	_line += str;
}

void Line::append(const Line &line)
{
	_line += line.getLine();
}

void Line::remove(const std::string &str)
{
	unsigned long size; //str length
	long pos = -1; //position in _line
	size = str.length();
	pos = _line.find(str);
	if(pos != -1) //if str was found in _line.
	{
		//the string in middle of _line gets cut of.
		_line = _line.substr(0, pos) + _line.substr(pos + size, _line.length());
	}
}

void Line::remove(const Line &line)
{
	std::string str = line.getLine();
	unsigned long size; //str length
	unsigned long pos; //position in _line
	size = str.length();
	pos = _line.find(str);
	if(pos != std::string::npos) //if str was found in _line.
	{
		//the string in middle of _line gets cut of.
		_line = _line.substr(0, pos) + _line.substr(pos + size, _line.length());
	}
}

void Line::replace(const std::string &src, const std::string &dst)
{
	unsigned long size; //str length
	unsigned long pos; //position in _line
	size = src.length();
	pos = _line.find(src);
	if(pos != std::string::npos) //if str was found in _line.
	{
		//the string in middle of _line gets replaced.
		_line = _line.substr(0, pos)  + dst + _line.substr(pos + size, _line.length());
	}
}

void Line::replace(const std::string &src, const std::string &dst, const unsigned long& pos)
{
	unsigned long size; //str length
	unsigned long posInLine; //position in _line
	size = src.length();
	posInLine = _line.find(src, pos);
	if(posInLine != std::string::npos) //if str was found in _line.
	{
		//the string in middle of _line gets replaced.
		_line = _line.substr(0, posInLine)	+ dst + _line.substr(posInLine + size, _line.length());
	}
}

std::string Line::operator+(const std::string &str) const
{
	return _line + str;
}

std::string Line::operator-(const std::string &str) const
{
	unsigned long size; //str length
	long pos = -1; //position in _line
	size = str.length();
	pos = _line.find(str);
	if(pos != -1) //if str was found in _line.
	{
		//the string in middle of _line gets cut of.
		return _line.substr(0, pos) + _line.substr(pos + size, _line.length());
	}
	return _line; //if string was not found.
}

Line &Line::operator+=(const std::string &str)
{
	append(str);
	return *this;
}

Line &Line::operator+=(const Line &line)
{
	append(line);
	return *this;
}

Line &Line::operator-=(const std::string &str)
{
	remove(str);
	return *this;
}

Line &Line::operator-=(const Line &line)
{
	remove(line);
	return *this;
}

Line &Line::operator=(const std::string &str)
{
	setLine(str);
	return *this;
}

Line &Line::operator=(const Line &line)
{
	setLine(line);
	return *this;
}

Line &Line::operator<<(const std::string &str)
{
	append(str);
	return *this;
}

Line &Line::operator<<(const Line &line)
{
	append(line);
	return *this;
}

