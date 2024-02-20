#pragma once

#include "IPluginFactory.h"

#ifdef _WIN32
  #define PLUGININTERFACE_EXPORT __declspec(dllexport)
#else
  #define PLUGININTERFACE_EXPORT
#endif

class PLUGININTERFACE_EXPORT PluginFactory : public PluginInterface::IPluginFactory
{
public:
    PluginFactory();
    ~PluginFactory() override;

    std::string GetStringFromPlugin() override;
};
