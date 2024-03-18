#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

// Function prototypes
int rollDie();
bool isFullHouse(vector<int>& dice);
bool isSmallStraight(vector<int>& dice);
bool isLargeStraight(vector<int>& dice);
bool isYahtzee(vector<int>& dice);
int calculateScore(vector<int>& dice, string category);
void rerollDice(vector<int>& dice, vector<bool>& keep);

int main() {
    // Unit tests for rollDie function
    for (int i = 0; i < 100; ++i) {
        int roll = rollDie();
        assert(roll >= 1 && roll <= 6); // A die roll should be between 1 and 6
    }

    // Unit tests for isFullHouse function
    vector<int> fullHouse1 = {1, 1, 2, 2, 2}; // Full House
    assert(isFullHouse(fullHouse1));

    vector<int> fullHouse2 = {3, 3, 4, 4, 4}; // Full House
    assert(isFullHouse(fullHouse2));

    vector<int> notFullHouse = {1, 1, 2, 3, 4}; // Not a Full House
    assert(!isFullHouse(notFullHouse));

    // Unit tests for isSmallStraight function
    vector<int> smallStraight1 = {1, 2, 3, 4, 4}; // Small Straight
    assert(isSmallStraight(smallStraight1));

    vector<int> smallStraight2 = {1, 3, 4, 5, 6}; // Small Straight
    assert(isSmallStraight(smallStraight2));

    vector<int> notSmallStraight = {1, 2, 3, 5, 6}; // Not a Small Straight
    assert(!isSmallStraight(notSmallStraight));

    // Unit tests for isLargeStraight function
    vector<int> largeStraight1 = {1, 2, 3, 4, 5}; // Large Straight
    assert(isLargeStraight(largeStraight1));

    vector<int> largeStraight2 = {2, 3, 4, 5, 6}; // Large Straight
    assert(isLargeStraight(largeStraight2));

    vector<int> notLargeStraight = {1, 2, 3, 5, 6}; // Not a Large Straight
    assert(!isLargeStraight(notLargeStraight));

    // Unit tests for isYahtzee function
    vector<int> yahtzee = {1, 1, 1, 1, 1}; // Yahtzee
    assert(isYahtzee(yahtzee));

    vector<int> notYahtzee = {1, 1, 1, 1, 2}; // Not a Yahtzee
    assert(!isYahtzee(notYahtzee));

    // Unit tests for calculateScore function
    vector<int> dice = {1, 1, 1, 1, 1}; // Yahtzee
    assert(calculateScore(dice, "Yahtzee") == 50);

    dice = {1, 1, 2, 2, 2}; // Full House
    assert(calculateScore(dice, "Full House") == 25);

    dice = {1, 2, 3, 4, 5}; // Large Straight
    assert(calculateScore(dice, "Large Straight") == 40);

    dice = {1, 2, 3, 4, 4}; // Small Straight
    assert(calculateScore(dice, "Small Straight") == 30);

    // Test rerollDice function
    vector<bool> keep = {true, true, false, true, false};
    rerollDice(dice, keep);
    assert(count(dice.begin(), dice.end(), 4) == 1); // Only one die should be rerolled
    assert(count(keep.begin(), keep.end(), false) == 2); // Two dice should be rerolled

    cout << "All unit tests passed successfully!" << endl;

    return 0;
}

// Function to simulate rolling a single die
int rollDie() {
    return rand() % 6 + 1;
}

// Function to check for a full house
bool isFullHouse(vector<int>& dice) {
    // Sort the dice
    sort(dice.begin(), dice.end());

    // Check for the combination of a full house
    return ((dice[0] == dice[1] && dice[1] == dice[2] && dice[3] == dice[4]) ||
        (dice[0] == dice[1] && dice[2] == dice[3] && dice[3] == dice[4]));
}

// Function to check for a small straight
bool isSmallStraight(vector<int>& dice) {
    // Sort the dice
    sort(dice.begin(), dice.end());

    // Check for the combination of a small straight
    for (int i = 0; i < 3; ++i) {
        int count = 0;
        for (int j = i; j < i + 4; ++j) {
            if (dice[j] == dice[j + 1] - 1) {
                count++;
            }
        }
        if (count >= 3) {
            return true;
        }
    }
    return false;
}

// Function to check for a large straight
bool isLargeStraight(vector<int>& dice) {
    // Sort the dice
    sort(dice.begin(), dice.end());

    // Check for the combination of a large straight
    for (int i = 0; i < 2; ++i) {
        int count = 0;
        for (int j = i; j < i + 4; ++j) {
            if (dice[j] == dice[j + 1] - 1) {
                count++;
            }
        }
        if (count >= 4) {
            return true;
        }
    }
    return false;
}

// Function to check for Yahtzee
bool isYahtzee(vector<int>& dice) {
    // Check if all dice have the same value
    for (int i = 1; i < dice.size(); ++i) {
        if (dice[i] != dice[0]) {
            return false;
        }
    }
    return true;
}

// Function to calculate the score for a specific category
int calculateScore(vector<int>& dice, string category) {
    // Implement scoring logic based on the chosen category
    // This function should return the score that would be obtained by keeping the current roll for the given category
    // Example implementation:
    if (category == "Yahtzee") {
        if (isYahtzee(dice))
            return 50;
    } else if (category == "Full House") {
        if (isFullHouse(dice))
            return 25;
    } else if (category == "Small Straight") {
        if (isSmallStraight(dice))
            return 30;
    } else if (category == "Large Straight") {
        if (isLargeStraight(dice))
            return 40;
    }
    // Implement scoring logic for other categories like Ones, Twos, Threes, ...
    return 0;
}

// Function to reroll the dice based on the keep vector
void rerollDice(vector<int>& dice, vector<bool>& keep) {
    for (int i = 0; i < dice.size(); ++i) {
        if (!keep[i]) {
            dice[i] = rollDie(); // Reroll the die
        }
    }
}