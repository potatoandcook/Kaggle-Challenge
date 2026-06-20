#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

const fs::path apoImgP = "/mnt/c/Kaggle/umud-challenge-muscle-architecture-in-ultrasound-data/apo_imgs_v1/apo_images_new_model_v1";
const fs::path apoMskP = "/mnt/c/kaggle/umud-challenge-muscle-architecture-in-ultrasound-data/apo_masks_v1/apo_masks_new_model_v1";
const fs::path fasImgP = "/mnt/c/Kaggle/umud-challenge-muscle-architecture-in-ultrasound-data/fasc_imgs_v1/fasc_images_new_model_v1";
const fs::path fasMskP = "/mnt/c/Kaggle/umud-challenge-muscle-architecture-in-ultrasound-data/fasc_masks_v1/fasc_masks_new_model_v1";

cv::Mat newMask(const fs::path &path)
{
    for (const fs::directory_entry &file: fs::directory_iterator(path)) {
        cv::Mat img = cv::imread(file.path().string(), cv::IMREAD_GRAYSCALE);
        int size = img.rows * img.cols;
        std::vector<uchar> pixels (size,0);
        for (int j = 0; j < size; j++) {
            if (img.data[j]>35) {
                int cRow = j/img.rows;
                int cCol = j%img.cols;
                int allP[8];
                uchar pixelC = img.data[j];

                //Start from top left
                allP[0] = (cRow-1) *img.cols + (cCol-1) ;
                allP[1] = (cRow-1) * img.cols + (cCol);
                allP[2] = (cRow-1) *img.cols + (cCol+1);
                allP[3] = (cRow) * img.cols + (cCol+1);
                allP[4] = (cRow+1) *img.cols + (cCol+1);
                allP[5]= (cRow+1) * img.cols + (cCol);
                allP[6] = (cRow+1) *img.cols + (cCol-1);
                allP[7] = (cRow) * img.cols + (cCol-1);






                uchar uLP = img.data[uL];
                uchar uP = img.data[u];
                uchar uRP = img.data[uR];
                uchar bRP = img.data[bR];
                uchar dP = img.data[d];
                uchar lP = img.data[l];
                uchar rP = img.data[r];
                uchar bLP = img.data[bL];

                // Spahgeti code
                uchar avgP = (uLP + uRP + bRP + dP + lP + rP + uP + bLP)/8;
                if (((pixelC <= avgP) && (pixelC >= (avgP-20)))||((pixelC >= avgP) && (pixelC <= (avgP+20)))) {
                    pixels[j]=(255);
                }
                else {
                    continue;
                }
            }
        }
        std::cout << (int)img.data[2] << "FilePath: "<<file.path().string()<< std::endl;
        cv::Mat maskImg(img.rows,img.cols,CV_8UC1,(pixels.data()));
        return maskImg.clone();
    }
}

