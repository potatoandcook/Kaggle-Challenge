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
        std::vector<uchar> pixels;
        int size = img.rows * img.cols;
        for (int j = 0; j < size; j++) {
            if (img.data[j]>0) {
                pixels.push_back(255);
            }
            else {
                pixels.push_back(0);
            }

        }
        std::cout << (int)img.data[2] << "FilePath: "<<file.path().string()<< std::endl;
        cv::Mat maskImg(img.rows,img.cols,CV_8UC1,(pixels.data()));
        return maskImg.clone();
    }


}

