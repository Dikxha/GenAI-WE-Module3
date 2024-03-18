#include <iostream>
#include <vector>

int minIdlisDistribution(const std::vector<int>& idlis) {
    int n = idlis.size();
    int totalIdlis = 0;

    for (int idli : idlis) {
        totalIdlis += idli;
    }

    if (totalIdlis % 2 != 0) {
        return -1; // Total idlis must be even to satisfy the condition
    }

    std::vector<int> idlisCopy = idlis; // Create a copy of the input vector
    int minDistributedIdlis = 0;
    for (int i = 0; i < n; ++i) {
        if (idlisCopy[i] % 2 != 0) {
            if (i == n - 1 || idlisCopy[i + 1] % 2 == 0) {
                return -1; // Impossible to distribute idlis satisfying the condition
            }
            idlisCopy[i]++;
            idlisCopy[i + 1]++;
            minDistributedIdlis += 2;
        }
    }
    return minDistributedIdlis;
}

int main() {
    std::vector<std::vector<int>> testCases = {
        {2, 3, 1, 4, 2},
        {2, 2, 2, 2},
        {1, 3, 2, 5},
        {1, 1, 1, 1, 1}
    };

    for (int i = 0; i < testCases.size(); ++i) {
        int minIdlis = minIdlisDistribution(testCases[i]);
        std::cout << "Test case " << i + 1 << ": ";
        if (minIdlis == -1) {
            std::cout << "Impossible to distribute idlis satisfying the condition.\n";
        } else {
            std::cout << "Minimum number of idlis to distribute: " << minIdlis << "\n";
        }
    }

    return 0;
}
