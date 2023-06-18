#pragma once

#include <string>

class BitmapImage;

class Filter
{
public:
	virtual std::string getName() = 0;
	virtual BitmapImage process(const BitmapImage& im) = 0;
};

class NegativeFilter : public Filter
{
	std::string getName() override;
	BitmapImage process(const BitmapImage& im) override;
};

class GaussianFilter : public Filter
{
	std::string getName() override;
	BitmapImage process(const BitmapImage& im) override;
};

class ZoomInFilter : public Filter
{
	std::string getName() override;
	BitmapImage process(const BitmapImage& im) override;
};

class ZoomOutFilter : public Filter
{
	std::string getName() override;
	BitmapImage process(const BitmapImage& im) override;
};

class HighPassFilter : public Filter
{
	std::string getName() override;
	BitmapImage process(const BitmapImage& im) override;
};

class SharpenFilter : public Filter
{
	std::string getName() override;
	BitmapImage process(const BitmapImage& im) override;
};
