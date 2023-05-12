#include "opencv2/opencv.hpp"
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;
using namespace cv;

//Declare time variables
clock_t Start, End;
int Frame = 0;
double FPS;

// Declare frames
Mat Color_Frame, Gray_Frame, Sobel_Frame;

void to442_grayscale(uint8_t* colorPtr, uint8_t* grayPtr, int ch);
void to442_sobel(uint8_t* grayPtr, uint8_t* sobelPtr, int8_t Gx[3][3], int8_t Gy[3][3]);

int main(){

  // Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name
  VideoCapture capture("/home/pi/Documents/CPE442/Amogus.mp4"); 
   
  // Check if camera opened successfully
  if(!capture.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }

  // Start monitoring time for later FPS calculation
  Start = clock();

  while(1){

    Frame += 1;
    // Sobel arrays
    int8_t Gx[3][3] = {-1,0,1,-2,0,2,-1,0,1};    // filter is signed but gray scale is unsigned
    int8_t Gy[3][3] = {1,2,1,0,0,0,-1,-2,-1};
    
    // Capture frame-by-frame
    capture.read(Color_Frame);

    // If the frame is empty, break immediately
    if (Color_Frame.empty()){
       break;
    }
    
    // Define Gray_Frame as an 1 channel mat object
    Gray_Frame = Mat(Color_Frame.size(), CV_8UC1, Scalar(0));
    Sobel_Frame = Mat((Gray_Frame.rows - 2), (Gray_Frame.cols - 2), CV_8UC1, Scalar(0));

    // Create Pointers for Color_Frame
    uint8_t* colorPtr = (uint8_t*)Color_Frame.data;
    int ch = Color_Frame.channels();

    // Create Pointers for Gray_Frame and Sobel_Frame
    uint8_t* grayPtr = (uint8_t*)Gray_Frame.data;
    uint8_t* sobelPtr = (uint8_t*)Sobel_Frame.data;

    // Generate Gray Scale
    to442_grayscale(colorPtr, grayPtr, ch);

    // Apply Sobel Filter
    to442_sobel(grayPtr, sobelPtr, Gx, Gy);  

    // Display the resulting frame
    imshow( "Frame1", Sobel_Frame );

    // Press  ESC on keyboard to exit
    char c=(char)waitKey(25);
    if(c==27)
      break;
  }
 
  // Calculate FPS(Frame Per Second)
  End = clock();
  FPS = Frame /((double)(End - Start) / CLOCKS_PER_SEC);
  cout << "FPS (Frame Per Second): " << FPS << "\n";

  // When everything done, release the video capture object
  capture.release();

  // Closes all the frames
  destroyAllWindows();
	
  return 0;
}

void to442_grayscale(uint8_t* colorPtr, uint8_t* grayPtr, int ch){

  for(int i = 0; i < (Color_Frame.rows * Color_Frame.cols); i++){
    grayPtr[i] = colorPtr[i*ch + 0] * 0.0722   //B
                + colorPtr[i*ch + 1] * 0.7152  //G
                + colorPtr[i*ch + 2] * 0.2126; //R
  }
}

void to442_sobel(uint8_t* grayPtr, uint8_t* sobelPtr, int8_t Gx[3][3], int8_t Gy[3][3]){
  
  int8_t Gx_abs, Gy_abs = 0;  
  for(int i = 0; i < (Color_Frame.rows -2); i++){
    for(int j = 0; j < (Color_Frame.cols -2); j++){

    int8_t Gx_abs = abs(
    grayPtr[i * Color_Frame.cols + j]             * Gx[0][0]+
    grayPtr[i * Color_Frame.cols + (j + 1)]       * Gx[0][1]+
    grayPtr[i * Color_Frame.cols + (j + 2)]       * Gx[0][2]+
    grayPtr[(i + 1) * Color_Frame.cols + j]       * Gx[1][0]+
    grayPtr[(i + 1) * Color_Frame.cols + (j + 1)] * Gx[1][1]+
    grayPtr[(i + 1) * Color_Frame.cols + (j + 2)] * Gx[1][2]+
    grayPtr[(i + 2) * Color_Frame.cols + j]       * Gx[2][0]+
    grayPtr[(i + 2) * Color_Frame.cols + (j + 1)] * Gx[2][1]+
    grayPtr[(i + 2) * Color_Frame.cols + (j + 2)] * Gx[2][2]);

    int8_t Gy_abs = abs(
    grayPtr[i * Color_Frame.cols + j]             * Gy[0][0]+
    grayPtr[i * Color_Frame.cols + (j + 1)]       * Gy[0][1]+
    grayPtr[i * Color_Frame.cols + (j + 2)]       * Gy[0][2]+
    grayPtr[(i + 1) * Color_Frame.cols + j]       * Gy[1][0]+
    grayPtr[(i + 1) * Color_Frame.cols + (j + 1)] * Gy[1][1]+
    grayPtr[(i + 1) * Color_Frame.cols + (j + 2)] * Gy[1][2]+
    grayPtr[(i + 2) * Color_Frame.cols + j]       * Gy[2][0]+
    grayPtr[(i + 2) * Color_Frame.cols + (j + 1)] * Gy[2][1]+
    grayPtr[(i + 2) * Color_Frame.cols + (j + 2)] * Gy[2][2]);

    sobelPtr[i * (Color_Frame.cols - 2) + j] = Gx_abs + Gy_abs;
    }
  }
}
