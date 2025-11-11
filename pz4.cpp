#include <iostream>
#include <algorithm>

class DynamicArr {
protected:
    int* data;
    size_t size;
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

// --------------------------------------------------------------------------------

class DynamicArrNasled : public DynamicArr {
public:   
    DynamicArrNasled(size_t size) : DynamicArr(size) {}                               
    DynamicArrNasled(const DynamicArr& other) : DynamicArr(other) {}                    
  
    
    double average() const {
        if (size == 0) {
            std::cerr << "Массив пустой\n";
            return 0.0;
        }
        
        double sum = 0.0;
        for (size_t i = 0; i < size; i++) {
            sum += data[i];  
        }
        return sum / size;
    }

    
    double median() {
        if (size == 0) {
            std::cerr << "Массив пустой\n";
            return 0.0;
        }
        
        int* temp = new int[size];
        for (size_t i = 0; i < size; i++) {
            temp[i] = data[i];
        }
        
        std::sort(temp, temp + size);
        
        double result;
        if (size % 2 == 0) {
            result = (temp[size/2 - 1] + temp[size/2]) / 2.0;
        } else {
            result = temp[size/2];
        }
        
        delete[] temp;
        return result;
    }

    int min() const {
        if (size == 0) {
            std::cerr << "Массив пустой\n";
            return 0;
        }
        
        int minVal = data[0];  
        for (size_t i = 1; i < size; i++) {
            if (data[i] < minVal) {
                minVal = data[i];
            }
        }
        return minVal;
    }

    int max() const {
        if (size == 0) {
            std::cerr << "Массив пустой\n";
            return 0;
        }
        
        int maxVal = data[0];  
        for (size_t i = 1; i < size; i++) {
            if (data[i] > maxVal) {
                maxVal = data[i];
            }
        }
        return maxVal;
    }
};