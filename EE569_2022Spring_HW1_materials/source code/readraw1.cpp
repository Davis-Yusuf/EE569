// This sample code reads in image data from a RAW image file and 
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])

{
	int array[]={100, 80, 90, 100, 80, 60, 80}; 
	const int number = sizeof(array)/sizeof(int); 
	pair<int, size_t> result[number];
	int nres=0; 
 
	cout<<"Map approach: "<<endl; 
 
	std::sort(array, array + number);
	int counter;  
	for(int i = 0; i < number; i+=counter) {
		for (counter=1;i+counter<number && array[i+counter]==array[i] ; )
		    counter++; 
		if (counter>1) {
			cout << "dup: " << array[i] << " "<<counter<<endl;   
			result[nres++] = make_pair(array[i], counter);
		}
	}
	cout <<"---"<<endl; 
	for (int i=0; i<nres; i++) 
	    cout << result[i].first <<" : "<<result[i].second<<" ->" << result[i].first/result[i].second<<endl;

}
