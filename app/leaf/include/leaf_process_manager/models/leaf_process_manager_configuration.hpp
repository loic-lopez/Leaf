//
// Created by LoicL on 19/12/2020.
//

#ifndef LEAF_LEAF_PROCESS_MANAGER_CONFIGURATION_HPP
#define LEAF_LEAF_PROCESS_MANAGER_CONFIGURATION_HPP

#include <string>

namespace Leaf::LeafProcessManager::Models {

    class LeafProcessManagerConfiguration {
    private:
        const std::string serversRootPath;
        const std::string leafLogDirectoryPath;
        const std::string mimeTypesConfigFilePath;


    public:
        explicit LeafProcessManagerConfiguration(
                const std::string &serversRootPath,
                const std::string &leafLogDirectoryPath,
                const std::string &mimeTypesConfigFilePath);

        [[nodiscard]] const std::string &getServersRootPath() const;

        [[nodiscard]] const std::string &getLeafLogDirectoryPath() const;

        [[nodiscard]] const std::string &getMimeTypesConfigFilePath() const;
    };

}


#endif // LEAF_LEAF_PROCESS_MANAGER_CONFIGURATION_HPP
