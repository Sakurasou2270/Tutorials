// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildActorBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"

ABuildActorBase::ABuildActorBase()
	: MeshComp{CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"))},
	  WidgetComp{CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComp"))},
	  bVisible{false}
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MeshComp->SetCollisionObjectType(ECC_GameTraceChannel1);
	MeshComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	RootComponent = MeshComp;

	WidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComp->bVisible = false;
	WidgetComp->AttachToComponent(MeshComp, FAttachmentTransformRules::KeepRelativeTransform);
}

void ABuildActorBase::BeginPlay()
{
	Super::BeginPlay();

	MeshComp->SetVisibility(false);
}

void ABuildActorBase::ShowWidget()
{
	if (BuildWidget)
	{
		if (CurrentWidget)
		{
			CurrentWidget->SetRenderOpacity(1.0f);
		}
		else
		{
			CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), BuildWidget);
			if (CurrentWidget)
			{
				CurrentWidget->AddToViewport();
			}
		}
	}
}

void ABuildActorBase::SetWidgetVisibility(bool Visible)
{
	WidgetComp->SetVisibility(Visible);
}

void ABuildActorBase::SetActorVisibility(bool Visible)
{
	if (bVisible)
	{
		WidgetComp->SetVisibility(Visible);
	}
	else
	{
		WidgetComp->SetVisibility(Visible);
		MeshComp->SetVisibility(Visible);
		MeshComp->SetCollisionResponseToAllChannels(
			Visible ? ECR_Overlap : ECR_Ignore);
	}
}

void ABuildActorBase::BuildComplete()
{
	bVisible = true;
	MeshComp->SetMaterial(0, FinishedMaterial);
	MeshComp->SetVisibility(true);
	MeshComp->SetCollisionResponseToAllChannels(ECR_Block);
}