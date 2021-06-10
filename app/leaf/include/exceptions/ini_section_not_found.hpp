//
// Created by LoicL on 23/12/2020.
//

#ifndef LEAF_INI_SECTION_NOT_FOUND_HPP
#define LEAF_INI_SECTION_NOT_FOUND_HPP

#include "exceptions/abstracts/exception.hpp"

namespace Leaf::Exceptions {
    class IniSectionNotFound : public Exceptions::Abstracts::Exception {
    private:
        std::string _section;
        std::string _configFilePath;

    public:
        explicit IniSectionNotFound(
                std::string section,
                std::string configFilePath,
                const boost::source_location &location
        );

    protected:
        void buildStdExceptionMessage(const char *exceptionClassName) override;
    };
}

#endif //LEAF_INI_SECTION_NOT_FOUND_HPP
