#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "exception/leaf_exit_to_main.hpp"
#include "leaf_process_manager/leaf_process_manager.hpp"

using namespace leaf;

int main(const int argc, const char **argv)
{
  process_manager::LeafProcessManager &leafProcessManager = process_manager::LeafProcessManager::GetInstance();
  int exitCode = 0;
  auto console = spdlog::stdout_color_mt("console");

  console->info("Hello world form spdlog!");

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
