#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <map>

using namespace std;

// Function prototypes
int rollDie();
void printDice(vector<int>& dice);
int calculateScore(vector<int>& dice, string category);
void rerollDice(vector<int>& dice, vector<bool>& keep);
int bestRoll(vector<int>& dice, string category);
void trackScore(vector<pair<string, int>>& history, string category, int score);
bool isFullHouse(vector<int>& dice);
bool isSmallStraight(vector<int>& dice);
bool isLargeStraight(vector<int>& dice);
bool isYahtzee(vector<int>& dice);

int main() {
    // Seed the random number generator
    srand(time(0));

    // Initialize variables
    const int NUM_DICE = 5;
    vector<int> dice(NUM_DICE);
    vector<pair<string, int>> scoreHistory;

    // Roll the initial dice
    for (int i = 0; i < NUM_DICE; ++i) {
        dice[i] = rollDie();
    }

    // Print the initial roll
    cout << "Initial roll: ";
    printDice(dice);

    // Choose scoring category
    string category;
    cout << "Choose scoring category (e.g., Ones, Twos, Threes, ...): ";
    cin >> category;

    // Calculate and print the best score for the chosen category
    int score = bestRoll(dice, category);
    cout << "Best score for " << category << ": " << score << endl;

    // Track the score
    trackScore(scoreHistory, category, score);

    // Print the score history
    cout << "\nScore History:" << endl;
    for (const auto& entry : scoreHistory) {
        cout << entry.first << ": " << entry.second << endl;
    }

    return 0;
}

// Function to simulate rolling a single die
int rollDie() {
    return rand() % 6 + 1;
}

// Function to print the dice
void printDice(vector<int>& dice) {
    cout << "[ ";
    for (int value : dice) {
        cout << value << " ";
    }
    cout << "]" << endl;
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

// Function to find the best roll for a given category
int bestRoll(vector<int>& dice, string category) {
    int bestScore = 0;

    // Try all possible combinations of keeping and rerolling dice
    for (int mask = 0; mask < (1 << dice.size()); ++mask) {
        vector<bool> keep(dice.size(), false);
        for (int i = 0; i < dice.size(); ++i) {
            if (mask & (1 << i)) {
                keep[i] = true; // Keep this die
            }
        }

        // Reroll dice based on keep vector
        rerollDice(dice, keep);

        // Calculate the score for the current roll
        int score = calculateScore(dice, category);
        if (score > bestScore) {
            bestScore = score; // Update best score
        }
    }

    return bestScore;
}

// Function to track the score history
void trackScore(vector<pair<string, int>>& history, string category, int score) {
    history.push_back(make_pair(category, score));
}

// Function to check for a full house
bool isFullHouse(vector<int>& dice) {
    // Sort the dice
    sort(dice.begin(), dice.end());

    // Check for the combination of a full house
    if ((dice[0] == dice[1] && dice[1] == dice[2] && dice[3] == dice[4]) ||
        (dice[0] == dice[1] && dice[2] == dice[3] && dice[3] == dice[4])) {
        return true;
    }
    return false;
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