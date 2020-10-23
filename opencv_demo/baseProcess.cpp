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

// max filter
cv::Mat max_pooling(cv::Mat img)
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
                        v = fmaxl(img.at<cv::Vec3b>(y + dy, x + dx)[c], v);
                    }
                }
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

// gaussian filter
cv::Mat gaussian_filter(cv::Mat img, double sigma, int kernel_size)
{
    int height  = img.rows;
    int width   = img.cols;
    int channel = img.channels();
    
    // prepare output
    cv::Mat out = cv::Mat::zeros(height, width, CV_8UC3);
    
    // prepare kernel
    int pad = floor(kernel_size / 2);
    int _x = 0, _y = 0;
    double kernel_sum = 0.0;
    
    // get gaussian kernel
    float kernel[kernel_size][kernel_size];
    for (int y = 0; y < kernel_size; ++y)
    {
        for (int x = 0; x < kernel_size; ++x)
        {
            _y = y - pad;
            _x = x - pad;
            kernel[y][x] = 1 / (2 * M_PI * sigma * sigma) * exp(-(_x * _x + _y * _y) / (2 * sigma * sigma));
            kernel_sum += kernel[y][x];
        }
    }
    
    for (int y = 0; y < kernel_size; ++y)
    {
        for (int x = 0; x < kernel_size; ++x)
        {
            kernel[y][x] /= kernel_sum;
        }
    }
    
    // filtering
    double v = 0.0;
    
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x  < width; ++x)
        {
            for (int c = 0; c < channel; ++c)
            {
                v = 0.0;
                for (int dy = -pad; dy < pad + 1; ++dy)
                {
                    for (int dx = -pad; dx < pad + 1; ++dx)
                    {
                        if (((x + dx) >= 0) && ((y + dy) >= 0))
                        {
                            v += (double)img.at<cv::Vec3b>(y + dy, x + dx)[c] * kernel[dy + pad][dx + pad];
                        }
                    }
                }
                
                out.at<cv::Vec3b>(y, x)[c] = v;
            }
        }
    }
    return out;
}

// median filter
cv::Mat median_filter(cv::Mat img, int kernel_size)
{
    int height  = img.rows;
    int width   = img.cols;
    int channel = img.channels();
    
    // prepare output
    cv::Mat out = cv::Mat::zeros(height, width, CV_8UC3);
    
    
    // prepare kernel
    int pad = floor(kernel_size / 2);
    
    double v = 0.0;
    int vs[kernel_size * kernel_size];
    int count = 0;
    
    // filtering
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            for (int c = 0; c < channel; ++c)
            {
                v = 0.0;
                count = 0;
                
                for (int i = 0; i < kernel_size * kernel_size; ++i)
                {
                    vs[i] = 999;
                }
                
                // get neighbor pixels
                for (int dy = -pad; dy < pad + 1; ++dy)
                {
                    for (int dx = -pad; dx < pad + 1; ++dx)
                    {
                        if (((y + dy) >= 0) && ((x + dx) >= 0))
                        {
                            vs[count++] = (int)img.at<cv::Vec3b>(y + dy, x + dx)[c];
                        }
                    }
                }
                
                // get and assign median
                std::sort(vs, vs + (kernel_size * kernel_size));
                out.at<cv::Vec3b>(y, x)[c] = (uchar)vs[int(floor(count/2)) + 1];
            }
        }
    }
    return out;
}

// mean_filter
cv::Mat mean_filter(cv::Mat img, int kernel_size)
{
    int height =  img.rows;
    int width  = img.cols;
    int channel = img.channels();
    
    
    // propare output
    cv::Mat out = cv::Mat::zeros(height, width, CV_8UC3);
    
    // prepare kernel
    // floor(向下取整)，floor(3/2) = 1
    int pad = floor(kernel_size / 2);
        
    // filtering
    double v = 0.0;
    int vs[kernel_size * kernel_size];
    int count = 0;
    
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            for (int c = 0; c < channel; ++c)
            {
                v = 0;
                // get pixel sum
                for (int dy = -pad; dy < pad + 1; ++dy)
                {
                    for (int dx = -pad; dx < pad + 1; ++dx)
                    {
                        if (((y + dy) >= 0) && ((x + dx) >= 0))
                        {
                            v += (int)img.at<cv::Vec3b>(y + dy, x + dx)[c];
                        }
                    }
                }
                
                // assign mean value
                v /= (kernel_size * kernel_size);
                out.at<cv::Vec3b>(y, x)[c] = (uchar)v;
            }
        }
    }
    return out;
}

