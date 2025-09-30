//
// Created by ptskn on 02/08/25.
//

#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include "CoreIncludes.h"
#include "../Modules/Processors/DataBaseProcessor.h"
#include "../Modules/Processors/WebProcessor.h"
#include "../Router/HttpServer.h"
#include "../Modules/WebComponents/Menus/MenuInterface.h"

//#include "../../External/Router/FMRouter.h"
//#include "../../../Libs/IM/Windows/include/GuiWindow.h"



using namespace juce;

class BootLoader// : public DocumentWindow
{



 //   Array<ElementProcessor*> viewProcessors;

 //   void regElementProcessor(ElementProcessor *p);

    virtual void regWebProcessors()=0;
    virtual void regDatabaseProcessors()=0;

    void clear();
protected:
    HttpServer* server{nullptr};
    void regWebProcessor(WebProcessor *p);
    void regDatabaseProcessor(DataBaseProcessor *p);
    DataManager *dbManager;
    Array<WebProcessor*> webProcessors;
    Array<DataBaseProcessor*> dbProcessors;
public:

    void initialize();

    BootLoader() ;
    //void closeButtonPressed() override;

 virtual ~BootLoader();



};


#endif //BOOTLOADER_H
