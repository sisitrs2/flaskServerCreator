//
// Created by daniel on 6/25/18.
//

#include "Website.h"

Website::Website(const std::string& path) : _path(path)
{
    addFiles();
}

const std::vector<std::string> &Website::getTemplates() const
{
    return _templates;
}

const std::string &Website::getAssets() const
{
    return _assets;
}

const std::string& Website::getPath() const
{
    return _path;
}

void Website::addFiles()
{
    std::vector<std::string> files; //files and directories
    std::string dotName;

    getFiles(files);

    for(const std::string& file : files) // for(each value in vector : vector) - Added in c++11
    {
        dotName = getFileType(file);
        if(dotName == "html")
        {
            _templates.push_back(file);
        }
        else if (dotName.empty() && (file == "assets" || file == "Assets"))
        {
            _assets = file;
        }
        else
        {
            std::cout << "Loose file: " + file << '\n';
        }
        std::cout << std::endl; //Space paragraph and flush buffer.
    }
}

std::string Website::getFileType(const std::string& file)
{
    std::size_t pos;
    pos = file.find_last_of('.');
    if(pos != std::string::npos)
    {
        return( file.substr(pos + 1, file.length()) ); //returns word AFTER dot.
    }
    return("");
}

void Website::getFiles(std::vector<std::string>& files)
{
    std::string output; //store exec function output.
    std::size_t pos;
    std::string cmd = "cd " + _path + "; ls";

    output = exec(cmd); //ls - shell command that lists unhidden files and directories in directory.

    while( (pos = output.find('\n')) != std::string::npos )
    {
        files.push_back(output.substr(0, pos));
        output = output.substr(pos + 1);
    }
}

std::string Website::exec(const std::string& cmd) const
{
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}

