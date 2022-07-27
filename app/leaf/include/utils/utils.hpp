//
// Created by LoicL on 23/12/2020.
//

#ifndef __LEAF_UTILS_HPP__
#define __LEAF_UTILS_HPP__

#include <string>

namespace leaf::utils
{
extern std::string BuildInfo();

consteval std::string_view LeafBanner()
{
  using std::string_view_literals::operator""sv;

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

#endif// __LEAF_UTILS_HPP__
