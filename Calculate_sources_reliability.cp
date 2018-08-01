#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

class SortingAlgorithms {

private:
	vector<double> totalSum;
	vector<double>* sources;
	double* sum;
	int inversion;

public:
	//Constructor
	SortingAlgorithms(string fileNames[], double r[]) {

		const int no_files = 5;
		ifstream File[no_files];
		sources = new vector<double>[no_files];

		//Load file names into an array of Files
		for (int i = 0; i < no_files; i++) {
			std::ostringstream fileName;
			fileName << "source" << i + 1 << ".txt";
			File[i].open(fileName.str());
		}

		//Open the files and extract the data from it
		for (int i = 0; i < no_files; i++)
		{
			if (!File[i])
				cout << "**Error Reading File!**\n" << endl;
			else {
				int j = -1;
				while (File[i] >> ++j)
					sources[i].push_back(j*r[i]);
			}
		}

		//Pass it to the totalSum vector
		for (unsigned int i = 0; i < sources[0].size()/5; i++)
			totalSum.push_back(sources[0][i] + sources[1][i] + sources[2][i] + sources[3][i] + sources[4][i]);

	}

	//Destructor
	~SortingAlgorithms() {
		if (sum)
			delete[] sum;
	}

	//Return total sum
	vector<double> getTotalSum() {
		return totalSum;
	}

	//Return the number of inversions
	int getNoInversions() {
		return this->inversion;
	}

	//Return sorces
	vector<double> getSorces(int i) {
		return sources[i];
	}

	//set inversion to default
	void setInversion() {
		inversion = 0;
	}

	//Quick Sort
	vector<double> concatnate(vector<double> left, vector<double> equal, vector<double> greater) {

		vector<double> AB;

		AB.reserve(left.size() + equal.size() + greater.size()); // preallocate memory
		AB.insert(AB.end(), left.begin(), left.end());
		AB.insert(AB.end(), equal.begin(), equal.end());
		AB.insert(AB.end(), greater.begin(), greater.end());

		return AB;
	}
	vector<double> quickSort(vector<double> a) {

		if (a.size() <= 1)
			return a;

		vector<double> left;
		vector<double> equal;
		vector<double> greater;

		double pivot = a[0];

		for (unsigned int i = 0; i < a.size(); i++) {
			if (a[i] > pivot)
				greater.push_back(a[i]);
			else if (a[i] == pivot) {
				equal.push_back(a[i]);
				inversion += greater.size();
			}
			else {
				left.push_back(a[i]);
				inversion += greater.size() + equal.size();
			}
		}

		return concatnate(quickSort(left), equal, quickSort(greater));
	}

	//Merge sort
	vector<double> merge(vector<double> L, vector<double> R) {
		vector<double> B;
		int size = L.size() + R.size();
		int i = 0;
		int j = 0;
		for (unsigned int k = 0; k < size; k++) {
			if (j >= R.size() || (i < L.size() && L[i] <= R[j])) {
				B.push_back(L[i]);
				i++;
			}
			else {
				B.push_back(R[j]);
				j++;

				inversion += L.size() - i;
			}
		}
		return B;
	}

	vector<double> mergeSort(vector<double> a) {
	//	inversion = 0;
		if (a.size() == 1)
			return a;
		else {
			int q = a.size() / 2;
			vector<double> L;
			vector<double> R;

			vector<double> LS;
			vector<double> RS;

			for (unsigned int i = 0; i < q; i++)
				L.push_back(a[i]);

			for (unsigned int i = q; i < a.size(); i++)
				R.push_back(a[i]);

			LS = mergeSort(L);
			RS = mergeSort(R);


			return merge(LS, RS);
		}
	}

	//Insertion Sort
	vector<double> insertionSort(vector<double> a) {
		for (int i = 1; i < a.size(); i++) {
			int j = i;
			double insert = a[i];
			// Loop from i = 1 to n-1.
			while ((j > 0) && a[j - 1] > insert) {
				a[j] = a[j - 1];
				j--;
			}
			a[j] = insert;
			inversion += i - j;
		}

		return a;
	}

	//Insertion sort for Sum array
	void insertionSortSum(vector<double> &a) {

		for (int i = 1; i < a.size(); i++) {
			int j = i;
			double insert = a[i];
			double insertS1 = sources[0][i];
			double insertS2 = sources[1][i];
			double insertS3 = sources[2][i];
			double insertS4 = sources[3][i];
			double insertS5 = sources[4][i];
			// Loop from i = 1 to n-1.
			while ((j > 0) && a[j - 1] > insert) {
				a[j] = a[j - 1];
				sources[0][j] = sources[0][j - 1];
				sources[1][j] = sources[1][j - 1];
				sources[2][j] = sources[2][j - 1];
				sources[3][j] = sources[3][j - 1];
				sources[4][j] = sources[4][j - 1];

				j--;
			}
			a[j] = insert;
			sources[0][j] = insertS1;
			sources[1][j] = insertS2;
			sources[2][j] = insertS3;
			sources[3][j] = insertS4;
			sources[4][j] = insertS5;

			inversion += i - j;
		}

	}

	//print first 10
	void printFirst100(vector<double> totalSum) {

		for (int i = 0; i < 10; i++)
			cout << totalSum[i] << " ";
		cout << endl;
	}

	//Get the correct no of Inversion
	int testInversion(vector<double> test) {
		int result = 0;

		for (unsigned int i = 0; i < test.size() - 1; i++)
			for (unsigned int j = i + 1; j < test.size(); j++)
				if (test[i] > test[j])
					result++;

		return result;
	}

};



//Main Function
void main() {
	const int numOfSources = 5;
	double r[numOfSources] = { 1,1,1,1,1 };
	string fileNames[numOfSources] = { "source1.txt", "source2.txt" , "source3.txt" , "source4.txt" ,"source5.txt" };
	int current_time = clock();
	double realibility = 5;
	double preRealibility = 5;


	int inversion, inversion1, inversion2, inversion3, inversion4, inversion5;

	do
	{
		cout << "Sorting will continue until the previous realibility and current realibility "
			<<"\nis the same into every decimal places (decimal could be too small to print)" << endl;
		for (int count = 0; count < numOfSources; count++)
			r[count] = r[count]* numOfSources / realibility;

		//Read data from files and Get the Sum array
		SortingAlgorithms Sum(fileNames, r);
		Sum.insertionSortSum(Sum.getTotalSum());
		SortingAlgorithms source1 = Sum;
		SortingAlgorithms source2 = Sum;
		SortingAlgorithms source3 = Sum;
		SortingAlgorithms source4 = Sum;
		SortingAlgorithms source5 = Sum;
		SortingAlgorithms temp = Sum;

		for (int counter = 0; counter < numOfSources; counter++)
		{

			//The correct inversion
			//cout <<" The correct inversion for source"<<counter+1<<" is "
			//<< Sum.testInversion(Sum.getSorces(counter)) << endl;


			temp.printFirst100(Sum.getSorces(counter));

			//setting the inversion to 0 before calculating
			temp.setInversion();
			temp.quickSort(Sum.getSorces(counter));
			inversion = temp.getNoInversions();
			cout << "Number of inversions for source"<<counter+1<<" with quick Sort: " << inversion << endl;
			//cout << "Total time taken for inversions: " << clock() - current_time << " milliseconds." << endl << endl;


			temp.setInversion();
			temp.mergeSort(Sum.getSorces(counter));
			inversion = temp.getNoInversions();
			cout << "                                      merge Sort: " << inversion << endl;
			//cout << "Total time taken for inversions: " << clock() - current_time << " milliseconds." << endl << endl;


			temp.setInversion();
			temp.insertionSort(Sum.getSorces(counter));
			inversion = temp.getNoInversions();
			cout << "                                  insertion Sort: " << inversion << endl;
			//cout << "Total time taken for inversions: " << clock() - current_time << " milliseconds." << endl << endl;


			//calculating the realibility for each sources with the inversion
			r[counter] = 1.0 / (inversion + 1.0);

			cout << endl;
		}

		//storeing the previous realibility before setting the realibility
		preRealibility = realibility;
		realibility = 0;

		//Suming the realibility for all sources
		for (int count = 0; count < numOfSources; count++)
		{
			cout << r[count]<<"  ";
			realibility += r[count];

		}
		
		cout <<endl;
		cout << "previous realibility: "<< preRealibility <<endl;
		cout << "current realibility: " << realibility  << endl;

	} while (realibility  != preRealibility);
		
	cout << "The realibility haven't changed " << realibility << endl;

	delete[] r;
}

