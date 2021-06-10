
#ifndef LEAF_LEAF_MIME_TYPES_LOADER_HPP
#define LEAF_LEAF_MIME_TYPES_LOADER_HPP

#include <vector>
#include "abstracts/ini_configuration_loader.hpp"
#include "models/mime_types.hpp"

namespace Leaf::LeafProcessManager::ConfigurationLoaders {

    class MimeTypesLoader : public Abstracts::INIConfigurationLoader<std::unique_ptr, Leaf::Models::MimeTypes> {
    public:
        explicit MimeTypesLoader();

        std::unique_ptr<Leaf::Models::MimeTypes> load(const std::string &configFilePath) override;

        inline static const char MIME_TYPE_SECTION[] = "MimesTypes";
    };


}

#endif //LEAF_LEAF_MIME_TYPES_LOADER_HPP
