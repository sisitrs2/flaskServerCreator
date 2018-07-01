#include <iostream>
#include "Website.h"
#include "ServerCreator.h"

using std::cout;
using std::endl;

int main() {

    Website a("../site");
    ServerCreator b(a);

    std::cout << "End of Program." << std::endl;

    return 0;
}

