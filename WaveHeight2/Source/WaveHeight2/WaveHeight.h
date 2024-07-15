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
struct FWaveFrequenciesMetadataStruct : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float step_size;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int number_of_frequencies_to_include;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int number_of_rows_to_include;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int len_x;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int len_y;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int start_trace_y;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int start_trace_x;
};

USTRUCT(BlueprintType)
struct FWaveFrequenciesDataStruct : public FTableRowBase
{
    GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FEncapsule> f;
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
