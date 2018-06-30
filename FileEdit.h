//
// Created by daniel on 6/30/18.
//

#ifndef FLASKSERVERCREATOR_FILEEDIT_H
#define FLASKSERVERCREATOR_FILEEDIT_H
#include <string>
#include <vector>
#include <fstream>
#include <cstring>

#define NEW_TEMP_FILE "FileEdit"

class Line;

class FileEdit {

    FileEdit() = default;
    explicit FileEdit(const std::string& file);
    FileEdit(const std::string& src, const std::string& dst);
    ~FileEdit();

    void open(const std::string& file);
    void open(const std::string& src, const std::string& dst);
    void close();
    void saveChanges() const;
    /***
     * replaceAll function allow  a change on all lines in file.
     * if you a var string you may replace a container part of a string.
     *
     * example:
     * replace("href='{{x}}.html'", "source='{{x}}.js'", "{{x}}");
     *
     * In this case, strings like: href='myFile.html'
     * Would turn to: source='myFile.js'
     *
     */
    void replaceAll(const std::string& toRemove, const std::string& newStr);
    void replaceAll(const std::string& toRemove, const std::string& newStr, const std::string& var);


private:

    std::string _fileType;
    std::string _file;
    std::string _newFile;
    bool _isReplaced; //If there is no dst file the file will be replaced with it's new instance.
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
    void setLine(const Line& line);
    unsigned long length() const;
    unsigned long find(const std::string& str) const;
    void append(const std::string& str);
    void append(const Line& line);
    void remove(const std::string& str);
    void remove(const Line& line);
    void replace(const std::string& src, const std::string& dst);
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



private:

    std::string _line;

};

#endif //FLASKSERVERCREATOR_FILEEDIT_H