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


int main(int argc, const char * argv[]) {
    //read image
    cv::Mat img = cv::imread("/Users/william/git/learning/opencv_learning/opencv_demo/res/test.jpg", cv::IMREAD_COLOR);//载入

    // channel swap
    cv::Mat out = channel_swap(img);
    cv::imshow("channel_swap", out);
    cv::waitKey(0);//等待
    cv::destroyAllWindows();
    return 0;
}
