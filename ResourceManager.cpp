#include "ResourceManager.h"

#include <iostream>

ResourceManager::ResourceManager() {

}

ResourceManager::~ResourceManager() {
    for(ResourceNode* nodePtr : nodes) {
        if (nodePtr != nullptr) {
            delete nodePtr;
        }
    }
}

ResourceNode* ResourceManager::findNode(std::string resource) {
    for(ResourceNode* nodePtr : nodes) {
        if (nodePtr != nullptr && nodePtr->getResouce().compare(resource) == 0) {
            return nodePtr;
        }
    }
    return nullptr;
}

std::string ResourceManager::generateGraphBlock(int maxResouceLength, std::string resource) const {
    std::string returnVal;
    int diff = maxResouceLength - resource.size();
    int diffLeft = (diff/2) + (diff%2); // Odd difference get one extra on left
    int diffRight = (diff/2);
    // Space out diffrence to left of word
    for(int i = 0; i < diffLeft; i++) {
        returnVal += " ";
    }
    // Add word label
    returnVal += resource;
    // Space out difference to right of word
    for(int i = 0; i < diffRight; i++) {
        returnVal += " ";
    }
    returnVal += " | ";
    return returnVal;
}

std::string ResourceManager::generateGraphBreak(int maxResouceLength, int numOfResources) const {
    std::string returnVal;
    for(int i = 0; i < numOfResources + 1; i++) {
        for(int j = 0; j < maxResouceLength; j++) {
            returnVal += "-";
        }
        if(i == numOfResources) {
            returnVal += "-|";
        } else {
            returnVal += "-|-";
        }
    }
    returnVal += "\n";
    return returnVal;
}

void ResourceManager::addNode(std::string resource, std::string requirement) {
    ResourceNode* resourceNode = this->findNode(resource);
    ResourceNode* requiredNode = this->findNode(requirement);

    if(resourceNode == nullptr) { // Resource node does not exist
        resourceNode = new ResourceNode(resource);
        if(requiredNode == nullptr) { // Both nodes do not exist
            requiredNode = new ResourceNode(requirement); // Required node does not exist
            resourceNode->addRequirement(requiredNode);
            this->nodes.push_back(resourceNode);
            this->nodes.push_back(requiredNode);
        } else { // Only Resource node does not exist
            resourceNode->addRequirement(requiredNode);
            this->nodes.push_back(resourceNode);
        }
    } else { // Resource node exists
        if(requiredNode != nullptr) { // Both nodes already exist
            resourceNode->setUsable(true); // Add nodes back to being valid (if deleted)
            requiredNode->setUsable(true);
            resourceNode->addRequirement(requiredNode); // However, the my not be connected
        } else { // Only required node does not exist
            requiredNode = new ResourceNode(requirement); // Required node does not exist
            resourceNode->addRequirement(requiredNode);
            this->nodes.push_back(requiredNode);
        }
    }


}

void ResourceManager::deleteNode(std::string resource) {
    ResourceNode* resourceNode = this->findNode(resource);
    if(resourceNode != nullptr) {
        resourceNode->setUsable(false);
    }
}

std::string ResourceManager::toString(bool asMatrix) const {
    std::string returnVal;
    if(asMatrix) { // Print adjecentcy matrix
        std::vector<std::string> resources;
        int maxResouceLength = 0;
        for(ResourceNode* nodePtr : this->nodes) {
            if(nodePtr->toString().length() > maxResouceLength) {
                maxResouceLength = nodePtr->toString().length();
            }
            resources.push_back(nodePtr->getResouce());
        }
                       // Each grid slot same size as max resource. Separated by ' | '.
                       //  There must also be a slot for the vertical labels.
        // int gridSize = maxResouceLength*(this->nodes.size() + 1) + 3*this->nodes.size();

        // Generate the top left space of grid
        for(int i = 0; i < maxResouceLength; i++) {
            returnVal += " ";
        }
        returnVal += " | ";

        // Add labels to the grid slots
        for(std::string resource : resources) {
            returnVal += this->generateGraphBlock(maxResouceLength, resource);
        }
        returnVal += "\n";

        returnVal += this->generateGraphBreak(maxResouceLength, this->nodes.size());
        for(ResourceNode* nodeLabelPtr : this->nodes) {
            // Generates the label for this row
            returnVal += this->generateGraphBlock(maxResouceLength, nodeLabelPtr->toString());
            std::vector<const ResourceNode*> requirements = nodeLabelPtr->getRequirements();
            for(ResourceNode* nodePtr : this->nodes) {
                bool nodeIsRequirement = false;
                for(const ResourceNode* requiredNode : requirements) {
                    if(nodePtr->getResouce().compare(requiredNode->getResouce()) == 0) { // If a node is a required node of the current labelNode
                        returnVal += this->generateGraphBlock(maxResouceLength, "1");
                        nodeIsRequirement = true;
                        break;
                    }
                }
                if(!nodeIsRequirement) {
                    returnVal += this->generateGraphBlock(maxResouceLength, "0");
                }
            }
            returnVal += "\n";
            returnVal += this->generateGraphBreak(maxResouceLength, this->nodes.size());
        }
    } else { // Print list of requirements for each node
        for(ResourceNode* nodePtr : this->nodes) {
            returnVal += nodePtr->toString();
            returnVal += " | ";
            for(const ResourceNode* requirementPtr : nodePtr->getRequirements()) {
                returnVal += requirementPtr->toString() + " ";
            }
            returnVal += "\n";
        }
    }
    return returnVal;
}
