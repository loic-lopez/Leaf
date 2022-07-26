//
// Created by LoicL on 23/12/2020.
//

#ifndef LEAF_UTILS_HPP
#define LEAF_UTILS_HPP

#include <string>

namespace leaf::utils
{
extern std::string BuildInfo();

consteval std::string_view LeafBanner()
{
  using namespace std::string_view_literals;

  return
    R"(
     .\^/.                                            .\^/.
   . |`|/| .                                        . |`|/| .
   |\|\|'|/|       _                       __       |\|\|'|/|
.--'-\`|/-''--.   | |       ___    __ _   / _|   .--'-\`|/-''--.
 \`-._\|./.-'/    | |      / _ \  / _` | | |_     \`-._\|./.-'/
  >`-._|/.-'<     | |___  |  __/ | (_| | |  _|     >`-._|/.-'<
 '~|/~~|~~\|~'    |_____|  \___|  \__,_| |_|      '~|/~~|~~\|~'
       |                                                |
)"sv;
}
}// namespace leaf::utils

#endif// LEAF_UTILS_HPP
