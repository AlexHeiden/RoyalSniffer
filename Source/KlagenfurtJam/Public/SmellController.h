// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rules.h"
#include "Components/ActorComponent.h"
#include "SmellController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KLAGENFURTJAM_API USmellController : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USmellController();
	
	int color; // blue, yellow, red, green
	int shape; // cylinder, cone, sphere, cube
	int emission; // 0, 1, 2, 3
	int food; // cheese, meat, veggies
	bool poisonous;
	Rule* rules;

	bool getPoisonous() const {
		return poisonous;
	}

	int getColor() const {
		return color;
	}

	int getShape() const {
		return shape;
	}

	int getEmission() const {
		return emission;
	}

	int getFood() const {
		return food;
	}



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
