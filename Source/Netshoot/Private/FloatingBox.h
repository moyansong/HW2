// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingBox.generated.h"

class USphereComponent;

UCLASS()
class NETSHOOT_API AFloatingBox : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFloatingBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	/*UFUNCTION()
		float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);*/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite);
		UStaticMeshComponent* Mesh;

	// 球体碰撞组件
	UPROPERTY(VisibleAnywhere)
		USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, Category = "Emitter")
		UParticleSystem* BrokenSpark;

	float LifeSpan;

};

