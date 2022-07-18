#include "exception/leaf_exit_to_main.hpp"
#include "leaf_process_manager/leaf_process_manager.hpp"

using namespace leaf;

int main(const int argc, const char **argv)
{
  process_manager::LeafProcessManager &leafProcessManager = process_manager::LeafProcessManager::GetInstance();
  int exitCode                                            = 0;

  try
  {
    leafProcessManager.parseCommandLineArgs(argc, argv);
    leafProcessManager.start();
  }
  catch (const exception::LeafExceptionWithExitStatus &leafExceptionWithExitStatus)
  {
    exitCode = leafExceptionWithExitStatus.getExitCode();
  }

  return exitCode;
}
