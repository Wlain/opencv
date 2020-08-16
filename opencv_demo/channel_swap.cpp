//
//  channel_swap.cpp
//  opencv_demo
//
//  Created by william on 2020/8/16.
//  Copyright © 2020 william. All rights reserved.
//
/*
 问题一：通道交换
 读取图像，然后将text{RGB}通道替换成text{BGR}通道
 下面代码用于提取图像的红色通道。
 注意,cv2.imread()的系数是按照text{BGR}的顺序排列的
 其中的变量red表示的是仅有原图像红色通道的图像
 */

#include "base.h"

cv::Mat channel_swap(cv::Mat img)
{
    // get height and width
    int width = img.cols;
    int height = img.rows;
    
    // prepare output
    cv::Mat out = cv::Mat::zeros(height, width, CV_8UC3);
    
    // each y, x
    for(int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // R -> B
            out.at<cv::Vec3b>(y, x)[0] = img.at<cv::Vec3b>(y, x)[2];
            // B -> R
            out.at<cv::Vec3b>(y, x)[2] = img.at<cv::Vec3b>(y, x)[0];
            // G -> B
            out.at<cv::Vec3b>(y, x)[1] = img.at<cv::Vec3b>(y, x)[1];
        }
    }
    return out;
}



