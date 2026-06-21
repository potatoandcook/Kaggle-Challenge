#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <vector>
#include "create.h"
namespace fs = std::filesystem;


// Paste all file directories into here
const fs::path apoImgP = "/mnt/c/Kaggle/umud-challenge-muscle-architecture-in-ultrasound-data/apo_imgs_v1/apo_images_new_model_v1";
const fs::path apoMskP = "/mnt/c/kaggle/umud-challenge-muscle-architecture-in-ultrasound-data/apo_masks_v1/apo_masks_new_model_v1";
const fs::path fasImgP = "/mnt/c/Kaggle/umud-challenge-muscle-architecture-in-ultrasound-data/fasc_imgs_v1/fasc_images_new_model_v1";
const fs::path fasMskP = "/mnt/c/Kaggle/umud-challenge-muscle-architecture-in-ultrasound-data/fasc_masks_v1/fasc_masks_new_model_v1";


enum class DataType {
    Apo,
    Fas
};
struct Combine {
    DataType Type;
    fs::path ImgP;
    fs::path MskP;
};


// Vector of objects that are the type directory_entry
std::vector<fs::directory_entry> obj_apoImg;
std::vector<fs::directory_entry> obj_apoMsk;
std::vector<fs::directory_entry> obj_fasImg;
std::vector<fs::directory_entry> obj_fasMsk;
std::vector<Combine> allFiles;


void setVec(std::vector<fs::directory_entry> &files, const fs::path &path) {
    for (const auto &file : fs::directory_iterator(path)) {
        if (file.path().extension() == ".db") {
    //        std::cout << file.path().extension().string() << std::endl;
            continue;
        }
        files.push_back(file);
    }
    std::sort(files.begin(), files.end(),  [](const auto &a,const auto &b) {
        return a.path().filename() < b.path().filename();
    });
}

void mkStruct(std::vector<fs::directory_entry> &image, std::vector<fs::directory_entry> &mask, DataType type) {
    for (size_t i = 0; i < image.size(); i++) {
        Combine combine;
        combine.Type = type;
        combine.ImgP = image[i].path();
        combine.MskP = mask[i].path();
        //combine.Img = cv::imread(image[i].path().string(), cv::IMREAD_UNCHANGED);
        //combine.Msk = cv::imread(mask[i].path().string(), cv::IMREAD_UNCHANGED);
        allFiles.push_back(combine);
    }
}

int main() {


    setVec(obj_apoImg, apoImgP);
    setVec(obj_apoMsk, apoMskP);
    setVec(obj_fasImg, fasImgP);
    setVec(obj_fasMsk, fasMskP);
    //std::cout << obj_apoImg.size() << std::endl;
    //std::cout << obj_apoMsk.size() << std::endl;
    //std::cout << obj_fasImg.size() << std::endl;
    //std::cout << obj_fasMsk.size() << std::endl;

    mkStruct(obj_apoImg, obj_apoMsk, DataType::Apo);
    mkStruct(obj_fasImg, obj_fasMsk, DataType::Fas);
/*
for (const auto &file : allFiles) {
        cv::Mat img = cv::imread(file.ImgP.string(), cv::IMREAD_GRAYSCALE);
        cv::Mat msk = cv::imread(file.MskP.string(), cv::IMREAD_GRAYSCALE);
        cv::Mat modO, modC;
        if (img.size() != msk.size()) {
            cv::resize(msk, msk, img.size(), 0, 0, cv::INTER_NEAREST);
        }
        //cv::addWeighted(img, 0.5, msk, 0.5, 0, modC);
        cv::add(img, msk, modC);
        std::cout << file.ImgP << std::endl;

        if (file.Type == DataType::Apo) {
            cv::imwrite(("/mnt/c/outImg/apo/" + file.ImgP.filename().string()), modC);
        }
        else {
            cv::imwrite(("/mnt/c/outImg/fas/" + file.ImgP.filename().string()), modC);

        }
        } */


    cv::imwrite(("/mnt/c/outImg/test/img5.tif"), newMask(apoImgP));

    }