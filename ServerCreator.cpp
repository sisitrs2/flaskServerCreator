//
// Copyright(c) 2018 Daniel Arad.
//
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
// ---------------------------------------------------------------------
// File: ServerCreator.cpp
// ---------------------------------------------------------------------

#include "ServerCreator.h"

ServerCreator::ServerCreator(Website &website) : _website(website)
{
    // Create website_server and website_server/templates directories.
    this->makeServerDir();

    // Add html files to templates directory.
    this->createTemplates();

    // Create app.py file and add routes to html file.
    this->createApp();

    // Create website_server/static directory and copy all content from assets directory.
    this->createStatic();
}


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
    std::string cmd;

    //Create shell code to make the server folder.
    this->getWebsiteDirName(name);
    name.pop_back(); //delete \n
    name.append("_server");
    cmd = "mkdir " + name;

    //Create website_server directory.
    exec(cmd);
    _serverDirName = name;
    std::cout << "Directory " << name << " added." << std::endl;

    //Create shell code to make the templates folder.
    cmd = "cd " + name + "; mkdir templates";

    //Create website_server/templates directory.
    output = this->exec(cmd);
    std::cout << "Directory " << name << "/templates added." << std::endl;
}

void ServerCreator::getWebsiteDirName(std::string& name) const
{
    std::string output;
    std::string cmd;

    //Shell command: $ cd website_path; pwd
    //cd: change directory
    //pwd: writes the full pathname of the current working directory.
    cmd = "cd " + _website.getPath() + "; pwd";
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
    std::string fixPage; // replace '-' char with '_'.
    unsigned long pos;
    std::map<std::string, std::string> badNames = _website.getBadNames();

    srcFile = _website.getPath();
    srcFile += '/' + page;


    dstFile = _serverDirName + "/templates/" + page;

    auto file = new FileEdit(srcFile, dstFile);

    for (std::map<std::string,std::string>::iterator it=badNames.begin(); it!=badNames.end(); ++it)
        file->replaceAll("href=\"" + it->first + "\"", "href=\"" + it->second + "\"");


    //Html links
    file->replaceAll("href=\"{{x}}.html\"", "href=\"{{ url_for('{{x}}') }}\"", "{{x}}");

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
    std::map<std::string, std::string> badNames = _website.getBadNames();
    for(const std::string& page : _website.getTemplates())
    {
        pageName = page.substr(0, page.length() - 5); // index.html => index
        if (pageName == "index")
        {
            app << "@app.route('/')";
            app << "def index():";
            app << "    return render_template('index.html')";
            app << "";
        }
        else
        {
            app << "@app.route('/" + pageName + "')";
            if(badNames.find(page) == badNames.end())
            {
                app << "def " + pageName + "():";
            }
            else
            {
                app << "def " + badNames[page].substr(0, page.length() - 5) + "():";
            }
            app << "    return render_template('" + pageName + ".html')";
            app << "";
        }

    }
}

void ServerCreator::createStatic() const
{
    std::string output;
    std::string srcPath;
    std::string dstPath;

    output = exec("cd " + _serverDirName + "; mkdir static");
    std::cout << "Directory " << _serverDirName << "/static added." << std::endl;

    srcPath = _website.getPath() + "/" + _website.getAssets();
    dstPath = _serverDirName + "/static";
    output = exec("cp -a " + srcPath + "/. " + dstPath);
}
