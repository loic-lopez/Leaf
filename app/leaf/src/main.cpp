#include <iostream>

#include "exception/leaf_exit_to_main.hpp"
#include "leaf_process_manager/leaf_process_manager.hpp"

using namespace leaf;

int main(const int argc, const char **argv)
{
  process_manager::LeafProcessManager &leafProcessManager = process_manager::LeafProcessManager::GetInstance();

  try
  {
    leafProcessManager.parseCommandLineArgs(argc, argv);
    leafProcessManager.start();
  }
  catch (const exception::LeafExceptionWithExitStatus &leafExceptionWithExitStatus)
  {
    return leafExceptionWithExitStatus.getExitCode();
  }

  return 0;
}
