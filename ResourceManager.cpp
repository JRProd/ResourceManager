#include "ResourceManager.h"

ResourceManager::ResourceManager() {

}

ResourceManager::~ResourceManager() {
    for(ResourceNode* nodePtr : nodes) {
        if (nodePtr != nullptr) {
            delete nodePtr;
        }
    }
}

// Find node from the list of nodes added
ResourceNode* ResourceManager::findNode(std::string resource) {
    for(ResourceNode* nodePtr : nodes) {
        if (nodePtr != nullptr && nodePtr->getResouce().compare(resource) == 0) {
            return nodePtr;
        }
    }
    return nullptr;
}

// Aligns the resource into middle of a graph block
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

// Generates the horizontal breaks in the graph
std::string ResourceManager::generateGraphBreak(int maxResouceLength, int numOfResources) const {
    std::string returnVal;
    returnVal += "> ";
    // For the left open slot and the number of resources
    for(int i = 0; i < numOfResources + 1; i++) {
        // For the maxResouceLength
        for(int j = 0; j < maxResouceLength; j++) {
            // Add the line breaks
            returnVal += "-";
        }
        // Add the vertical breaks
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
    // Find the node
    ResourceNode* resourceNode = this->findNode(resource);
    if(resourceNode != nullptr) {
        // Set usable to false
        resourceNode->setUsable(false);
    }
}

std::string ResourceManager::toString(bool asMatrix) const {
    std::string returnVal;
    if(asMatrix) { // Print adjecentcy matrix
        // Get largest resource
        int maxResouceLength = 0;
        for(ResourceNode* nodePtr : this->nodes) {
            if(nodePtr->toString().length() > maxResouceLength) {
                maxResouceLength = nodePtr->toString().length();
            }
        }

        // Generate the top left space of grid
        returnVal += "> Node(usable): 1=Usable, 0=Not Usable\n";
        returnVal += "> ";
        for(int i = 0; i < maxResouceLength; i++) {
            returnVal += " ";
        }
        returnVal += " | ";

        // Add labels to the grid slots
        for(ResourceNode* nodePtr : this->nodes) {
            returnVal += this->generateGraphBlock(maxResouceLength, nodePtr->getResouce());
        }
        returnVal += "\n";

        returnVal += this->generateGraphBreak(maxResouceLength, this->nodes.size());
        for(ResourceNode* nodeLabelPtr : this->nodes) {
            // Generates the label for this row
            returnVal += "> ";
            returnVal += this->generateGraphBlock(maxResouceLength, nodeLabelPtr->toString());
            std::vector<const ResourceNode*> requirements = nodeLabelPtr->getRequirements();
            // For all nodes in added
            for(ResourceNode* nodePtr : this->nodes) {
                bool nodeIsRequirement = false;
                for(const ResourceNode* requiredNode : requirements) {
                    if(nodePtr->getResouce().compare(requiredNode->getResouce()) == 0) { // If a node is a required node of the current labelNode
                        // Generate graph block for nodes that are required
                        returnVal += this->generateGraphBlock(maxResouceLength, "1");
                        nodeIsRequirement = true;
                        break;
                    }
                }
                // Generate graph block for nodes not required
                if(!nodeIsRequirement) {
                    returnVal += this->generateGraphBlock(maxResouceLength, "0");
                }
            }
            returnVal += "\n";
            returnVal += this->generateGraphBreak(maxResouceLength, this->nodes.size());
        }
    } else { // Print list of requirements for each node
        // Get max resource length larger then 'Resources'
        int maxResouceLength = 9;
        for(ResourceNode* nodePtr : this->nodes) {
            if(nodePtr->toString().length() > maxResouceLength) {
                maxResouceLength = nodePtr->toString().length();
            }
        }

        returnVal += "> ";
        returnVal += this->generateGraphBlock(maxResouceLength, "Resources");
        returnVal += "Requirements for the resources. Node(usable): 1=Usable, 0=Not Usable\n";

        // For all the nodes, print the node and then requirements
        for(ResourceNode* nodePtr : this->nodes) {
            returnVal += "> ";
            returnVal += this->generateGraphBlock(maxResouceLength, nodePtr->toString());
            for(const ResourceNode* requirementPtr : nodePtr->getRequirements()) {
                returnVal += requirementPtr->toString() + " ";
            }
            returnVal += "\n";
        }
    }
    return returnVal;
}
