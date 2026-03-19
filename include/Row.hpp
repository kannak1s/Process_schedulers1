#ifndef ROW_HPP
#define ROW_HPP

template<typename T>
class row {
private:
    T* data;
    size_t size_;
public:
    row(size_t size) : size_(size) {
        data = new T[size_];
    }
    ~row() {
        delete[] data;
    }
    T& operator[](size_t index) {
        return data[index];
    }
    size_t size() const {
        return size_;
    }
};

#endif // ROW_HPP
