//
// Created by LoicL on 29/11/2020.
//

#ifndef LEAF_LEAF_CONF_HPP
#define LEAF_LEAF_CONF_HPP

#include "abstracts/ini_configuration.hpp"

namespace Leaf::LeafServer {
    class LeafConf : public Abstracts::INIConfiguration {

    public:
        void initialize(const std::string &configFilePath) override;

        // remove possibility to copy
        LeafConf(const LeafConf &) = delete;

        LeafConf &operator=(const LeafConf) = delete;

        LeafConf(LeafConf &&) = delete;

        LeafConf &operator=(LeafConf &&) = delete;

        LeafConf() = default;

        virtual ~LeafConf() = default;
    };
}

#endif //LEAF_LEAF_CONF_HPP
