//
//  decrease_color.cpp
//  opencv_demo
//
//  Created by william on 2020/9/1.
//  Copyright © 2020 william. All rights reserved.
//

#include "base.h"

// Decrease color
cv::Mat decrease_color(cv::Mat img)
{
    int height = img.cols;
    int width = img.rows;
    int chinnel = img.channels();
    cv::Mat out = cv::Mat::zeros(height, width, CV_8UC3);
    
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            for (int c = 0; c < chinnel; ++c)
            {
                out.at<cv::Vec3b>(y, x)[c] = (uchar)(floor((double)img.at<cv::Vec3b>(y, x)[c] / 64) * 64 + 32);
            }
        }
    }
    return out;
}
