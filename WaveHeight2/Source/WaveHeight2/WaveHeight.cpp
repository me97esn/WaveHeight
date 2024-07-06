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

double ifft2(int x, int y, const ComplexMatrix& fourierCoefficients, int lenX, int lenY, int numberOfFrequenciesToInclude = 30, int numberOfRowsToIncludeBottom = 2, int numberOfRowsToIncludeTop = 10) {
    Complex result(0.0, 0.0);
    int number_to_skip = lenY - numberOfFrequenciesToInclude * 2;
    int numberOfRowsToSkip = lenX - numberOfRowsToIncludeBottom * 2;

    int numRows = fourierCoefficients.size();
    int numCols = fourierCoefficients[0].size();

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
            Complex fourierCoefficient = fourierCoefficients[m][n];
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
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWaveHeight::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("----------------------------------------::: Hello, World!"));

	/***
	 * Call the ifft2 with example data
	 */
	// Example usage
    ComplexMatrix fourierCoefficients = {
        {Complex(1, 1), Complex(1, -1)},
        {Complex(-1, 1), Complex(-1, -1)}
    };

    int lenX = 4;
    int lenY = 4;

    double result2 = ifft2(1, 1, fourierCoefficients, lenX, lenY);
	UE_LOG(LogTemp, Warning, TEXT("The result from the ifft2 function is: %f"), result2);
	/** */

	// Get a row from the data table
	 FWaveFrequenciesDataStruct* Item = waveData->FindRow<FWaveFrequenciesDataStruct>("Frame_752", "");
	 if(Item){
		float real = Item->f[0].arr[0].re;
	 	UE_LOG(LogTemp, Warning, TEXT("The 0,0 real float value from the data table is: %f"), real);
	 }
}

// Called every frame
void AWaveHeight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

