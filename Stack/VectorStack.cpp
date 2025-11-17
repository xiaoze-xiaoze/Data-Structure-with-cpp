#include <iostream>
#include <vector>
#include "../Error.cpp"

template<typename T>
class VectorStack {
private:
    std::vector<T> data;

public:
    VectorStack() = default;
    explicit VectorStack(int capacity) { data.reserve(capacity); }

    ~VectorStack() = default;

    bool isEmpty() const { return data.empty(); }

    std::expected<T, DataStructureError> top() const {
        if (empty()) return std::unexpected(DataStructureError::ContainerIsEmpty);
        return data.back();
    }

    int getSize() const { return data.size(); }

    void push(const T& value) {
        data.push_back(value);
    }

    std::expected<T, DataStructureError> pop() {
        if (empty()) return std::unexpected(DataStructureError::ContainerIsEmpty);
        T value = data.back();
        data.pop_back();
        return value;
    }
    
    void clear() {
        data.clear();
    }
};