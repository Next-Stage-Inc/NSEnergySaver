
# NSEnergySaver Plugin for Unreal Engine

## Overview

The NSEnergySaver plugin is designed to help manage and reduce the energy consumption of Unreal Engine projects, particularly during the development process. It achieves this by setting frame rate limits and enabling dynamic resolution when using Direct3D 12 on Windows platforms.

## Features

- Limits the maximum frame rate to 60 FPS.
- Enables dynamic resolution support for Direct3D 12 on Windows.
- Executes console commands to optimize energy savings automatically.

## Installation

1. **Download the Plugin:**
   - Obtain the latest version of the NSEnergySaver plugin from the repository or distribution site.

2. **Add to Your Project:**
   - Copy the `NSEnergySaver` plugin folder into the `Plugins` directory of your Unreal Engine project.

3. **Enable the Plugin:**
   - Open your project in Unreal Engine.
   - Go to `Edit` -> `Plugins`.
   - Find `NSEnergySaver` in the list and enable it.
   - Restart the Unreal Engine editor to apply changes.

## Usage

The plugin is designed to automatically execute upon the completion of the engine loop initialization. There is no need for manual intervention beyond installation and enabling the plugin.

## How It Works

### Startup Module

Upon starting up, the plugin:

1. Sets the maximum frames per second (FPS) to 60.
2. Checks if the platform is Windows and if the RHI (Rendering Hardware Interface) type is Direct3D 12. If both conditions are met, it enables support for dynamic resolution.

### Code Overview

```cpp
void FNSEnergySaverModule::StartupModule()
{
#if WITH_EDITOR
    FCoreDelegates::OnFEngineLoopInitComplete.AddLambda([this]()
        {
            ExecuteConsoleCommand(TEXT("t.maxfps 60"));

#if PLATFORM_WINDOWS
            if (RHIGetInterfaceType() == ERHIInterfaceType::D3D12)
            {
                GRHISupportsDynamicResolution = true;
            }

            ExecuteConsoleCommand(TEXT("r.DynamicRes.OperationMode 2"));
#endif
        });
#endif
}

void FNSEnergySaverModule::ExecuteConsoleCommand(const FString& Command)
{
    if (GEngine)
    {
        GEngine->Exec(nullptr, *Command);
        UE_LOG(LogTemp, Log, TEXT("NSEnergySaver Executed command: %s"), *Command);
    }
}
```

### Shutdown Module

The `ShutdownModule` function is defined but currently does not execute any specific commands. This can be customized if needed for future updates.

### Implementation

The plugin is implemented and registered using the `IMPLEMENT_MODULE` macro:

```cpp
IMPLEMENT_MODULE(FNSEnergySaverModule, NSEnergySaver)
```

## Contributing

We welcome contributions to the NSEnergySaver plugin. If you find any issues or have suggestions for improvements, please open an issue or submit a pull request in the repository.

## License

This plugin is provided under the Epic Games, Inc. license. Please refer to the LICENSE file included with the plugin for more details.

## Support

For support, please contact the development team or visit the official support forum.

## Changelog

### Version 1.0

- Initial release with FPS limiting and dynamic resolution support.

---

Thank you for using the NSEnergySaver plugin. We hope it enhances your development experience by optimizing energy consumption during your Unreal Engine projects.
