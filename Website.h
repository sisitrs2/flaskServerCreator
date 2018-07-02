//
// Copyright(c) 2018 Daniel Arad.
//
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
// ---------------------------------------------------------------------
// File: Website.h
// ---------------------------------------------------------------------
//
// This header file contains the Website class.
// The Website class is responsible for holding information of a static website,
// Information such as:
//
//     _path - Path to static website
//
//     _assets - Contains the name of the assets directory,
//               for now either assets or Assets.
//
//     _templates - Contains names of all html files in the website directory.
//
// This class was created for the use of the ServerCreator class.
//
// Use:
//
//     Website staticWebsite("/path/to/website/directory");
//     ServerCreator create(staticWebsite);
//

#ifndef FLASKSERVERCREATOR_WEBSITE_H
#define FLASKSERVERCREATOR_WEBSITE_H

#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <memory>


class Website
{

public:

    explicit Website(const std::string& path);

    const std::vector<std::string>& getTemplates() const;
    const std::string& getAssets() const;
    const std::string& getPath() const;

    // This function gets files from path and save them in class vectors
    // I would've put them as private but in case files were added to the
    // path directory they should be added to the classes vector.
    void addFiles();

private:

    std::string _path;                   // Holds website path name.
    std::vector<std::string> _templates; // Holds names of .html files.
    std::string _assets;                 // Holds name of assets/Assets.

    // Future idea - use map for _assets, get all non .html files and put them
    // in _assets with file name as key and file type as value.
    // Then when creating a server create static folder with folder for
    // each type instead of assets folder as a requirement.

    // Change empty vector sent by reference and fill it with
    // names of files and directories under _path.
    void getFiles(std::vector<std::string>& files);

    // Returns file type
    // Example:
    //     std::string fileType getFileType("index.html");
    // Outcome:
    //     fileType = "html"
    std::string getFileType(const std::string& file);


    // Function that takes shell command and return output.
    // found on stackoverflow: https://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c-using-posix
    // Credits to: waqas.
    std::string exec(const std::string& cmd) const;
};


#endif //FLASKSERVERCREATOR_WEBSITE_H
