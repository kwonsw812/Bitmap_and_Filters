#pragma once

#include <string>

class BitmapImage
{
public:
	BitmapImage(int w, int h) 
		: width{w}, height{h}
	{
		bitmap = new double[w * h];
	}
	BitmapImage(const std::string& path)
		: width{ 0 }, height{ 0 }, bitmap{ nullptr }
	{
		loadPGM(path);
	}
	
	~BitmapImage() { delete[] bitmap; }

	BitmapImage(const BitmapImage& im)
		: width{ im.width }, height{ im.height }, bitmap{ new double[im.width * im.height] }
	{
		for (int i = 0; i < im.width * im.height; i++) {
			bitmap[i] = im.bitmap[i];
		}
	}

	BitmapImage(BitmapImage&& im)
		: width{ im.width }, height{ im.height }, bitmap{ im.bitmap }
	{
		im.width = 0;
		im.height = 0;
		im.bitmap = nullptr;
	}

	BitmapImage& operator=(const BitmapImage& im);
	BitmapImage& operator=(BitmapImage&& im);

	void setPixel(int x, int y, double v);
	double getPixel(int x, int y) const;

	void clear();

	bool loadPGM(const std::string& path);
	bool savePGM(const std::string& path) const;

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }

private:
	int width;
	int height;
	double* bitmap;
};
