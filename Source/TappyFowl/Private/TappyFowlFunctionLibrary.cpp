// Copyright (c) 2024 Thirdweb. All Rights Reserved.


#include "TappyFowlFunctionLibrary.h"

#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"

#include "Kismet/KismetSystemLibrary.h"

void UTappyFowlFunctionLibrary::PrintDevWarning(const UObject* WorldContextObject, const FText InText)
{
	UKismetSystemLibrary::PrintText(WorldContextObject, InText, true, true, FLinearColor(0.732248f, 1.0f, 0.0f, 1.0f), 10.0f);
}

void UTappyFowlFunctionLibrary::PrintDevError(const UObject* WorldContextObject, const FText InText)
{
	UKismetSystemLibrary::PrintText(WorldContextObject, InText, true, true, FLinearColor(1.0f, 0.037429f, 0.0f, 1.0f), 30.0f);
}

UMaterialInstanceDynamic* UTappyFowlFunctionLibrary::CreateActorMaterialInstance(AActor* Actor,
	UPaperSpriteComponent* Sprite,
	UPaperFlipbookComponent* Flipbook,
	UStaticMeshComponent* Static,
	USkeletalMeshComponent* Skeletal)
{
	if (IsValid(Skeletal) && IsValid(Skeletal->GetSkinnedAsset()))
	{
		return Skeletal->CreateDynamicMaterialInstance(0);
	}
	
	if (IsValid(Flipbook) && IsValid(Flipbook->GetFlipbook()))
	{
		return Flipbook->CreateDynamicMaterialInstance(0);
	}

	if (IsValid(Static) && IsValid(Static->GetStaticMesh().Get()))
	{
		return Static->CreateDynamicMaterialInstance(0);
	}

	if (IsValid(Sprite) && IsValid(Sprite->GetSprite()))
	{
		return Sprite->CreateDynamicMaterialInstance(0);
	}
	PrintDevError(Actor, FText::FromString(TEXT("Unable to find a valid Mesh or Sprite reference. One of these is required for classes to create Material Instance In Object: ") + UKismetSystemLibrary::GetDisplayName(Actor)));
	return nullptr;
}
