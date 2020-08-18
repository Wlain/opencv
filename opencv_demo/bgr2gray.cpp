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


// Gray -> Binary
cv::Mat Binarize(cv::Mat gray, int th)
{
    int width = gray.cols;
    int height = gray.rows;
    
    cv::Mat out = cv::Mat::zeros(height, width, CV_8UC1);
    
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // Binarize
            out.at<uchar>(y, x) = (gray.at<uchar>(y, x) > th) ? 255 : 0;
        }
    }
    return out;
}


// Gray ->Binary
cv::Mat Binarize_Otsu(cv::Mat gray)
{
    int width = gray.cols;
    int height = gray.rows;
    
    // determine threshold
    double w0 = 0, w1 = 0;
    double m0 = 0, m1 = 0;
    double max_sb = 0, sb = 0;
    int th = 0;
    int val = 0;
    
    
    // get threshold
    for (int t = 0; t < 255; ++t)
    {
        w0 = 0;
        w1 = 0;
        m0 = 0;
        m1 = 0;
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                val = (int)(gray.at<uchar>(y, x));
                
                if (val < t)
                {
                    w0++;
                    m0 += val;
                }
                else
                {
                    w1++;
                    m1 += val;
                }
            }
        }
        m0 /= w0;
        m1 /= w1;
        w0 /= (height * width);
        w1 /= (height * width);
        sb = w0 * w1 * pow((m0 - m1), 2);
        if (sb > max_sb)
        {
            max_sb = sb;
            th = t;
        }
    }
    
    std::cout << "threshold:" << th << std::endl;

    // prepare output
    cv::Mat out = cv::Mat::zeros(height, width, CV_8UC1);;
    
    // each x, y
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            out.at<uchar>(y, x) = gray.at<uchar>(y, x) > th ? 255 : 0;
        }
    }
    return out;
}
