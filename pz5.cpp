#include <iostream>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>

class DynamicArr {
protected:
    int* data;
    size_t size;
    
public:
    DynamicArr(size_t arrSize) {
        size = arrSize;  
        data = new int[size]();
    }

    DynamicArr(const DynamicArr& other) {
        size = other.size;
        data = new int[size];
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    virtual ~DynamicArr() {
        delete[] data;
    }

    void PrintArr() const {
        for (size_t i = 0; i < size; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    bool SetCheckValue(size_t index, int value) {
        if (index >= size) {
            std::cerr << "Индекс выходит за границы массива!";
            return false;
        }

        if (value < -100 || value > 100) {
            std::cerr << "Значение должно быть в диапазоне [-100,100]";
            return false;
        }

        data[index] = value;
        return true;
    }

    size_t getSize() const {
        return size;
    }

    bool GetCheckValue(size_t index, int& result) const {
        if (index >= size) {
            std::cerr << "Индекс выходит за границы массива!";
            return false;
        }

        result = data[index];
        return true;
    }

    bool AddValue(int value) {
        if (value < -100 || value > 100) {
            std::cerr << "Добавляемое значение должно быть в диапазоне [-100,100]";
            return false;
        }
        
        int* newData = new int[size + 1];
        
        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        
        newData[size] = value;
        size++;
    
        delete[] data;
        data = newData;
        
        return true;
    }
         
    void AddArr(const DynamicArr& other) {
        size_t minSize = std::min(size, other.size);
        
        for (size_t i = 0; i < minSize; i++) {
            int newValue = data[i] + other.data[i];
            data[i] = newValue;
        }
    }

    void SubtractArr(const DynamicArr& other) {
        size_t minSize = std::min(size, other.size);
        
        for (size_t i = 0; i < minSize; i++) {
            int newValue = data[i] - other.data[i];
            data[i] = newValue;
        }
    }
};

class ArrTxt : public DynamicArr {
public:
    ArrTxt(size_t arrSize) : DynamicArr(arrSize) {}
    ArrTxt(const DynamicArr& other) : DynamicArr(other) {}

    void PrintToFile() const {
        std::string filename = getCurrentDateTime() + ".txt";
        std::ofstream file(filename);
        
        if (!file.is_open()) {
            std::cerr << "Не удалось создать файл: " << filename << std::endl;
            return;
        }

        for (size_t i = 0; i < size; i++) {
            file << data[i] << " ";
        }
        file << std::endl;
        file.close();
        std::cout << "Данные записаны в файл: " << filename << std::endl;
    }

private:
    std::string getCurrentDateTime() const {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&time);
        
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S");
        return oss.str();
    }
};

class ArrCSV : public DynamicArr {
public:
    ArrCSV(size_t arrSize) : DynamicArr(arrSize) {}
    ArrCSV(const DynamicArr& other) : DynamicArr(other) {}

    void PrintToFile() const {
        std::string filename = getCurrentDateTime() + ".csv";
        std::ofstream file(filename);
        
        if (!file.is_open()) {
            std::cerr << "Не удалось создать файл: " << filename << std::endl;
            return;
        }

        for (size_t i = 0; i < size; i++) {
            file << data[i];
            if (i != size - 1) file << ",";
        }
        file << std::endl;
        file.close();
        std::cout << "Данные записаны в файл: " << filename << std::endl;
    }

private:
    std::string getCurrentDateTime() const {
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&time);
        
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S");
        return oss.str();
    }
};
