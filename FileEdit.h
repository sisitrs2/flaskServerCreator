//
// Copyright(c) 2018 Daniel Arad.
//
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
// ---------------------------------------------------------------------
// File: FileEdit.h
// ---------------------------------------------------------------------

#ifndef FLASKSERVERCREATOR_FILEEDIT_H
#define FLASKSERVERCREATOR_FILEEDIT_H
#include <string>
#include <vector>
#include <fstream>
#include <cstring>


class Line;

class FileEdit {

public:

    explicit FileEdit(const std::string& file);
    FileEdit(const std::string& src, const std::string& dst);
    ~FileEdit();

    void saveChanges() const;

    // replaceAll function allow  a change on all lines in file.
    // if you a var string you may replace a container part of a string.
    //
    // example:
    // replace("href='{{x}}.html'", "source='{{x}}.js'", "{{x}}");
    //
    // In this case, strings like: href='myFile.html'
    // Would turn to: source='myFile.js'
    void replaceAll(const std::string& toRemove, const std::string& newStr);
    void replaceAll(const std::string& toRemove, const std::string& newStr, const std::string& var);
    std::vector<Line>& getLines();

    void operator<<(const std::string& str);

private:

    std::string _fileType;
    const std::string _file;
    std::string _newFile;
    const bool _isReplaced; //If there is no dst file the file will be replaced with it's new instance.
    std::vector<Line> _lines;


    void initFileType();
    void initLines();

};


class Line {

public:

    explicit Line(const std::string& str);
    Line(const Line& line);

    const std::string& getLine() const;
    void setLine(const std::string& str);
    void setLine(const Line line);
    unsigned long length() const;
    unsigned long find(const std::string& str) const;
    unsigned long find(const std::string& str, const unsigned long& pos) const;
    void append(const std::string& str);
    void append(const Line& line);
    void remove(const std::string& str);
    void remove(const Line& line);
    void replace(const std::string& src, const std::string& dst);
    void replace(const std::string& src, const std::string& dst, const unsigned long& pos);
    /*Add change word*/
    /*Next step will be to add split and join options*/

    std::string operator+(const std::string& str) const;
    std::string operator-(const std::string& str) const;
    Line& operator+=(const std::string &str);
    Line& operator+=(const Line& line);
    Line& operator-=(const std::string &str);
    Line& operator-=(const Line& line);
    Line& operator=(const std::string& str);
    Line& operator=(const Line& line);
    Line& operator<<(const std::string& str);
    Line& operator<<(const Line& line);
private:

    std::string _line;

};

#endif //FLASKSERVERCREATOR_FILEEDIT_H
