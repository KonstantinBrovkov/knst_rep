#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

struct Image {
    int width;
    int height;
    vector<vector<int>> pixels;
};

bool readPGM(const string& filename, Image& img) {
    ifstream file(filename);
    if (!file) {
        cout << "Cannot open file: " << filename << endl;
        return false;
    }

    string format;
    file >> format;
    if (format != "P2") {
        cout << "Invalid format " << format << endl;
        return false;
    }

    file >> img.width >> img.height;
    int maxVal;
    file >> maxVal;

    img.pixels.resize(img.height, vector<int>(img.width));

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            if (!(file >> img.pixels[y][x])) {
                cout << "Error reading pixel data" << endl;
                return false;
            }
        }
    }
    file.close();
    return true;
}

bool writePGM(const string& filename, const Image& img) {
    ofstream file(filename);
    if (!file) return false;
    file << "P2\n" << img.width << " " << img.height << "\n255\n";
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            file << img.pixels[y][x] << " ";
        }
        file << "\n";
    }

    file.close();
    return true;
}

void addNoise(Image& img, float noiseLevel) {
    int totalPixels = img.width * img.height;
    int noisePixels = static_cast<int>(totalPixels * noiseLevel);
    for (int i = 0; i < noisePixels; i++) {
        int x = rand() % img.width;
        int y = rand() % img.height;
        img.pixels[y][x] = (rand() % 2) * 255;
    }
}

void medianFilter(const Image& src, Image& dst, int filterSize) {
    int offset = filterSize / 2;
    
    dst.width = src.width;
    dst.height = src.height;
    dst.pixels = src.pixels;
    
    for (int y = offset; y < src.height - offset; y++) {
        for (int x = offset; x < src.width - offset; x++) {
            vector<int> values;
            values.reserve(filterSize * filterSize);
            
            for (int ky = -offset; ky <= offset; ky++) {
                for (int kx = -offset; kx <= offset; kx++) {
                    values.push_back(src.pixels[y + ky][x + kx]);
                }
            }
            sort(values.begin(), values.end());
            dst.pixels[y][x] = values[values.size() / 2];
        }
    }
}

double compareImages(const Image& img1, const Image& img2) {
    int matched = 0;
    int total = img1.width * img1.height;
    
    for (int y = 0; y < img1.height; y++) {
        for (int x = 0; x < img1.width; x++) {
            if (img1.pixels[y][x] == img2.pixels[y][x]) {
                matched++;
            }
        }
    }
    return (static_cast<double>(matched) / total) * 100.0;
}

int main() { 
    srand(static_cast<unsigned int>(time(nullptr)));
    
    Image original;
    if (!readPGM("dog.pgm", original)) {
        cout << "Error: Cannot load 'dog.pgm' << endl";
        return 1;
    }
    
    cout << "Image loaded successfully: " << original.width << "x" << original.height << endl;
    
    // Разные уровни шума
    float noiseLevels[] = {0.05f, 0.1f, 0.2f}; // 5%, 10%, 20% шума
    
    for (int i = 0; i < 3; i++) {
        float noiseLevel = noiseLevels[i];
        cout << "\nTesting with " << (int)(noiseLevel * 100) << "% noise" << endl;
        
        Image noisy = original;
        addNoise(noisy, noiseLevel);
        
        // Создание зашумленного файла
        stringstream noisyName;
        noisyName << "dog_noisy_" << (int)(noiseLevel * 100) << "percent.pgm";
        writePGM(noisyName.str(), noisy);
        cout << "Created: " << noisyName.str() << endl;
        
        // Разные фильтры
        int filterSizes[] = {3, 5, 7};
        
        for (int j = 0; j < 3; j++) {
            int filterSize = filterSizes[j];
            Image filtered;
            medianFilter(noisy, filtered, filterSize);
            
            // Создание файла отфильтрованного изображения
            stringstream filteredName;
            filteredName << "dog_filtered_" << (int)(noiseLevel * 100) << "percent_" << filterSize << "x" << filterSize << ".pgm";
            writePGM(filteredName.str(), filtered);
            
            double similarity = compareImages(original, filtered);
            cout << "Filter " << filterSize << "x" << filterSize 
                 << " Similarity: " << similarity << "%" << endl;
        }
    }
    
    return 0;
}