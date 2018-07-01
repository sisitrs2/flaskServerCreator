//
// Created by Daniel(sisitrs2) on 6/26/18.
//

#include "ServerCreator.h"

ServerCreator::ServerCreator(Website &website) : _website(website)
{
    //Create website_server and website_server/templates directories.
    this->makeServerDir();
    this->createTemplates();
    this->createApp();
    this->createStatic();
}

/***
     * This function that takes shell command and return output.
     * found on stackoverflow: https://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c-using-posix
     * Credits to: waqas.
     */
std::string ServerCreator::exec(const std::string& cmd) const
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

void ServerCreator::makeServerDir()
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
    this->exec(cmd);
    _serverDirName = name;
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
    output = this->exec(cmd);
    std::cout << "Directory " << name << "/templates added." << std::endl;
    delete cmd;

}

void ServerCreator::getWebsiteDirName(std::string& name) const
{
    std::string output;
    std::string cmd;
    const char *path = _website.getPath();

    //Shell command: $ cd website_path; pwd
    //cd: change directory
    //pwd: writes the full pathname of the current working directory.
    cmd = "cd " + std::string(_website.getPath()) + "; pwd";
    output = exec(cmd);

    name = getLastDirInPath(output);
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

void ServerCreator::createTemplates() const
{
    for(const std::string& page : _website.getTemplates())
    {
        createTemplatePage(page);
    }
}

void ServerCreator::createTemplatePage(const std::string &page) const
{
    std::string srcFile;
    std::string dstFile;

    srcFile = _website.getPath();
    srcFile += '/' + page;
    dstFile = _serverDirName + "/templates/" + page;

    auto file = new FileEdit(srcFile, dstFile);

    //Html links
    file->replaceAll("href=\"{{x}}.html\"", "href=\"{{ url_for({{x}}) }}\"", "{{x}}");

    //Non-js links
    file->replaceAll("href=\"assets/{{x}}\"", "href=\"{{ url_for('static', filename='{{x}}') }}\"", "{{x}}");

    //Js links
    file->replaceAll("src=\"assets/{{x}}\"", "src=\"{{ url_for('static', filename='{{x}}') }}\"", "{{x}}");

    delete file;
}

void ServerCreator::createApp() const
{
    FileEdit file(_serverDirName + "/app.py");
    file << "from flask import Flask, request, render_template";
    file << "";
    file << "app = Flask(__name__)";
    file << "";
    addRoutesToApp(file);
    file << "";
    file << "if __name__ == \"__main__\":";
    file << "   app.run(debug = True, host='0.0.0.0', port=80)";
}

void ServerCreator::addRoutesToApp(FileEdit& app) const
{
    std::string pageName;
    for(const std::string& page : _website.getTemplates())
    {
        pageName = page.substr(0, page.length() - 5); // index.html => index
        if (page == "index")
        {
            app << "@app.route('/')";
            app << "def index():";
            app << "    return render_template('index.html')";
        }
        app << "@app.route('/" + pageName + "')";
        app << "def " + pageName + "():";
        app << "    return render_template('" + pageName + ".html')";
        app << "";
    }
}

void ServerCreator::createStatic() const
{
    std::string output;
    std::string srcPath;
    std::string dstPath;

    output = exec("cd " + _serverDirName + "; mkdir static");
    std::cout << "Directory " << _serverDirName << "/static added." << std::endl;

    srcPath = std::string(_website.getPath()) + "/" + _website.getAssets();
    dstPath = _serverDirName + "/static";
    output = exec("cp -a " + srcPath + "/. " + dstPath);
}
