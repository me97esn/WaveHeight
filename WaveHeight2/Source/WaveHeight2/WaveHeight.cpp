// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveHeight.h"

// Sets default values
AWaveHeight::AWaveHeight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWaveHeight::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("----------------------------------------::: Hello, World!"));
	
	
}

// Called every frame
void AWaveHeight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

