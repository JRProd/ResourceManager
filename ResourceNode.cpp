#include "ResourceNode.h"

#include <iostream>

ResourceNode::ResourceNode(std::string resource) {
    this->resource = resource;
    this->usable = true;
}

ResourceNode::ResourceNode(std::string resource, bool usable) {
    this->resource = resource;
    this->usable = usable;
}

bool ResourceNode::requirementsSatisfied() {
    for(ResourceNode* nodePtr : this->requirements) {
        if(nodePtr != nullptr && !(nodePtr->isUsable())) {
            return false;
        }
    }
    return true;
}

void ResourceNode::notifyRecipients(bool usable) {
    for(ResourceNode* nodePtr : this->recipients) {
        if(nodePtr != nullptr) {
            nodePtr->setUsable(usable);
        }
    }
}

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

void ResourceNode::addRequirement(ResourceNode* nodePtr) {
    if(!this->isRequirement(nodePtr->getResouce())) {
        nodePtr->addRecipient(this);
        this->requirements.push_back(nodePtr);
    }
}

std::string ResourceNode::getResouce() const {
    return this->resource;
}

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
    bool nodeValid = usable & this->requirementsSatisfied();
    if(this->usable != nodeValid) {
        this->usable = nodeValid;
        this->notifyRecipients(nodeValid);
    }
}

std::string ResourceNode::toString() const {
    std::string returnVal = this->resource + "(";
    returnVal += this->isUsable() ? "1" : "0";
    returnVal += ")";
    return returnVal;
}
