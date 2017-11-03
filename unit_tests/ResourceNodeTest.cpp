#include <iostream>

#include "ResourceNode.h"

int main(int argc, char const *argv[]) {

    ResourceNode* node1_1 = new ResourceNode("Node 1_1", false);
    ResourceNode* node1_2 = new ResourceNode("Node 1_2", true);
    ResourceNode* node1_3 = new ResourceNode("Node 1_3", true);

    ResourceNode* node2_1 = new ResourceNode("Node 2_1", true);

    ResourceNode* node3_1 = new ResourceNode("Node 3_1", true);
    ResourceNode* node3_2 = new ResourceNode("Node 3_2", true);
    ResourceNode* node3_3 = new ResourceNode("Node 3_3", true);

    node1_1->addRequirement(node2_1);
    node1_2->addRequirement(node2_1);
    node1_3->addRequirement(node2_1);

    node2_1->addRequirement(node3_1);
    node2_1->addRequirement(node3_2);
    node2_1->addRequirement(node3_3);

    std::string cmd;
    do{
        std::cout << node1_1->toString() << " --\\             /-- " << node3_1->toString() << "\n";
        std::cout << node1_2->toString() << " --- " << node2_1->toString() << " --- " << node3_2->toString() << "\n";
        std::cout << node1_3->toString() << " --/             \\-- " << node3_3->toString() << "\n";
        std::cout << "Enter the node to toggle the usable boolean\n";
        std::cout << ">>> ";
        std::cin >> cmd;
        if(cmd.compare("1_1") == 0) {
            node1_1->setUsable(!node1_1->isUsable());
        } else if (cmd.compare("1_2") == 0) {
            node1_2->setUsable(!node1_2->isUsable());
        } else if (cmd.compare("1_2") == 0) {
            node1_3->setUsable(!node1_3->isUsable());
        } else if (cmd.compare("2_1") == 0) {
            node2_1->setUsable(!node2_1->isUsable());
        } else if (cmd.compare("3_1") == 0) {
            node3_1->setUsable(!node3_1->isUsable());
        } else if (cmd.compare("3_2") == 0) {
            node3_2->setUsable(!node3_2->isUsable());
        } else if (cmd.compare("3_3") == 0) {
            node3_3->setUsable(!node3_3->isUsable());
        } else {
            std::cout << "That node does not exist\n";
        }

    }while(cmd.compare("Q") != 0);

    return 0;
}
