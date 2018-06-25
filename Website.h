//
// Created by Daniel(sisitrs2) on 6/25/18.
//

#ifndef FLASKSERVERCREATOR_WEBSITE_H
#define FLASKSERVERCREATOR_WEBSITE_H

#include <vector>
#include <string>

/*** Required for the exec function ***/
#include <memory>
/*** ***/


class Website {

public:

    explicit Website(std::string &path);

    const std::vector<std::string>& getTemplates() const;
    void setTemplates(const std::vector<std::string> &_templates);
    const std::vector<std::string>& getAssets() const;
    void setAssets(const std::vector<std::string> &_assets);

    /***
     * This functions get files from path and save them in class vectors
     * I would have put them as private but in case the path directory was
     * changed, and a file was added it should be too added to the templates
     * vector.
     */
    void addTemplates();
    void addAssets();

    /***
     * Function that takes shell command and return output.
     * found on stackoverflow: https://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c-using-posix
     * Credits to: waqas.
     */
    std::string exec(const char* cmd) const;

private:

    std::string _path;
    std::vector<std::string> _templates; //Holds names of .html files.
    std::vector<std::string> _assets;    //Holds names of directories.

};


#endif //FLASKSERVERCREATOR_WEBSITE_H
