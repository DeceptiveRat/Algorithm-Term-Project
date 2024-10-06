#pragma once

// 구조
// structures
struct ITEM
{
	ITEM();
    ~ITEM();

    // x = 폭, y = 너비, z = 높이
    // x = width, y = length, z = height
    int x, y, z, weight;
	
	int bagNumber, xLocation, yLocation, zLocation;
};

struct BAG
{
	BAG();
    ~BAG();

    int x, y, z, maxCapacity;
};

// 함수
// functions
void getInput();
