// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BuildInterface.generated.h"

class ABuildActorBase;

UINTERFACE(MinimalAPI)
class UBuildInterface : public UInterface
{
	GENERATED_BODY()
};

class DEMOS_API IBuildInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interaction")
	void OnInteract(bool IsKeyHeldDown, ABuildActorBase *BuildActor);
};
