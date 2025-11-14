#include <iostream>
#include <list>
#include "../Error.cpp"

template<typename T>
class ListStack {
private:
    std::list<T> data;

public:
    ListStack() = default;

    ~ListStack() = default;

    bool empty() const { return data.empty(); }

    std::expected<T, DataStructureError> top() const {
        if (empty()) return std::unexpected(DataStructureError::ContainerIsEmpty);
        return data.back();
    }

    int size() const { return data.size(); }

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