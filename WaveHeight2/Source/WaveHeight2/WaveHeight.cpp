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

double AWaveHeight::calculateWaveHeight(
    int x, 
    int y, 
    int frame_number) {
    
    FWaveFrequenciesDataStruct* Row = waveData->FindRow<FWaveFrequenciesDataStruct>("Frame_"+frame_number, "");
    FWaveFrequenciesMetadataStruct* MetadataRow = waveMetadata->FindRow<FWaveFrequenciesMetadataStruct>("Metadata", "");

    int lenX = MetadataRow->len_x;
    int lenY = MetadataRow->len_y;
    int numberOfRowsToIncludeTop = MetadataRow->number_of_rows_to_include;
    int numberOfRowsToIncludeBottom = MetadataRow->number_of_rows_to_include;
    int numberOfFrequenciesToInclude = MetadataRow->number_of_frequencies_to_include;

	if(!Row || ! MetadataRow)
	{
        UE_LOG(LogTemp, Warning, TEXT("Could not find any wave data or metadata for frame: %i"), frame_number);
        return 0.0;
    }
    const TArray<FEncapsule>& fourierCoefficients = Row->f;


    Complex result(0.0, 0.0);
    int number_to_skip = lenY - numberOfFrequenciesToInclude * 2;
    int numberOfRowsToSkip = lenX - numberOfRowsToIncludeBottom * 2;
    int numRows = fourierCoefficients.Num();
    int numCols = fourierCoefficients[0].arr.Num();

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

