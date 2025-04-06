#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cctype>

bool canCreateNote(const std::string& note, const std::vector<std::string>& articles) {
    std::unordered_map<char, int> count;

    for (std::string article : articles) {
        for (char c : article) {
            if (!std::isspace(c)) {
                c = std::tolower(c);
                count[c]++;
            }
        }
    }
    for (char c : note) {
        if (!std::isspace(c)) {
            c = std::tolower(c);
            if (count[c] <= 0) {
                return false;
            }
            count[c]--;
        }
    }
    return true;
}
int main() {

    std::cout << "Test 1: "
        << (canCreateNote("a", { "a" }) ? "Passed" : "Failed")
        << std::endl;

    std::cout << "Test 2: "
        << (canCreateNote("a", { "ab" }) ? "Passed" : "Failed")
        << std::endl;

    std::cout << "Test 3: "
        << (canCreateNote("a", { "a", "b" }) ? "Passed" : "Failed")
        << std::endl;

    std::cout << "Test 4: "
        << (canCreateNote("abc", { "a", "b", "c" }) ? "Passed" : "Failed")
        << std::endl;

    std::cout << "Test 5: "
        << (canCreateNote("The bird is red!", { "I write a lot.", "To and fro.", "Here be deadly dragons!" }) ? "Passed" : "Failed")
        << std::endl;

    std::cout << "Test 6: "
        << (canCreateNote("a", { "b" }) ? "Passed" : "Failed")
        << std::endl;

    std::cout << "Test 7: "
        << (canCreateNote("a", { "bc" }) ? "Passed" : "Failed")
        << std::endl;

    std::cout << "Test 8: "
        << (canCreateNote("a", { "b", "c" }) ? "Passed" : "Failed")
        << std::endl;

    std::cout << "Test 9: "
        << (canCreateNote("abc", { "a", "b", "d" }) ? "Passed" : "Failed")
        << std::endl;

    std::cout << "Test 10: "
        << (canCreateNote("The bird is red", { "I write a lot.", "To and fro." }) ? "Passed" : "Failed")
        << std::endl;

    std::cout << "Test 11: "
        << (canCreateNote("The bird is red!", { "I write a lot.", "To and fro.", "Here be deadly dragons" }) ? "Passed" : "Failed")
        << std::endl;

    return 0;
}
