#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

const fs::path apoImgP = "/mnt/c/Kaggle/umud-challenge-muscle-architecture-in-ultrasound-data/apo_imgs_v1/apo_images_new_model_v1";
const fs::path apoMskP = "/mnt/c/kaggle/umud-challenge-muscle-architecture-in-ultrasound-data/apo_masks_v1/apo_masks_new_model_v1";
const fs::path fasImgP = "/mnt/c/Kaggle/umud-challenge-muscle-architecture-in-ultrasound-data/fasc_imgs_v1/fasc_images_new_model_v1";
const fs::path fasMskP = "/mnt/c/Kaggle/umud-challenge-muscle-architecture-in-ultrasound-data/fasc_masks_v1/fasc_masks_new_model_v1";

auto loadFile(const fs::path &path)
{
    for (const fs::directory_entry &file: fs::directory_iterator(path)) {
        cv::Mat img = cv::imread(file.path().string(), cv::IMREAD_COLOR);

    }
}