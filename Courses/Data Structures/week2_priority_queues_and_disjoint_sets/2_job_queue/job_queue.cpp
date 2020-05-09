#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::vector;
using std::cin;
using std::cout;
using std::priority_queue;

class Worker {
public:
    int id_;
    long long release_time_;

    Worker(int id): id_(id), release_time_(0) {}

    bool operator<(const Worker& obj) const {
        if (release_time_ == obj.release_time_)
            return id_ > obj.id_;
        return release_time_ > obj.release_time_;
    }
    
    bool operator>(const Worker& obj) const {
        if (release_time_ == obj.release_time_)
            return id_ < obj.id_;
        return release_time_ < obj.release_time_;
    }
};

class JobQueue {
private:
    int num_workers_;
    vector<int> jobs_;

    vector<int> assigned_workers_;
    vector<long long> start_times_;

    void WriteResponse() const {
        for (int i = 0; i < (int)jobs_.size(); ++i) {
            cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
        }
    }

    void ReadData() {
        int m;
        cin >> num_workers_ >> m;
        jobs_.resize(m);
        for (int i = 0; i < m; ++i)
            cin >> jobs_[i];
    }

    void AssignJobs() {
        // TODO: replace this code with a faster algorithm.
        assigned_workers_.resize(jobs_.size());
        start_times_.resize(jobs_.size());
        priority_queue <Worker> pq;

        for (int i = 0; i < num_workers_; ++i) {
            pq.push(Worker(i));
        }

        for (int i = 0; i < (int)jobs_.size(); ++i) {
            Worker worker = pq.top();
            pq.pop();
            assigned_workers_[i] = worker.id_;
            start_times_[i] = worker.release_time_;
            worker.release_time_ += jobs_[i];
            pq.push(worker);
        }
    }

public:
    void Solve() {
        ReadData();
        AssignJobs();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    JobQueue job_queue;
    job_queue.Solve();
    return 0;
}
