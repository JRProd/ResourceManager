/* ########## RESOURCE MANAGER APPLICATION ##########
 * The UI runner for the Resource Manager Application.
 *  Manages the user input and adding/deleting nodes.
 *
 * Aurthor - Jake Rowland
 * Date - November 5, 2107
*/

#include <fstream>
#include <iostream>

#include "ResourceManager.h"

int main(int argc, char const *argv[]) {
    std::cout << "< ##################################################\n";
    std::cout << "< ##           Resource Manager Application       ##\n";
    std::cout << "< ##          (A)dd nodes or (D)elete a node      ##\n";
    std::cout << "< ##                                              ##\n";
    std::cout << "< ##                 By Jake Rowland              ##\n";
    std::cout << "< ##################################################\n";
    std::cout << "< (Q)uit to leave program\n<\n";

    // Open generic file
    std::ifstream inputFile;
    inputFile.open("resource.txt", std::ios::in);

    // If file does not exist
    if(!inputFile.good()) {
        std::string fileUrl;
        // Get file from command line arguments
        if(argc >= 2) {
            fileUrl = argv[1];
        // Get file from user input
        } else {
            std::cout << "< Please enter the file to read the resources from.\n";
            std::cout << "> ";
            std::cin >> fileUrl;
            if(fileUrl.compare("Q") == 0) {
                std::cout << "< Bye!\n";
                return 0;
            }
        }
    }

    // Define ResourceManager
    ResourceManager manager;

    // Get resources from file
    while(inputFile.good()) {
        std::string resourceLine;
        getline(inputFile, resourceLine, '\n');

        std::string resource = resourceLine.substr(0, resourceLine.find(' '));
        std::string requirement = resourceLine.substr(resourceLine.find(' ') + 1, resourceLine.length());

        if(!resource.empty() && !requirement.empty()) {
            manager.addNode(resource, requirement);
        }
    }

    // Prompt user on how to show output
    std::cout << "< Would you like (L)ist of requirements for a resource, or\n";
    std::cout << "< a adjacency (M)atrix?\n";


    std::string cmd;
    bool writeList = false;
    // Get user command
    do {
        std::cout << "> ";
        std::cin >> cmd;
        if(cmd.compare("L") == 0) {
            break;
        } else if (cmd.compare("M") == 0) {
            writeList = true;
            break;
        } else if (cmd.compare("Q") == 0){
            std::cout << "< Bye!\n";
            return 0;
        }else {
            std::cout << "< Command not recognized\n";
            std::cout << "< Please enter (L)ist or adjacency (M)atrix\n";
        }
    } while(true);

    // Add or delete node commands
    do {
        std::cout << manager.toString(writeList);
        std::cout << "< (A)dd or (D)elete a node\n";
        std::cout << "> ";

        std::cin >> cmd;
        if(cmd.compare("A") == 0) {
            std::cout << "< Enter the resource and requirement separated by a single space.\n";
            std::cout << "< This will generate a link between the nodes.\n";
            std::cout << "> ";
            std::string resource;
            std::string requirement;
            std::cin >> resource >> requirement;
            if(!resource.empty() && !requirement.empty()) {
                manager.addNode(resource, requirement);
            }
        } else if(cmd.compare("D") == 0) {
            std::cout << "< Enter the resouce to delete\n";
            std::cout << "> ";
            std::string resource;
            std::cin >> resource;
            manager.deleteNode(resource);
        } else if (cmd.compare("Q") == 0){
            break;
        } else {
            std::cout << "< Command not recognized\n";
            std::cout << "< Please enter (A)dd, (D)elete, or (Q)uit to continue\n";

        }
    }while(true);

    std::cout << "< Bye!\n";

    return 0;
}
