// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BallRollaGameModeBase.generated.h"


class UBallRollaWidget;


/**
 * Main things this class will handle is:
 * Widget System: how many items collected, how many left
 * 
 */
UCLASS()
class BALLROLLA_API ABallRollaGameModeBase : public AGameModeBase	//AGameModeBase is our parent class
{
	GENERATED_BODY()

protected:

	//just use int32 for unreal
	int32 ItemsCollected = 0;
	int32 ItemsInLevel = 0;


	UPROPERTY(EditAnywhere, Category="Widgets")
	TSubclassOf<class UUserWidget> GameWidgetClass;	//allows us to create another widget that we can switch between in our editor


	UPROPERTY()
	UBallRollaWidget* GameWidget;		//apparently this is the widget we display while the GameWidgetClass is a class the user can choose
	

	//override the BeginPlay function
	virtual void BeginPlay() override;

	void UpdateItemText();

public:

	//update info to the widget
	void ItemCollected();
	
};
