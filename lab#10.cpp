#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Job {
    string desc;
    int priority;
public:
    Job(string d, int p) : desc(d), priority(p) {}
    void execute() {
        cout << desc << endl;
    }
    bool operator<(const Job &other) const {
        return priority < other.priority;
    }
};

template <typename T>
class MaxHeap {
    vector<T> data;
    void heapifyDown(int i) {
        int left = 2*i + 1;
        int right = 2*i + 2;
        int largest = i;
        if (left < (int)data.size() && data[largest] < data[left]) largest = left;
        if (right < (int)data.size() && data[largest] < data[right]) largest = right;
        if (largest != i) {
            swap(data[i], data[largest]);
            heapifyDown(largest);
        }
    }
public:
    void insert(const T &item) {
        data.push_back(item);
        int curr = data.size() - 1;
        while (curr > 0) {
            int parent = (curr - 1) / 2;
            if (data[parent] < data[curr]) {
                swap(data[parent], data[curr]);
                curr = parent;
            } else {
                break;
            }
        }
    }
    T extractMax() {
        if (data.empty()) {
            cerr << "Heap is empty" << endl;
            exit(1);
        }
        T top = data[0];
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) heapifyDown(0);
        return top;
    }
    bool isEmpty() const {
        return data.empty();
    }
};

template <typename T>
class PriorityQueue {
    MaxHeap<T> mh;
public:
    void add(const T &item) {
        mh.insert(item);
    }
    T poll() {
        return mh.extractMax();
    }
    bool isEmpty() const {
        return mh.isEmpty();
    }
};

class JobQueue {
    PriorityQueue<Job> pq;
public:
    void insert(const Job &j) {
        pq.add(j);
    }
    void runHighestPriority() {
        if (!pq.isEmpty()) {
            Job j = pq.poll();
            j.execute();
        }
    }
};

int main() {
    JobQueue jobQueue;
    
    Job jobA("This is job a", 5);
    Job jobB("This is job b", 2);
    Job jobC("This is job c", 9);
    Job jobD("This is job d", 8);
    Job jobE("This is job e", 1);
    jobQueue.insert(jobA);
    jobQueue.insert(jobB);
    jobQueue.insert(jobC);
    jobQueue.insert(jobD);
    jobQueue.insert(jobE);
    
    jobQueue.runHighestPriority(); // Calls jobC.execute() since job C has the highest priority
    jobQueue.runHighestPriority(); // Calls jobD.execute() since job C has the highest priority
    jobQueue.runHighestPriority(); // Calls jobA.execute() since job C has the highest priority
    jobQueue.runHighestPriority(); // Calls jobB.execute() since job C has the highest priority
    jobQueue.runHighestPriority(); // Calls job1.execute() since job C has the highest priority
    return 0;
}
