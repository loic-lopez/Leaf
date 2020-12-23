#include <iostream>
#include "server/leaf_process_manager.hpp"

int main(const int argc, const char **argv) {

    Leaf::LeafServer::LeafProcessManager leafProcessManager(argc, argv);

    leafProcessManager.start();

    // Leaf::LeafServer::LeafServerOptionsParser serverOptionsParser;

    /* // Check command line arguments.
     if (argc != 3) {
         std::cerr << "Usage: Leaf <address> <port> <doc_root>\n";
         std::cerr << "  For IPv4, try:\n";
         std::cerr << "    receiver 0.0.0.0 80 .\n";
         std::cerr << "  For IPv6, try:\n";
         std::cerr << "    receiver 0::0 80 .\n";
         return 1;
     }*/

    return 0;
}
