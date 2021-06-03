#include "stdfix.h"
#include "opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;


int main() {
    const int MAX_CLUSTERS = 5; // 最大类别数
    Scalar colorTab[] = { // 绘图颜色组
        Scalar(0, 0, 255),
        Scalar(0, 255, 0),
        Scalar(255, 100, 100),
        Scalar(255, 0, 255),
        Scalar(0, 255, 255),
    };

    Mat img(500, 500, CV_8UC3); // 新建画布
    img = Scalar::all(255); // 将画布置为白色
    RNG rng(12345);

    // 主循环
    for(;;) {
        
    }
}