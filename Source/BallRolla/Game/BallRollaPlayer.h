// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BallRollaPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent; //this is forward declaration, more lightweight than using #include, doesn't allow us to edit anything within the class

UCLASS()
class BALLROLLA_API ABallRollaPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABallRollaPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Define Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")	//these allow us to define specific behavior for different things in our C++ class to direct them to behave or look a certain way in our blueprint class 
	UStaticMeshComponent* Mesh;		//This is our ball mesh, i.e our visual component, the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")		//all these variables are pointers, so we want limited access to it which is why we say blueprintreadonly
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UCameraComponent* Camera;
	
	//VARIABLES
	UPROPERTY(EditAnywhere, BlueprintReadWrite)		//editAnywhere -> means anywhere we see this in our blueprints we can easily edit it, since these arent pointers we can directly change them in the blueprints
	float MoveForce = 500.0f;		// how fast ball moves
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpImpulse = 500.0f;		//how high it can jump
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxJumpCount = 1;



	

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:		//these cannot be edited by outside classes

	//FUNCTIONS
	void MoveRight (float Value);		//value is which button is pressed, for movement direction
	void MoveForward (float Value);
	void Jump ();

	//in arguments we are defining a UPrimitiveComponent called ... , ex "HitComponent"
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


	int32 JumpCount = 0;		//we will compare this to our MaxJumpCount
	

};
