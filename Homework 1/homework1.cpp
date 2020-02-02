//Burak Bozdag

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>

using namespace std;

void bubble(int* A, int N) {
	bool flag;								//Bubble finisher flag
	while(true) {
		flag = false;
		for(int i = 0; i < N - 1; i++) {	//Looping inside the array
			if(A[i] > A[i + 1]) {			//Swapping numbers
				int temp = A[i];
				A[i] = A[i + 1];
				A[i + 1] = temp;
				flag = true;
			}
		}
		if(flag == false)
			break;
	}
}

void merge(int* A, int L, int R) {
	if(L < R) {
		int M = (L + R) / 2;
		merge(A, L, M);						//Sort the left side
		merge(A, M + 1, R);					//Sort the right side
		
		int arrL[M - L + 1], arrR[R - M];	//Temp arrays for both sides
		
		for(int i = 0; i < M - L + 1; i++)	//Copying numbers to the temp arrays
			arrL[i] = A[i + L];
		for(int i = 0; i < R - M; i++)
			arrR[i] = A[i + M + 1];
		
		int i = 0, j = 0, k = L;			//i = arrL[0], j = arrR[0], k = A[L]
		while(i < M - L + 1 && j < R - M) {	//Merge the temp arrays
			if(arrL[i] <= arrR[j])
				A[k] = arrL[i++];
			else
				A[k] = arrR[j++];
			++k;
		}
		
		while(i < M - L + 1)				//Adding remaining numbers
			A[k++] = arrL[i++];
		while(k < R - M)
			A[k++] = arrR[j++];
	}
}

int main(int argc, char** argv)
{
	if(argc != 4) {
		cout << "Invalid arguments." << endl;
		return 1;
	}
	char algorithmType = argv[1][0];
	int N = atoi(argv[2]);
	ifstream readFile(argv[3]);
	
	bool error = false;
	if(algorithmType != 'b' && algorithmType != 'm') {
		cout << "Invalid sorting type." << endl;
		error = true;
	}
	if(N < 2) {
		cout << "Not enough numbers to sort." << endl;
		error = true;
	}
	if(error)
		return 1;
	
	int A[N] = {0};
	for(int i = 0; i < N; i++)
		readFile >> A[i];
	
	cout << "Sorting..." << endl;
	clock_t t = clock();
	switch(algorithmType){
		case 'b':
			bubble(A, N);
			break;
		case 'm':
			merge(A, 0, N);
			break;
		default:
			return 1;
	}
	t = clock() - t;
	cout << ((float)t) / CLOCKS_PER_SEC << " seconds" << endl << endl;
	
	cout << "Writing to the output file... " << endl;
	ofstream writeFile("output.txt");
	for(int i = 0; i < N; i++)
		writeFile << A[i] << endl;
	cout << "Done." << endl;
	return 0;
}
