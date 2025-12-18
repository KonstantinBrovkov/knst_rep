#include <iostream>
#include <algorithm>
#include <stdexcept>

class DynamicArr {
protected:
    int* data;
    size_t size;

    void checkIndex(size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Индекс выходит за границы массива!");
        }
    }

    void checkValue(int value) const {
        if (value < -100 || value > 100) {
            throw std::invalid_argument("Значение должно быть в диапазоне [-100, 100]");
        }
    }

public:
    DynamicArr(size_t arrSize) {
        size = arrSize;  
        data = new int[size];
    }

    DynamicArr(const DynamicArr& other) {
        size = other.size;
        data = new int[size];
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    ~DynamicArr() {
        delete[] data;
    }

    void PrintArr() const {
        for (size_t i = 0; i < size; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    void SetValue(size_t index, int value) {
        checkIndex(index);
        checkValue(value);
        data[index] = value;
    }

    size_t getSize() const {
        return size;
    }

    int GetValue(size_t index) const {
        checkIndex(index);
        return data[index];
    }

    void AddValue(int value) {
        checkValue(value);
        
        int* newData = new int[size + 1];
        
        for (size_t i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        
        newData[size] = value;
        size++;
    
        delete[] data;
        data = newData;
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

