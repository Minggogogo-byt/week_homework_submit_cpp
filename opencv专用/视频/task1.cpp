#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main ()
{   
    string path="../text.png";
    Mat img = path;
    Mat hsv;
    cvtColor(img,hsv,COLOR_BGR21HSV);
    vector<Mat> channels;
    split(hsv,channels);
    Mat H =channels[0];
    Mat S =channels[1];
    Mat V =channels[2];
    imshow("通道H",H);
    imshow("通道S",S);
    imshow("通道V",V);
    Mat mask1,mask2,red_mask;
    Scalar lower_red1 = Scalar(0,120,70);
    Scalar upper_red1 = Scalar(10,255,255);
    Scalar lower_red2 = Scalar(170,120,70);
    Scalar upper_red2 = Scalar(180,255,255);
    inRange(hsv,lower_red1,upper_red1,mask1);
    inRange(hsv,lower_red2,upper_red2,mask2);
    red_mask = mask1 | mask2;
    imshow("红色掩",red_mask);
    imwrite("red_mask.png",red_mask);
    waitKey(0);
    destroyAllWindows();
    return 0;

}
