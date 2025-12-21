#include <iostream>
#include <cmath>
#include <type_traits>
#include <stdexcept>

template <typename T>
class DynamicArray {
private:
    T* array;
    int size;

public:
    DynamicArray(int s) : size(s) {
        array = new T[size]{};
    }

    DynamicArray(const DynamicArray& other) : size(other.size) {
        array = new T[size];
        for (int i = 0; i < size; i++) {
            array[i] = other.array[i];
        }
    }

    ~DynamicArray() {
        delete[] array;
    }

    // Общий сеттер 
    void set_element(T data, int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        array[index] = data;
    }

    // Сеттер для числовых типов
    template<typename U = T>
    void set_numeric_element(U data, int index) {
        if constexpr (std::is_arithmetic_v<U>) {
            if (index < 0 || index >= size) {
                throw std::out_of_range("Index out of range");
            }
            array[index] = data;
        } else {
            throw std::bad_typeid();
        }
    }

    T get_element(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return array[index];
    }

    int get_size() const {
        return size;
    }

    // Вычисление евклидова расстояния
    template<typename U>
    double euclidean_distance(const DynamicArray<U>& other) const {
        if constexpr (!std::is_arithmetic_v<T> || !std::is_arithmetic_v<U>) {
            throw std::bad_typeid();
        } else {
            if (size != other.get_size()) {
                throw std::invalid_argument("Arrays must have same size");
            }
            
            double sum = 0.0;
            for (int i = 0; i < size; i++) {
                double diff = static_cast<double>(array[i]) - static_cast<double>(other.get_element(i));
                sum += diff * diff;
            }
            
            return std::sqrt(sum);
        }
    }

    // Перегрузка <<
    friend std::ostream& operator<<(std::ostream& os, const DynamicArray& obj) {
        for (int i = 0; i < obj.size; i++) {
            os << obj.array[i];
            if (i != obj.size - 1) {
                os << " ";
            }
        }
        return os;
    }
};

