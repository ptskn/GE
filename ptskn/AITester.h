//
// Created by ptskn on 15/09/2025.
//

#ifndef SAASCORE_AITESTER_H
#define SAASCORE_AITESTER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include "String.h"
class AITester
{
public :
    void createFile(const std::string& path,const std::string& content)
{
    std::ofstream file(path);
    file << content;
    file.close();
}
};


#endif //SAASCORE_AITESTER_H