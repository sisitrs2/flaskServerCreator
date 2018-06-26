//
// Created by Daniel(sisitrs2) on 6/25/18.
//

#ifndef FLASKSERVERCREATOR_WEBSITE_H
#define FLASKSERVERCREATOR_WEBSITE_H

#include <vector>
#include <string>
#include <string.h>

/*** Required for the exec function ***/
#include <memory>
/*** ***/


class Website {

public:

    explicit Website(const char *path);

    /***
     * Getters and Setters.
     */
    void setTemplates(const std::vector<std::string> &_templates);
    void setAssets(const std::vector<std::string> &_assets);
    const std::vector<std::string>& getTemplates() const;
    const std::vector<std::string>& getAssets() const;

    /***
     * This function gets files from path and save them in class vectors
     * I would've put them as private but in case files were added to the
     * path directory they should be added to the classes vector.
     */
    void addFiles();

private:

    const char *_path;
    std::vector<std::string> _templates; //Holds names of .html files.
    std::vector<std::string> _assets;    //Holds names of directories.

    /***
     * Helper functions.
     */
    void getFiles(std::vector<std::string>& files);
    std::string getDotName(const std::string& file);
    /***
     * Function that takes shell command and return output.
     * found on stackoverflow: https://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c-using-posix
     * Credits to: waqas.
     */
    std::string exec(const char* cmd) const;
};


#endif //FLASKSERVERCREATOR_WEBSITE_H
