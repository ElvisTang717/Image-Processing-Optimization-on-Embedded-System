#include "opencv2/opencv.hpp"
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <pthread.h>
#include <arm_neon.h>
#include <time.h>
#define numThreads 4
#define red 0b00110110
#define green 0b10110111
#define blue 0b00010010

using namespace std;
using namespace cv;

// Declare Time variables
clock_t Start, End;
uint16_t Frame = 0;
double FPS;

// Declare frames
Mat Color_Frame, Gray_Frame, Sobel_Frame;

// Declare Threads, mutex, barier
pthread_t trd[numThreads];
pthread_mutex_t Image_Write = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier;

struct threadArgs{
  uint8_t* colorPtr;
  uint8_t* grayPtr;
  uint8_t* sobelPtr;
  uint8_t chl;
} typedef threadArgs;

// Sobel arrays
int8_t Gx[3][3] = {-1,0,1,-2,0,2,-1,0,1};
int8_t Gy[3][3] = {1,2,1,0,0,0,-1,-2,-1};

void to442_grayscale(uint8_t* colorPtr, uint8_t* grayPtr, uint8_t chl);
void to442_sobel(uint8_t* grayPtr, uint8_t* sobelPtr);
void* ColortoSobel(void * trd);



int main(){

  // Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name
  //VideoCapture capture("/home/pi/Documents/CPE442/Funny_animal_screaming.mp4");
  VideoCapture capture("/home/pi/Documents/CPE442/Amogus.mp4");

  // Check if camera opened successfully
  if(!capture.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }

  //Barrier Initializaton
  pthread_barrier_init(&barrier, NULL, numThreads);

  //Start monitoring time for later FPS calculation
  Start = clock();	

  while(1){

    Frame += 1;    
    // Capture frame-by-frame
    capture.read(Color_Frame);

    // If the frame is empty, break immediately
    if (Color_Frame.empty())
      break;

    // Define Gray_Frame as an 1 channel mat object
    Gray_Frame = Mat(Color_Frame.size(), CV_8UC1, Scalar(0));
    Sobel_Frame = Mat((Gray_Frame.rows - 2), (Gray_Frame.cols - 2), CV_8UC1, Scalar(0));

    // Create Pointers for Color_Frame
    uint8_t* colorPtr = (uint8_t*)Color_Frame.data;
    uint8_t chl = Color_Frame.channels();

    // Create Pointers for Gray_Frame and Sobel_Frame
    uint8_t* grayPtr = (uint8_t*)Gray_Frame.data;
    uint8_t* sobelPtr = (uint8_t*)Sobel_Frame.data;

    threadArgs threadArgs = {
      .colorPtr = colorPtr,
      .grayPtr = grayPtr,
      .sobelPtr = sobelPtr,
      .chl = chl
    };

    // Thread Implement
    for(int i = 0; i < numThreads; i++){
      if(pthread_create(&trd[i], NULL, &ColortoSobel, (void *)&threadArgs) != 0){
        printf("Thread create failed!!\n");
      }
    }
    for(int i = 0; i < numThreads; i++){
      if(pthread_join(trd[i], NULL) != 0){
        printf("Thread create failed!!\n");
      }
    }  

    // Display the resulting frame
    imshow( "Frame1", Sobel_Frame );

    // Press  ESC on keyboard to exit
    char c=(char)waitKey(25);
    if(c==27)
      break;
  }

  pthread_barrier_destroy(&barrier); 

  //Calculate FPS(Frame Per Second)
  End = clock();
  FPS = Frame / ((double)(End - Start) / CLOCKS_PER_SEC);
  cout << "FPS (Frame Per Second): " << FPS << "\n"; 

  // When everything done, release the video capture object
  capture.release();

  // Closes all the frames
  destroyAllWindows();
	
  return 0;
}

void *ColortoSobel(void * threadArgs){

  struct threadArgs * myArgs = (struct threadArgs *)threadArgs;
  to442_grayscale(myArgs->colorPtr, myArgs->grayPtr, myArgs->chl);
  to442_sobel(myArgs->grayPtr, myArgs->sobelPtr);

  pthread_barrier_wait(&barrier);

  return NULL;
}

void to442_grayscale(uint8_t* colorPtr, uint8_t* __restrict grayPtr, uint8_t chl){
  
  uint8_t * color = colorPtr;
  uint8_t * gray = grayPtr; 
  uint8_t index;
  int numPixels = Color_Frame.rows * Color_Frame.cols;
  int numVec = numPixels/(8*numThreads);

  // Vectorize the weight for RGB pixels (neon intrinsics)
  uint8x8_t w_r = vdup_n_u8(red);
  uint8x8_t w_g = vdup_n_u8(green);
  uint8x8_t w_b = vdup_n_u8(blue);
  uint16x8_t temp;
  uint8x8_t result;

  // Identify each threads
  for(int i = 0; i < numThreads; i++){
    if(pthread_self() == trd[i]){
      index = i;
      color += 8 * 3 * numVec * index;
      gray += 8 * numVec * index;
      break;
      }
  }

  // wait for all threads enter the function
  pthread_barrier_wait(&barrier);
  
  // Vectorize the conversion (neon intrinsics) 
  for(int i = 0; i < numVec; i++, color += 8*3, gray += 8){

	uint8x8x3_t src = vld3_u8(color);

	temp = vmull_u8(src.val[0],w_b);
  	temp = vmlal_u8(temp, src.val[1], w_g);
  	temp = vmlal_u8(temp, src.val[2], w_r);

	result = vshrn_n_u16(temp, 8);
	vst1_u8(gray, result);
  }

  // Convert the left over pixels to gray scale
  if(index == (numThreads - 1)){ 
	  for(int i = 8 * numVec * 4; i < numPixels; i++){
		  grayPtr[i] = colorPtr[i*chl + 0] * 0.0722   //B
			     + colorPtr[i*chl + 1] * 0.7152  //G
			     + colorPtr[i*chl + 2] * 0.2126; //R
	  }
  }

}

void to442_sobel(uint8_t* grayPtr, uint8_t* sobelPtr){
  
  uint8_t* gray = grayPtr;
  uint8_t* sobel = sobelPtr;
  int8_t  index;
  int numPixels = Color_Frame.rows * (Color_Frame.cols - 2);
  int numVec = numPixels/(8*numThreads);
  uint16_t row_start;
  uint16_t row_end;
  int row_0,row_1,row_2;
  uint8_t leftover = (Gray_Frame.cols - 2) % 8;
  int8_t Gx_abs, Gy_abs = 0;

  uint16x8x4_t src1, src2;
  uint8x8_t G;

  // Identify threads
  for(int i = 0; i < numThreads; i++){
    if(pthread_self() == trd[i]){
      index = i;
      break;
      }
  }

  // Calculate the start & end rows for each threads
  if(index == 0){
    row_start = 0;
    row_end = (Color_Frame.rows/numThreads)*(index+1) - 1;
  }
  else if(index == (numThreads - 1)){
    row_start = (Color_Frame.rows/numThreads)*index - 1;
    row_end = (Color_Frame.rows/numThreads)*(index+1) - 2;
  }
  else{
    row_start = (Color_Frame.rows/numThreads)*index - 1;
    row_end = (Color_Frame.rows/numThreads)*(index+1) - 1;
  }

  // wait for all threads enter the function
  pthread_barrier_wait(&barrier);

  for(int i = row_start; i < row_end; i++){
  	row_0 = Gray_Frame.cols * i;
	row_1 = Gray_Frame.cols * (i+1);
	row_2 = Gray_Frame.cols * (i+2);

	for(int j = 0; j < (Gray_Frame.cols - leftover - 1); j += 8){
		
		// First row of the 3x3 sobel filter
		src1.val[0] = vmovl_u8(vld1_u8(gray + row_0 + j));
		src1.val[1] = vmovl_u8(vld1_u8(gray + row_0 + j + 1));
		src1.val[2] = vmovl_u8(vld1_u8(gray + row_0 + j + 2));

		// Second row of the 3x3 sobel filter
		src1.val[3] = vmovl_u8(vld1_u8(gray + row_1 + j));
		src2.val[0] = vmovl_u8(vld1_u8(gray + row_1 + j + 2));	

		// Third row of the 3x3 sobel filter
		src2.val[1] = vmovl_u8(vld1_u8(gray + row_2 + j));
		src2.val[2] = vmovl_u8(vld1_u8(gray + row_2 + j + 1));
		src2.val[3] = vmovl_u8(vld1_u8(gray + row_2 + j + 2));
		
		// Apply 3x3 sobel filter: Gx & Gy
		G =	 vqmovn_u16(
		   	 vaddq_u16(
			 vabsq_s16(	
			 	vsubq_s16(	
			 		vaddq_u16(vaddq_u16(src1.val[2], src2.val[3]),vshlq_n_u16(src2.val[0],1))
			 		,vaddq_u16(vaddq_u16(src1.val[0], src2.val[1]),vshlq_n_u16(src1.val[3],1))))
			 ,vabsq_s16(	
			 	vsubq_s16(	
			 		vaddq_u16(vaddq_u16(src1.val[0], src1.val[2]),vshlq_n_u16(src1.val[1],1))
			 		,vaddq_u16(vaddq_u16(src2.val[1], src2.val[3]),vshlq_n_u16(src2.val[2],1))))));
		
		// Store into Sobel Frame
		vst1_u8(sobel + Sobel_Frame.cols * i + j, G);
	}
	for(int j = (Gray_Frame.cols - leftover - 1); j < (Gray_Frame.cols - 1); j++){
	
    		int col = Gray_Frame.cols;
    		int8_t Gx_abs = abs(
    		grayPtr[row_0 + j]             * Gx[0][0]+
    		grayPtr[row_0 + (j + 1)]       * Gx[0][1]+
    		grayPtr[row_0 + (j + 2)]       * Gx[0][2]+
    		grayPtr[row_1 + j]       * Gx[1][0]+
    		grayPtr[row_1 + (j + 1)] * Gx[1][1]+
    		grayPtr[row_1 + (j + 2)] * Gx[1][2]+
    		grayPtr[row_2 + j]       * Gx[2][0]+
    		grayPtr[row_2 + (j + 1)] * Gx[2][1]+
    		grayPtr[row_2 + (j + 2)] * Gx[2][2]);

    		int8_t Gy_abs = abs(
    		grayPtr[row_0 + j]             * Gy[0][0]+
    		grayPtr[row_0  + (j + 1)]       * Gy[0][1]+
    		grayPtr[row_0 + (j + 2)]       * Gy[0][2]+
    		grayPtr[row_1 + j]       * Gy[1][0]+
    		grayPtr[row_1 + (j + 1)] * Gy[1][1]+
    		grayPtr[row_1 + (j + 2)] * Gy[1][2]+
    		grayPtr[row_2 + j]       * Gy[2][0]+
    		grayPtr[row_2 + (j + 1)] * Gy[2][1]+
    		grayPtr[row_2 + (j + 2)] * Gy[2][2]);

    		sobelPtr[row_0 + j] = Gx_abs + Gy_abs;
    	}
	
  	}
  }
