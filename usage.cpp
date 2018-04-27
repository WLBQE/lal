#include <iostream>
#include <Eigen/Dense>
#include "include/dmatrix.hpp"
#include <array>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct RGB{
    RGB(){
        this->r = 0;
        this->g = 0;
        this->b = 0;
    }
    RGB(float color){
        this->r = color;
        this->g = color;
        this->b = color;
    }
    RGB(float r, float g, float b){
        this->r = r;
        this->g = g;
        this->b = b;
    }
    
    RGB& operator=(const RGB& rgb){
        this->r = rgb.r;
        this->g = rgb.g;
        this->b = rgb.b;
        return *this;
    }
    
    RGB& operator*(const float scale){
        this->r*=scale;
        this->g*=scale;
        this->b*=scale;
        return *this;
    }
    
    RGB& operator/(const float scale){
        this->r/=scale;
        this->g/=scale;
        this->b/=scale;
        return *this;
    }
    
    RGB& operator*=(const RGB &rgb){
        this->r*=rgb.r;
        this->g*=rgb.g;
        this->b*=rgb.b;
        return *this;
    }
    
    RGB& operator/=(const RGB &rgb){
        this->r/=rgb.r;
        this->g/=rgb.g;
        this->b/=rgb.b;
        return *this;
    }
    
    bool operator==(const RGB &rgb){
        return (this->r==r)&&(this->g==g)&&(this->b==b);
    }
    
    bool operator!=(const RGB &rgb){
        return (this->r!=r)&&(this->g!=g)&&(this->b!=b);
    }
    
    RGB& operator+(const RGB &rgb){
        this->r+=rgb.r;
        this->g+=rgb.g;
        this->b+=rgb.b;
        return *this;
    }
    
    RGB& operator+=(const RGB &rgb){
        this->r+=rgb.r;
        this->g+=rgb.g;
        this->b+=rgb.b;
        return *this;
    }
    
    float r;
    float g;
    float b;
};

//unsigned int width = 0;
//unsigned int height = 0;

/*
 lal::dynamic_matrix<RGB> loadImage(const string filename){
 
 ifstream fileReader;
 fileReader.open(filename);
 
 if(fileReader.fail()){
 throw("Can't open input file");
 }
 string format;
 fileReader>>format;
 if(format!="P6")
 throw("Format not supported yet :(");
 
 int scale = 0;
 fileReader>>width>>height>>scale;
 lal::dynamic_matrix<RGB> image(height, width, RGB());
 fileReader.ignore(256, '\n');
 unsigned char pixel[3];
 for(int i = 0; i < height; i++){
 for(int j = 0; j < width; j++){
 fileReader.read(reinterpret_cast<char *>(pixel),3);
 image[i][j].r = pixel[0]/255.0f;
 image[i][j].g = pixel[1]/255.0f;
 image[i][j].b = pixel[2]/255.0f;
 }
 }
 fileReader.close();
 return image;
 }
 */
lal::dynamic_matrix<RGB> loadImage(const string filename, int& _height, int& _width){
    
    ifstream fileReader;
    fileReader.open(filename);
    
    if(fileReader.fail()){
        throw("Can't open input file");
    }
    string format;
    fileReader>>format;
    if(format!="P6")
        throw("Format not supported yet :(");
    
    int scale = 0;
    fileReader>>_width>>_height>>scale;
    lal::dynamic_matrix<RGB> image(_height, _width, RGB());
    fileReader.ignore(256, '\n');
    unsigned char pixel[3];
    for(int i = 0; i < _height; i++){
        for(int j = 0; j < _width; j++){
            fileReader.read(reinterpret_cast<char *>(pixel),3);
            image[i][j].r = pixel[0]/255.0f;
            image[i][j].g = pixel[1]/255.0f;
            image[i][j].b = pixel[2]/255.0f;
        }
    }
    fileReader.close();
    return image;
}
/*
 void saveImage(const lal::dynamic_matrix<RGB> &image, const string filename){
 ofstream fileWriter;
 fileWriter.open(filename);
 if (fileWriter.fail())
 throw("Open file error");
 fileWriter<<"P6"<<endl<<width<<" "<<height<<endl<<"255"<<endl;
 unsigned char r,g,b;
 for(int i = 0; i<height; i++){
 for(int j = 0; j<width; j++){
 r = static_cast<unsigned char>(min(1.0f, image[i][j].r)*255);
 g = static_cast<unsigned char>(min(1.0f, image[i][j].g)*255);
 b = static_cast<unsigned char>(min(1.0f, image[i][j].b)*255);
 fileWriter<<r<<g<<b;
 }
 }
 fileWriter.close();
 }
 */
void saveImage(int h, int w, const lal::dynamic_matrix<RGB> &image, const string filename){
    ofstream fileWriter;
    fileWriter.open(filename);
    if (fileWriter.fail())
        throw("Open file error");
    fileWriter<<"P6"<<endl<<w<<" "<<h<<endl<<"255"<<endl;
    unsigned char r,g,b;
    for(int i = 0; i<h; i++){
        for(int j = 0; j<w; j++){
            r = static_cast<unsigned char>(min(1.0f, image[i][j].r)*255);
            g = static_cast<unsigned char>(min(1.0f, image[i][j].g)*255);
            b = static_cast<unsigned char>(min(1.0f, image[i][j].b)*255);
            fileWriter<<r<<g<<b;
        }
    }
    fileWriter.close();
}

lal::dynamic_matrix<RGB> adjustBrightness(lal::dynamic_matrix<RGB>& image, float brightness, int height, int width){
    lal::dynamic_matrix<RGB> output(image);
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            output[i][j]*=brightness;
        }
    }
    return output;
}

lal::dynamic_matrix<RGB> colorFilter(lal::dynamic_matrix<RGB> image, RGB filter, int height, int width){
    lal::dynamic_matrix<RGB> result(image);
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            result[i][j]*=filter;
        }
    }
    return result;
}

lal::dynamic_matrix<RGB> imageGenerator(string filename, int height, int width, int row_start, int row_end, int col_start, int col_end, RGB color){
    
    lal::dynamic_matrix<RGB> image(height, width, RGB());
    for(int i = row_start; i < row_end; i++){
        for(int j = col_start; j < col_end; j++){
            image[i][j] = color;
        }
    }
    saveImage(height, width, image, filename);
    return image;
}


lal::dynamic_matrix<RGB> rotateImageHelper(lal::dynamic_matrix<RGB> original, int height, int width){
    lal::dynamic_matrix<RGB> rotated(width, height, RGB());
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            rotated[j][height-1-i] = original[i][j];
        }
    }
    return rotated;
}

lal::dynamic_matrix<RGB> shiftImageHelper(lal::dynamic_matrix<RGB> original, int rowOffset, int colOffset, int height, int width){
    lal::dynamic_matrix<RGB> shifted(original);
    
    for(int j = 0; j < height; j++){
        for(int i = 0 ;i < width; i++){
            shifted[(j+colOffset)%height][(i+rowOffset)%width] = original[j][i];
        }
    }
    return shifted;
}

// TODO FIX SOME BUGS
lal::dynamic_matrix<RGB> blurFilter(lal::dynamic_matrix<RGB> original, int oh, int ow, lal::dynamic_matrix<RGB> mask, int mh, int mw){
    lal::dynamic_matrix<RGB> result(oh, ow, RGB());
    float brightness = 0;
    for(int j = 0; j < mw; j++){
        for(int i = 0; i <mh; i++){
            if(mask[i][j].r!=0 && mask[i][j].g!=0 && mask[i][j].b!=0){
                lal::dynamic_matrix<RGB> shifted =shiftImageHelper(original, j, i, oh, ow);
                for(int k = 0; k < oh; k++){
                    for(int p = 0; p < ow; p++){
                        shifted[k][p]*=mask[i][j];
                    }
                }
                for(int k = 0; k < oh; k++){
                    for(int p = 0; p < ow; p++){
                        result[k][p]+=shifted[k][p];
                    }
                }
                brightness+=(mask[i][j].r+mask[i][j].g+mask[i][j].b)/3.f;
            }
        }
    }
    for(int i = 0; i < oh; i++){
        for(int j = 0; j < ow; j++){
            result[i][j]/=brightness;
        }
    }
    return result;
}



lal::dynamic_matrix<RGB> verticalAppend(lal::dynamic_matrix<RGB> original, int height, int width){
    lal::dynamic_matrix<RGB> result(height, 2*width, RGB());
    for(int i = 0; i < height; i++){
        int j = 0;
        for(; j < width; j++){
            result[i][j] = original[i][j];
        }
        for(int k = 0; k < width; k++, j++){
            result[i][j] = original[i][k];
        }
    }
    return result;
}

void useCase4(){
    int oh = 0;
    int ow = 0;
    lal::dynamic_matrix<RGB> original = loadImage("cu7.ppm", oh, ow);
    //lal::dynamic_matrix<RGB> appended = verticalAppend(original, oh, ow);
    //lal::dynamic_matrix<RGB> appendeded = verticalAppend(original, oh, 2*ow);
    int mh = 0;
    int mw = 0;
    lal::dynamic_matrix<RGB> mask = loadImage("circle.ppm", mh, mw);
    lal::dynamic_matrix<RGB> result = blurFilter(original, oh, ow, mask, mh, mw);
    
    //saveImage(oh, 4*ow, appended, "cu_heart.ppm");
    
    saveImage(oh, ow, result, "cu_heart.ppm");
    
}



void useCase1(){
    lal::dynamic_matrix<RGB> left = imageGenerator("left.ppm",1024, 1024, int(1024*0.4), int(1024*0.8), int(1024*0.1), int(1024*0.5), RGB(1.f, 0.f, 0.f));
    
    lal::dynamic_matrix<RGB> right = imageGenerator("right.ppm",1024, 1024, int(1024*0.4), int(1024*0.8), int(1024*0.5), int(1024*0.9), RGB(0.f, 1.f, 0.f));
    
    lal::dynamic_matrix<RGB> top = imageGenerator("top.ppm",1024, 1024, int(1024*0.15), int(1024*0.55), int(1024*0.3), int(1024*0.7), RGB(0.f, 0.f, 1.f));
    
    lal::dynamic_matrix<RGB> outImage(left);
    
    for(int i = 0; i < 1024; i++){
        for(int j = 0; j < 1024; j++){
            outImage[i][j]+=right[i][j];
            outImage[i][j]+=top[i][j];
        }
    }
    saveImage(1024, 1024,outImage, "combine.ppm");
}

void useCase2(){
    int height = 0;
    int width = 0;
    lal::dynamic_matrix<RGB> output = loadImage("cu4.ppm", height, width);
    
    lal::dynamic_matrix<RGB> rotated = rotateImageHelper(output, height, width);
    
    saveImage(width, height, rotated, "cu4_90.ppm");
    
    lal::dynamic_matrix<RGB> rotated2 = rotateImageHelper(rotated, width, height);
    
    saveImage(height, width, rotated2, "cu4_180.ppm");
    
    lal::dynamic_matrix<RGB> rotated3 = rotateImageHelper(rotated2, height, width);
    
    saveImage(width, height, rotated3, "cu4_270.ppm");
    
}


void useCase3(){
    int height = 0;
    int width = 0;
    lal::dynamic_matrix<RGB> output = loadImage("shanghai.ppm", height, width);
    
    lal::dynamic_matrix<RGB> shifted1 = shiftImageHelper(output, 200, 0, height, width);
    
    saveImage(height, width, shifted1, "shifted_shanghai_200.ppm");
    
    lal::dynamic_matrix<RGB> shifted2 = shiftImageHelper(output, 400, 0, height, width);
    
    saveImage(height, width, shifted2, "shifted_shanghai_400.ppm");
    
    lal::dynamic_matrix<RGB> shifted3 = shiftImageHelper(output, 600, 0, height, width);
    
    saveImage(height, width, shifted3, "shifted_shanghai_600.ppm");
    
    lal::dynamic_matrix<RGB> shifted4 = shiftImageHelper(output, 800, 0, height, width);
    
    saveImage(height, width, shifted4, "shifted_shanghai_800.ppm");
    
}


void useCase5(){
    int height = 0;
    int width = 0;
    lal::dynamic_matrix<RGB> image = loadImage("columbia.ppm", height, width);
    
    lal::dynamic_matrix<RGB> brightness1 = adjustBrightness(image , 1.5, height, width);
    
    saveImage(height, width, brightness1, "columbia_brightness_1.5.ppm");
    
    
    lal::dynamic_matrix<RGB> brightness2 = adjustBrightness(image, 2.0, height, width);
    
    saveImage(height, width, brightness2, "columbia_brightness_2.0.ppm");
    
    lal::dynamic_matrix<RGB> brightness3 = adjustBrightness(image, 2.5, height, width);
    
    saveImage(height, width, brightness3, "columbia_brightness_2.5.ppm");
    
    lal::dynamic_matrix<RGB> brightness4 = adjustBrightness(image, 3.0, height, width);
    
    saveImage(height, width, brightness4, "columbia_brightness_3.0.ppm");
    
}


void useCase6(){
    int height = 0;
    int width = 0;
    lal::dynamic_matrix<RGB> image = loadImage("columbia.ppm", height, width);
    
    lal::dynamic_matrix<RGB> brightness1 = adjustBrightness(image , 0.8, height, width);
    
    saveImage(height, width, brightness1, "columbia_brightness_0.8.ppm");
    
    
    lal::dynamic_matrix<RGB> brightness2 = adjustBrightness(image, 0.6, height, width);
    
    saveImage(height, width, brightness2, "columbia_brightness_0.6.ppm");
    
    lal::dynamic_matrix<RGB> brightness3 = adjustBrightness(image, 0.4, height, width);
    
    saveImage(height, width, brightness3, "columbia_brightness_0.4.ppm");
    
    lal::dynamic_matrix<RGB> brightness4 = adjustBrightness(image, 0.1, height, width);
    
    saveImage(height, width, brightness4, "columbia_brightness_0.2.ppm");
    
}


void useCase7(){
    
    int height = 0;
    int width = 0;
    lal::dynamic_matrix<RGB> image = loadImage("cu6.ppm", height, width);
    
    lal::dynamic_matrix<RGB> redFilter = colorFilter(image, RGB(1,0,0), height, width);
    saveImage(height, width, redFilter, "cu6_red.ppm");
    
    lal::dynamic_matrix<RGB> blueFilter = colorFilter(image, RGB(0,1,0), height, width);
    saveImage(height, width, blueFilter, "cu6_blue.ppm");
    
    lal::dynamic_matrix<RGB> yellowFilter = colorFilter(image, RGB(0,0,1), height, width);
    saveImage(height, width, yellowFilter, "cu6_yellow.ppm");
    
}

void useCase8(){
    int oh = 0;
    int ow = 0;
    lal::dynamic_matrix<RGB> original = loadImage("ds.ppm", oh, ow);
    lal::dynamic_matrix<RGB> appended = verticalAppend(original, oh, ow);
    //lal::dynamic_matrix<RGB> appendeded = verticalAppend(original, oh, 2*ow);
    //int mh = 0;
    //int mw = 0;
    //lal::dynamic_matrix<RGB> mask = loadImage("circle.ppm", mh, mw);
    //lal::dynamic_matrix<RGB> result = blurFilter(original, oh, ow, mask, mh, mw);
    
    //saveImage(oh, 4*ow, appended, "cu_heart.ppm");
    
    saveImage(oh, 2*ow, appended, "ds_appended.ppm");
    
}


void useCase9(){
    int height = 0;
    int width = 0;
    lal::dynamic_matrix<RGB> image = loadImage("filtered.ppm", height, width);
    
    lal::dynamic_matrix<RGB> output = shiftImageHelper(image, width*0.6, 0, height, width);
    
    saveImage(height, width, output, "filtered_ouput.ppm");
    
}

int main() {
    
    //useCase1();
    
    //useCase2();
    
    //useCase3();
    
    // useCase4();
    
    //useCase5();
    
    //useCase6();
    
    //useCase7();
    //useCase8();
    //useCase9();
    return 0;
}

