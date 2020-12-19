
#ifndef LEAF_LEAF_MIME_TYPES_LOADER_HPP
#define LEAF_LEAF_MIME_TYPES_LOADER_HPP

#include <vector>
#include "abstracts/ini_configuration_loader.hpp"
#include "models/mime_type.hpp"

namespace Leaf::LeafServer::ConfigurationLoaders {

    class MimeTypes : public Abstracts::INIConfigurationLoader<std::vector<Models::MimeType>> {
    protected:
        static void checkForPtreeIntegrity(const boost::property_tree::ptree &pTree);

    public:
        MimeTypes() = default;

        std::vector<Models::MimeType> load(const std::string &configFilePath) override;

        inline static const char MIME_TYPE_SECTION[] = "MimesTypes";
    };


}

#endif //LEAF_LEAF_MIME_TYPES_LOADER_HPP
