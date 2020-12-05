
#ifndef LEAF_MIME_TYPES_HPP
#define LEAF_MIME_TYPES_HPP

#include <vector>
#include "abstracts/ini_configuration.hpp"

namespace Leaf::LeafServer {

    struct MimeTypeMapping {
        const char *extension;
        const char *mime_type;
    };


    class MimeTypes : public Abstracts::INIConfiguration {
    private:
        std::vector<MimeTypeMapping> mappings;

    public:
        // methods
        void initialize(const std::string &configFilePath) override;

        std::string extensionToType(const std::string &extension);

        // remove possibility to copy
        MimeTypes(const MimeTypes &) = delete;

        MimeTypes &operator=(const MimeTypes) = delete;

        MimeTypes(MimeTypes &&) = delete;

        MimeTypes &operator=(MimeTypes &&) = delete;

        MimeTypes() = default;

        virtual ~MimeTypes() = default;
    };


}
#endif //LEAF_MIME_TYPES_HPP
