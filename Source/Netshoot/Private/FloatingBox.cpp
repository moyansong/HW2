// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingBox.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFloatingBox::AFloatingBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LifeSpan = 4.0f;

	if (!CollisionComponent)
	{
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		CollisionComponent->InitSphereRadius(60.0f);
		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("BlockAllDynamic"));
		CollisionComponent->OnComponentHit.AddDynamic(this, &AFloatingBox::OnHit);
		RootComponent = CollisionComponent;
	}

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("StaticMesh'/Game/Environment/Barrel.Barrel'"));

	if (CubeVisualAsset.Succeeded())
	{
		Mesh->SetStaticMesh(CubeVisualAsset.Object);
		Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, -60.0f));
	}
	Mesh->BodyInstance.SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

// Called when the game starts or when spawned
void AFloatingBox::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFloatingBox::Tick(float DeltaTime)
{
	float RunningTime = GetGameTimeSinceCreation();
	FVector Location = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	Location.Z += DeltaHeight * 20.0f;
	float DeltaRotation = DeltaTime * 20.0f;
	NewRotation.Yaw += DeltaRotation;
	SetActorLocationAndRotation(Location, NewRotation);
}

void AFloatingBox::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BrokenSpark, GetActorLocation(), GetActorRotation(), 1.0f);
	}
}

//和ApplyDamage是一对，打击物调用ApplyDamage施加伤害，被打物调用Take Damage承受伤害
//float AFloatingBox::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
//{
//	return 0.0f;// 返回伤害值
//}




