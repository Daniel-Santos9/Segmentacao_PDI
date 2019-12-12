#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int encontraPP(Mat src){
    int preto=0;
    for(int i =0; i<src.rows;i++){
        for(int j=0; j<src.cols;j++){
            if(src.at<uchar>(i,j) == 0)
                preto++;
        }
    }
    return preto;
}
Mat contraste(Mat src, float c){
    Mat dst = src.clone();
   // float f = (259 * (c + 255)) / (255*(259-c));
    for(int i=0; i<src.rows;i++){
        for(int j=0; j<src.cols;j++){
            dst.at<uchar>(i,j) = uint(128*(double(src.at<uchar>(i,j))-128)+128);
        }
    }
    return dst;
}
Mat umParaTres(Mat src){
    //Mat dst(src.rows, src.cols, Vec3b)
    Mat dst(src.rows,src.cols, DataType<Vec3b>::type);
    for(int i=0; i<src.rows;i++){
        for(int j=0; j<src.cols;j++){
                dst.at<Vec3b>(i,j)[0] = src.at<uchar>(i,j);
                dst.at<Vec3b>(i,j)[1] = src.at<uchar>(i,j);
                dst.at<Vec3b>(i,j)[2] = src.at<uchar>(i,j);
        }
    }
    return dst;
}

Mat umParaTresVermelho(Mat src){
    //Mat dst(src.rows, src.cols, Vec3b)
    Mat dst(src.rows,src.cols, DataType<Vec3b>::type);
    for(int i=0; i<src.rows;i++){
        for(int j=0; j<src.cols;j++){
            if(src.at<uchar>(i,j) == 0){
                dst.at<Vec3b>(i,j)[0] = src.at<uchar>(i,j);
                dst.at<Vec3b>(i,j)[1] = src.at<uchar>(i,j);
                dst.at<Vec3b>(i,j)[2] = src.at<uchar>(i,j);
            }else{
                dst.at<Vec3b>(i,j)[0] = 0;
                dst.at<Vec3b>(i,j)[1] = 0;
                dst.at<Vec3b>(i,j)[2] = 255;
            }
        }
    }
    return dst;
}

int main(){
     Mat img,dst;
     img = imread("codorna10.jpeg",0);
     if(img.empty())
       cout<<"imagem não encontrada";
     medianBlur(img,dst,9);
//        dst = contraste(dst,10);
     threshold(dst,dst,95,255,THRESH_BINARY);
     int ele_tam=1;
     Mat elemento = getStructuringElement(MORPH_RECT, Size(ele_tam+2, ele_tam+3), Point(ele_tam, ele_tam));
     dilate(dst, dst, elemento);
     erode(dst, dst, elemento);
     dilate(dst, dst, elemento);
     erode(dst, dst, elemento);
     medianBlur(dst,dst,9);
     medianBlur(dst,dst,9);
     medianBlur(dst,dst,9);
     medianBlur(dst,dst,3);
     Canny(dst,dst,200,100);
     Mat resulOriginal = umParaTres(img);
     Mat resulContorno = umParaTresVermelho(dst);

     Mat resulFinal = resulOriginal + resulContorno;
     //Mat resul = img + resultado;
     int preto = encontraPP(dst);

     //Sobel(dst, dst,CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);
     namedWindow("segmentado");
     namedWindow("Codorna");
     namedWindow("Circulado");
     imshow("Codorna", resulOriginal);
     imshow("segmentado",resulContorno);
     imshow("Circulado",resulFinal);
     waitKey(0);
     destroyWindow("Codorna");
     destroyWindow("segmentado");
     destroyWindow("Circulado");

    return 0;
}
