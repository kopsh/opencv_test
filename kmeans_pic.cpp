#include "opencv2/opencv.hpp"
#include <iostream>
#include <locale>
using namespace std;
using namespace cv;

int main()
{
    //1. 把图像转换为数据集
    Mat img = imread("messi.jpeg", 1);
    Mat samples = img.reshape(0, img.cols * img.rows);

    //转换为samplCount行 * 3通道的矩阵
    printf("image: h=%d, w=%d, c=%d", img.rows, img.cols, img.channels());
    samples.convertTo(samples, CV_32FC3);
    printf(": h=%d, w=%d, c=%d", samples.rows, samples.cols, samples.channels());

    //2. 聚类
    TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.0);
    int K = 2; // 聚类类别数 4, 8, 16
    Mat labels; // 聚类结果索引矩阵3
    Mat centers; // 聚类中心
    double compactness = kmeans(samples, K, labels, criteria, 3, KMEANS_PP_CENTERS, centers);

    //3. 按聚类结果重新为图像赋值
    //将数据转为CV_8UC3型，以便恢复图像
    centers.convertTo(centers, CV_8UC3);
    samples.convertTo(samples, CV_8UC3);

    //按label标签重新为samples赋值，实现色彩压缩
    for (int i=0; i < labels.rows; i++)
    {
        int cluster = labels.at<int>(i);
        //Vec3b为OpenCV中CV_8UC3类型的RGB彩色图像数据类型
        samples.at<Vec3b>(i, 0) = centers.at<Vec3b>(cluster, 0);
    }

    //4. 输出或显示聚类结果
    //将sample转为img尺寸
    Mat img_out = samples.reshape(0, img.rows);
    //将图像转换为sampleCount行*3通道的矩阵
    cout << "Compactness: " << compactness << endl;
    imshow("image", img);
    imshow("clusters", img_out);

    stringstream ss;
    ss << K;
    string str = ss.str();
    string image_save_name = str + "_cluster.jpg";
    imwrite(image_save_name, img_out);
    waitKey();
    return 0;
}