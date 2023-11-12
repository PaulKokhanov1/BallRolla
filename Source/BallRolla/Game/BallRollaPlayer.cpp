// Fill out your copyright notice in the Description page of Project Settings.


#include "BallRollaPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABallRollaPlayer::ABallRollaPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Create Components - Before this they aren't applied to our actor, rather they were just initialized
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh"); // within the <> it is the type of object we are creating
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	
	//Set Root Component to be our Mesh, all actors need a root component
	RootComponent = Mesh;
	//Attach the SpringArm to the Mesh, Spring will now follow the Mesh Transforms 
	SpringArm->SetupAttachment(Mesh);
	//Attach the Camera to the SpringArm, Camera will now follow the SpringArm Transforms
	Camera->SetupAttachment(SpringArm);

	//Set Physics to True
	Mesh->SetSimulatePhysics(true);




	
}

// Called when the game starts or when spawned
void ABallRollaPlayer::BeginPlay()
{
	Super::BeginPlay();

	//Acount for Mass in MoveForce
	MoveForce *= Mesh->GetMass();
	JumpImpulse *= Mesh->GetMass();


	//can either be "hit" when mesh collides with soemthing or overlaps something, i.e moves into a wall, like glitches into it
	Mesh->OnComponentHit.AddDynamic(this, &ABallRollaPlayer::OnHit); //function we are binding to should have same signatures as AddDynamic


	
}


// Called to bind functionality to input
//this is connecting what to do when a certain key is pressed
void ABallRollaPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Custom Input Axis Binding
	InputComponent->BindAxis("MoveForward", this,&ABallRollaPlayer::MoveForward);	//naming needs to match exactly how we named it in Project Settings in Unreal,
	//"this" refers to binding the object to a function defined in this class

	InputComponent->BindAxis("MoveRight", this,&ABallRollaPlayer::MoveRight);
	//Custom Action Binding
	InputComponent->BindAction("Jump", IE_Pressed, this,&ABallRollaPlayer::Jump); //KeyEvent could also be like "IE_Released" and would deal wit the case when the key is released
}

//Types of member Operators, "." and "->" and "::", they are used to are used to reference individual members of classes, structures, and unions.
//the "." is used to access a value of an object
//the "->" is used to access the value of a pointer to an object

void ABallRollaPlayer::MoveRight(float Value)
{

	// Get the right vector of the camera as it doesnt rotate and move the player in this direction based on the input and MoveForce
	const FVector Right = Camera->GetRightVector() * MoveForce * Value; //essentially we are just getting the right vector in reference with the Camera, since that vector stays always right
	//whereas if we just used (0,1,0) then its possible our "right" direction may change as the ball moves around and the camera moves
	Mesh->AddForce(Right);
}

void ABallRollaPlayer::MoveForward(float Value)
{

	const FVector Forward = Camera->GetForwardVector() * MoveForce * Value;
	Mesh->AddForce(Forward);	//Accumulates over time, doesnt just reset
	
}

void ABallRollaPlayer::Jump()
{

	if (JumpCount >= MaxJumpCount){return;}

	//Apply an impulse to the Mesh in the Z Axis
	Mesh->AddImpulse(FVector(0,0,JumpImpulse)); //creating custom vector on function call to the Mesh

	JumpCount++;

}


//this is called whenever mesh hits something since we defined this in the default value Section
void ABallRollaPlayer::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	//get direction we hit the surface on the z-axis
	const float HitDirection = Hit.Normal.Z;

	//Useful for debugging
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, FString::Printf(TEXT("Z Normal: %f"), HitDirection));

	
	//basically HitDirection is -1 if top of ball hits something and 1 if bottom of ball hits something, and anything inbetween those values is like a part of the z-axis hit something
	if (HitDirection > 0)
	{
		JumpCount = 0;
	}
	
}

