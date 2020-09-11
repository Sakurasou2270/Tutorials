// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCharacter.h"
#include "BuildInterface.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "BuildActorBase.h"
#include "Blueprint/UserWidget.h"

const auto InterfaceCall = [](UUserWidget *Widget, bool KeyHeldDown, ABuildActorBase *Buildable) {
	if (Widget)
	{
		if (Widget->GetClass()->ImplementsInterface(UBuildInterface::StaticClass()))
		{
			IBuildInterface::Execute_OnInteract(Widget, KeyHeldDown, Buildable);
		}
	}
};

AFPSCharacter::AFPSCharacter()
	: CameraComp{CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"))},
	  Range{300.0f},
	  bInBuildMode{false},
	  bInInteractRange{false}
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComp->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
	CameraComp->bUsePawnControlRotation = true;
	CameraComp->SetupAttachment(GetCapsuleComponent());
}

void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickEnabled(false);
}

void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Start = CameraComp->GetComponentLocation();
	FVector Forward = CameraComp->GetForwardVector();
	FVector Finish = (Forward * Range) + Start;

	GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		Start,
		Finish,
		FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_GameTraceChannel1)),
		CollisionQueryParams);

	bInInteractRange = HitResult.bBlockingHit;

	if (bInInteractRange)
	{
		Buildable = Cast<ABuildActorBase>(HitResult.GetActor());
		if (Buildable)
		{
			Buildable->ShowWidget();
			Widget = Buildable->CurrentWidget;
		}
	}
	else
	{
		if (Widget)
		{
			InterfaceCall(Widget, false, nullptr);
			Widget->SetRenderOpacity(0.0f);
		}
	}
}

void AFPSCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(FName("ToggleMode"), IE_Pressed, this, &AFPSCharacter::ToggleMode);
	PlayerInputComponent->BindAction(FName("Interact"), IE_Pressed, this, &AFPSCharacter::OnInteractPressed);
	PlayerInputComponent->BindAction(FName("Interact"), IE_Released, this, &AFPSCharacter::OnInteractReleased);

	PlayerInputComponent->BindAxis(FName("MoveForward/Backwards"), this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight/Left"), this, &AFPSCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &APawn::AddControllerPitchInput);
}

void AFPSCharacter::ToggleMode()
{
	!bInBuildMode ? bInBuildMode = true : bInBuildMode = false;
	OnBuildModeActivate.Broadcast(bInBuildMode);
	SetActorTickEnabled(bInBuildMode);

	if (Widget)
	{
		InterfaceCall(Widget, false, Buildable);
		Widget->SetRenderOpacity(0.0f);
		Widget = nullptr;
		Buildable = nullptr;
	}
}

void AFPSCharacter::OnInteractPressed()
{
	InterfaceCall(Widget, bInBuildMode && bInInteractRange, Buildable);
}

void AFPSCharacter::OnInteractReleased()
{
	InterfaceCall(Widget, false, Buildable);
}

void AFPSCharacter::MoveForward(float Val)
{
	FVector Direction = GetCapsuleComponent()->GetForwardVector();
	AddMovementInput(Direction, Val);
}

void AFPSCharacter::MoveRight(float Val)
{
	FVector Direction = GetCapsuleComponent()->GetRightVector();
	AddMovementInput(Direction, Val);
}