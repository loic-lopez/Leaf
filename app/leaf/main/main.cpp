#include <iostream>
#include "leaf_process_manager/leaf_process_manager.hpp"

int main(const int argc, const char **argv) {

    Leaf::LeafProcessManager::LeafProcessManager leafProcessManager;

    leafProcessManager.parseCommandLineArgs(argc, argv);
    leafProcessManager.start();

    return 0;
}
