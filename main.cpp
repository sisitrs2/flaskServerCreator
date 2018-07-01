#include <iostream>
#include "Website.h"
#include "ServerCreator.h"

using std::cout;
using std::endl;
using std::cin;

int main() {
    std::string path;

    cout << "Enter website directory: ";
    cin >> path;
    Website a(path);
    ServerCreator b(a);

    std::cout << "End of Program." << std::endl;

    return 0;
}

