#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <chrono>

// Класс для измерения времени выполнения функций
class TimeMeter {
private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;
    
public:
    void start() {
        start_time = std::chrono::high_resolution_clock::now();
    }
    
    void stop() {
        end_time = std::chrono::high_resolution_clock::now();
    }
    
    double get_elapsed_time() const {
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        return duration.count() / 1000.0; // возвращаем время в миллисекундах
    }
};

// Функция для измерения времени выполнения любой функции
template<typename Func, typename... Args>
double measure_time(Func func, Args&&... args) {
    TimeMeter meter;
    meter.start();
    func(std::forward<Args>(args)...); // вызываем переданную функцию
    meter.stop();
    return meter.get_elapsed_time();
}

// Примеры функций для тестирования
int multiply(int a, int b) {
    // Имитация некоторой работы
    std::vector<int> temp(1000, a);
    int result = 0;
    for (int i = 0; i < 1000; ++i) {
        result += temp[i] * b;
    }
    return result / 1000;
}

double power(double base, int exponent) {
    double result = 1.0;
    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }
    return result;
}

void print_vector(const std::vector<int>& vec, const std::string& name) {
    std::cout << name << ": ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i != vec.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
}

int main() {
    // Часть 1: Измерение времени выполнения функций
    
    // Тестирование с лямбда-функцией
    auto lambda_func = [](int x, int y) -> int {
        int sum = 0;
        for (int i = 0; i < 1000; ++i) {
            sum += x * y + i;
        }
        return sum;
    };
    
    double lambda_time = measure_time(lambda_func, 5, 3);
    std::cout << "Время выполнения лямбда-функции: " << lambda_time << " мс" << std::endl;
    
    // Тестирование с std::bind
    auto bound_func = std::bind(multiply, 10, std::placeholders::_1);
    double bind_time = measure_time(bound_func, 7);
    std::cout << "Время выполнения функции с std::bind: " << bind_time << " мс" << std::endl;
    
    // Тестирование с обычной функцией
    double func_time = measure_time(power, 2.0, 10);
    std::cout << "Время выполнения обычной функции: " << func_time << " мс" << std::endl;
    
    std::cout << std::endl;
    
    // Часть 2: Использование std::bind, std::multiplies и std::transform
    // для возведения в степень всех чисел в векторе
    
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::vector<int> result(numbers.size());
    int exponent = 3; // степень
    
    std::cout << "Возведение чисел в степень " << exponent << ":" << std::endl;
    print_vector(numbers, "Исходный вектор");
    
    // Создаем функтор для возведения в степень с помощью std::bind и std::multiplies
    auto power_func = std::bind(std::multiplies<int>(), 
                               std::placeholders::_1, 
                               std::placeholders::_1);
    
    // Применяем функтор несколько раз для возведения в нужную степень
    std::vector<int> temp = numbers;
    for (int i = 1; i < exponent; ++i) {
        std::transform(temp.begin(), temp.end(), 
                      numbers.begin(), temp.begin(), 
                      std::multiplies<int>());
    }
    result = temp;
    
    print_vector(result, "Результат");
    
    // Альтернативный способ с использованием лямбда-функции
    std::vector<int> result2(numbers.size());
    std::transform(numbers.begin(), numbers.end(), result2.begin(),
                  [exponent](int x) {
                      int result = 1;
                      for (int i = 0; i < exponent; ++i) {
                          result *= x;
                      }
                      return result;
                  });
    
    print_vector(result2, "Результат (альтернативный)");
    
    return 0;
}