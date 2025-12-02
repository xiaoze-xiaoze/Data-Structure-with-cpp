#include <expected>
#include <string>

#define TRY(var, expr) \
    auto var##Result = (expr); \
    if (!var##Result) return std::unexpected(var##Result.error()); \
    auto var = var##Result.value()

enum class DataStructureError {
    IndexOutOfRange,
    ContainerIsEmpty,
    ContainerIsFull,
    InvalidArgument,
    MemoryAllocationFailed,
    ElementNotFound,
    DuplicateValue    // 
};

std::string error_message(DataStructureError error) {
    switch (error) {
        case DataStructureError::IndexOutOfRange: return "Index out of range";
        case DataStructureError::ContainerIsEmpty: return "Container is empty";
        case DataStructureError::ContainerIsFull: return "Container is full";
        case DataStructureError::InvalidArgument: return "Invalid argument";
        case DataStructureError::MemoryAllocationFailed: return "Memory allocation failed";
        case DataStructureError::ElementNotFound: return "Element not found";
        case DataStructureError::DuplicateValue: return "Duplicate value";
        default: return "Unknown error";
    }
}