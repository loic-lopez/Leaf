#include <iostream>

#include "leaf_process_manager/leaf_process_manager.hpp"

using namespace leaf::process_manager;

int main(const int argc, const char **argv)
{
  LeafProcessManager &leafProcessManager = LeafProcessManager::GetInstance();

  leafProcessManager.parseCommandLineArgs(argc, argv);
  leafProcessManager.start();

  return 0;
}
