#pragma once
#include "pch.h"

#include "Figure.h"

class Circle : public Figure
{
public:
	explicit Circle(int size, int offsetX, int offsetY);

	void draw() override;
	bool isInnerPoint(int x, int y) override;
};

