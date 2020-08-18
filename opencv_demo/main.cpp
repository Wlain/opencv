//
//  main.cpp
//  opencv_demo
//
//  Created by william on 2020/8/16.
//  Copyright © 2020 william. All rights reserved.
//

#include "base.h"

// exterm
extern cv::Mat channel_swap(cv::Mat img);
extern cv::Mat BRG2GRAY(cv::Mat img);
extern cv::Mat Binarize(cv::Mat img, int th);
extern cv::Mat Binarize_Otsu(cv::Mat gray);
extern cv::Mat BGR2HSV(cv::Mat img);
extern cv::Mat HSV2BGR(cv::Mat hsv);
extern cv::Mat inverse_hue(cv::Mat hsv);



int main(int argc, const char * argv[]) {
    //read image
    cv::Mat img = cv::imread("/Users/william/git/learning/opencv_learning/opencv_demo/res/test.jpg", cv::IMREAD_COLOR);//载入
    
    // channel swap
    // cv::Mat out = channel_swap(img);
    // BGR -> Gray
    // cv::Mat gray = BRG2GRAY(img);
    // Gray -> Binary
    // cv::Mat out = Binarize_Otsu(gray);
    cv::Mat hsv = BGR2HSV(img);
    hsv = inverse_hue(hsv);
    cv::Mat out = HSV2BGR(hsv);
    cv::imshow("Binary", out);
    cv::waitKey(0);//等待
    cv::destroyAllWindows();
    return 0;
}
