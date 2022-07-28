//
// Created by LoicL on 29/11/2020.
//

#ifndef __LEAF_LEAF_MIME_TYPES_LOADER_HPP__
#define __LEAF_LEAF_MIME_TYPES_LOADER_HPP__

#include "abstract/ini_configuration_loader.hpp"
#include "mime_type/mime_types.hpp"

#include <vector>

namespace leaf::process_manager::configuration_loader
{

using std::string_view_literals::operator""sv;

class MimeTypesLoader : public abstract::INIConfigurationLoader<std::unique_ptr, mime_type::MimeTypes>
{
  public:
    inline static constinit const defines::ini::Section MIME_TYPE_SECTION = "MimesTypes"sv;

    explicit MimeTypesLoader();
    virtual ~MimeTypesLoader() = default;

    std::unique_ptr<mime_type::MimeTypes> load(const defines::Path &configFilePath) override;
};

}// namespace leaf::process_manager::configuration_loader

#endif// __LEAF_LEAF_MIME_TYPES_LOADER_HPP__
