

#include <iostream>
#include <memory>
#include "../include/TimeManagementService/TimeManagementInterface.h"
#include "../../include/GithubActionInterface.h"
std::unique_ptr<TimeManagementInterface> inter;
std::unique_ptr<GithubActionInterface> gitActions;
        [[noreturn]] int main ()
        {
            //site=new BootLoad;
            inter = std::make_unique<TimeManagementInterface>();
            gitActions = std::make_unique<GithubActionInterface>();
            std:: cout << "GitHubActionsInterface" << std::endl;
            gitActions->getRootMenu();

            while (true)
            {

            }
            inter=nullptr;

        }


