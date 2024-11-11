#include <bits/stdc++.h>
using namespace std;

// Function to find the maximum profit from stock prices
int calculateMaxProfit(int* stockPrices, int numDays) {
	int totalProfit = 0;
	int sellDay = numDays - 1;

	// Start from the last day and calculate profit
	while (sellDay > 0) {
		int buyDay = sellDay - 1;

		// Accumulate profit until finding a day with a price higher than the sell day
		while (buyDay >= 0 && (stockPrices[sellDay] > stockPrices[buyDay])) {
			totalProfit += (stockPrices[sellDay] - stockPrices[buyDay]);
			buyDay--;
		}

		// Update sellDay to the last checked buyDay
		sellDay = buyDay;
	}

	// Return the total profit
	return totalProfit;
}

// Driver Code
int main() {
	// Array of stock prices
	int stockPrices[] = { 2, 3, 5 };

	int numDays = sizeof(stockPrices) / sizeof(stockPrices[0]);

	// Function Call
	cout << "Maximum Profit: " << calculateMaxProfit(stockPrices, numDays) << endl;

	return 0;
}
