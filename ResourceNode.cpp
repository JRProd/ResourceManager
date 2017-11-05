#include "ResourceNode.h"

ResourceNode::ResourceNode(std::string resource) {
    this->resource = resource;
    this->usable = true;
}

ResourceNode::ResourceNode(std::string resource, bool usable) {
    this->resource = resource;
    this->usable = usable;
}

// Checks if all requirements are satisfied
bool ResourceNode::requirementsSatisfied() {
    for(ResourceNode* nodePtr : this->requirements) {
        if(nodePtr != nullptr && !(nodePtr->isUsable())) {
            return false;
        }
    }
    return true;
}

// Notify recipients that usable bit has changed
void ResourceNode::notifyRecipients(bool usable) {
    for(ResourceNode* nodePtr : this->recipients) {
        if(nodePtr != nullptr) {
            nodePtr->setUsable(usable);
        }
    }
}

// Check if a resource is a requirement
bool ResourceNode::isRequirement(std::string resource) {
    for(ResourceNode* nodePtr : this->requirements) {
        if(nodePtr != nullptr && nodePtr->getResouce().compare(resource) == 0) {
            return true;
        }
    }
    return false;
}

void ResourceNode::addRecipient(ResourceNode* nodePtr) {
    this->recipients.push_back(nodePtr);
}

// Add a requirement to a node
void ResourceNode::addRequirement(ResourceNode* nodePtr) {
    // If node is not a requirement
    if(!this->isRequirement(nodePtr->getResouce())) {
        // The required node is a supplyer of this node
        nodePtr->addRecipient(this);
        // Add node to requirements
        this->requirements.push_back(nodePtr);
    }
}

std::string ResourceNode::getResouce() const {
    return this->resource;
}

// Get a vector of requirements for the node
std::vector<const ResourceNode*> ResourceNode::getRequirements() const {
    std::vector<const ResourceNode*> constVector;
    for(ResourceNode* nodePtr : this->requirements) {
        const ResourceNode* constPtr = nodePtr;
        constVector.push_back(constPtr);
    }
    return constVector;
}

bool ResourceNode::isUsable() const{
    return this->usable;
}

void ResourceNode::setUsable(bool usable) {
    // Checks if node should be usable and the requirements are usable
    bool nodeValid = usable & this->requirementsSatisfied();
    if(this->usable != nodeValid) {
        this->usable = nodeValid;
        this->notifyRecipients(nodeValid);
    }
}

std::string ResourceNode::toString() const {
    // Returns string of Resource(usable bit)
    std::string returnVal = this->resource + "(";
    returnVal += this->isUsable() ? "1" : "0";
    returnVal += ")";
    return returnVal;
}
