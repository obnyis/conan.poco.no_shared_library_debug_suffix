#include "PluginFactory.h"

#include "Poco/ClassLibrary.h"

POCO_BEGIN_MANIFEST(PluginInterface::IPluginFactory)
POCO_EXPORT_CLASS(PluginFactory)
POCO_END_MANIFEST

PluginFactory::PluginFactory(){}

PluginFactory::~PluginFactory(){}

std::string PluginFactory::GetStringFromPlugin(){
    #ifdef NDEBUG
    return "plugin/1.0: Hello World Release!\n";
    #else
    return "plugin/1.0: Hello World Debug!\n";
    #endif
}
