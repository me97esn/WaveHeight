// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveHeight.h"
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

using Complex = complex<double>;
using ComplexMatrix = vector<vector<Complex>>;

tuple<float,float> AWaveHeight::convertCoordToSampleIndex(float x, float y){
    FWaveFrequenciesMetadataStruct* MetadataRow = waveMetadata->FindRow<FWaveFrequenciesMetadataStruct>("Metadata", "");
    pair<float, float> result;
    if(!MetadataRow)
	{
        UE_LOG(LogTemp, Warning, TEXT("Could not find metadata "));
        // return pair;
    }
    
    result.first = (x - MetadataRow->start_trace_x)/MetadataRow->step_size;
    result.second = (y - MetadataRow->start_trace_y)/MetadataRow->step_size;
    return result;
}

double AWaveHeight::waveHeight(float x, 
    float y, 
    FName rowName){
        UE_LOG(LogTemp, Log, TEXT("Calculating wave height for coord: %f, %f"), x, y);
        auto sampleIndexes = convertCoordToSampleIndex( x,y );
        return calculateWaveHeight(get<0>(sampleIndexes), get<1>(sampleIndexes), rowName);
    }

double AWaveHeight::calculateWaveHeight(
    float sampleNumberX, 
    float sampleNumberY, 
    FName rowName) {
    FWaveFrequenciesDataStruct* Row = waveData->FindRow<FWaveFrequenciesDataStruct>(rowName, "");
    FWaveFrequenciesMetadataStruct* MetadataRow = waveMetadata->FindRow<FWaveFrequenciesMetadataStruct>("Metadata", "");

    if(!Row || ! MetadataRow)
	{
        UE_LOG(LogTemp, Warning, TEXT("Could not find any wave data or metadata "));
        return 0.0;
    }
    UE_LOG(LogTemp, Log, TEXT("Calculating wave height for sample: %f, %f"), sampleNumberX, sampleNumberY);
    int x = sampleNumberX;
    int y = sampleNumberY;
    int lenX = MetadataRow->len_x;
    int lenY = MetadataRow->len_y;
    int numberOfRowsToIncludeTop = MetadataRow->number_of_rows_to_include;
    int numberOfRowsToIncludeBottom = MetadataRow->number_of_rows_to_include;
    int numberOfFrequenciesToInclude = MetadataRow->number_of_frequencies_to_include;

    // UE_LOG(LogTemp, Warning, TEXT("lenX: %i"), lenX);
    // UE_LOG(LogTemp, Warning, TEXT("lenY: %i"), lenY);
    // UE_LOG(LogTemp, Warning, TEXT("numberOfFrequenciesToInclude: %i"), numberOfFrequenciesToInclude);
    // UE_LOG(LogTemp, Warning, TEXT("numberOfFrequenciesToInclude: %i"), numberOfRowsToIncludeBottom);
    // UE_LOG(LogTemp, Warning, TEXT("numberOfRowsToIncludeTop: %i"), numberOfRowsToIncludeTop);

    const TArray<FEncapsule>& fourierCoefficients = Row->f;

    Complex result(0.0, 0.0);
    int number_to_skip = lenY - numberOfFrequenciesToInclude * 2;
    int numberOfRowsToSkip = lenX - numberOfRowsToIncludeBottom * 2;
    int numRows = fourierCoefficients.Num();
    int numCols = fourierCoefficients[0].arr.Num();
    // UE_LOG(LogTemp, Warning, TEXT("numOfRows: %i"), numRows);
    // UE_LOG(LogTemp, Warning, TEXT("numOfCols: %i"), numCols);
    for (int m = 0; m < numRows; ++m) {
        int _m;
        if (m < numberOfRowsToIncludeBottom) {
            _m = m;
        } else if (m >= numRows - numberOfRowsToIncludeTop) {
            _m = m + numberOfRowsToSkip;
        } else {
            continue;
        }

        for (int n = 0; n < numCols; ++n) {
            FComplex fourierCoefficientWrapper = fourierCoefficients[m].arr[n];
			Complex fourierCoefficient(fourierCoefficientWrapper.re, fourierCoefficientWrapper.im);
            if (n < numberOfFrequenciesToInclude) {
                result += fourierCoefficient * exp(Complex(0, 2 * M_PI * (_m * x / double(lenX) + n * y / double(lenY)))) / double(lenX * lenY);
            } else {
                int _n = n + number_to_skip;
                result += fourierCoefficient * exp(Complex(0, 2 * M_PI * (_m * x / double(lenX) + _n * y / double(lenY)))) / double(lenX * lenY);
            }
        }
    }
    return result.real();
}

// Sets default values
AWaveHeight::AWaveHeight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWaveHeight::BeginPlay()
{
	Super::BeginPlay();

	/***
	 * Call the ifft2 with example data
	 */
	// TODO: this should be exposed in a function, callable from blueprint instead of in the beginPlay function.
	// FWaveFrequenciesDataStruct* Row = waveData->FindRow<FWaveFrequenciesDataStruct>("Frame_752", "");
	//  if(Row)
	//  {	
	// 	float height = ifft2(1,1, Row->f,Row->l_x, Row->l_y, Row->num_of_f, Row->num_of_r);
	// 	//float real = Item->f[0].arr[0].re;
	//  	UE_LOG(LogTemp, Warning, TEXT("The 0,0 real float value from the ifft2 of the data table is: %f"), height);
	//  }
}

// Called every frame
void AWaveHeight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

