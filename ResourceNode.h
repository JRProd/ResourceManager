#ifndef RESOURCE_NODE
    #define RESOURCE_NODE

#include <string>
#include <vector>

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

    ~ResourceNode();

    void addRequirement(ResourceNode* nodePtr);

    std::string getResouce();

    std::vector<std::string> getRequirements();

    bool isUsable() const;
    void setUsable(bool usable);

    std::string toString();
};

#endif
