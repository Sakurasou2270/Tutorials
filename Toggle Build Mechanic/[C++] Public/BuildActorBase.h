// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildActorBase.generated.h"

class UUserWidget;
class UStaticMeshComponent;
class UWidgetComponent;
class UMaterialInterface;

UCLASS() class DEMOS_API ABuildActorBase : public AActor
{
	GENERATED_BODY()

public:
	ABuildActorBase();

	UPROPERTY()
	UUserWidget *CurrentWidget;

	void ShowWidget();
	void SetWidgetVisibility(bool Visible);
	void SetActorVisibility(bool Visible);

	UFUNCTION(BlueprintCallable, Category = "Progress")
	void BuildComplete();

protected:
	virtual void BeginPlay() override;

	private:
	UPROPERTY(VisibleAnywhere, Category = "Mesh", meta = (AllowPrivateAccess="true"))
	UStaticMeshComponent *MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "UI", meta = (AllowPrivateAccess="true"))
	UWidgetComponent *WidgetComp;

	bool bVisible;

	UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (AllowPrivateAccess="true"))
	TSubclassOf<UUserWidget> BuildWidget;

	UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UMaterialInterface *FinishedMaterial;
};
