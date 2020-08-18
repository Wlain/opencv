//
//  hsv_utils.cpp
//  opencv_demo
//
//  Created by william on 2020/8/18.
//  Copyright © 2020 william. All rights reserved.
//

#include "base.h"

// BGR -> HSV
cv::Mat BGR2HSV(cv::Mat img)
{
    int width = img.cols;
    int height = img.rows;
    
    float r = 0.0f, g = 0.0f, b = 0.0f;
    float h = 0.0f, s = 0.0f, v = 0.0f;
    float _max = 0.0f, _min = 0.0f;
    
    // prepare output
    cv::Mat hsv = cv::Mat::zeros(height, width, CV_32FC3);
    
    // each y, x
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // BGR -> HSV
            r = (float)img.at<cv::Vec3b>(y, x)[2] / 255.0f;
            g = (float)img.at<cv::Vec3b>(y, x)[1] / 255.0f;
            b = (float)img.at<cv::Vec3b>(y, x)[0] / 255.0f;
            
            _max = fmax(r, fmax(g, b));
            _min = fmin(r, fmin(g, b));
            
            // get hue
            if (_max == _min)
            {
                h = 0.0f;
            }
            else if (_min == b)
            {
                h = 60.0f * (g - r) / (_max - _min) + 60;
            }
            else if (_min == r)
            {
                h = 60.0f * (b - g) / (_max - _min) + 180;
            }
            else if (_min == g)
            {
                h = 60.0f * (r - b) / (_max - _min) + 300;
            }
                
            // get saturation
            s = _max - _min;
            
            // get value
            v = _max;
            
            hsv.at<cv::Vec3f>(y, x)[0] = h;
            hsv.at<cv::Vec3f>(y, x)[1] = s;
            hsv.at<cv::Vec3f>(y, x)[2] = v;
        }
    }
    return hsv;
}

// HSV -> BGR
cv::Mat HSV2BGR(cv::Mat hsv)
{
    int width = hsv.cols;
    int height = hsv.rows;
    
    float h = 0.0f, s = 0.0f, v = 0.0f;
    double c = 0.0, _h = 0.0, _x = 0.0;
    double r = 0.0, g = 0.0, b = 0.0;
    
    // prepare output
    cv::Mat out = cv::Mat::zeros(height, width, CV_8UC3);
        
    // each y, x
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            h = hsv.at<cv::Vec3f>(y, x)[0];
            s = hsv.at<cv::Vec3f>(y, x)[1];
            v = hsv.at<cv::Vec3f>(y, x)[2];
            
            c = s;
            _h = h / 60.0;
            _x = c * (1.0 - abs(fmod(_h, 2) - 1));
            
            r = g = b = v - c;
            
            if (_h < 1.0)
            {
                r += c;
                g += _x;
            }
            else if (_h < 2)
            {
                r += _x;
                g += c;
            }
            else if(_h < 3)
            {
                g += c;
                b += _x;
            }
            else if (_h < 4)
            {
                g += _x;
                b += c;
            }
            else if (_h < 5)
            {
                r += _x;;
                b += c;
            }
            else if (_h < 6)
            {
                r += c;
                b += _x;
            }
            
            out.at<cv::Vec3b>(y, x)[0] = (uchar)(b * 255.0);
            out.at<cv::Vec3b>(y, x)[1] = (uchar)(g * 255.0);
            out.at<cv::Vec3b>(y, x)[2] = (uchar)(r * 255.0);
        }
    }
    return out;
}

// inverse Hue
cv::Mat inverse_hue(cv::Mat hsv)
{
    int width = hsv.cols;
    int height = hsv.rows;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            hsv.at<cv::Vec3f>(y, x)[0] = fmod(hsv.at<cv::Vec3f>(y, x)[0] + 180, 360);
        }
    }
    return hsv;
}
