// This sample code reads in image data from a RAW image file and 
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <array>
#include <unordered_map>

using namespace std;

std::unordered_map<int, int> counter;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int Size = 256;
	
	// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
		return 0;
	}
	
	// Check if image is grayscale or color
	if (argc < 4){
		BytesPerPixel = 1; // default is grey image
	} 
	else {
		BytesPerPixel = atoi(argv[3]);
		// Check if size is specified
		if (argc >= 5){
			Size = atoi(argv[4]);
		}
	}
	
	// Allocate image data array
	unsigned char Imagedata[Size][Size][BytesPerPixel];
	unsigned char out_image[Size][Size][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	// if (!(file=fopen(argv[1],"rb"))) {
	// 	cout << "Cannot open file: " << argv[1] <<endl;
	// 	exit(1);
	// }
	// fread(Imagedata, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
	// fclose(file);

    // std::ofstream new_file;
    // new_file.open("histogram.csv"); 

    // for (int x = 0; x < Size; x++){
    //     new_file << int(Imagedata[x][0][0]); 
	// 	for (int y = 0; y < Size; y++){
    //             new_file << "," << (int)Imagedata[x][y][0];
    //     }
    //     new_file << endl;
    // }

    // new_file.close();

	cout << ", "; 

    int pixel_count[] = {1, 16, 744, 200, 154, 145, 132, 154, 129, 111, 129, 1354, 121, 115, 100, 91, 95, 73, 87, 1089, 92, 81, 73, 76, 61, 48, 47, 1484, 45, 37, 33, 26, 31, 23, 14, 1664, 23, 30, 22, 23, 18, 22, 15, 1677, 20, 24, 13, 19, 23, 13, 2091, 27, 16, 28, 24, 22, 25, 2543, 28, 28, 22, 26, 27, 33, 2078, 43, 37, 37, 30, 26, 24, 1110, 30, 25, 22, 36, 30, 23, 114, 625, 26, 31, 33, 40, 42, 53, 446, 38, 41, 53, 45, 50, 207, 50, 35, 47, 53, 35, 378, 48, 34, 26, 21, 18, 13, 428, 8, 7, 1, 4, 2, 245, 1, 610, 355, 742, 602, 84, 1297, 993, 2602, 1162, 1512, 2431, 929, 744, 1476, 615, 137, 577, 491, 852, 302, 271, 485, 472, 844, 435, 417, 262, 403, 387, 356, 351, 333, 351, 638, 322, 310, 350, 406, 325, 334, 357, 377, 401, 400, 449, 433, 471, 479, 694, 504, 525, 505, 511, 507, 518, 480, 554, 512, 942, 441, 471, 440, 481, 455, 446, 398, 414, 330, 905, 332, 338, 318, 291, 271, 242, 236, 193}; 
	// int pixel_values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 84, 85, 86, 87, 88, 89, 91, 92, 93, 94, 95, 97, 98, 99, 100, 102, 103, 104, 105, 107, 108, 109, 111, 112, 113, 115, 116, 117, 119, 120, 121, 123, 124, 126, 127, 128, 130, 131, 133, 134, 136, 137, 139, 140, 142, 143, 145, 146, 148, 149, 151, 152, 154, 155, 157, 158, 160, 162, 163, 165, 166, 168, 170, 171, 173, 175, 176, 178, 180, 181, 183, 185, 186, 188, 190, 192, 193, 195, 197, 199, 200, 202, 204, 206, 207, 209, 211, 213, 215, 217, 218, 220, 222, 224, 226, 228, 230, 232, 233, 235, 237, 239, 241, 243, 245, 247, 249, 255};
	// int adjusted_pixel_values[256];
	// std::array<int, 256> adjusted_pixel_count;
	// adjusted_pixel_count = {1,16,114,84,137,262,406,694,942,905,744,1354,1089,1484,1664,1677,2091,2543,2078,1110,625,446,207,378,428,245,610,355,742,602,1297,993,2602,1162,1512,2431,929,744,1476,615,577,491,852,302,271,485,472,844,435,417,403,387,356,351,333,351,638,322,310,350,325,334,357,377,401,400,449,433,471,479,504,525,0,505,511,507,518,480,554,512,441,471,440,0,481,455,446,398,414,330,0,332,338,318,291,271,0,242,236,193,200,0,154,145,132,154,0,129,111,129,0,121,115,100,0,91,95,73,0,87,92,81,0,73,76,0,61,48,47,0,45,37,0,33,26,0,31,23,0,14,23,0,30,22,0,23,18,0,22,15,0,20,24,0,13,19,0,23,13,0,27,0,16,28,0,24,22,0,25,0,28,28,0,22,0,26,27,0,33,0,43,37,0,37,0,30,26,0,24,0,30,0,25,22,0,36,0,30,0,23,26,0,31,0,33,0,40,42,0,53,0,38,0,41,0,53,0,45,50,0,50,0,35,0,47,0,53,0,35,0,48,0,34,26,0,21,0,18,0,13,0,8,0,7,0,1,0,4,0,2,0,0,0,0,0,1};

	// for (int i = 0; i < Size; i++){
	// 	adjusted_pixel_values[i] = i; 
	// }

	for (int i = 0; i < 256; i++){
		for (int j = 0; j < 256; j++){
			counter[pixel_count[i]]++;
		}
	}

	cout << ", "; 

	// for (auto &e:counter){
    // 	cout << e.first <<" : "<<e.second<< "-> "<< e.first/e.second << endl; 
	// }

	// double normalized_count[256];
	// double cumulative_probp[256];
	// double sum = 0.0;
	// double total_pixels = 65536.0;


	// for (int i = 0; i < 256; i++){
	// 	normalized_count[i] = adjusted_pixel_count[i] / total_pixels;
	// 	sum = sum + normalized_count[i];
	// 	cumulative_probp[i] = round(sum * 255);
	// }

	// total_pixels = round(total_pixels / 256);

	// for (int i = 0; i < Size; i++){
	// 	for (int j = 0; j < Size; j++){
	// 		out_image[i][j][0] = cumulative_probp[(int)Imagedata[i][j][0]];
	// 	}
	// 	cout << adjusted_pixel_values[i] << ", ";
	// }


	// int buckets[]; 
	// if intensity I < 256, belong in one bucket, if I > 256, divide I by 256 and round up, then randomize that many next buckets. 

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

	// Write image data (filename specified by second argument) from image data matrix

	// if (!(file=fopen(argv[2],"wb"))) {
	// 	cout << "Cannot open file: " << argv[2] << endl;
	// 	exit(1);
	// }
	// fwrite(out_image, sizeof(unsigned char), Size*Size*BytesPerPixel, file);
	// fclose(file);

	return 0;
}

// Questions to ask: 
// 6. If I have to count in C++ instead of excel, can I use maps?
// 8. if intensity I < 256, belong in one bucket, if I > 256, divide I by 256 and round up, then randomize that many next buckets.
// 9. This is result of 1a, is this correct? and why do those artifacts appear? 