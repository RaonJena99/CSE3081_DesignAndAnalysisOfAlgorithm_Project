#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

/* for calculating time */
//#include <stdio.h>
//#include "measure_cpu_time.h"
//#include "test.h"
//#define CMAX 1000000000
//int Count, Count2 = 0;
/*//////////////////////*/

using namespace std;

void Algorithm3(vector<vector<long> >& A, vector<long>& O, int row, int col); // Algorithm 3 , O(n^4)
void Algorithm4(vector<vector<long> >& A, vector<long>& O, int row, int col); // Algorithm 4 , O(n^3*logn)
void Algorithm5(vector<vector<long> >& A, vector<long>& O, int row, int col); // Algorithm 5 , O(n^3)
int MaxSubSum(vector<int>& tmp, int& a, int& b, int left, int right); //Divide-and-Conquer Algorithm
int kadane(vector<int> tmp, int* a, int* b, int n); // Kadane Algorihtm

int main() {
	ifstream file, inPgm, inAvg;
	ofstream writeFile;
	stringstream ss;
	string s, pgm, avg, out, str_pgm, str_avg;

	int tc = 0, idx = 0, cnt = 0;
	int Al_type, col, row, level;

	/* opening file */
	file.open("./Data/HW1_config.txt");
	if (!file.is_open()) {
		cout << "Error opening file: HW1_config.txt\n";
		return 0;
	}

	file >> s;
	tc = stoi(s);

	vector<vector<string> > parsed_file(tc);

	/* parsing file */
	while (file >> s) {
		parsed_file[idx].push_back(s);
		cnt++;
		if (cnt == 4) {
			idx++; cnt = 0;
		}
	}
	file.close();

	/* array allocation */
	for (int i = 0; i < tc; i++) {
		Al_type = stoi(parsed_file[i][0]);
		pgm = parsed_file[i][1];
		avg = parsed_file[i][2];
		out = parsed_file[i][3];

		/* opeing pgm, avg file */
		inPgm.open("./Data/" + pgm);
		inAvg.open("./Data/" + avg);
		if (!inPgm.is_open()) {
			cout << "Error opening file: " << pgm << "\n";
		}
		else if (!inAvg.is_open()) {
			cout << "Error opening file: " << avg << "\n";
		}

		getline(inPgm, str_pgm);
		inAvg >> str_avg;

		if (!str_pgm.compare("P2")) {
			ss.str("");
			ss.clear();

			/* array size */
			ss << inPgm.rdbuf();
			ss >> row >> col;
			ss >> level;

			
			vector<vector<long> > Arr(row, vector<long>(col));
			vector<long> Out(5);

			/* write pgm data */
			for (int i = 0; i < row; i++) 
				for (int j = 0; j < col; j++) {
					ss >> Arr[i][j];
					Arr[i][j] -= stoi(str_avg);
				}

			/* time val for calculating time */
			/*Count, Count2 = 0;
			fprintf(stdout, "************* test%d ****************\n",i);  */                     
			/* caculation of  max_sum */
			switch (Al_type){
			case 3:
				/*CHECK_TIME_START(_start, _freq);*/                                                
				Algorithm3(Arr, Out, row, col);
				/*CHECK_TIME_END(_start, _end, _freq, _compute_time);                              
				fprintf(stdout, "*** n = %u --> count2 = %u, count = %u\n", row, Count2, Count);
				fprintf(stdout, "    run time = %.3fms \n", _compute_time); */                     
				break;
			case 4:
				/*CHECK_TIME_START(_start, _freq); */                                               
				Algorithm4(Arr, Out, row, col);
				/*CHECK_TIME_END(_start, _end, _freq, _compute_time);                              
				fprintf(stdout, "*** n = %u --> count2 = %u, count = %u\n", row, Count2, Count); 
				fprintf(stdout, "    run time = %.3fms \n", _compute_time);   */                  
				break;
			case 5:
				/*CHECK_TIME_START(_start, _freq);   */                                             
				Algorithm5(Arr, Out, row, col);
				/*CHECK_TIME_END(_start, _end, _freq, _compute_time);                             
				fprintf(stdout, "*** n = %u --> count2 = %u, count = %u\n", row, Count2, Count); 
				fprintf(stdout, "    run time = %.3fms \n", _compute_time);    */                 
				break;
			}
			/*print_test();*/

			/* writing output file */
			writeFile.open("./Data/" + out);
			for (int i = 0; i < 5; i++) writeFile << Out[i]<<" ";

			writeFile.close();
			writeFile.clear();
		}

		inPgm.close();
		inAvg.close();
		inPgm.clear();
		inAvg.clear();
	}

	return 0;
}

void Algorithm3(vector<vector<long> >& A, vector<long>& O, int row, int col) {
	int Sum, Max = LONG_MIN;

	for (int i = 0; i < row; i++) {
		for (int j = 1; j < col; j++) {
			if (i > 0) A[i][j] += A[i - 1][j];
			if (j > 0) A[i][j] += A[i][j - 1];
			if (i > 0 && j > 0) A[i][j] -= A[i - 1][j - 1];
			/*Count++;
			if (Count == CMAX) {
				Count2++;
				Count = 0;
			}*/
		}
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			for (int k = i; k < row; k++) {
				for (int l = j; l < col; l++) {
					Sum = A[k][l];
					
					if (i > 0) Sum -= A[i - 1][l];
					if (j > 0) Sum -= A[k][j - 1];
					if (i > 0 && j > 0) Sum += A[i - 1][j - 1];

					if (Max < Sum) {
						Max = Sum;
						O[0] = Max; O[1] = i;O[2] = j;O[3] = k;O[4] = l;
					}
					/*Count++;
					if (Count == CMAX) {
						Count2++;
						Count = 0;
					}*/
				}
			}
		}
	}
}

void Algorithm4(vector<vector<long> >& A,vector<long>& O, int row, int col) {
	int Sum, cur_sum = 0, Max = LONG_MIN, a, b;

	for (int i = 0; i < col; i++) {
		vector<int> tmp(row, 0);
		cur_sum = 0;
		for (int j = i; j < col; j++) {
			for (int k = 0; k < row; k++)
				tmp[k] += A[k][j];

			Sum = MaxSubSum(tmp, a, b, 0, row-1);

			if (Max < Sum) {
				Max = Sum;
				O[0] = Max; O[1] = a; O[2] = i; O[3] = b; O[4] = j;
			}
			/*Count++;
			if (Count == CMAX) {
				Count2++;
				Count = 0;
			}*/
		}
	}
}

int MaxSubSum(vector<int>& tmp, int& a, int& b, int left, int right) {
	/*Count++;
	if (Count == CMAX) {
		Count2++;
		Count = 0;
	}*/

	if (left == right) {
		a = b = left;
		return tmp[left];
	}

	int center = (left + right) / 2;

	int LS=0, LF=0, RS=0, RF=0;
	int MLS = MaxSubSum(tmp, LS, LF, left, center);
	int MRS = MaxSubSum(tmp, RS, RF, center+1, right);

	int LBS = 0, MLBS = INT_MIN;
	int TLS = center;
	for (int i = center; i >= left; i--) {
		LBS += tmp[i];
		if (LBS > MLBS) {
			MLBS = LBS;
			TLS = i;
		}
		/*Count++;
		if (Count == CMAX) {
			Count2++;
			Count = 0;
		}*/
	}

	int RBS = 0, MRBS = INT_MIN;
	int TRS = center + 1;
	for (int i = center + 1; i <= right; i++) {
		RBS += tmp[i];
		if (RBS > MRBS) {
			MRBS = RBS;
			TRS = i;
		}
		/*Count++;
		if (Count == CMAX) {
			Count2++;
			Count = 0;
		}*/
	}

	int MCS = MLBS + MRBS;

	if (MLS >= MRS && MLS >= MCS) {
		a = LS;
		b = LF;
		return MLS;
	}
	else if (MRS >= MLS && MRS >= MCS) {
		a = RS;
		b = RF;
		return MRS;
	}
	else {
		a = TLS;
		b = TRS;
		return MCS;
	}
}

void Algorithm5(vector<vector<long> >& A, vector<long>& O, int row, int col) {
	int Sum, cur_sum = 0, Max = LONG_MIN, a, b;

	for (int i = 0; i < col; i++) {
		vector<int> tmp(row, 0);
		cur_sum = 0;
		for (int j = i; j < col; j++) {
			for (int k = 0; k < row; k++) 
				tmp[k] += A[k][j];
			
			Sum = kadane(tmp,&a,&b,row);

			if (Max < Sum) {
				Max = Sum;
				O[0] = Max; O[1] = a; O[2] = i; O[3] = b; O[4] = j;
			}
			/*Count++;
			if (Count == CMAX) {
				Count2++;
				Count = 0;
			}*/
		}
	}
}

int kadane(vector<int> tmp, int* a, int* b, int n) {
	int sum = 0, maxSum = LONG_MIN;
	*b = -1;
	int local_start = 0;

	for (int i = 0; i < n; i++) {
		sum += tmp[i];

		if (sum < 0) {
			sum = 0; local_start = i + 1;
		}
		else if (sum > maxSum) {
			maxSum = sum;
			*a = local_start; *b = i;
		}
		/*Count++;
		if (Count == CMAX) {
			Count2++;
			Count = 0;
		}*/
	}

	if (*b != -1) return maxSum;

	maxSum = tmp[0]; *a = *b = 0;
	for (int i = 1; i < n; i++) {
		if (tmp[i] > maxSum) {
			maxSum = tmp[i]; *a = *b = i;
		}
		/*Count++;
		if (Count == CMAX) {
			Count2++;
			Count = 0;
		}*/
	}
	return maxSum;
}