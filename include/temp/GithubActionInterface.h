//
// Created by ptskn on 29/09/2025.
//

#ifndef SAASCORE_GITHUBACTIONINTERFACE_H
#define SAASCORE_GITHUBACTIONINTERFACE_H
#include <functional>
#include <string>
#include <cstdlib>
     #include <iostream>
static std::string projectName{"GitHubCli"};
typedef std::function<void()> menuFunction;

template < typename... TYPES > std::tuple<TYPES...> variadicTuple( TYPES&&... refs )
{ return std::tuple<TYPES...>{ std::forward<TYPES>(refs)... } ; } // construct tuple using pack expansion





class CliMenu
{
    typedef std::tuple<std::string,std::string> choices;
    std::unordered_map<int,choices> choicess;
    std::string menuName;

protected:
 //   typedef std::unordered_map<int, menuFunction> MenuFunctionsMap;
    typedef std::function<void()> tupleFunction;
public:
    CliMenu(std::string &&n)
    {
        menuName=n;
    }
    void createItem(int pos,std::string key,std::string text)
    {
        const auto liste= variadicTuple(key,text);
        choicess[pos]=liste;
    }
   virtual void createItems()=0;
    void showCrudMenu()
    {
//for (auto )

    };
};
class CrudMenu : public CliMenu
{
public:
    CrudMenu()
    {
        createItems();
    }
    void createItems()
    {
        createItem("-",projectName);
        createItem("0","Create "+projectName);
        createItem("c","Read   "+projectName);
        createItem("r","Update "+projectName);
        createItem("u","Delete "+projectName);
        createItem("d","");
    }
};
class ProjectMenu : public CliMenu
{
    CrudMenu crudMenu;
public:
    void createItems()
    {

    }
};
class GithubActionInterface
{
public:
   void getEpicMenu();
   void getProjectMenu();
    void getRootMenu();
    int userSelect(const menuFunction& active);
    void stepIn(menuFunction *parent,menuFunction *active);

};


#endif //SAASCORE_GITHUBACTIONINTERFACE_H