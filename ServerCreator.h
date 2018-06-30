//
// Created by Daniel(sisitrs2) on 6/26/18.
//

#ifndef FLASKSERVERCREATOR_SERVERCREATOR_H
#define FLASKSERVERCREATOR_SERVERCREATOR_H

#include "Website.h"
#

class ServerCreator
{

public:

    explicit ServerCreator(Website& website);


private:

    Website _website;

    /***
     * This function that takes shell command and return output.
     * found on stackoverflow: https://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c-using-posix
     * Credits to: waqas.
     */
    std::string exec(const char* cmd) const;
    void makeServerDir() const;
    void getWebsiteDirName(std::string& name) const;
    std::string getLastDirInPath(const std::string& path) const;
};


#endif //FLASKSERVERCREATOR_SERVERCREATOR_H
