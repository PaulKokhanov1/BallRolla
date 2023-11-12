// Fill out your copyright notice in the Description page of Project Settings.


#include "BallRollaItemBase.h"

#include "BallRolla/Game/BallRollaGameModeBase.h"
#include "BallRolla/Game/BallRollaPlayer.h"

// Sets default values
ABallRollaItemBase::ABallRollaItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	//dont wanna use onCompoenntHit cause may cause situation where player may sligthly bounch off the item it is trying to collect
	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ABallRollaItemBase::OverlapBegin);

}

// Called when the game starts or when spawned
void ABallRollaItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}


//when player rolls into item we do something
void ABallRollaItemBase::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//checking if what we hit is a player type
	if (Cast<ABallRollaPlayer>(OtherActor) != nullptr)
	{
		Collected();
	}
}

void ABallRollaItemBase::Collected_Implementation()		//basically most of the function is implemented within the blueprint
{

	//we use a cast whenever we want to check against another class to see if it is of a certain type 
	ABallRollaGameModeBase* GameMode = Cast<ABallRollaGameModeBase>(GetWorld()->GetAuthGameMode());

	if(GameMode)
	{
		GameMode->ItemCollected();
	}
}
