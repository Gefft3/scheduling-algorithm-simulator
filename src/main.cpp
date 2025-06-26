#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

class Process {
public:
    int pid;
    int arrival;
    int burst;
    int remaining;    // para preemptivos
    int priority;     // só p/ prioridade

    Process(int id=0, int arr=0, int br=0, int pr=0)
        : pid(id), arrival(arr), burst(br), remaining(br), priority(pr) {}
};

void log(int time, int pid, const string& state) {
    cout << "[t=" << time << "] P" << pid << " " << state << "\n";
}

void fcfs(vector<Process> P) {
    sort(P.begin(), P.end(), [](auto &a, auto &b){ return a.arrival < b.arrival; });
    int t = 0;
    for (auto &p : P) {
        if (t < p.arrival) { log(t, -1, "idle"); t = p.arrival; }
        log(t, p.pid, "start");
        t += p.burst;
        log(t, p.pid, "finish");
    }
}

void sjf_np(vector<Process> P) {
    int t = 0, done = 0, n = P.size();
    vector<bool> used(n, false);
    while (done < n) {
        int idx = -1, minb = INT_MAX;
        for (int i = 0; i < n; ++i)
            if (!used[i] && P[i].arrival <= t && P[i].burst < minb)
                minb = P[i].burst, idx = i;
        if (idx < 0) { log(t, -1, "idle"); t++; continue; }
        auto &p = P[idx]; used[idx] = true; ++done;
        log(t, p.pid, "start");
        t += p.burst;
        log(t, p.pid, "finish");
    }
}

void sjf_p(vector<Process> P) {
    int t = 0, done = 0, n = P.size();
    for (auto &p : P) p.remaining = p.burst;
    while (done < n) {
        int idx = -1, minr = INT_MAX;
        for (int i = 0; i < n; ++i)
            if (P[i].arrival <= t && P[i].remaining > 0 && P[i].remaining < minr)
                minr = P[i].remaining, idx = i;
        if (idx < 0) { log(t, -1, "idle"); t++; continue; }
        auto &p = P[idx]; log(t, p.pid, "run");
        --p.remaining; ++t;
        if (p.remaining == 0) { log(t, p.pid, "finish"); ++done; }
    }
}

void priority(vector<Process> P) {
    int t = 0, done = 0, n = P.size();
    vector<bool> used(n, false);
    while (done < n) {
        int idx = -1, minpr = INT_MAX;
        for (int i = 0; i < n; ++i)
            if (!used[i] && P[i].arrival <= t && P[i].priority < minpr)
                minpr = P[i].priority, idx = i;
        if (idx < 0) { log(t, -1, "idle"); t++; continue; }
        auto &p = P[idx]; used[idx] = true; ++done;
        log(t, p.pid, "start");
        t += p.burst;
        log(t, p.pid, "finish");
    }
}

void round_robin(vector<Process> P, int q) {
    queue<int> Q;
    int t = 0, n = P.size(), done = 0;
    for (auto &p : P) p.remaining = p.burst;
    while (done < n) {
        for (int i = 0; i < n; ++i) {
            if (P[i].arrival <= t && P[i].remaining > 0) {
                // Check if i is already in Q
                bool inQ = false;
                queue<int> tmpQ = Q;
                while (!tmpQ.empty()) {
                    if (tmpQ.front() == i) { inQ = true; break; }
                    tmpQ.pop();
                }
                if (!inQ)
                    Q.push(i);
            }
        }
        if (Q.empty()) { log(t, -1, "idle"); t++; continue; }
        int i = Q.front(); Q.pop(); auto &p = P[i];
        log(t, p.pid, "run");
        int dt = min(q, p.remaining);
        p.remaining -= dt; t += dt;
        for (int j = 0; j < n; ++j)
            if (P[j].arrival > t-dt && P[j].arrival <= t && P[j].remaining > 0)
                Q.push(j);
        if (p.remaining > 0) {
            Q.push(i);
            log(t, p.pid, "preempt");
        } else {
            ++done;
            log(t, p.pid, "finish");
        }
    }
}

int main() {
    int opt;
    cout << "1.FCFS\n2.SJF Não Preemptivo\n3.SJF Preemptivo\n4.Prioridade\n5.RR\n>";
    cin >> opt;
    int n; cout << "Number of processes::\n>"; cin >> n;
    vector<Process> P;
    P.reserve(n);
    for (int i = 0; i < n; ++i) {
        int arr, br, pr = 0;
        cout << "Process"<< i+1 << " arrival burst:";
        cin >> arr >> br;
        if (opt == 4) { cout << " priority:"; cin >> pr; }
        P.emplace_back(i+1, arr, br, pr);
    }
    int q = 0;
    if (opt == 5) { cout << "Quantum:\n>"; cin >> q; }
    switch (opt) {
        case 1: fcfs(P); break;
        case 2: sjf_np(P); break;
        case 3: sjf_p(P); break;
        case 4: priority(P); break;
        case 5: round_robin(P, q); break;
        default: return 1;
    }
    return 0;
}
