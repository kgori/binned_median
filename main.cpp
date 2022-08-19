#include <concepts>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::string clear_console_line() {
    return "\r\x1b[K";
}

template <typename T = unsigned long>
concept UnsignedInteger = std::is_unsigned_v<T> && std::is_integral_v<T>;

template<UnsignedInteger T = long>
class Bins {
public:
    Bins() = delete;
    explicit Bins(size_t n) : _data(n, 0), _size{0} {
        if (n < 1) throw std::domain_error("At least one bin must be specified");
    }
    T find_nth(size_t n);
    void insert(T val);
    double median();
    size_t size() { return _size; }

private:
    std::vector<T> _data;
    size_t _size;
};

template<UnsignedInteger T>
T Bins<T>::find_nth(size_t n) {
    if (_size == 0) throw std::out_of_range("Attempt to access item in empty container");
    if (n >= _size) throw std::out_of_range("Attempt to access more items than are in the container");
    T nth{0};
    size_t seen{0};
    auto it = _data.begin();
    while (seen < n + 1) {
        nth = std::distance(_data.begin(), it);
        seen += (*it++);
        if (seen >= n + 1) {
            return nth;
        }
    }
    return nth;
}

template<UnsignedInteger T>
double Bins<T>::median() {
    if (_size & 1) { // is odd
        return static_cast<double>(find_nth((_size - 1) / 2));
    } else {
        T nth = find_nth((_size / 2) - 1);
        T nth_plus_one = find_nth(_size / 2);
        return static_cast<double>(nth + nth_plus_one) / 2.0;
    };
}

template<UnsignedInteger T>
void Bins<T>::insert(T val) {
    if (val < _data.size() - 1) {
        _data[val]++;
    } else {
        _data.back()++;
    }
    _size++;
}

int main() {
    auto bins = Bins<unsigned long>(10000001);
    unsigned long val;
    while(std::cin >> val) {
        bins.insert(val);
        if (bins.size() % 1000000 == 0) {
            std::cout << clear_console_line() << "Processed " << bins.size() << " items. Current median = " << bins.median() << std::flush;
        }
    }
    std::cout << "\nFinal median = " << bins.median() << std::endl;
}
