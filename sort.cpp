#include <iostream>
#include <vector>
#include <ctime>
#include <SDL.h>

using namespace std;

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 400;

SDL_Window* window = NULL;
SDL_Renderer* render = NULL;

// window manager
//
void initSDL() {
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Sort", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}
void closeSDL() {
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void draw(vector<int>& v, int currIdx,int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
	SDL_RenderClear(render);

	int barWidth = SCREEN_WIDTH / v.size();

	for (size_t i = 0; i < v.size(); i++) {
		SDL_Rect barRect = { static_cast<int>(i * barWidth), SCREEN_HEIGHT - v[i], barWidth, v[i] };
		
		if (i == currIdx) {
			SDL_SetRenderDrawColor(render, r, g, b, a);
			SDL_RenderFillRect(render, &barRect);
		}
		else {
			SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
			SDL_RenderFillRect(render, &barRect);
		}
		
	}
	SDL_RenderPresent(render);
 }

// sort algorithms
//
vector<int> rndArr(int size) {
	vector<int> arr;
	arr.reserve(size);
	srand(static_cast<unsigned int>(time(NULL)));

	for (int i = 0; i < size; i++)
		arr.push_back(rand() % 300 + 1);

	return arr;
}

void bubbleSort(vector<int>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		for (int j = 0; j < arr.size() - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;

				draw(arr, j+1, 255, 0, 0, 1);
				SDL_Delay(10);
			}
		}
	}
}

void selectionSort(vector<int>& arr) {
	for (int i = 0; i < arr.size() - 1; i++) {
		int min = i;
		for (int j = i + 1; j < arr.size(); j++) {
			if (arr[min] > arr[j]) min = j;
			draw(arr, j, 0, 0, 255, 1);
			SDL_Delay(10);
		}
		if (min != i) {
			int temp = arr[min];
			arr[min] = arr[i];
			arr[i] = temp;

			draw(arr, i, 255, 0, 0, 1);
			SDL_Delay(200);
		}
	}
}

int partition(vector<int>& arr, int left, int right) {
	int pivot = arr[left];
	int i = 0;

	for (int j = left + 1; j <= right; j++) {
		if (arr[j] <= pivot)
			i++;
	}

	int pivotIdx = left + i;
	swap(arr[pivotIdx], arr[left]);

	int l = left;
	int r = right;

	while (l < pivotIdx && r > pivotIdx) {
		while (arr[l] <= pivot) l++;
		while (arr[r] > pivot) r--;

		if (l < pivotIdx && r > pivotIdx) {
			swap(arr[l], arr[r]);
			
			draw(arr, i, 0, 255, 0, 1);
			SDL_Delay(20);
		}
	}

	return pivotIdx;
}
void quickSort(vector<int>& arr, int left, int right) {
	if (left >= right) return;

	int pivot = partition(arr, left, right);
	quickSort(arr, left, pivot - 1);
	quickSort(arr, pivot + 1, right);
}

void merge(vector<int>& arr, int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;

	vector<int> lArr(n1);
	vector<int> rArr(n2);

	for (int i = 0; i < n1; i++) lArr[i] = arr[left + i];
	for (int j = 0; j < n2; j++) rArr[j] = arr[mid + 1 + j];

	int i = 0, j = 0, k = left;

	while (i < n1 && j < n2) {
		if (lArr[i] <= rArr[j]) {
			arr[k] = lArr[i];
			i++;
		}
		else {
			arr[k] = rArr[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		arr[k] = lArr[i];
		i++;
		k++;
	}

	while (j < n2) {
		arr[k] = rArr[j];
		j++;
		k++;
	}

	draw(arr, k, 93, 0, 137, 1);
	SDL_Delay(20);
}
void mergeSort(vector<int>& arr, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;

		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);

		merge(arr, left, mid, right);
	}
}

void algo(int input, vector<int>& arr) {
	switch (input) {
	case 1:
		bubbleSort(arr);
		SDL_Delay(2000);
		closeSDL();
		arr.clear();
		break;

	case 2:
		selectionSort(arr);
		SDL_Delay(2000);
		closeSDL();
		arr.clear();
		break;

	case 3:
		quickSort(arr, 0, arr.size() - 1);
		SDL_Delay(2000);
		closeSDL();
		
		arr.clear();
		break;

	case 4:
		mergeSort(arr, 0, arr.size() - 1);
		SDL_Delay(2000);
		closeSDL();

		arr.clear();
		break;
	}
}

int main(int argc, char *argv[]) {
	int input = 0;

	while (true) {
		cout << "Choose sorting algorithm: " << endl;
		cout << "(1) | bubble sort" << endl;
		cout << "(2) | selection sort" << endl;
		cout << "(3) | quick sort" << endl;
		cout << "(4) | merge sort" << endl;
		cout << "[0] | to close" << endl;
		cin >> input; cout << endl;

		if (input != 0) {
			vector<int> arr = rndArr(100);
			initSDL();
			algo(input, arr);
		}
		else
			break;
	}

	system("pause");
	return 0;
}