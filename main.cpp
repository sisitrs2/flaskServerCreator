#include <iostream>
#include "Website.h"
#include "ServerCreator.h"
#include <fstream>
#include "FileEdit.h"

using std::cout;
using std::endl;

int main() {
    FileEdit file("../index.html", "../changed.html");
    //file.replaceAll("href=\"{{x}}.html\"", "href=\"{{ url_for({{x}}) }}\"", "{{x}}");
    //file.replaceAll("href=\"assets/{{x}}\"", "href=\"{{ url_for('static', filename='{{x}}') }}\"", "{{x}}");
    //std::string path;
    //std::cout << "Enter website path (for current enter \"./\"): ";
    //std::cin >> path;
    //Website a(path.c_str());
    //ServerCreator b(a);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

