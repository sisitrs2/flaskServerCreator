//
// Copyright(c) 2018 Daniel Arad.
//
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
// ---------------------------------------------------------------------
// File: ServerCreator.h
// ---------------------------------------------------------------------
//
// This header file contains the ServerCreator class.
// It is responsible to use the data stored in the Website class
// (which will be initialized in the constructor) and use it to create
// a website with a server side (python-flask server).
// All operations is done in the constructor.
//
//  Operations:
//
//     - Creates server directory using the format websiteDirectoryName_server
//     - Creates the templates directory within the server directory.
//     - Adds to the templates directory all the html pages found in _templates
//       vector in the Website class one by one, each added after it is edited
//       with the FileEdit class to match the flask format.
//     - Creates an app.py file for the execution of the flask server app.
//       and adds all the routes for each html file in the templates directory.
//     - Creates the static directory within the server directory, and
//       recursively copies all files inside assets directory to the static directory.
//
//
// Use:
//
//     Website staticWebsite("/path/to/website/directory");
//     ServerCreator create(staticWebsite);
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

    std::string exec(const std::string& cmd) const;
    void makeServerDir();
    void getWebsiteDirName(std::string& name) const;
    std::string getLastDirInPath(const std::string& path) const;

    void createTemplates() const;
    void createTemplatePage(const std::string& page) const;
    void createApp() const;
    void addRoutesToApp(FileEdit& app) const;
    void createStatic() const;
};


#endif //FLASKSERVERCREATOR_SERVERCREATOR_H
