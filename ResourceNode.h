/* ########## RESOURCE MANAGER APPLICATION ##########
 * The ResourceNode module is used to store the resource
 *  and its requirements. The usable bit is updated based
 *  on requirements and the current usable bit
 *
 * Aurthor - Jake Rowland
 * Date - November 5, 2107
*/

#ifndef RESOURCE_NODE
    #define RESOURCE_NODE

#include <string> // For the resouce
#include <vector> // For list of requirements

class ResourceNode {
private:
    std::string resource;

    std::vector<ResourceNode*> requirements;
    std::vector<ResourceNode*> recipients;

    bool requirementsSatisfied();
    void notifyRecipients(bool usable);

    bool isRequirement(std::string resource);

    void addRecipient(ResourceNode* nodePtr);

    bool usable; // Should only return true if this node is usable
                 //  and all recusive children are usable

public:
    ResourceNode(std::string resource);
    ResourceNode(std::string resource, bool usable);

    void addRequirement(ResourceNode* nodePtr);

    std::string getResouce() const;

    std::vector<const ResourceNode*> getRequirements() const;

    bool isUsable() const;
    void setUsable(bool usable);

    std::string toString() const;
};

#endif
