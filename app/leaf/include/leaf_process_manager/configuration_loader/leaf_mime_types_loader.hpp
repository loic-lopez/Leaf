
#ifndef LEAF_LEAF_MIME_TYPES_LOADER_HPP
#define LEAF_LEAF_MIME_TYPES_LOADER_HPP

#include <vector>

#include "abstract/ini_configuration_loader.hpp"
#include "mime_type/mime_types.hpp"

namespace leaf::process_manager::configuration_loader
{

class MimeTypesLoader : public abstract::INIConfigurationLoader<std::unique_ptr, mime_type::MimeTypes>
{
  public:
    explicit MimeTypesLoader();

    std::unique_ptr<mime_type::MimeTypes> load(const std::string &configFilePath) override;

    constexpr static const char MIME_TYPE_SECTION[] = "MimesTypes";
};

}// namespace leaf::process_manager::configuration_loader

#endif// LEAF_LEAF_MIME_TYPES_LOADER_HPP