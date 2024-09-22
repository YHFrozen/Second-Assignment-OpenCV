#include<iostream>
#include<opencv4/opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main(int argc,char** argv){
    Mat src=imread("/home/yhfrozen2/opencv_project/resources/test_image.png"); //读取图片
    Mat src_gray, src_hsv; //定义灰度图、HSV图
    Mat src_blur, src_gaussian;//定义滤波图，均质滤波、高斯滤波
    
    //颜色转换
    cvtColor(src,src_gray,COLOR_BGR2GRAY); //制作灰度图
    cvtColor(src,src_hsv,COLOR_BGR2HSV);//制作HSV图
    
    //滤波
    blur(src,src_blur,Size(9,9),Point(-1,-1));  //制作均质滤波
    GaussianBlur(src,src_gaussian,Size(9,9),0); //制作高斯滤波
    
    //提取红色区域
    Scalar lower_red1=Scalar(0,120,70);  //红色区域范围
    Scalar upper_red1=Scalar(10,255,255);
    Scalar lower_red2=Scalar(160,120,70);
    Scalar upper_red2=Scalar(180,255,255);

    Mat src_red1,src_red2;
    inRange(src_hsv,lower_red1,upper_red1,src_red1); //选取红色区域
    inRange(src_hsv,lower_red2,upper_red2,src_red2);
    Mat red_mask = src_red1 +src_red2;//红色mask
    Mat src_red;//红色区域
    bitwise_and(src,src,src_red,red_mask); //提取出红色区域，src与src按位与，即依旧是原图，满足mask条件，得到src_red
    GaussianBlur(src_red,src_red,Size(9,9),0); //高斯滤波去噪

    //轮廓绘制
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    Mat src_red_gray;
    cvtColor(src_red,src_red_gray,COLOR_BGR2GRAY); //根据src_red的灰度图寻找轮廓
    findContours(src_red_gray,contours,hierarchy,RETR_TREE,CHAIN_APPROX_NONE);  
    Mat src_draw=Mat::zeros(src.rows,src.cols,CV_8UC3);  //三通道，大小与src一致
    src_draw.setTo(Scalar(255,255,255));  //切换成黑色
    int index=0;
    for(;index>=0;index=hierarchy[index][0]){
        Scalar color(255,255,0);
        drawContours(src_draw,contours,index,color,10,8,hierarchy);
    }
    Mat src_draw_ori=Mat::zeros(src.rows,src.cols,CV_8UC3); //将轮廓绘制于原图src上
    bitwise_and(src,src_draw,src_draw_ori);  //src_draw的非轮廓部分为黑色1111111,按位与将保留src

    //绘制bonding box
    Mat src_bonding = src.clone();
    for (size_t i = 0; i < contours.size(); i++) {
        // 计算每个轮廓的最小外接矩形
        Rect boundingBox = boundingRect(contours[i]);
        // 绘制边界框，颜色为蓝色
        rectangle(src_bonding, boundingBox, Scalar(255, 0, 0), 2);
        //计算轮廓面积
        double area = contourArea(contours[i]); 
        // 输出面积
        cout << "轮廓 " << i << " 的面积: " << area << endl;
    }

    //二值化
    Mat src_binary=src.clone();
    threshold(src_gray,src_binary,100,255,THRESH_BINARY);

    //膨胀操作（扩展白色区域）
    Mat src_dilated;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(src_binary, src_dilated, kernel);

    //腐蚀操作（缩小白色区域）
    Mat src_eroded;
    erode(src_dilated, src_eroded, kernel);

    //漫水填充
    Mat src_flood = src_eroded.clone();
    floodFill(src_flood, Point(0, 0), Scalar(0,255,0));  // 从左上角(0, 0)进行漫水填充

    //绘制图形、文字
    Mat image = Mat::zeros(500, 500, CV_8UC3);
    Point center(100,100),lefttop(100,100),rightbottom(200,200);//圆点
    circle(image,center,100,Scalar(0,255,0),3);
    rectangle(image,lefttop,rightbottom,Scalar(0,255,0),3);
    string text = "Hello, OpenCV!";
    Point textOrigin(130, 480); // 文本左下角的坐标
    Scalar textColor(255, 255, 255); 
    putText(image, text, textOrigin, FONT_HERSHEY_SIMPLEX, 1.0, Scalar(222,122,255), 2);

    //图像旋转
    Point2f rotcent(src.cols/2.0,src.rows/2.0);
    Mat rotationMat=getRotationMatrix2D(rotcent,35.0,1.0);
    Mat src_rotate;
    warpAffine(src,src_rotate,rotationMat,src.size());

    //图像裁减
    Rect roi(0,0,src.cols/2.0,src.rows/2.0);
    Mat src_crop=src(roi);
    
    //窗口处理
    // namedWindow("input_ori",WINDOW_FREERATIO); //设置窗口为自定义大小
    // namedWindow("input_gray",WINDOW_FREERATIO);
    // namedWindow("input_HSV",WINDOW_FREERATIO);
    // namedWindow("input_blur",WINDOW_FREERATIO);
    // namedWindow("input_gaussian",WINDOW_FREERATIO);
    // namedWindow("input_red",WINDOW_FREERATIO);
    // namedWindow("input_draw",WINDOW_FREERATIO);
    // namedWindow("input_draw_ori",WINDOW_FREERATIO);
    // namedWindow("input_bonding",WINDOW_FREERATIO);
    // namedWindow("input_binary",WINDOW_FREERATIO);
    // namedWindow("input_dilated",WINDOW_FREERATIO);
    // namedWindow("input_eroded",WINDOW_FREERATIO);
    // namedWindow("input_flood",WINDOW_FREERATIO);
    // namedWindow("input_image",WINDOW_FREERATIO);
    // namedWindow("input_rotate",WINDOW_FREERATIO);
    // namedWindow("input_crop",WINDOW_FREERATIO);
    
    
    
    


    //图片输出
    // imshow("input_ori",src);
    // imshow("input_gray",src_gray);
    // imshow("input_HSV",src_hsv);
    // imshow("input_blur",src_blur);
    // imshow("input_gaussian",src_gaussian);
    // imshow("input_red",src_red);
    // imshow("input_draw",src_draw);
    // imshow("input_draw_ori",src_draw_ori);
    // imshow("input_bonding",src_bonding);
    // imshow("input_binary",src_binary);
    // imshow("input_dilated",src_dilated);
    // imshow("input_eroded",src_eroded);
    // imshow("input_flood",src_flood);
    // imshow("input_image",image);
    // imshow("input_rotate",src_rotate);
    // imshow("input_crop",src_crop);
    
    //图片保存
    imwrite("../resources/src_gray.png",src_gray);
    imwrite("../resources/src_hsv.png",src_hsv);
    imwrite("../resources/src_blur.png",src_blur);
    imwrite("../resources/src_gaussian.png",src_gaussian);
    imwrite("../resources/src_red.png",src_red);
    imwrite("../resources/src_draw.png",src_draw);
    imwrite("../resources/src_draw_ori.png",src_draw_ori);
    imwrite("../resources/src_bonding.png",src_bonding);
    imwrite("../resources/src_binary.png",src_binary);
    imwrite("../resources/src_dilated.png",src_dilated);
    imwrite("../resources/src_eroded.png",src_eroded);
    imwrite("../resources/src_flood.png",src_flood);
    imwrite("../resources/image.png",image);
    imwrite("../resources/src_rotate.png",src_rotate);
    imwrite("../resources/src_crop.png",src_crop);
    

    waitKey(0); //等待10秒关闭
    // destroyAllWindows();
    return 0;
}
