//
// Created by Daniel(sisitrs2) on 6/26/18.
//

#include "ServerCreator.h"

ServerCreator::ServerCreator(Website &website) : _website(website)
{}


std::string Website::exec(const char* cmd) const
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
