//
// Created by LoicL on 28/11/2020.
//

#include <iostream>

#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>

#include "exception/mime_types_config_file_not_found.hpp"
#include "leaf_process_manager/configuration_loader/leaf_mime_types_loader.hpp"

namespace leaf::process_manager::configuration_loader
{
std::unique_ptr<mime_type::MimeTypes> MimeTypesLoader::load(const std::string &configFilePath)
{
  const boost::property_tree::ptree pTree = this->initializeBoostPtree<exception::MimeTypesConfigFileNotFound>(configFilePath);
  std::vector<mime_type::MimeType> mimeTypes;

  for (const auto &[first, second] : pTree.find(MIME_TYPE_SECTION.data())->second)
  {
    auto mimeTypeValues = second.get_value<std::string>();
    std::vector<std::string> parsedMimeTypes;

    boost::trim(mimeTypeValues);
    boost::split(parsedMimeTypes, mimeTypeValues, boost::is_any_of(","));

    mimeTypes.emplace_back(first, parsedMimeTypes);
  }

  std::cout << configFilePath << " successfully loaded." << std::endl;

  return std::make_unique<mime_type::MimeTypes>(mimeTypes);
}

configuration_loader::MimeTypesLoader::MimeTypesLoader()
    : abstract::INIConfigurationLoader<std::unique_ptr, mime_type::MimeTypes>({{.name = MIME_TYPE_SECTION, .properties = {}}})
{
}

}// namespace leaf::process_manager::configuration_loader
