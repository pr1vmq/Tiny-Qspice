#include <iostream>
#include <string>
#include <ranges>
#include <format>
#include <numeric>

std::string stringToHexFast(const std::string& input) {
    auto hex_view = input | std::views::transform([](unsigned char c) {
        return std::format("{:02X}", c);
    });
    return std::accumulate(hex_view.begin(), hex_view.end(), std::string{});
}

int main() {
    std::string str = "Hello C++";
    std::string hexStr = stringToHexFast(str);

    std::cout << "Chuoi goc: " << str << std::endl;
    std::cout << "Hex string: " << hexStr << std::endl; 
    // Kết quả: 48656C6C6F20432B2B
    return 0;
}