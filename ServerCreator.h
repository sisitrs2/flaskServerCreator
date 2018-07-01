//
// Created by Daniel(sisitrs2) on 6/26/18.
//

#ifndef FLASKSERVERCREATOR_SERVERCREATOR_H
#define FLASKSERVERCREATOR_SERVERCREATOR_H

#include "Website.h"
#include "FileEdit.h"

class ServerCreator
{

public:

    explicit ServerCreator(Website& website);


private:

    Website _website;
    std::string _serverDirName;

    std::string exec(const char* cmd) const;
    void makeServerDir();
    void getWebsiteDirName(std::string& name) const;
    std::string getLastDirInPath(const std::string& path) const;

    void createTemplates() const;
    void createTemplatePage(const std::string& page) const;
    void createApp() const;
    void addRoutesToApp(FileEdit& app) const;
};


#endif //FLASKSERVERCREATOR_SERVERCREATOR_H
