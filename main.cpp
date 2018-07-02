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
    Website staticWebsite(path);
    ServerCreator create(staticWebsite);

    std::cout << "End of Program." << std::endl;

    return 0;
}

