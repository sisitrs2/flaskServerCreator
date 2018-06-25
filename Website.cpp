//
// Created by daniel on 6/25/18.
//

#include "Website.h"

Website::Website(std::string &path) : _path(path)
{
    //TODO: get templates from directory
    //TODO: get assets from directory
}

const std::vector<std::string> &Website::getTemplates() const
{
    return _templates;
}

void Website::setTemplates(const std::vector<std::string> &_templates)
{
    this->_templates = _templates;
}

const std::vector<std::string> &Website::getAssets() const
{
    return _assets;
}

void Website::setAssets(const std::vector<std::string> &_assets)
{
    this->_assets = _assets;
}

std::string Website::exec(const char* cmd) const
{
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}
