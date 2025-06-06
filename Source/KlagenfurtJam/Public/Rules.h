// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Rules.generated.h"

UCLASS(Blueprintable)
class URule : public UObject{
    GENERATED_BODY()
    
    public:
        int condTypes[2];
        int conditions[2];

        void Init(int inputCondTypes[2], int inputConditions[2])
        {
            for (int i = 0; i < 2; ++i)
            {
                condTypes[i] = inputCondTypes[i];
                conditions[i] = inputConditions[i];
            }
        }

        std::string toString() const {
            std::string result = "";
            bool hasFirst = false;
            for (int i = 0; i < 2; i++) {
            if (condTypes[i] == -1) continue;

            if (hasFirst) result += "and ";

            switch (condTypes[i]) {
                case 0:
                    switch (conditions[i]) {
                        case 0: result += "Blue "; break;
                        case 1: result += "Yellow "; break;
                        case 2: result += "Red "; break;
                        case 3: result += "Green "; break;
                    }
                    //result += "Color ";
                    break;
                case 2:
                    switch (conditions[i]) {
                        case 0: result += "Fast Concentrated "; break;
                        case 1: result += "Fast Spread "; break;
                        case 2: result += "Slow Concentrated "; break;
                        case 3: result += "Slow Spread "; break;
                    }
                
                    break;
                case 1:
                    switch (conditions[i]) {
                        case 0: result += "Strings "; break;
                        case 1: result += "Cones "; break;
                        case 2: result += "Sphere "; break;
                        case 3: result += "Cubes "; break;
                    }
                    //result += "Shape ";
                    break;
                case 3:
                    result += "Food Type ";
                    break;
            }

            hasFirst = true;
        }

            return result;
        }
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KLAGENFURTJAM_API URules : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URules();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int numberOfRules = 2;
    
    TArray<URule*> rules;

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
    void NextSetOfRules()
    {
        rules.Empty();
        std::srand(std::time(nullptr));
        int lastRuleType = -1;
        for (int i = 0; i < numberOfRules; i++) {
            //bool oneOrTwoRules = ((std::rand() % 5) == 1);
            //if (oneOrTwoRules)
            //{
            int type;
            while (true)
            {
                type = std::rand() % 3;
                if (type != lastRuleType)
                {
                    lastRuleType = type;
                    break;
                }
            }
            
            int condition = std::rand() % 4;

            int condTypeArr[2] = {type, -1};
            int conditionArr[2] = {condition, -1};

            URule* newRule = NewObject<URule>(this);
            newRule -> Init(condTypeArr, conditionArr);
            rules.Add(newRule);
            //}
            // } else {
            //     int typeOne = std::rand() % 3;
            //     int conditionOne = std::rand() % 4;
            //
            //     int typeTwo = std::rand() % 3;
            //     int conditionTwo = std::rand() % 4;
            //
            //     while (typeTwo == typeOne) {
            //         typeTwo = std::rand() % 3;
            //     }
            //
            //     int condTypeArr[2] = {typeOne, typeTwo};
            //     int conditionArr[2] = {conditionOne, conditionTwo};
            //
            //     URule* newRule = NewObject<URule>(this);
            //     newRule -> Init(condTypeArr, conditionArr);
            //     rules.Add(newRule);
            // }
        }
    };

    UFUNCTION(BlueprintCallable)
    TArray<URule*> getRules() {
        return rules;
    }
    
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
