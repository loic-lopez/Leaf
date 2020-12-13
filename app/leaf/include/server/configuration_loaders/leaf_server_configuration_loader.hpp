//
// Created by LoicL on 29/11/2020.
//

#ifndef LEAF_SERVER_CONFIGURATION_LOADER_HPP
#define LEAF_SERVER_CONFIGURATION_LOADER_HPP

#include "abstracts/ini_configuration_loader.hpp"

namespace Leaf::LeafServer::ConfigurationLoaders {
    class ServerConfiguration : public Abstracts::INIConfigurationLoader {
    private:
        std::string _serversRootPath;
        std::string _mimeTypesFilePath;
    public:
/*        [[nodiscard]] const std::string &getMimeTypesFilePath() const;

        [[nodiscard]] const std::string &getServersRootPath() const;*/

    public:
        void load(const std::string &configFilePath) override;
    };
}

#endif //LEAF_SERVER_CONFIGURATION_LOADER_HPP
