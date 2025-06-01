// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Rules.h"
#include "Components/ActorComponent.h"
#include "SmellController.generated.h"


UCLASS(Blueprintable)
class USmell : public UObject
{
	GENERATED_BODY()
	
	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int color; // blue, yellow, red, green

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int shape; // cylinder, cone, sphere, cube

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int emission; // 0, 1, 2, 3

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int food; // cheese, meat, eggs

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool poisonous;

	void Init(int newColor, int newShape, int newEmission, int newFood, bool newPoisonous) {
		this->color = newColor;
		this->shape = newShape;
		this->emission = newEmission;
		this->food = newFood;
		this->poisonous = newPoisonous;
	}

	UFUNCTION(BlueprintCallable)
	bool getPoisonous() const {
		return poisonous;
	}

	UFUNCTION(BlueprintCallable)
	int getColor() const {
		return color;
	}

	UFUNCTION(BlueprintCallable)
	int getShape() const {
		return shape;
	}

	UFUNCTION(BlueprintCallable)
	int getEmission() const {
		return emission;
	}

	UFUNCTION(BlueprintCallable)
	int getFood() const {
		return food;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KLAGENFURTJAM_API USmellController : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USmellController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int numberOfRules = 2;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<URule*> rules;

	UFUNCTION(BlueprintCallable)
	void setRules(TArray<URule*> newRules, int newNumberOfRules)
	{
		numberOfRules = newNumberOfRules;
		for (int i = 0; i < numberOfRules; i++)
		{
			rules.Add(newRules[i]);
		}
	}

	UFUNCTION(BlueprintCallable)
	FString getRulesString() {
		FString result = "Types of poisonous smells:\n\n";
        
		for (int i = 0; i < numberOfRules; i++) {
			result += FString(std::to_string(i+1).c_str());
			result += ". ";
			result += FString(rules[i]->toString().c_str()) + '\n';
		}

		return result;
	}
	
	UFUNCTION(BlueprintCallable)
	USmell* getNext() {
        USmell* smell = NewObject<USmell>(this);
		smell -> Init(-1, -1, -1, -1, false);

        int rPoison = std::rand() % 3;

        bool poisonous = (rPoison == 1);

        smell->poisonous = poisonous;

        if (poisonous) {
            int ruleToComplyNum = std::rand() % numberOfRules;
            URule* ruleToComply = rules[ruleToComplyNum];
            for (int i = 0; i < numberOfRules; i++) {
                switch (ruleToComply->condTypes[i])
                {
                    case 0:
                        smell->color = ruleToComply->conditions[i];
                        break;
                    case 1:
                        smell->shape = ruleToComply->conditions[i];
                        break;
                    case 2:
                        smell->emission = ruleToComply->conditions[i];
                        break;
                    default:
                        break;
                }
            }
            if (smell->color == -1) {
                smell->color = std::rand() % 4;
            }
            if (smell->shape == -1) {
                smell->shape = std::rand() % 4;
            }
            if (smell->emission == -1) {
                smell->emission = std::rand() % 4;
            }
            //smell.food to be added!
        } else {
            bool ok = false;
            while (!ok) {
                smell->color = std::rand() % 4;
                smell->shape = std::rand() % 4;
                smell->emission = std::rand() % 4;

                ok = true;
                for (int i = 0; i < numberOfRules; i++) {
                    for (int j = 0; j < 2; j++) {
                        if (rules[i]->condTypes[j] == 0 && rules[i]->conditions[j] == smell->color) {
                            ok = false;
                        }
                        if (rules[i]->condTypes[j] == 1 && rules[i]->conditions[j] == smell->shape) {
                            ok = false;
                        }
                        if (rules[i]->condTypes[j] == 2 && rules[i]->conditions[j] == smell->emission) {
                            ok = false;
                        }
                    }
                }
            }
        }
		
        return smell;
    }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
