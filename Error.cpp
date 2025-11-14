#include <expected>
#include <string>

enum class DataStructureError {
    IndexOutOfRange,
    ContainerIsEmpty,
    ContainerIsFull,
    InvalidArgument,
    MemoryAllocationFailed,
    ElementNotFound
};

std::string error_message(DataStructureError error) {
    switch (error) {
        case DataStructureError::IndexOutOfRange: return "Index out of range";
        case DataStructureError::ContainerIsEmpty: return "Container is empty";
        case DataStructureError::ContainerIsFull: return "Container is full";
        case DataStructureError::InvalidArgument: return "Invalid argument";
        case DataStructureError::MemoryAllocationFailed: return "Memory allocation failed";
        case DataStructureError::ElementNotFound: return "Element not found";
    }
}