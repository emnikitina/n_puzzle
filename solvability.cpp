#include <iostream>

using namespace std;

int main() {
	int a[9];
	for (int i=0; i<9; ++i)
		cin >> a[i];
	
	int inv = 0;
	for (int i=0; i<9; ++i)
		if (a[i])
			for (int j=0; j<i; ++j)
				if (a[j] > a[i])
					++inv;
	for (int i=0; i<9; ++i)
		if (a[i] == 0)
			inv += 1 + i / 3;
	
	puts ((inv & 1) ? "No Solution" : "Solution Exists");
}