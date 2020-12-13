
#ifndef LEAF_LEAF_MIME_TYPES_LOADER_HPP
#define LEAF_LEAF_MIME_TYPES_LOADER_HPP

#include <vector>
#include "abstracts/ini_configuration_loader.hpp"
#include "models/mime_type.hpp"

namespace Leaf::LeafServer::ConfigurationLoaders {

    class MimeTypes : public Abstracts::INIConfigurationLoader {
    private:
        std::vector<Models::MimeType> mappings;

    public:
        // methods
        void load(const std::string &configFilePath) override;

        //std::string extensionToType(const std::string &extension);
    };


}
#endif //LEAF_LEAF_MIME_TYPES_LOADER_HPP
