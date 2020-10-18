//
//  baseProcess.cpp
//  opencv_demo
//
//  Created by william on 2020/8/24.
//  Copyright © 2020 william. All rights reserved.
//

#include "base.h"

// load image:cv::imread
// opecv 支持tiff,png,jpg等常见的图片格式

// change image:cv:cvtClor
// save image:cv:imwrite

cv::Mat average_pooling(cv::Mat img)
{
    int height  = img.rows;
    int width   = img.cols;
    int channel = img.channels();
    
    // prepare output
    cv::Mat out = cv::Mat::zeros(height, width, CV_8UC3);
    
    int r = 10;
    double v = 0;
    
    for (int y = 0; y < height; y += r)
    {
        for (int x = 0; x < width; x += r)
        {
            for (int c = 0; c < channel; ++c)
            {
                v = 0;
                for (int dy = 0; dy < r; ++dy)
                {
                    for (int dx = 0; dx < r; ++dx)
                    {
                        v += (double)img.at<cv::Vec3b>(y + dy, x + dx)[c];
                    }
                }
                v /= (r * r);
                for (int dy = 0; dy < r; ++dy)
                {
                    for (int dx = 0; dx < r; ++dx)
                    {
                        out.at<cv::Vec3b>(y + dy, x + dx)[c] = (uchar)v;
                    }
                }
            }
        }
    }
    return out;
}



