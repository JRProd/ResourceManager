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

ResourceNode::~ResourceNode() {
    for(int i = 0; i < requirements.size(); i++) {
        ResourceNode* nodePtr = this->requirements.at(i);
        if(nodePtr != nullptr) {
            delete nodePtr;
        }
    }
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

std::string ResourceNode::getResouce() {
    return this->resource;
}

std::vector<std::string> ResourceNode::getRequirements() {
    std::vector<std::string> requiredResouces;
    for(ResourceNode* nodePtr : this->requirements) {
        requiredResouces.push_back(nodePtr->toString());
    }
    return requiredResouces;
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

std::string ResourceNode::toString() {
    std::string returnVal = this->resource + "(";
    returnVal += this->isUsable() ? "1" : "0";
    returnVal += ")";
    return returnVal;
}
