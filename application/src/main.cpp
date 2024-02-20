#include "IPluginFactory.h"

#include "Poco/ClassLoader.h"
#include "Poco/Manifest.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

int main() {
    std::shared_ptr<PluginInterface::IPluginFactory> pluginFactory;
    Poco::ClassLoader<PluginInterface::IPluginFactory> loader;
    std::string pluginName = "libplugin";
    std::string className = "PluginFactory";

    // This is the line that causes us problems for a debug build
    // as it returns the wrong suffix when building under conan
    pluginName.append(Poco::SharedLibrary::suffix());

    try
    {
        std::cout << "Loading Plugin " << pluginName << std::endl;
        loader.loadLibrary(pluginName);

        std::cout << pluginName << " loaded, creating " << className << std::endl;
        PluginInterface::IPluginFactory* t = loader.create(className);
        pluginFactory = std::shared_ptr<PluginInterface::IPluginFactory>(t);

        std::cout << pluginFactory->GetStringFromPlugin() << std::endl;
    }
    catch (const Poco::Exception& e)
    {
        std::cout << e.displayText() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    if (pluginFactory)
    {
        std::cout << "Unloading Plugin " << pluginName << std::endl;
        try
        {
            pluginFactory.reset();
            loader.unloadLibrary(pluginName);
        }
        catch (const Poco::Exception& e)
        {
            std::cout << e.displayText() << std::endl;
        }
        std::cout << pluginName << " unloaded" << std::endl;
    }
}
