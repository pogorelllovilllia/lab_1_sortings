/**
 * @file main.cpp
 * @brief Program for sorting train schedules and measuring sorting time.
 *
 * Supports reading from CSV, writing to file, insertion sort, quicksort,
 * merge sort, and std::sort. Implements the Schedule class with overloaded operators.
 */
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <vector>

 /**
  * @brief Class representing a train schedule.
  */

class Schedule {
public:
    int trainNumber;             ///< Train number
    std::string departureDate;  ///< Departure date (format "YYYY-MM-DD")
    std::string trainType;      ///< Train type (e.g., "fast")
    std::string departureTime;  ///< Departure time (format "HH:MM")
    int travelMinutes;          ///< Travel time in minutes

    /// @brief Equality operator
    /// @param other Another schedule
    /// @return true if all fields are equal
    bool operator==(const Schedule& other) const;
    /// @brief Less-than operator
    /// @param other Another schedule
    /// @return true if this < other
    bool operator<(const Schedule& other) const;
    /// @brief Inequality operator
    bool operator!=(const Schedule& other) const;
    /// @brief Greater-than operator
    bool operator>(const Schedule& other) const;
    /// @brief Less-than-or-equal operator
    bool operator<=(const Schedule& other) const;

    /// @brief Greater-than-or-equal operator
    bool operator>=(const Schedule& other) const;

public:
    //Schedule(int num, const std::string& date, const std::string& type,
    //    const std::string& time, const std::string& travelTime)
    //    : trainNumber(num), departureDate(date), trainType(type), departureTime(time) {
    //    // Разбор строки travelTime вручную: формат "HH:MM"
    //    int hours = (travelTime[0] - '0') * 10 + (travelTime[1] - '0');
    //    int minutes = (travelTime[3] - '0') * 10 + (travelTime[4] - '0');
    //    travelMinutes = hours * 60 + minutes;
    //}

/**
     * @brief Outputs the schedule to an output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const Schedule& s) {
        os << "Train " << s.trainNumber << ", " << s.trainType
            << ", Departure: " << s.departureDate << " " << s.departureTime
            << ", Travel Time: " << s.travelMinutes << " minutes";
        return os;
    }

    /**
    * @brief Writes the Schedule object to a CSV file
    * @param outFile Reference to the output file
    */
    void writeToCSV(std::ofstream& outFile) const {
        outFile << trainNumber << ","
            << departureDate << ","
            << trainType << ","
            << departureTime << ","
            << travelMinutes << "\n";
    }
};

bool Schedule::operator==(const Schedule& other) const {
    return departureDate == other.departureDate &&
        departureTime == other.departureTime &&
        trainNumber == other.trainNumber &&
        travelMinutes == other.travelMinutes;
}

// <
bool Schedule::operator<(const Schedule& other) const {
    if (departureDate != other.departureDate)
        return departureDate < other.departureDate;

    if (departureTime != other.departureTime)
        return departureTime < other.departureTime;

    if (trainNumber != other.trainNumber)
        return trainNumber < other.trainNumber;

    return travelMinutes > other.travelMinutes;
}

// >
bool Schedule::operator>(const Schedule& other) const {
    return other < *this;
}

// !=
bool Schedule::operator!=(const Schedule& other) const {
    return !(*this == other);
}

// <=
bool Schedule::operator<=(const Schedule& other) const {
    return !(other < *this);
}

// >=
bool Schedule::operator>=(const Schedule& other) const {
    return !(*this < other);
}

/**
 * @brief Insertion sort
 * @tparam T Element type
 * @param a Array to sort
 * @param size Size of array
 */
template<class T> void insertSort(T a[], long size)
{
    T x;
    long i, j;

    for (i = 0; i < size; i++)
    {			// i is a step number
        x = a[i];

        // search the place to insert element in ordered part of array
        for (j = i - 1; j >= 0 && a[j] > x; j--)
            a[j + 1] = a[j];  	// move the element to the right until it is necessary

                  // place found, insert element
        a[j + 1] = x;
        
    }
}

/**
 * @brief Recursive quick sort
 * @tparam T Element type
 * @param a Array to sort
 * @param N Array size
 */

template<class T> void quickSortR(T* a, long N)
{
    long i = 0, j = N - 1; 		// initializing the bounds i and j
    T p = a[N >> 1];		// base element p is a central element

    // division procedure
    do
    {
        while (a[i] < p) i++;
        while (a[j] > p) j--;

        if (i <= j)
        {
            std::swap(a[i], a[j]);
            i++; j--;
        }
    } while (i <= j);

    // recursive division 
    if (j > 0) quickSortR(a, j);
    if (N > i) quickSortR(a + i, N - i);
}
/**
 * @brief Merges two parts of the array
 * @tparam T Element type
 */
template<class T> void merge(T a[], long low, long mid, long high)
{
    // Variables declaration. 
    T* b = new T[high + 1 - low];
    long h, i, j, k;
    h = low;
    i = 0;
    j = mid + 1;
    // Merges the two array's into b[] until the first one is finish
    while ((h <= mid) && (j <= high))
    {
        if (a[h] <= a[j])
        {
            b[i] = a[h];
            h++;
        }
        else
        {
            b[i] = a[j];
            j++;
        }
        i++;
    }
    // Completes the array filling in it the missing values
    if (h > mid)
    {
        for (k = j;k <= high;k++)
        {
            b[i] = a[k];
            i++;
        }
    }
    else
    {
        for (k = h;k <= mid;k++)
        {
            b[i] = a[k];
            i++;
        }
    }
    // Prints into the original array
    for (k = 0;k <= high - low;k++)
    {
        a[k + low] = b[k];
    }
    delete[] b;
}
/**
 * @brief Recursive merge sort
 * @tparam T Element type
 */
template<class T> void merge_sort(T a[], long low, long high)
{// Recursive sort ...
    long mid;
    if (low < high)
    {
        mid = (low + high) / 2;
        merge_sort(a, low, mid);
        merge_sort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}

/**
 * @brief Reads schedule data from a CSV file
 * @param filename File name
 * @param arr Array to store the data
 * @param maxSize Maximum number of records
 * @return Number of records read
 */

int readSchedulesFromCSV(const std::string& filename, Schedule arr[], int maxSize) {
    std::ifstream file(filename);
    std::string line;
    int count = 0;

    while (std::getline(file, line) && count < maxSize) {
        std::stringstream ss(line);
        std::string token;

        Schedule s;

        // 1. trainNumber
        std::getline(ss, token, ',');
        try {
            s.trainNumber = std::stoi(token);
        }
        catch (...) {
            s.trainNumber = 0;
        }

        // 2. departureDate
        std::getline(ss, s.departureDate, ',');

        // 3. trainType
        std::getline(ss, s.trainType, ',');

        // 4. departureTime
        std::getline(ss, s.departureTime, ',');

        // 5. travelMinutes
        std::getline(ss, token, ',');
        try {
            s.travelMinutes = std::stoi(token);
        }
        catch (...) {
            s.travelMinutes = 0;
        }

        arr[count++] = s; 
    }

    file.close();
    return count;
}

/**
 * @brief Writes a sorted array of schedules to a file
 * @param arr Array to write
 * @param size Number of elements
 * @param filename Output file name
 */
void writeSortedArrayToFile(Schedule* arr, int size, const std::string& filename) {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cerr << "no file" << std::endl;
        return;
    }

    // Записываем заголовок
    outFile << "TrainNumber,DepartureDate,TrainType,DepartureTime,TravelMinutes\n";

    // Записываем все элементы массива
    for (int i = 0; i < size-1; ++i) {
        arr[i].writeToCSV(outFile);
    }

    outFile.close();
    
}

int main() {
    int times[] = { 100,1000,1500, 5000, 10000,15000, 20000,30000, 50000, 100000 };

    for (int i : times) {
        std::cout << "==== Sort time " << i << " elements ====" << std::endl;

        Schedule* schedules = new Schedule[i];
        int size = readSchedulesFromCSV("trains_!.csv", schedules, i);

        // std::sort
        Schedule* a1 = new Schedule[size];
        std::copy(schedules, schedules + size, a1);
        auto t1_start = std::chrono::high_resolution_clock::now();
        std::sort(a1, a1 + size);
        auto t1_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dt1 = t1_end - t1_start;
        std::cout << "std::sort: " << dt1.count() << " sec\n";

        // insertSort 
        
        Schedule* a2 = new Schedule[size];
        std::copy(schedules, schedules + size, a2);
        auto t2_start = std::chrono::high_resolution_clock::now();
        insertSort(a2, size);
        auto t2_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dt2 = t2_end - t2_start;
        std::cout << "insertSort: " << dt2.count() << " sec\n";
        delete[] a2;
        

        // quickSortR
        Schedule* a3 = new Schedule[size];
        std::copy(schedules, schedules + size, a3);
        auto t3_start = std::chrono::high_resolution_clock::now();
        quickSortR(a3, size);
        auto t3_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dt3 = t3_end - t3_start;
        std::cout << "quickSortR: " << dt3.count() << " sec\n";
        delete[] a3;

        // mergeSort
        Schedule* a4 = new Schedule[size];
        std::copy(schedules, schedules + size, a4);
        auto t4_start = std::chrono::high_resolution_clock::now();
        merge_sort(a4, 0, size - 1);
        auto t4_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dt4 = t4_end - t4_start;
        std::cout << "mergeSort: " << dt4.count() << " sec\n";

        delete[] a1;
        delete[] a4;
        delete[] schedules;

        std::cout << std::endl;
    }

    return 0;
}

