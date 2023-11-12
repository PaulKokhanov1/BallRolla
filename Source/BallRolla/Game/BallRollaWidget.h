// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BallRollaWidget.generated.h"

/**
 * 
 */
UCLASS()
class BALLROLLA_API UBallRollaWidget : public UUserWidget
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintImplementableEvent)	//meaning this has no C++ implementation at all, so we dont make a definition for this
	void SetItemText(int32 ItemsCollected, int32 ItemsInLevel);
	
};
