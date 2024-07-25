// Copyright Epic Games, Inc. All Rights Reserved.

#include "NSEnergySaver.h"
#include "Engine/Engine.h"
#include "TimerManager.h"

#define LOCTEXT_NAMESPACE "FNSEnergySaverModule"

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

void FNSEnergySaverModule::ShutdownModule()
{
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FNSEnergySaverModule, NSEnergySaver)