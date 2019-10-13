#include <iostream>
#include <assert.h>
#include <ctime>
#include <random>

template<class T, class Comparator = std::less<T> >
int partition(T* arr, int l, int r, int k, Comparator comp) {
  int pivot_idx = l + (r - l)/2;
  int pivot = arr[pivot_idx];

  std::swap(arr[pivot_idx], arr[r-1]);
  int i = l;
  int j = r - 1;

  while (i < j)
  {
    for (; comp(arr[i], pivot); ++i); // i указывает на элемент >= pivot
    while (!comp(arr[j],pivot) && j >= i) // обязательно!!!!! j >= i
    {
      j--; // j указывает на элемент < pivot
    }
    if (i < j) {
      std::swap(arr[i], arr[j]);
    }
  }
  std::swap(arr[i], arr[r-1]);
  return i;
}

template<class T, class Comparator = std::less<T> >
void kth_elem(T* arr, int size, int k, Comparator comp = Comparator()) {
  int l = 0;
  int r = size;

  while(l < r) {
    int m = partition(arr, l, r, k, comp);
    if (m < k) {
      l = m + 1;
    } else {
      r = m;
    }
  }
}

int main2() {
  std::vector<int> arr = {};
  int k = 0;
  int n = 0;
  std::cin >> n >> k;
  for (int i = 0; i < n; ++i) {
    int val = 0;
    std::cin >> val;
    arr.push_back(val);
  }
  kth_elem(&arr[0], arr.size(), k);
  std::cout << arr[k] << std::endl;

  return 0;
}