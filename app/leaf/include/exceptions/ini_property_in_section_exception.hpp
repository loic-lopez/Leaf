//
// Created by LoicL on 23/12/2020.
//

#ifndef LEAF_INI_PROPERTY_IN_SECTION_EXCEPTION_HPP
#define LEAF_INI_PROPERTY_IN_SECTION_EXCEPTION_HPP

#include "exceptions/ini_section_not_found.hpp"

namespace Leaf::Exceptions {
    class IniPropertyInSectionException : public Exceptions::IniSectionNotFound {
    public:
        enum IniPropertyInSectionExceptionType {
            DUPLICATED,
            MISSING
        };

    private:
        std::string _property;
        IniPropertyInSectionExceptionType _exceptionType;

    public:

        explicit IniPropertyInSectionException(
                IniPropertyInSectionExceptionType exceptionType,
                const std::string &property,
                const std::string &section,
                const std::string &configFilePath,
                const std::source_location &location
        );

    protected:
        void buildStdExceptionMessage(const char *exceptionClassName) override;
    };
}

#endif //LEAF_INI_PROPERTY_IN_SECTION_EXCEPTION_HPP
