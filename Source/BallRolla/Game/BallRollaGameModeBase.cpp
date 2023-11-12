// Fill out your copyright notice in the Description page of Project Settings.


#include "BallRollaGameModeBase.h"

#include "BallRollaWidget.h"
#include "BallRolla/Items/BallRollaItemBase.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ABallRollaGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//this gets all items in our world

	//creating an array of items, specifically we are saying create an array of AActors
	TArray<AActor*> Items;
	//GetWorld is the context where we want to look within our game, it returns the map that we are in,
	//Next is an ActorClass, we typecast to the specific class we want, it specifies to return the Uclass version of the ABallRollaItemBase
	//last parameter is where we place all the items we find in our world into
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABallRollaItemBase::StaticClass(), Items);
	ItemsInLevel = Items.Num();		//gives length of array

	if(GameWidgetClass)		//Checking if this class has been selected
	{
		//setting our GameWidget
		//making sure that the class which is exposed in the editor is derived from the UBallRollaWidget
		GameWidget = Cast<UBallRollaWidget>(CreateWidget(GetWorld(), GameWidgetClass));

		if (GameWidget)	//checking if there is value in gamewidget, i.e not null
		{
			GameWidget->AddToViewport();
			UpdateItemText();
			
		}
		
	}
	
}

void ABallRollaGameModeBase::UpdateItemText()
{
	GameWidget->SetItemText(ItemsCollected, ItemsInLevel);
}


//updating the number of items we have collected
void ABallRollaGameModeBase::ItemCollected()
{
	ItemsCollected++;
	UpdateItemText();
}
