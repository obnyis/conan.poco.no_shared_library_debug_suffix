# Reproduction of conan-center-index issue #22805


```bash
export CONAN_HOME=$PWD/conan_cache
conan profile detect

conan install plugin-interface -pr default -b missing
conan install plugin-interface -pr default -b missing -s build_type=Debug
conan export plugin-interface

conan create plugin -b missing
conan create plugin -b missing -s build_type=Debug

conan create application -b missing
conan create application -b missing -s build_type=Debug

conan install --deployer-package=* --deployer-folder=install/Release \
  --requires application/1.0 \
  --requires plugin/1.0 \
  -c tools.graph:skip_binaries=False

conan install --deployer-package=* --deployer-folder=install/Debug \
  --requires application/1.0 \
  --requires plugin/1.0 \
  -c tools.graph:skip_binaries=False \
  -s build_type=Debug

# This runs fine
./install/Release/bin/application

# This cannot find the plugin due to Poco::SharedLibrary::suffix() giving the incorrect value
./install/Debug/bin/application
```

After these commands have run, ./install will contain:

```
install
├── Debug
│   ├── bin
│   │   └── application
│   └── lib
│       └── libplugin.so
└── Release
    ├── bin
    │   └── application
    └── lib
        └── libplugin.so
```

Running `./install/Release/bin/application` will result in:

```
Loading Plugin libplugin.so
libplugin.so loaded, creating PluginFactory
plugin/1.0: Hello World Release!

Unloading Plugin libplugin.so
libplugin.so unloaded
```

Running `./install/Debug/bin/application` will result in:

```
Loading Plugin libplugind.so
Cannot load library: libplugind.so: cannot open shared object file: No such file or directory
```
