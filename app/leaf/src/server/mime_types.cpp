//
// Created by LoicL on 28/11/2020.
//

#include <iostream>
#include "exceptions/mime_types_config_file_not_found.hpp"
#include "server/mime_types.hpp"

using namespace Leaf::LeafServer;

std::string MimeTypes::extensionToType(const std::string &extension) {
    for (const auto &mapping : mappings) {
        if (mapping.extension == extension) {
            return mapping.mime_type;
        }
    }

    return "text/plain";
}


void MimeTypes::initialize(const std::string &configFilePath) {

    boost::property_tree::ptree pTree = this->initializeBoostPtree<Leaf::Exceptions::MimeTypesConfigFileNotFound>(configFilePath);

    for (const auto &section : pTree) {
        std::cout << '[' << section.first << "]\n";
        for (const auto &key : section.second)
            std::cout << key.first << "=" << key.second.get_value<std::string>() << "\n";
    }
}

