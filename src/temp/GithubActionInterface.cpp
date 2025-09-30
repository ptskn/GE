//
// Created by ptskn on 29/09/2025.

//
#include "../../include/temp/GithubActionInterface.h"
void GithubActionInterface::getProjectMenu()
{
    std::cout << "Project Menu\n";
    std::cout << "0 - Up\n";
    std::cout << "c - Create Project\n";
    std::cout << "r - Read Project\n";
    std::cout << "u - Update Project\n";
    std::cout << "d - Delete Project\n";
    std::cout << "3 - Create Epic \n";
    std::cout << "2 - Select Epic\n";
    std::cout << "Selection: ";
}
void GithubActionInterface::getEpicMenu()
{
    std::cout << "Project Menu\n";
    std::cout << "0 - Up\n";
    std::cout << "c - Create Epic\n";
    std::cout << "r - Read Epic\n";
    std::cout << "u - Update Epic\n";
    std::cout << "d - Delete Epic\n";
    std::cout << "Selection: ";
}
void GithubActionInterface::getRootMenu()
{
    std::cout << "Main Menu\n";
    std::cout << "Please make your selection\n";
    std::cout << "0 - Up\n";
    std::cout << "1 - Create Project\n";
    std::cout << "2 - Read Project\n";
    std::cout << "3 - Update Project\n";
    std::cout << "4 - Delete Project\n";
}
int GithubActionInterface::userSelect(const menuFunction& active)
{
    active();
    int r=0;
    std::cin >> r;
    return r;
}
void GithubActionInterface::stepIn(menuFunction *parent,menuFunction *active)
{
    if (parent&&active)
    {
        int to =
    }
}
