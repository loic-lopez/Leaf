//
// Created by LoicL on 12/12/2020.
//

#ifndef LEAF_SERVER_OPTIONS_HPP
#define LEAF_SERVER_OPTIONS_HPP

#include <string>

namespace Leaf::LeafServer::Models {

    class ServerOptions {
    private:
        std::string _serverConfigFilePath;
    public:
        [[nodiscard]] const std::string &getServerConfigFilePath() const;

        void setServerConfigFilePath(const std::string &serverConfigFilePath);

    };
}

#endif //LEAF_SERVER_OPTIONS_HPP
