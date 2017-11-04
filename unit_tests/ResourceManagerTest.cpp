#include "ResourceManager.h"

#include <iostream>

int main(int argc, char const *argv[]) {
    ResourceManager rscMngr;

    std::string cmd;
    do {
        std::cout << rscMngr.toString(true);
        std::cout << "(A)dd or (D)elete a node\n";
        std::cout << ">>> ";

        std::cin >> cmd;
        if(cmd.compare("A") == 0) {
            std::cout << "Enter the resource and requirement separated by a single space\n";
            std::cout << ">>> ";
            std::string resource;
            std::string requirement;
            std::cin >> resource >> requirement;
            rscMngr.addNode(resource, requirement);
        } else if(cmd.compare("D") == 0) {
            std::cout << "Enter the resouce to delete\n";
            std::cout << ">>> ";
            std::string resource;
            std::cin >> resource;
            rscMngr.deleteNode(resource);
        } else {
            std::cout << "Command not recognized\n";
        }
    }while(cmd.compare("Q") != 0);

    return 0;
}
