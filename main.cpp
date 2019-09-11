#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;

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



void setBlackWhite(Mat &image, int boundary){
	// Set pixel black
	for(int x = 0; x<image.rows; ++x){
    	for(int y = 0; y<image.cols; ++y){

    		Vec3b &color = image.at<Vec3b>(Point(x,y));
    		// Set pixel
			if((color[0]+color[1]+color[2]) > (boundary * 3)){
				setColor(color, 255);
			}
			// Set pixel white
			else{
				setColor(color, 0);
			}
		}
	}
}

// Make light pixels lighter and dark pixels darker
void setContrast(Mat &image, int boundary, int amount){
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
}

// Set all pixels brighter or darker 
void setBrightness(Mat &image, int brightness){
		for(int x = 0; x<image.rows; ++x){
    	for(int y = 0; y<image.cols; ++y){
    		Vec3b &color = image.at<Vec3b>(Point(x,y));
    		
	addToColor(color, brightness);
}
}
}


void setNegative(Mat &image){
	for(int x = 0; x<image.rows; ++x){
    	for(int y = 0; y<image.cols; ++y){
    		Vec3b &color = image.at<Vec3b>(Point(x,y));

			color[0] = -color[0];
			color[1] = -color[1];
			color[2] = -color[2];
		}
	}	
}




enum FocusedMode{
	BlackWhite,
	Contrast,
	Negative,
	Brightness,
	None
};

int main(int argc, char *argv[])
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    
    Mat image;
    // Parse char to int
    

    image = imread( argv[1], 1 );
    Mat resetImage = imread( argv[1], 1 );
    // Go over every pixel and set it either black or white depending on the threshold 
    // for(int x = 0; x<image.rows; ++x)
    // 	for(int y = 0; y<image.cols; ++y)
    // 		setBlackWhite(image.at<Vec3b>(Point(x,y)), threshold);
    
    //std::string asciImage;
    FocusedMode mode = None;
    namedWindow("Display Image", WINDOW_AUTOSIZE );

   if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }

    bool looping = true;
    int threshold = 127;
    int value = 127;
    do{


	    // for(int x = 0; x<image.rows; ++x){
	    // 	for(int y = 0; y<image.cols; ++y){
	    // 		setContrast(image.at<Vec3b>(Point(x,y)), 127, threshold);
	    // 	}
	    // }

	 //setBrightness(image.at<Vec3b>(Point(x,y)), threshold);

	   std::cout << mode << std::endl;
	   
	   std::cout << "Value: " << value << "\nThreshold: " << threshold << std::endl;
	    switch(mode){
	    	case BlackWhite:
	    		setBlackWhite(image, value);
	    	break;
	    	case Contrast:
	    
	    		setContrast(image, threshold, value);
			    

	
	    		
	    	break;
	    	case Brightness:
	    
			    setBrightness(image, value);

		
	    	break;
	    	case Negative:

	    		setNegative(image);
	   
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
	    	image = resetImage;
		    mode = Contrast;
		    value = 0;
		    threshold = 127;
	    }	
	    if(k == 118){ 	// On b
	    	image = resetImage;
		    mode = Brightness;
		    value = 0;
		    threshold = 127;
	    }	
	    if(k == 98){ 	// On v
	    	image = resetImage;
		    mode = BlackWhite;
		    value = 0;
		    threshold = 0;
	    }	
	    if(k == 110){ 	// On n
	    	image = resetImage;
		    mode = Negative;
		    value = 0;
		    threshold = 0;
	    }	

	    if(k == 81) threshold += 10;	// On arrow left
	    if(k == 83) threshold -= 10;	// On arrow right
	    if(k == 82) value += 10;	// On arrow top
	    if(k == 84) value -= 10;	// On arrow down	
	    if(k == 114){				// On r
	    	
	    	image = resetImage;
	    	value = 0;
		    threshold = 0;
		    mode = None;
	    }

	} while(looping);
    
    

    return 0;
}