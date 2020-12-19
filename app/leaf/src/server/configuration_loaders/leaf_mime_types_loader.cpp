//
// Created by LoicL on 28/11/2020.
//

#include <iostream>
#include <boost/algorithm/string.hpp>
#include "exceptions/mime_types_config_file_not_found.hpp"
#include "server/configuration_loaders/leaf_mime_types_loader.hpp"

using namespace Leaf::Exceptions;
using namespace Leaf::LeafServer;

/*std::string MimeTypes::extensionToType(const std::string &extension) {
    for (const auto &mapping : mappings) {
        if (mapping.extension == extension) {
            return mapping.mime_type;
        }
    }

    return "text/plain";
}*/



std::vector<Leaf::Models::MimeType> ConfigurationLoaders::MimeTypes::load(const std::string &configFilePath) {
    boost::property_tree::ptree pTree = this->initializeBoostPtree<MimeTypesConfigFileNotFound>(configFilePath);
    std::vector<Models::MimeType> mimeTypes;

    checkForPtreeIntegrity(pTree);

    for (const auto &mimeTypeLine : pTree.find(MimeTypes::MIME_TYPE_SECTION)->second) {
        std::string mimeTypeValues = mimeTypeLine.second.get_value<std::string>();
        std::vector<std::string> parsedMimeTypes;

        boost::trim(mimeTypeValues);
        boost::split(parsedMimeTypes, mimeTypeValues, boost::is_any_of(","));

        mimeTypes.emplace_back(mimeTypeLine.first, parsedMimeTypes);
    }

    return mimeTypes;
}

void ConfigurationLoaders::MimeTypes::checkForPtreeIntegrity(const boost::property_tree::ptree &pTree) {
    if (pTree.find(MimeTypes::MIME_TYPE_SECTION)->second.empty())
        throw std::runtime_error("SECTION NOT FOUND"); // TODO: CREATE DEDICATED EXCEPTION
}

