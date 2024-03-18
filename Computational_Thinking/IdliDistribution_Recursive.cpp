#include <iostream>
#include <vector>
#include <string>

// Function to check if idlis sum is odd or even
bool isEvenSum(const std::vector<int>& idlis) {
    int sum = 0;
    for (int idli : idlis) {
        sum += idli;
    }
    return sum % 2 == 0;
}

// Function to convert idlis list to a string representation
std::string convertToQueue(const std::vector<int>& idlis) {
    std::string queue;
    for (int idli : idlis) {
        queue += (idli % 2 == 1) ? 'o' : 'e';
    }
    return queue;
}

// Function to distribute idlis
int distributeB(const std::string& queue) {
    if (queue.length() < 2) {
        return 0;
    }
    if (queue.substr(0, 2) == "ee") {
        return distributeB(queue.substr(2));
    }
    if (queue.substr(0, 2) == "oo") {
        return 2 + distributeB(queue.substr(2));
    }
    if (queue[0] == 'e') {
        return distributeB(queue.substr(1));
    }
    return 2 + distributeB("o" + queue.substr(2));
}

// Main function to distribute idlis
int distributeA(const std::vector<int>& idlis) {
    if (!isEvenSum(idlis)) {
        return -1;
    }
    std::string queue = convertToQueue(idlis);
    return distributeB(queue);
}

int main() {
    std::vector<std::vector<int>> testCases = {
        {2, 3, 1, 4, 2},
        {2, 2, 2, 2},
        {1, 3, 2, 5},
        {1, 1, 1, 1, 1}
    };

    for (int i = 0; i < testCases.size(); ++i) {
        int minIdlis = distributeA(testCases[i]);
        std::cout << "Test case " << i + 1 << ": ";
        if (minIdlis == -1) {
            std::cout << "Impossible to distribute idlis satisfying the condition.\n";
        } else {
            std::cout << "Minimum number of idlis to distribute: " << minIdlis << "\n";
        }
    }

    return 0;
}
