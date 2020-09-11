// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildManager.generated.h"

UCLASS()
class DEMOS_API ABuildManager : public AActor
{
	GENERATED_BODY()

public:
	ABuildManager();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "UI", meta = (AllowPrivateAccess = "true"))
	float VisibleRange;

	UPROPERTY()
	TArray<AActor *> Interactables;

	UFUNCTION()
	void BuildModeActivate(bool InBuildMode);
};
