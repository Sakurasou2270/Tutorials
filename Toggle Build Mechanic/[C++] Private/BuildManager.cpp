// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildManager.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BuildActorBase.h"

ABuildManager::ABuildManager()
	: VisibleRange{2000.0f}
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABuildManager::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickEnabled(false);

	AFPSCharacter *Player = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->OnBuildModeActivate.AddDynamic(this, &ABuildManager::BuildModeActivate);

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABuildActorBase::StaticClass(), Interactables);
}

void ABuildManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (auto &&Buildable : Interactables)
	{
		ABuildActorBase *BuildClass = Cast<ABuildActorBase>(Buildable);
		if (BuildClass)
		{
			BuildClass->SetWidgetVisibility(
				FVector::Distance(
					UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation(),
					BuildClass->GetActorLocation()) < VisibleRange);
		}
	}
}

void ABuildManager::BuildModeActivate(bool InBuildMode)
{
	UE_LOG(LogTemp, Warning, TEXT("Something"));
	for (auto &&Buildable : Interactables)
	{
		ABuildActorBase *BuildClass = Cast<ABuildActorBase>(Buildable);
		if (BuildClass)
		{
			BuildClass->SetActorVisibility(InBuildMode);
		}
	}
	SetActorTickEnabled(InBuildMode);
}