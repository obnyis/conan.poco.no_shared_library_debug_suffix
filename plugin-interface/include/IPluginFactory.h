#pragma once

#include <string>

#ifdef _WIN32
  #define PLUGININTERFACE_EXPORT __declspec(dllexport)
#else
  #define PLUGININTERFACE_EXPORT
#endif

namespace PluginInterface {

class PLUGININTERFACE_EXPORT IPluginFactory
{
public:
    virtual ~IPluginFactory() = default;

    virtual std::string GetStringFromPlugin() = 0;
};

}
