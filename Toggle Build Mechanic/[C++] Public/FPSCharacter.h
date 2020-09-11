// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSCharacter.generated.h"

class UCameraComponent;
class ABuildActorBase;
class UUserWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildModeActivateDispatcher, bool, InBuildMode);

UCLASS()
class DEMOS_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFPSCharacter();

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnBuildModeActivateDispatcher OnBuildModeActivate;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	private:
	UPROPERTY()
	UCameraComponent *CameraComp;

	float Range;
	bool bInBuildMode;
	bool bInInteractRange;
	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParams;

	UPROPERTY()
	ABuildActorBase *Buildable;

	UPROPERTY()
	UUserWidget *Widget;

	void ToggleMode();
	void OnInteractPressed();
	void OnInteractReleased();
	void MoveForward(float Val);
	void MoveRight(float Val);
};
