

//#pragma warning(disable:4996)
#include <assert.h>
#include <fstream>
#include <iostream>
#include "imageloader.h"

using namespace std;
  bool color=true;
Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h) {
	
}

Image::~Image() {
	delete[] pixels;
}

namespace {
	
	int toInt(const char* bytes) {
		return (int)(((unsigned char)bytes[3] << 24) |
					 ((unsigned char)bytes[2] << 16) |
					 ((unsigned char)bytes[1] << 8) |
					 (unsigned char)bytes[0]);
	}
	
	//Converts a two-character array to a short, using little-endian form
	short toShort(const char* bytes) {
		return (short)(((unsigned char)bytes[1] << 8) |
					   (unsigned char)bytes[0]);
	}
	
	//Reads the next four bytes as an integer, using little-endian form
	int readInt(ifstream &input) {
		char buffer[4];
		input.read(buffer, 4);
		return toInt(buffer);
	}
	
	//Reads the next two bytes as a short, using little-endian form
	short readShort(ifstream &input) {
		char buffer[2];
		input.read(buffer, 2);
		return toShort(buffer);
	}
	
	//Just like auto_ptr, but for arrays
	template<class T>
	class auto_array {
		private:
			T* array;
			mutable bool isReleased;
		public:
			explicit auto_array(T* array_ = NULL) :
				array(array_), isReleased(false) {
			}
			
			auto_array(const auto_array<T> &aarray) {
				array = aarray.array;
				isReleased = aarray.isReleased;
				aarray.isReleased = true;
			}
			
			~auto_array() {
				if (!isReleased && array != NULL) {
					delete[] array;
				}
			}
			
			T* get() const {
				return array;
			}
			
			T &operator*() const {
				return *array;
			}
			
			void operator=(const auto_array<T> &aarray) {
				if (!isReleased && array != NULL) {
					delete[] array;
				}
				array = aarray.array;
				isReleased = aarray.isReleased;
				aarray.isReleased = true;
			}
			
			T* operator->() const {
				return array;
			}
			
			T* release() {
				isReleased = true;
				return array;
			}
			
			void reset(T* array_ = NULL) {
				if (!isReleased && array != NULL) {
					delete[] array;
				}
				array = array_;
			}
			
			T* operator+(int i) {
				return array + i;
			}
			
			T &operator[](int i) {
				return array[i];
			}
	};
}

Image* loadBMP(string filename,bool col,int br,int contrast) {
	color=col;
	ifstream input;
	input.open(filename, ifstream::binary);
	assert(!input.fail() || !"Could not find file");
	char buffer[2];
	input.read(buffer, 2);
	assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
	input.ignore(8);
	int dataOffset = readInt(input);
	
	//Read the header
	int headerSize = readInt(input);
	int width;
	int height;
	switch(headerSize) {
		case 40:
			//V3
			width = readInt(input);
			height = readInt(input);
			input.ignore(2);
			assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
			assert(readShort(input) == 0 || !"Image is compressed");
			break;
		case 12:
			//OS/2 V1
			width = readShort(input);
			height = readShort(input);
			input.ignore(2);
			assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
			break;
		case 64:
			//OS/2 V2
			assert(!"Can't load OS/2 V2 bitmaps");
			break;
		case 108:
			//Windows V4
			assert(!"Can't load Windows V4 bitmaps");
			break;
		case 124:
			//Windows V5
			assert(!"Can't load Windows V5 bitmaps");
			break;
		default:
			assert(!"Unknown bitmap format");
	}
	
	//Read the data
	int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
	int size = bytesPerRow * height;
	auto_array<char> pixels(new char[size]);
	input.seekg(dataOffset, ios_base::beg);
	input.read(pixels.get(), size);
	
	//Get the data into the right format
	auto_array<char> pixels2(new char[width * height * 3]);
	float val=.3;
	for(int y = 0; y < height; y++) 
	{
		for(int x = 0; x < width; x++) 
		{
			float f =(259*((float)contrast+255))/(255*(float)(259-contrast));
			//if(val==.3) {cout<<f<<endl; val=0;}
				if(col){
				pixels2[3 * (width * y + x) + 0] =
					f*(pixels[bytesPerRow * y + 3 * x + (2 - 0)]-128)+128+br;
				pixels2[3 * (width * y + x) + 1] =
					f*(pixels[bytesPerRow * y + 3 * x + (2 - 1)]-128)+128+br;
				pixels2[3 * (width * y + x) + 2] =
					f*(pixels[bytesPerRow * y + 3 * x + (2 - 2)]-128)+128+br;

				

				}
				else
					{ 
					pixels2[3 * (width * y + x) + 0]=
					f*(pixels[bytesPerRow * y + 3 * x + (2 - 0)]*0.2989-128)+128 +
					f*(pixels[bytesPerRow * y + 3 * x + (2 - 1)]* 0.5870-128)+128+
					f*(pixels[bytesPerRow * y + 3 * x + (2 - 2)]*0.1140-128)+128+br;

					pixels2[3 * (width * y + x) + 1]=
					f*(pixels[bytesPerRow * y + 3 * x + (2 - 0)]*0.2989-128)+128 +
					f*(pixels[bytesPerRow * y + 3 * x + (2 - 1)]* 0.5870-128)+128+
					f*(pixels[bytesPerRow * y + 3 * x + (2 - 2)]*0.1140-128)+128+br;

					pixels2[3 * (width * y + x) + 2]=
					f*(pixels[bytesPerRow * y + 3 * x + (2 - 0)]*0.2989-128)+128 +
					f*(pixels[bytesPerRow * y + 3 * x + (2 - 1)]* 0.5870-128)+128+
					f*(pixels[bytesPerRow * y + 3 * x + (2 - 2)]*0.1140-128)+128+br;
				}
				/*
				if((pixels2[3 * (width * y + x) + 0]+256)<0) pixels2[3 * (width * y + x) + 0]=-256;
				if((pixels2[3 * (width * y + x) + 1]+256)<0) pixels2[3 * (width * y + x) + 1]=-256;
				if((pixels2[3 * (width * y + x) + 2]+256)<0) pixels2[3 * (width * y + x) + 2]=-256;
				
				if((pixels2[3 * (width * y + x) + 0])+256>255) pixels2[3 * (width * y + x) + 0]=0;
				if((pixels2[3 * (width * y + x) + 1])+256>255) pixels2[3 * (width * y + x) + 1]=0;
				if((pixels2[3 * (width * y + x) + 2])+256>255) pixels2[3 * (width * y + x) + 2]=0;
		
				if(x<2&&y<2){cout<< (int)pixels2[3 * (width * y + x) + 0]+256<<" ";
				cout<< (int)pixels2[3 * (width * y + x) + 1]+256<<" ";
				cout<<(int)pixels2[3 * (width * y + x) + 2]+256<<endl;
				}*/
		}
	}
	
	input.close();
	return new Image(pixels2.release(), width, height);
}









