//
//  bgr2gray.cpp
//  opencv_demo
//
//  Created by william on 2020/8/16.
//  Copyright © 2020 william. All rights reserved.
//

#include "base.h"

// BGR -> GRAY
cv::Mat BRG2GRAY(cv::Mat img)
{
    // get height and width
    int width = img.cols;
    int height = img.rows;
    
    // prepare output
    cv::Mat out = cv::Mat::zeros(height, width, CV_8UC1);
    
    // each y, x
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // BGR -> GRAY
            out.at<uchar>(y, x) = 0.2126 * (float)img.at<cv::Vec3b>(y, x)[2] + 0.7152 * (float)img.at<cv::Vec3b>(y, x)[1] + 0.0722 * (float)img.at<cv::Vec3b>(y, x)[0];
        }
    }
    
    return out;
}
