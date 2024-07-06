// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveHeight.generated.h"

USTRUCT(BlueprintType)
struct FComplex : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float re;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float im;

};


USTRUCT(BlueprintType)
struct FEncapsule : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FComplex> arr;
};

USTRUCT(BlueprintType)
struct FWaveFrequenciesDataStruct : public FTableRowBase
{
    GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FEncapsule> f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float step;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int num_of_f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int num_of_r;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int l_x;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int l_y;
};


UCLASS()
class WAVEHEIGHT2_API AWaveHeight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveHeight();
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  meta=(RowType ="FWaveFrequenciesDataStruct"))
	class UDataTable* waveData;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
