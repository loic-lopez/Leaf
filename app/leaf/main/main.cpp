#include <iostream>
#include "server/leaf_server.hpp"
#include "server/leaf_conf.hpp"

int main(const int argc, const char **argv) {
    Leaf::LeafServer::Server greeter;
    greeter.greeting();
    (void) argv;

    Leaf::LeafServer::LeafConf leafConf;


    // Check command line arguments.
    if (argc != 3) {
        std::cerr << "Usage: Leaf <address> <port> <doc_root>\n";
        std::cerr << "  For IPv4, try:\n";
        std::cerr << "    receiver 0.0.0.0 80 .\n";
        std::cerr << "  For IPv6, try:\n";
        std::cerr << "    receiver 0::0 80 .\n";
        return 1;
    }

    return 0;
}
