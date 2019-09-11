#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;
#define COLOR image.at<Vec3b>(Point(x,y))

enum FocusedMode{
	BlackWhite,
	Contrast,
	Negative,
	Brightness,
	None
};

// Global variables 
Mat image;
std::string asciImage;
Mat resetImage;
FocusedMode mode = None;
int threshold;
int value;
std::string imageString;


void setColor(Vec3b &color, int val){
	for(int i = 0; i<3; ++i){
		color[i] = val;
	}

}


void addToColor(Vec3b &color, int val){
	for(int i = 0; i<3; ++i){
		color[i] = (color[i] + val <= 0) ? 0 : (color[i] + val >= 255) ? 255 : color[i] + val;
	}
}

void reset(FocusedMode m){
	// Mat image = imread(imageString, 1 );
	// Mat resetImage = imread(imageString, 1 );
	::mode = m;
	int threshold = 127;
	int value = 0;
}

Mat setBlackWhite(Mat image, int boundary){
	// Set pixel black
	boundary *= 3;
	for(int x = 0; x<image.rows; ++x){
		for(int y = 0; y<image.cols; ++y){

    		// Vec3b color = image.at<Vec3b>(Point(x,y));
    		// Set pixel

			if((COLOR[0]+COLOR[1]+COLOR[2]) > (boundary)){
				setColor(COLOR, 255);
			}
			// Set pixel white
			else{
				setColor(COLOR, 0);
			}
		}
	}
	return image;
}

// Make light pixels lighter and dark pixels darker
Mat setContrast(Mat image, int boundary, int amount){
	boundary *= 3;
	for(int x = 0; x<image.rows; ++x){
		for(int y = 0; y<image.cols; ++y){
			Vec3b &color = image.at<Vec3b>(Point(x,y));

			if((COLOR[0]+COLOR[1]+COLOR[2]) > (boundary)){
				addToColor(color, amount);
			}
			else{
				addToColor(color, -amount);
			}
		}
	}
	return image;
}


// Previous setContrast version that created cool distortion/noise effect
Mat setDistorion(Mat image, int boundary, int amount){
	for(int x = 0; x<image.rows; ++x){
		for(int y = 0; y<image.cols; ++y){
			Vec3b &color = image.at<Vec3b>(Point(x,y));
			
			if((color[0]+color[1]+color[2]) > (boundary * 3)){
				addToColor(color, amount);
			}
			else{
				amount = -amount;
				addToColor(color, amount);
			}
		}
	}
	return image;
}


// Set all pixels brighter or darker 
Mat setBrightness(Mat image, int brightness){
	for(int x = 0; x<image.rows; ++x){
		for(int y = 0; y<image.cols; ++y){
			Vec3b &color = image.at<Vec3b>(Point(x,y));

			addToColor(color, brightness);
		}
	}
	return image;
}


Mat setNegative(Mat image){
	for(int x = 0; x<image.rows; ++x){
		for(int y = 0; y<image.cols; ++y){
			Vec3b &color = image.at<Vec3b>(Point(x,y));

			color[0] = -color[0];
			color[1] = -color[1];
			color[2] = -color[2];
		}
	}	
	return image;
}


int main(int argc, char *argv[])
{
	if ( argc != 2 )
	{
		printf("usage: DisplayImage.out <Image_Path>\n");
		return -1;
	}    

	std::string imageString = argv[1];
	image = imread(imageString, 1);
	int threshold = 127;
	int value = 0;
	resetImage = imread(imageString, 1);

	namedWindow("Display Image", WINDOW_AUTOSIZE );

	if ( !image.data || !resetImage.data )
	{
		printf("No image data \n");
		return -1;
	}

	bool looping = true;


	do{

		std::cout << mode << std::endl;

		std::cout << "Value: " << value << "\nThreshold: " << threshold << std::endl;
		switch(mode){
			case BlackWhite:
			image = setBlackWhite(resetImage, threshold);
			break;
			case Contrast:

			image = setContrast(resetImage, threshold, value);




			break;
			case Brightness:

			image = setBrightness(resetImage, value);


			break;
			case Negative:

			image = setNegative(resetImage);

			break;
			case None:
			break;
		}




		imshow("Display Image", image);



		auto k = waitKey(0);
		std::cout << "you pressed: " << k << std::endl;

	    if(k == 27){	// On escape close program
	    	looping = false;
	    }
	    if(k == 99){ 	// On c 
	    	reset(Contrast);


	    }	
	    if(k == 118){ 	// On b
	    	reset(Brightness);


	    }	
	    if(k == 98){ 	// On v
	    	reset(BlackWhite);

	    }	
	    if(k == 110){ 	// On n
	    	reset(Negative);

	    }	

	    if(k == 83) threshold += 1;	// On arrow left
	    if(k == 81) threshold -= 1;	// On arrow right
	    if(k == 82) value += 1;	// On arrow top
	    if(k == 84) value -= 1;	// On arrow down	
	    if(k == 114){				// On r
	    	reset(None);
	    }

	} while(looping);


	return 0;
}