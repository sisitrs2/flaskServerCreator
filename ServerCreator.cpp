//
// Created by Daniel(sisitrs2) on 6/26/18.
//

#include "ServerCreator.h"

ServerCreator::ServerCreator(Website &website) : _website(website)
{
    //Create website_server and website_server/templates directories.
    this->makeServerDir();


}


std::string ServerCreator::exec(const char* cmd) const
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

void ServerCreator::makeServerDir() const
{
    std::string name; //Name of website directory.
    std::string output;
    std::size_t cmd_length;
    char* cmd;

    //Create shell code to make the server folder.
    this->getWebsiteDirName(name);
    name.pop_back(); //delete \n
    name.append("_server");
    cmd_length = strlen("mkdir ");
    cmd_length += strlen(name.c_str());
    cmd = new char[cmd_length + 1];
    strcpy(cmd, "mkdir ");
    strcat(cmd, name.c_str());

    //Create website_server directory.
    //TO_FREE: output = this->exec(cmd);
    std::cout << "Directory " << name << " added." << std::endl;
    delete cmd;

    //Create shell code to make the templates folder.
    cmd_length = strlen("cd ");
    cmd_length += strlen(name.c_str());
    cmd_length += strlen("; mkdir templates");
    cmd = new char[cmd_length + 1];
    strcpy(cmd, "cd ");
    strcat(cmd, name.c_str());
    strcat(cmd, "; mkdir templates");

    //Create website_server/templates directory.
    //TO_FREE: output = this->exec(cmd);
    std::cout << "Directory " << name << "/templates added." << std::endl;
    delete cmd;

}

void ServerCreator::getWebsiteDirName(std::string& name) const
{
    std::string output;
    const char *path = this->_website.getPath();

    //Shell command: $ cd website_path; pwd
    //cd: change directory
    //pwd: writes the full pathname of the current working directory.
    char cmd[strlen("cd ") + strlen(path) + strlen("; pwd") + 1];
    strcpy(cmd, "cd ");
    strcat(cmd, path);
    strcat(cmd, "; pwd");
    output = exec(cmd);
    name = this->getLastDirInPath(output);
    //before: name = "full/pathname/of/website_name"
    //after: name = "website_name"
}

std::string ServerCreator::getLastDirInPath(const std::string &path) const {
    std::size_t pos;
    pos = path.find_last_of('/');
    if(pos != std::string::npos)
    {
        return( path.substr(pos + 1, path.length()) ); //returns word AFTER '/'.
    }
    return(path);
}
