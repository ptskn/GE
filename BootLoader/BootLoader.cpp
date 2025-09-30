#include "BootLoader.h"


void BootLoader::initialize()
   {

    dbManager->loadUsers();
    regWebProcessor(new RootView(dbManager));
    regWebProcessor(new UserCreate(dbManager));
    regWebProcessor(new UserPasswordChange(dbManager));
    regWebProcessor(new UserLogin(dbManager));
    regWebProcessor(new UserEdit(dbManager));
    regWebProcessor(new RootMenu(dbManager));
    regWebProcessor(new ConnectorMenu(dbManager));
    regWebProcessor(new UserMenu(dbManager));

    regDatabaseProcessor(new UserDatabaseProcessor(dbManager));


    regDatabaseProcessors();
    regWebProcessors();






   }


BootLoader::BootLoader()
{
   Dictionary::getInstance()->setLanguage(Dictionary::French);
   Dictionary::getInstance()->load();
   HtmlLookAndFeel::getInstance()->load();
   dbManager = new PgDataManager;

}

void BootLoader::regWebProcessor(WebProcessor *p)
{
    webProcessors.add(p);
    server->addWebProcessor(p);
}
void BootLoader::regDatabaseProcessor(DataBaseProcessor *p)
{
    dbProcessors.add(p);
    server->addDataBaseProcessor(p);
}
/*
void BootLoader::regElementProcessor(ElementProcessor *p)
{
    viewProcessors.add(p);
    server->addElementProcessor(p);
}*/
void BootLoader::clear()
{
    for (auto p:webProcessors)
    {
        delete p;
    }
    for (auto p:dbProcessors)
    {
        delete p;
    }
 //   for (auto p:viewProcessors)
 //   {
 //       delete p;
 //   }
}
BootLoader::~BootLoader()
{
    server=nullptr;
    delete dbManager;
    clear();


}