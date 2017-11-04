#ifndef RESOURCE_MANAGER
    #define RESOURCE_MANAGER

#include "ResourceNode.h"

class ResourceManager {
private:
    std::vector<ResourceNode*> nodes;

    ResourceNode* findNode(std::string resource);

    std::string generateGraphBlock(int maxResouceLength, std::string resource) const;
    std::string generateGraphBreak(int maxResouceLength, int numOfResources) const;

public:
    ResourceManager();

    ~ResourceManager();

    void addNode(std::string resource, std::string requirement);
    void deleteNode(std::string resource);

    std::string toString(bool asMatrix) const;
};

#endif
