#include <poencv2/opencv.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace cv;
int main()
{
    VideCapture cap("../video.mp4")
    if(!cap.isOpened())
    {
        cout<<"视频无法打开"<<endl;
        return -1;

    }
    Mat frame;
    while(cap.read(frame))
    {
        Mat hsv;
        cvtColor(frame,hsv,COLOR_BGR2HSV);
        Mat mask1,mask2,red_mask;
        Scalar lower_red1=Scalar(0,120,70);
        Scalar upper_red1=Scalar(10,255,255);
        Scalar lower_red2=Scalar(170,120,70);
        Scalar upper_red2=Scalar(180,255,255);
        inRange(hsv,lower_red1,upper_red1,mask1);
        inRange(hsv,lower_red2,upper_red2,mask2);
        red_mask = mask1 | mask2;
        vector<vector<Point>>contours;
        vector<Vec4i>hierarchy;
        findContours(red_mask,contours,hierarchy,RETR_EXTERAL,CHAIN_APPROX_SIMPLE);
        vector<Rect> lightRects;
        for(int i = 0; i < contours.size(); i++)
        {
            double area = contourArea(contours[i]);
            if(area < 30)
            {
                continue;
            }
            Rect lightRect = boundingRect(contours[i]);
            rectangle(frame, lightRect, Scalar(0,255,255), 2);
            lightRects.push_back(lightRect);
        }

        if(lightRects.size() >= 2)
        {
            int minX = lightRects[0].x;
            int minY = lightRects[0].y;
            int maxX = lightRects[0].x + lightRects[0].width;
            int maxY = lightRects[0].y + lightRects[0].height;

            for(auto &r : lightRects)
            {
                minX = min(minX, r.x);
                minY = min(minY, r.y);
                maxX = max(maxX, r.x + r.width);
                maxY = max(maxY, r.y + r.height);
            }

            Rect armorBigRect(minX, minY, maxX - minX, maxY - minY);
            rectangle(frame, armorBigRect, Scalar(0,255,0), 2);
        }



    }
}