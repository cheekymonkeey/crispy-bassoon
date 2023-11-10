#include <iostream>
#include <vector>

class MyStack {
private:
    std::vector<double> data;

public:
    void push(double item) {
        data.push_back(item);
    }

    double pop() {
        double top = data.back();
        data.pop_back();
        return top;
    }

    double peek() {
        return data.back();
    }

    bool isEmpty() {
        return data.empty();
    }

    void timSort(int n);

private:
    static const int MIN_MERGE = 32;

    static int minRunLength(int n);

    static void insertionSort(std::vector<double>& arr, int left, int right);

    static void merge(std::vector<double>& arr, int l, int m, int r);
};

int MyStack::minRunLength(int n) {
    int r = 0;
    while (n >= MIN_MERGE) {
        r |= (n & 1);
        n >>= 1;
    }
    return n + r;
}

void MyStack::insertionSort(std::vector<double>& arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        double key = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

void MyStack::merge(std::vector<double>& arr, int l, int m, int r) {
    int len1 = m - l + 1, len2 = r - m;

    std::vector<double> leftArr(len1);
    std::vector<double> rightArr(len2);

    for (int i = 0; i < len1; i++) {
        leftArr[i] = arr[l + i];
    }

    for (int j = 0; j < len2; j++) {
        rightArr[j] = arr[m + 1 + j];
    }

    int i = 0, j = 0, k = l;

    while (i < len1 && j < len2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        }
        else {
            arr[k++] = rightArr[j++];
        }
    }

    while (i < len1) {
        arr[k++] = leftArr[i++];
    }

    while (j < len2) {
        arr[k++] = rightArr[j++];
    }
}

void MyStack::timSort(int n) {
    int minRun = minRunLength(n);

    for (int i = 0; i < n; i += minRun) {
        insertionSort(data, i, std::min((i + minRun - 1), (n - 1)));
    }

    for (int size = minRun; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = std::min((left + 2 * size - 1), (n - 1));

            if (mid < right) {
                merge(data, left, mid, right);
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    int size;
    std::cout << "Введите размер стека: ";
    std::cin >> size;

    MyStack myStack;

    std::cout << "Введите элементы стека:\n";
    for (int i = 0; i < size; i++) {
        double value;
        std::cin >> value;
        myStack.push(value);
    }

    myStack.timSort(size);

    std::cout << "Отсортированный стек:\n";
    std::vector<double> sortedData;
    while (!myStack.isEmpty()) {
        sortedData.push_back(myStack.pop());
    }

    for (int i = sortedData.size() - 1; i >= 0; i--) {
        std::cout << sortedData[i] << " ";
    }

    std::cout << std::endl;

    return 0;
}
