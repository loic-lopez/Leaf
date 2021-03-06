#include <iostream>
#include "leaf_process_manager/leaf_process_manager.hpp"

int main(const int argc, const char **argv) {

    Leaf::LeafProcessManager::LeafProcessManager leafProcessManager;

    leafProcessManager.parseCommandLineArgs(argc, argv);
    leafProcessManager.start();

    // Leaf::LeafServer::LeafOptionsParser_Surcharged serverOptionsParser;

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
