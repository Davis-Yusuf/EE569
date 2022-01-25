// This sample code reads in image data from a RAW image file and 
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

double temparr[514][770][3];
const int m = 768;
const int n = 512;
unsigned char output_image[n][m][3];

void filter(int x, int y, int z, double arr1[n + 2][m + 2][3], double arr2[3][3]){
	double sum; 
	sum = (arr1[x - 1][y - 1][z] * arr2[0][0]) + (arr1[x - 1][y][z] * arr2[0][1]) + (arr1[x - 1][y + 1][z] * arr2[0][2]) + (arr1[x][y - 1][z] * arr2[1][0]) + (arr1[x][y + 1][z] * arr2[1][2]) + (arr1[x + 1][y - 1][z] * arr2[2][0]) + (arr1[x + 1][y][z] * arr2[2][1]) + (arr1[x + 1][y + 1][z] * arr2[2][2]);
	// cout << arr1[x - 1][y][z] << ","; 
	// cout << arr2[0][1] << ","; 
	arr1[x][y][z] = sum; 
}


int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int Size_1 = 768;
	int Size_2 = 512;
	
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
			Size_1 = 768;
			Size_2 = 512;
		}
	}
	
	// Allocate image data array
	unsigned char Imagedata[Size_2][Size_1][BytesPerPixel];
	unsigned char NewImagedata[Size_2 + 2][Size_1 + 2][3];


	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), Size_1*Size_2*BytesPerPixel, file);

	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	// 0 for red, 1 for green, 2 for blue
	double blue_red[3][3];
	double br_green[3][3];
	double green_odd_red[3][3];
	double green_odd_blue[3][3];
	double green_even_red[3][3];
	double green_even_blue[3][3];
	
	blue_red[0][0] = 0.25;
	blue_red[0][1] = 0;
	blue_red[0][2] = 0.25;
	blue_red[1][0] = 0;
	blue_red[1][1] = 0;
	blue_red[1][2] = 0;
	blue_red[2][0] = 0.25;
	blue_red[2][1] = 0;
	blue_red[2][2] = 0.25;

	br_green[0][0] = 0;
	br_green[0][1] = 0.25;
	br_green[0][2] = 0;
	br_green[1][0] = 0.25;
	br_green[1][1] = 0;
	br_green[1][2] = 0.25;
	br_green[2][0] = 0;
	br_green[2][1] = 0.25;
	br_green[2][2] = 0;

	green_odd_blue[0][0] = 0;
	green_odd_blue[0][1] = 0.5;
	green_odd_blue[0][2] = 0;
	green_odd_blue[1][0] = 0;
	green_odd_blue[1][1] = 0;
	green_odd_blue[1][2] = 0;
	green_odd_blue[2][0] = 0;
	green_odd_blue[2][1] = 0.5;
	green_odd_blue[2][2] = 0;

	green_odd_red[0][0] = 0;
	green_odd_red[0][1] = 0;
	green_odd_red[0][2] = 0;
	green_odd_red[1][0] = 0.5;
	green_odd_red[1][1] = 0;
	green_odd_red[1][2] = 0.5;
	green_odd_red[2][0] = 0;
	green_odd_red[2][1] = 0;
	green_odd_red[2][2] = 0;

	green_even_red[0][0] = 0;
	green_even_red[0][1] = 0.5;
	green_even_red[0][2] = 0;
	green_even_red[1][0] = 0;
	green_even_red[1][1] = 0;
	green_even_red[1][2] = 0;
	green_even_red[2][0] = 0;
	green_even_red[2][1] = 0.5;
	green_even_red[2][2] = 0;

	green_even_blue[0][0] = 0;
	green_even_blue[0][1] = 0;
	green_even_blue[0][2] = 0;
	green_even_blue[1][0] = 0.5;
	green_even_blue[1][1] = 0;
	green_even_blue[1][2] = 0.5;
	green_even_blue[2][0] = 0;
	green_even_blue[2][1] = 0;
	green_even_blue[2][2] = 0;

	NewImagedata[0][0][1] = Imagedata[1][1][0];   //TOP LEFT CORNER
	NewImagedata[0][Size_1 + 1][2] = Imagedata[1][766][0];  //TOP right CORNER
	NewImagedata[Size_2 + 1][0][0] = Imagedata[510][1][0];  //BOTTOM LEFT CORNER
	NewImagedata[Size_2 + 1][Size_1 + 1][1] = Imagedata[510][766][0];  //BOTTOM RIGHT CORNER

	for (int i = 1; i < Size_2 + 1; i++){					//Horizontal Padding
		if ((i % 2) == 0){
			NewImagedata[i][0][1] = Imagedata[i - 1][1][0];
			NewImagedata[i][769][2] = Imagedata[i - 1][766][0];
		}
		else{
			NewImagedata[i][0][0] = Imagedata[i - 1][1][0];
			NewImagedata[i][769][1] = Imagedata[i - 1][766][0];
		}
	}

	for (int i = 1; i < Size_1 + 1; i++){					//Vertical Padding
		if ((i % 2) == 0){
			NewImagedata[0][i][1] = Imagedata[1][i - 1][0];
			NewImagedata[513][i][0] = Imagedata[510][i - 1][0];
		}
		else{
			NewImagedata[0][i][2] = Imagedata[1][i - 1][0];
			NewImagedata[513][i][1] = Imagedata[510][i - 1][0];
		}
	}

	for (int ii = 1; ii < Size_2 + 1; ii++){
		for (int jj = 1; jj < Size_1 + 1; jj++){
			if (((ii % 2 == 0) && (jj % 2 == 0)) || ((ii % 2 != 0) && (jj % 2 != 0))) { 
				NewImagedata[ii][jj][1] = Imagedata[ii - 1][jj - 1][0];
			}	
			else if ((ii % 2 == 0) && (jj % 2 != 0)) { 
				NewImagedata[ii][jj][2] = Imagedata[ii - 1][jj - 1][0];
			}	
			else if ((ii % 2 != 0) && (jj % 2 == 0)) { 
				NewImagedata[ii][jj][0] = Imagedata[ii - 1][jj - 1][0];
			}	
		}
	}

	for (int x = 0; x < Size_2 + 2; x++){
		for (int y = 0; y < Size_1 + 2; y++){
			for (int z = 0; z < 3; z++){
				temparr[x][y][z] = (double)NewImagedata[x][y][z] / 255.0; 
			}
		}
	}

	for(int xx = 1; xx < Size_2 + 1; xx++){
		for(int yy = 1; yy < Size_1 + 1; yy++){
			if ((xx % 2 == 0) && (yy % 2 == 0)){
				filter(xx, yy, 0, temparr, green_even_red); 
				filter(xx, yy, 2, temparr, green_even_blue); 
			}
			else if ((xx % 2 != 0) && (yy % 2 != 0)){
				filter(xx, yy, 0, temparr, green_odd_red); 
				filter(xx, yy, 2, temparr, green_odd_blue); 
			}
			else if ((xx % 2 == 0) && (yy % 2 != 0)){
				filter(xx, yy, 0, temparr, blue_red); 
				filter(xx, yy, 1, temparr, br_green); 
			}
			else if ((xx % 2 != 0) && (yy % 2 == 0)){
				filter(xx, yy, 2, temparr, blue_red); 
				filter(xx, yy, 1, temparr, br_green); 
			}
			// output_image[xx][yy][0] = round(temparr[xx][yy][0] * 255);
			// output_image[xx][yy][1] = round(temparr[xx][yy][1] * 255);
			// output_image[xx][yy][2] = round(temparr[xx][yy][2] * 255);
		}
	}

	for(int k = 0; k < Size_2; k++){
		for(int r = 0; r < Size_1; r++){
			output_image[k][r][0] = round(temparr[k + 1][r + 1][0] * 255);
			output_image[k][r][1] = round(temparr[k + 1][r + 1][1] * 255);
			output_image[k][r][2] = round(temparr[k + 1][r + 1][2] * 255);
		}
	}

	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(output_image, sizeof(unsigned char), Size_1*Size_2*3, file);
	fclose(file);

	return 0;
}