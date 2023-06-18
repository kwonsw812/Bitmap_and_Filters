#include "BitmapImage.h"

#include <iostream>
#include <fstream>

using namespace std;

bool BitmapImage::loadPGM(const string& path)
{
	ifstream is(path.c_str());
	if (!is.is_open())
	{
		return false;
	}

	int header_step = 0;
	int w = 0, h = 0, max_v = 0;

	while (!is.eof())
	{
		char first_char;
		is >> first_char;

		if (first_char == '#')
		{
			string str;
			getline(is, str, '\n');
		}
		else
		{
			is.putback(first_char);

			switch (header_step) {
			case 0:
			{
				string magic_number;
				is >> magic_number;

				if (magic_number != "P2")
				{
					return false;
				}
				header_step = 1;
			}
			break;

			case 1:
			{
				is >> w >> h;
				if (w <= 0 || h <= 0)
				{
					return false;
				}
				header_step = 2;
			}
			break;

			case 2:
			{
				is >> max_v;
				if (max_v <= 0)
				{
					return false;
				}
				header_step = 3;
			}
			break;
			}
		}

		if (header_step == 3)
		{
			break;
		}
	}

	if (header_step != 3)
	{
		return false;
	}

	delete[] this->bitmap;

	this->width = w;
	this->height = h;
	this->bitmap = new double[w * h];

	for (int y = 0; y < this->height; y++)
	{
		for (int x = 0; x < this->width; x++)
		{
			if (is.eof())
			{
				return false;
			}
			else
			{
				int v;
				is >> v;

				if (v > max_v || v < 0)
				{
					return false;
				}

				double pixel = (double)v / (double)max_v;
				setPixel(x, y, pixel);
			}
		}
	}

	return true;
}

bool BitmapImage::savePGM(const string& path) const
{
	ofstream os(path.c_str());
	if (!os.is_open())
	{
		return false;
	}

	if (this->width <= 0 || this->height <= 0 || this->bitmap == nullptr)
	{
		return false;
	}

	int max_v = 255;

	os << "P2" << endl;
	os << this->width << " " << this->height << endl;
	os << max_v << endl;

	for (int y = 0; y < this->height; y++)
	{
		for (int x = 0; x < this->width; x++)
		{
			double pixel = getPixel(x, y);
			int v = (int)(pixel * max_v);

			os << v << " ";
		}
		os << endl;
	}

	return true;
}

BitmapImage& BitmapImage::operator=(const BitmapImage& im)
{
	if (this == &im) return *this;

	if ((width * height) != (im.width * im.height)) {
		delete[] bitmap;
		bitmap = new double[im.width * im.height];
	}

	width = im.width;
	height = im.height;

	for (int i = 0; i < im.width * im.height; i++) {
		bitmap[i] = im.bitmap[i];
	}
	return *this;
}

BitmapImage& BitmapImage::operator=(BitmapImage&& im)
{
	delete[] bitmap;
	width = im.width;
	height = im.height;
	bitmap = im.bitmap;

	im.width = 0;
	im.height = 0;
	im.bitmap = nullptr;

	return *this;
}

void BitmapImage::setPixel(int x, int y, double v)
{
	if (x >= width || y >= height) return;
	else bitmap[y*width + x] = v;
}

double BitmapImage::getPixel(int x, int y) const
{
	if (x >= width || y >= height) return 0.0;
	else return bitmap[y * width + x];
}

void BitmapImage::clear()
{
	for (int i = 0; i < width * height; i++) {
		bitmap[i] = 0.0;
	}
}