
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <thread>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Function to print the DP table
void printTable(const vector<vector<int>>& dp, const string& X, const string& Y, int currentI = -1, int currentJ = -1) {
    int m = X.length();
    int n = Y.length();

    cout << "\n     ";
    for (int j = 0; j <= n; j++) {
        if (j == 0)
            cout << "   ";
        else
            cout << "  " << Y[j - 1];
    }
    cout << "\n";

    for (int i = 0; i <= m; i++) {
        if (i == 0)
            cout << "   ";
        else
            cout << " " << X[i - 1] << " ";
        for (int j = 0; j <= n; j++) {
            if (i == currentI && j == currentJ)
                cout << "[" << setw(2) << dp[i][j] << "]";
            else
                cout << " " << setw(2) << dp[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    this_thread::sleep_for(milliseconds(500)); // Pause to visualize
}

// Function to compute LCS and visualize the process
int LCS(string X, string Y) {
    int m = X.length();
    int n = Y.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    cout << "\nBuilding DP table...\n";
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

            printTable(dp, X, Y, i, j);
        }
    }

    // Reconstructing the LCS string
    string lcs = "";
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs = X[i - 1] + lcs;
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    cout << "Final LCS: " << lcs << "\n";
    cout << "Length: " << dp[m][n] << "\n";

    return dp[m][n];
}

int main() {
    string str1, str2;

    cout << "Enter first string: ";
    cin >> str1;

    cout << "Enter second string: ";
    cin >> str2;

    LCS(str1, str2);

    return 0;
}
