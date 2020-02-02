#include<iostream>

using namespace std;

int main()
{
	int r = 0, n;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		cout << "i=" << i << endl;
		for(int j = i + 1; j <= n; j++) {
			cout << "\t j=" << j << endl;
			for(int k = 1; k <= j; k++) {
				cout << "\t \t k=" << k << endl;
				++r;
			}
		}
	}
	cout << r << endl;
	return 0;
}
