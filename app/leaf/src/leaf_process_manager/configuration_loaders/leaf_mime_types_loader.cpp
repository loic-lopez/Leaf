//
// Created by LoicL on 28/11/2020.
//

#include <iostream>
#include <boost/algorithm/string.hpp>
#include "exceptions/mime_types_config_file_not_found.hpp"
#include "leaf_process_manager/configuration_loaders/leaf_mime_types_loader.hpp"

using namespace Leaf::Exceptions;
using namespace Leaf::LeafProcessManager;

Leaf::Models::MimeTypes *ConfigurationLoaders::MimeTypesLoader::load(const std::string &configFilePath) {
    boost::property_tree::ptree pTree = this->initializeBoostPtree<MimeTypesConfigFileNotFound>(configFilePath);
    std::vector<Models::MimeType> mimeTypes;

    for (const auto &mimeTypeLine : pTree.find(MimeTypesLoader::MIME_TYPE_SECTION)->second) {
        std::string mimeTypeValues = mimeTypeLine.second.get_value<std::string>();
        std::vector<std::string> parsedMimeTypes;

        boost::trim(mimeTypeValues);
        boost::split(parsedMimeTypes, mimeTypeValues, boost::is_any_of(","));

        mimeTypes.emplace_back(mimeTypeLine.first, parsedMimeTypes);
    }

    std::cout << configFilePath << " successfully loaded." << std::endl;

    return new Models::MimeTypes{
            .mimeTypes = mimeTypes
    };
}

ConfigurationLoaders::MimeTypesLoader::MimeTypesLoader() : INIConfigurationLoader({MIME_TYPE_SECTION}) {

}
