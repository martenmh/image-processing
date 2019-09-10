#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;

void setBlackWhite(Vec3b &color, int boundary){
	// Set pixel black
	if((color[0]+color[1]+color[2]) > (boundary * 3)){
		color[0] =	254;// Set R
		color[1] =	254;// Set G
		color[2] =	254;// Set B
	}
	// Set pixel white
	else{
		color[0] =	0;	// Set R
		color[1] =	0;	// Set G
		color[2] =	0;	// Set B
	}
}

// Make light pixels lighter and dark pixels darker
void setContrast(Vec3b &color, int boundary, int amount){
	if((color[0]+color[1]+color[2]) > (boundary * 3)){
		color[0] = (color[0] + amount >= 255)? 255 : color[0] + amount; 
		color[1] = (color[1] + amount >= 255)? 255 : color[1] + amount; 
		color[2] = (color[2] + amount >= 255)? 255 : color[2] + amount; 
		
	}
	else{
		color[0] = (color[0] - amount <= 0)? 0 : color[0] - amount; 
		color[1] = (color[1] - amount <= 0)? 0 : color[1] - amount; 
		color[2] = (color[2] - amount <= 0)? 0 : color[2] - amount; 
	}
}

// Set all pixels brighter or darker 
void setBrightness(Vec3b &color, int brightness){
	color[0] = color[0] + brightness <= 0? 0 : color[0] + brightness >= 255? 255 : color[0] + brightness;
	color[1] = color[1] + brightness <= 0? 0 : color[1] + brightness >= 255? 255 : color[1] + brightness;
	color[2] = color[2] + brightness <= 0? 0 : color[2] + brightness >= 255? 255 : color[2] + brightness;
	

}

void setNegative(Vec3b &color){
	color[0] = -color[0];
	color[1] = -color[1];
	color[2] = -color[2];
}

int main(int argc, char *argv[])
{
    if ( argc != 3 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    
    Mat image;
    // Parse char to int
    int threshold = atoi(argv[2]);

    image = imread( argv[1], 1 );

    // Go over every pixel and set it either black or white depending on the threshold 
    // for(int x = 0; x<image.rows; ++x)
    // 	for(int y = 0; y<image.cols; ++y)
    // 		setBlackWhite(image.at<Vec3b>(Point(x,y)), threshold);
    
    //std::string asciImage;

    for(int x = 0; x<image.rows; ++x){
    	for(int y = 0; y<image.cols; ++y){
    		setContrast(image.at<Vec3b>(Point(x,y)), 127, threshold);
    	}
    }

    for(int x = 0; x<image.rows; ++x){
    	for(int y = 0; y<image.cols; ++y){
    		setContrast(image.at<Vec3b>(Point(x,y)), 127, threshold);
    	}
    }

    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);
    waitKey(0);
    return 0;
}