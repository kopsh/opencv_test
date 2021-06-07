#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
    const int MAX_CLUSTERS = 5; // 最大类别数
    Scalar colorTab[] = {
        // 绘图颜色组
        Scalar(0, 0, 255),
        Scalar(0, 255, 0),
        Scalar(255, 100, 100),
        Scalar(255, 0, 255),
        Scalar(0, 255, 255),
    };

    Mat img(500, 500, CV_8UC3); // 新建画布
    img = Scalar::all(255);     // 将画布置为白色
    RNG rng((unsigned)time(NULL));

    // 主循环
    for (;;)
    {
        // 初始化类别数
        int k, clusterCount = rng.uniform(2, MAX_CLUSTERS + 1);
        // 在指定区间，随机生成一个整数
        // 初始化样本数
        int i, sampleCount = rng.uniform(1, 1001);
        // cout << "sampleCount: " << sampleCount << endl;
        Mat points(sampleCount, 1, CV_32FC2);          // sampleCount行 * 1列，浮点型，2通道
        Mat labels;                                    // 聚类结果索引矩阵
        clusterCount = MIN(clusterCount, sampleCount); // 聚类类别数 < 样本数
        std::vector<Point2f> centers;

        //2. 随机生成多高斯分布的样本
        for (k = 0; k < clusterCount; k++)
        {
            Point center;
            center.x = rng.uniform(0, img.cols);
            center.y = rng.uniform(0, img.rows);

            cout << "x: " << center.x << endl;
            cout << "y: " << center.y << endl;
            // 对样本指定行进行赋值
            Mat pointChunk = points.rowRange(k * sampleCount / clusterCount,
                                             k == clusterCount - 1 ? sampleCount : (k + 1) * sampleCount / clusterCount);

            // 以center为中心，产生高斯分布的随机点
            // RNG::NORMAL，高斯分布，参数3为均值，参数4为方差
            // 并把坐标保存在pointChunk中
            rng.fill(pointChunk,
                     RNG::NORMAL,
                     Scalar(center.x, center.y),
                     Scalar(img.cols * 0.05, img.rows * 0.05));
        }

        // 打乱points中的值
        randShuffle(points, 1, &rng);

        // 3. 执行kmeans
        double compactness = kmeans(points, clusterCount, labels,
                                    TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.0),
                                    3, KMEANS_PP_CENTERS, centers);

        // 4. 绘制或输出聚类结果
        for (i = 0; i < sampleCount; i++)
        {
            int clusterIdx = labels.at<int>(i);
            Point ipt = points.at<Point2f>(i);
            circle(img, ipt, 2, colorTab[clusterIdx], FILLED, LINE_AA);
        }

        for (i = 0; i < (int)centers.size(); i++)
        {
            Point2f c = centers[i];
            circle(img, c, 40, colorTab[i], 1, LINE_AA);
        }

        cout << "Compactness: " << compactness << endl;
        imshow("clusters", img);
        char key = (char)waitKey();
        if (key == 27 || key == 'q' || key == 'Q')
            break;
    }
    return 0;
}