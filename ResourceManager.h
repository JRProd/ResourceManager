/* ########## RESOURCE MANAGER APPLICATION ##########
 * The ResourceManager module is used to manage nodes
 *  and their connections. User can add or change a
 *  node's usable bit by deleting the node.
 *
 * The toString function can print out the nodes and
 *  their connections as a list of requirements for
 *  nodes, or as a adjecency matrix showing connections
 *
 * Aurthor - Jake Rowland
 * Date - November 5, 2107
*/

#ifndef RESOURCE_MANAGER
    #define RESOURCE_MANAGER

#include "ResourceNode.h"

class ResourceManager {
private:
    std::vector<ResourceNode*> nodes;

    ResourceNode* findNode(std::string resource);

    // Functions to generate the matrix
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
