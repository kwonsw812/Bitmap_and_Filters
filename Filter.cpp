#include "Filter.h"
#include "BitmapImage.h"

std::string NegativeFilter::getName()
{
	return "Negative";
}

BitmapImage NegativeFilter::process(const BitmapImage& im)
{
	BitmapImage negative(im.getWidth(), im.getHeight());

	for (int i = 0; i < im.getHeight(); i++)
	{
		for (int j = 0; j < im.getWidth(); j++)
		{
			negative.setPixel(j, i, 1.0 - im.getPixel(j, i));
		}
	}

	return negative;
}


std::string GaussianFilter::getName()
{
	return "Gaussian";
}

BitmapImage GaussianFilter::process(const BitmapImage& im)
{
	BitmapImage gaussian(im.getWidth(), im.getHeight());

	for (int i = 1; i < im.getHeight()-1; i++){
		for (int j = 1; j < im.getWidth()-1; j++){
			double sum = 0;
			for (int y = i - 1; y <= i + 1; y++) {
				for (int x = j - 1; x <= j + 1; x++) {
					sum += im.getPixel(x, y) / 9.0;
				}
			}
			gaussian.setPixel(j, i, sum);
		}
	}

	return gaussian;
}


std::string ZoomInFilter::getName()
{
	return "Zoom In";
}

BitmapImage ZoomInFilter::process(const BitmapImage& im)
{
	BitmapImage zoomin(im.getWidth(), im.getHeight());

	for (int i = 0; i < im.getHeight(); i++)
	{
		for (int j = 0; j < im.getWidth(); j++)
		{
			zoomin.setPixel(j, i, im.getPixel(j*0.8, i*0.8));
		}
	}

	return zoomin;
}


std::string ZoomOutFilter::getName()
{
	return "Zoom Out";
}

BitmapImage ZoomOutFilter::process(const BitmapImage& im)
{
	BitmapImage zoomout(im.getWidth(), im.getHeight());

	for (int i = 0; i < im.getHeight(); i++)
	{
		for (int j = 0; j < im.getWidth(); j++)
		{
			zoomout.setPixel(j, i, im.getPixel(j*1.25, i*1.25));
		}
	}

	return zoomout;
}


std::string HighPassFilter::getName()
{
	return "HighPass";
}

BitmapImage HighPassFilter::process(const BitmapImage& im)
{
	BitmapImage HighPassFilter(im.getWidth(), im.getHeight());
	BitmapImage gaussian(im.getWidth(), im.getHeight());

	for (int i = 1; i < im.getHeight() - 1; i++) {
		for (int j = 1; j < im.getWidth() - 1; j++) {
			double sum = 0;
			for (int y = i - 1; y <= i + 1; y++) {
				for (int x = j - 1; x <= j + 1; x++) {
					sum += im.getPixel(x, y) / 9.0;
				}
			}
			gaussian.setPixel(j, i, sum);
		}
	}

	for (int i = 0; i < im.getHeight(); i++) {
		for (int j = 0; j < im.getWidth(); j++) {
			HighPassFilter.setPixel(j, i, im.getPixel(j, i) - gaussian.getPixel(j, i));
		}
	}

	return HighPassFilter;
}


std::string SharpenFilter::getName()
{
	return "Sharpen";
}

BitmapImage SharpenFilter::process(const BitmapImage& im)
{
	BitmapImage sharpen(im.getWidth(), im.getHeight());

	for (int i = 1; i < im.getHeight() - 1; i++) {
		for (int j = 1; j < im.getWidth() - 1; j++) {
			double sum = 0;
			short num = 0;
			for (int y = i - 1; y <= i + 1; y++) {
				for (int x = j - 1; x <= j + 1; x++) {
					double diff = 0;
					diff = im.getPixel(j, i) - im.getPixel(x, y);
					sum += diff;
				}
			}
			sharpen.setPixel(j, i, im.getPixel(j, i) + sum);
		}
	}

	return sharpen;
}