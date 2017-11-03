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
        if(!(nodePtr->isUsable())) {
            return false;
        }
    }
    return true;
}

void ResourceNode::notifyRecipients(bool usable) {
    for(ResourceNode* nodePtr : this->recipients) {
        std::cout << "Notifying " << nodePtr->toString() << " of changing usability\n";
        nodePtr->setUsable(usable);
    }
}

void ResourceNode::addRecipient(ResourceNode* nodePtr) {
    std::cout << this->toString() << " supplys " << nodePtr->toString() << "\n";
    this->recipients.push_back(nodePtr);
}

void ResourceNode::addRequirement(ResourceNode* nodePtr) {
    std::cout << this->toString() << " requires " << nodePtr->toString() << " to be avaliable\n";
    nodePtr->addRecipient(this);
    this->requirements.push_back(nodePtr);
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
