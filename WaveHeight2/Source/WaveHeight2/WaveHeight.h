// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveHeight.generated.h"

USTRUCT(BlueprintType)
struct FEncapsule : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> arr = {1.0,2.1};
};

USTRUCT(BlueprintType)
struct FWaveFrequenciesDataStruct : public FTableRowBase
{
    GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FEncapsule> arr2;
};


UCLASS()
class WAVEHEIGHT2_API AWaveHeight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveHeight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
