#include <bits/stdc++.h>
using namespace std;

// Comparator function to sort shops by closing time (and opening time in case of tie)
bool compareByTime(const pair<int, int>& shop1, const pair<int, int>& shop2) {
	if (shop1.second != shop2.second)
		return shop1.second < shop2.second;
	return shop1.first < shop2.first;
}

// Function to find the maximum number of shops that can be visited by `max_visitors` people
int getMaxVisitedShops(int* opening_times, int* closing_times, int num_shops, int max_visitors) {
	// Array to store opening and closing times as pairs
	pair<int, int> shops[num_shops];

	for (int i = 0; i < num_shops; i++) {
		shops[i].first = opening_times[i];
		shops[i].second = closing_times[i];
	}

	// Sort shops by their closing time (and by opening time if closing times are the same)
	sort(shops, shops + num_shops, compareByTime);

	// Result to store the number of shops that can be visited
	int shop_count = 0;

	// Set to keep track of current visitors' shop visits and their closing times
	multiset<int> visitor_closing_times;

	for (int i = 0; i < num_shops; i++) {
		bool assigned = false;

		// Check if any visitor can be assigned to the current shop
		if (!visitor_closing_times.empty()) {
			auto visitor_it = visitor_closing_times.upper_bound(shops[i].first);

			if (visitor_it != visitor_closing_times.begin()) {
				--visitor_it;

				// If a visitor's previous shop closes before the current shop opens, reassign the visitor
				if (*visitor_it <= shops[i].first) {
					visitor_closing_times.erase(visitor_it);
					visitor_closing_times.insert(shops[i].second);
					shop_count++;
					assigned = true;
				}
			}
		}

		// If no visitor could be assigned to this shop, check if there are available visitors
		if (visitor_closing_times.size() < max_visitors && !assigned) {
			visitor_closing_times.insert(shops[i].second);
			shop_count++;
		}
	}

	return shop_count;
}

// Driver Code
int main() {
	// Given opening and closing times
	int opening_times[] = { 1, 8, 3, 2, 6 };
	int closing_times[] = { 5, 10, 6, 5, 9 };

	// Maximum number of visitors and total shops
	int max_visitors = 2;
	int num_shops = sizeof(opening_times) / sizeof(opening_times[0]);

	// Function call
	cout << getMaxVisitedShops(opening_times, closing_times, num_shops, max_visitors) << endl;
	return 0;
}
