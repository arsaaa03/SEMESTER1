#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include <limits>
#include <cmath>

using namespace std;

const int TIME_QUANTUM = 2;
const int QUEUE_RR_PRIORITY = 1;
const int QUEUE_FCFS_PRIORITY = 2;

struct Proses {
    string nama;
    int AT;
    int BT;
    int queueLevel;
    int RT_sisa;
    int CT = 0;
    int TAT = 0;
    int WT = 0;
    int RT = -1;
    int waktuMulai = -1;
    bool isCompleted = false;
    int currentExecution = 0;
};

int getNextFCFSProcessIndex(vector<Proses>& processes, int currentTime) {
    int nextProcessIndex = -1;
    int earliestAT = numeric_limits<int>::max();

    for (int i = 0; i < processes.size(); ++i) {
        if (processes[i].queueLevel == QUEUE_FCFS_PRIORITY && !processes[i].isCompleted && processes[i].AT <= currentTime) {
            if (processes[i].AT < earliestAT) {
                earliestAT = processes[i].AT;
                nextProcessIndex = i;
            } else if (processes[i].AT == earliestAT && nextProcessIndex != -1 && processes[i].nama < processes[nextProcessIndex].nama) {
                nextProcessIndex = i;
            }
        }
    }
    return nextProcessIndex;
}

void jalankanMLQ(vector<Proses>& processes) {
    int n = processes.size();
    int completed = 0;
    int currentTime = 0;
    int prevProcessIndex = -1;

    vector<int> rrReadyQueue; 
    vector<pair<string, string>> ganttChart;

    while (completed < n) {
        for (int i = 0; i < n; ++i) {
            if (processes[i].AT == currentTime) {
                if (processes[i].queueLevel == QUEUE_RR_PRIORITY) {
                    bool alreadyAdded = false;
                    for (int index : rrReadyQueue) {
                        if (index == i) {
                            alreadyAdded = true;
                            break;
                        }
                    }
                    if (!alreadyAdded) {
                        rrReadyQueue.push_back(i);
                    }
                }
            }
        }

        int currentIndex = -1;

        if (!rrReadyQueue.empty()) {
            currentIndex = rrReadyQueue.front();
        } else {
            currentIndex = getNextFCFSProcessIndex(processes, currentTime);
        }

        if (currentIndex == -1) {
            int nextAT = numeric_limits<int>::max();
            for(const auto& p : processes) {
                if(!p.isCompleted && p.AT > currentTime) {
                    nextAT = min(nextAT, p.AT);
                }
            }
            if (nextAT != numeric_limits<int>::max()) {
                string lastProcess = ganttChart.empty() ? "" : ganttChart.back().first;
                if (lastProcess == "IDLE") {
                    ganttChart.back().second = "IDLE/" + to_string(nextAT);
                } else {
                    ganttChart.push_back({"IDLE", "IDLE/" + to_string(nextAT)});
                }
                currentTime = nextAT;
                continue;
            } else {
                break;
            }
        }

        if (prevProcessIndex != -1 && prevProcessIndex != currentIndex) {
            ganttChart.back().second = processes[prevProcessIndex].nama + "-" + to_string(processes[prevProcessIndex].queueLevel) + "/" + to_string(currentTime);
        }

        if (processes[currentIndex].waktuMulai == -1) {
            processes[currentIndex].waktuMulai = currentTime;
            processes[currentIndex].RT = currentTime - processes[currentIndex].AT;
        }

        int executionTime = 1;
        
        processes[currentIndex].RT_sisa -= executionTime;
        currentTime += executionTime;

        if (processes[currentIndex].queueLevel == QUEUE_RR_PRIORITY) {
            processes[currentIndex].currentExecution += executionTime;
        }

        string currentGanttLabel = processes[currentIndex].nama + "-" + to_string(processes[currentIndex].queueLevel);
        string lastProcess = ganttChart.empty() ? "" : ganttChart.back().first;
        
        if (lastProcess.find(currentGanttLabel) != string::npos) {
            
        } else {
            ganttChart.push_back({currentGanttLabel, currentGanttLabel + "/" + to_string(currentTime)});
        }
        
        if (processes[currentIndex].RT_sisa == 0) {
            processes[currentIndex].isCompleted = true;
            completed++;
            processes[currentIndex].CT = currentTime;
            processes[currentIndex].TAT = processes[currentIndex].CT - processes[currentIndex].AT;
            processes[currentIndex].WT = processes[currentIndex].TAT - processes[currentIndex].BT;
            processes[currentIndex].currentExecution = 0;
            
            if (processes[currentIndex].queueLevel == QUEUE_RR_PRIORITY) {
                if (!rrReadyQueue.empty() && rrReadyQueue.front() == currentIndex) {
                    rrReadyQueue.erase(rrReadyQueue.begin());
                }
            }
            
            ganttChart.back().second = currentGanttLabel + "/" + to_string(currentTime);

        } else if (processes[currentIndex].queueLevel == QUEUE_RR_PRIORITY && processes[currentIndex].currentExecution == TIME_QUANTUM) {
            processes[currentIndex].currentExecution = 0;
            
            if (!rrReadyQueue.empty() && rrReadyQueue.front() == currentIndex) {
                rrReadyQueue.erase(rrReadyQueue.begin());
                rrReadyQueue.push_back(currentIndex);
            }
            
            ganttChart.back().second = currentGanttLabel + "/" + to_string(currentTime);
        }
        
        prevProcessIndex = currentIndex;
    }

    cout << "\n======================================================\n";
    cout << "        HASIL MULTI-LEVEL QUEUE (RR Q=2 | FCFS)\n";
    cout << "======================================================\n";

    cout << "Gantt Chart Multi-level:\n";
    cout << "--------------------------------------------------------------------------\n";
    
    cout << "|";
    int lastTime = 0;
    for (const auto& entry : ganttChart) {
        string label = entry.first;
        size_t pos = label.find("-");
        string name = (pos == string::npos) ? label : label.substr(0, pos);
        
        string timeStr = entry.second;
        size_t slashPos = timeStr.find("/");
        int endTime = stoi(timeStr.substr(slashPos + 1));
        
        int startTime = lastTime;
        int duration = endTime - startTime;

        if (duration > 0) {
            cout << setw(duration * 2) << name << "|";
        }
    }
    cout << "\n";
    
    cout << "|";
    lastTime = 0;
    for (const auto& entry : ganttChart) {
        string label = entry.first;
        size_t pos = label.find("-");
        string queue = (pos == string::npos) ? label : "Q" + label.substr(pos + 1);
        
        string timeStr = entry.second;
        size_t slashPos = timeStr.find("/");
        int endTime = stoi(timeStr.substr(slashPos + 1));
        
        int startTime = lastTime;
        int duration = endTime - startTime;
        
        if (duration > 0) {
            cout << setw(duration * 2) << queue << "|";
            lastTime = endTime;
        }
    }
    cout << "\n";

    cout << "0";
    lastTime = 0;
    for (const auto& entry : ganttChart) {
        string timeStr = entry.second;
        size_t slashPos = timeStr.find("/");
        int endTime = stoi(timeStr.substr(slashPos + 1));
        
        int duration = endTime - lastTime;
        if (duration > 0) {
            cout << setw(duration * 2) << endTime;
            lastTime = endTime;
        }
    }
    cout << "\n--------------------------------------------------------------------------\n\n";

    cout << "Tabel Hasil Lengkap:\n";
    cout << "------------------------------------------------------------\n";
    cout << "| Proses | AT | BT | Queue | CT | TAT | WT | RT |\n";
    cout << "------------------------------------------------------------\n";

    double totalTAT = 0, totalWT = 0, totalRT = 0;
    double totalTAT_Q1 = 0, totalWT_Q1 = 0;
    double totalTAT_Q2 = 0, totalWT_Q2 = 0;
    int countQ1 = 0, countQ2 = 0;

    for (const auto& p : processes) {
        totalTAT += p.TAT;
        totalWT += p.WT;
        totalRT += p.RT;
        
        if (p.queueLevel == QUEUE_RR_PRIORITY) {
            totalTAT_Q1 += p.TAT;
            totalWT_Q1 += p.WT;
            countQ1++;
        } else {
            totalTAT_Q2 += p.TAT;
            totalWT_Q2 += p.WT;
            countQ2++;
        }

        cout << "| " << setw(5) << p.nama << " | " << setw(2) << p.AT << " | " << setw(2) << p.BT << " | "
             << setw(5) << p.queueLevel << " | " << setw(2) << p.CT << " | " << setw(3) << p.TAT << " | " 
             << setw(2) << p.WT << " | " << setw(2) << p.RT << " |\n";
    }
    cout << "------------------------------------------------------------\n";

    cout << fixed << setprecision(2);
    cout << "\n>> Rata-rata Turnaround Time (Total): " << totalTAT / n << endl;
    cout << ">> Rata-rata Waiting Time (Total): " << totalWT / n << endl;
    cout << ">> Rata-rata Response Time (Total): " << totalRT / n << endl;

    cout << "\n------------------------------------------------------\n";
    cout << "Tantangan Tambahan:\n";

    double avgWT_Q1 = countQ1 > 0 ? totalWT_Q1 / countQ1 : 0.0;
    double avgTAT_Q1 = countQ1 > 0 ? totalTAT_Q1 / countQ1 : 0.0;
    double avgWT_Q2 = countQ2 > 0 ? totalWT_Q2 / countQ2 : 0.0;
    double avgTAT_Q2 = countQ2 > 0 ? totalTAT_Q2 / countQ2 : 0.0;

    cout << "a. Rata-rata WT & TAT per Queue:\n";
    cout << "   - Queue 1 (RR): Rata-rata WT = " << avgWT_Q1 << ", Rata-rata TAT = " << avgTAT_Q1 << endl;
    cout << "   - Queue 2 (FCFS): Rata-rata WT = " << avgWT_Q2 << ", Rata-rata TAT = " << avgTAT_Q2 << endl;

    cout << "   Perbandingan Rata-rata WT (Q1:Q2) = " << avgWT_Q1 << " : " << avgWT_Q2 << endl;
    cout << "   Perbandingan Rata-rata TAT (Q1:Q2) = " << avgTAT_Q1 << " : " << avgTAT_Q2 << endl;
    
    cout << "b. Kelebihan & Kelemahan MLQ pada kasus ini:\n";
    cout << "   - Kelebihan: Prioritas pada Queue 1 (RR) memastikan proses-proses interaktif mendapatkan waktu CPU yang cepat (low response time). Hal ini meningkatkan responsivitas sistem.\n";
    cout << "   - Kelemahan: Proses di Queue 2 (FCFS) dapat mengalami waktu tunggu yang sangat lama (soft starvation) jika ada aliran proses yang konstan di Queue 1, karena Queue 1 selalu diprioritaskan dan RR bersifat preemptive.\n";
    cout << "------------------------------------------------------\n";
}

void inputProses(vector<Proses>& processes) {
    int n;
    cout << "Masukkan jumlah proses: ";
    while (!(cin >> n) || n <= 0) {
        cout << "Input tidak valid. Masukkan angka positif: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nLevel Queue:\n";
    cout << "1 = Round Robin (Quantum = " << TIME_QUANTUM << ")\n";
    cout << "2 = FCFS\n";

    for (int i = 0; i < n; ++i) {
        Proses p;
        p.nama = "P" + to_string(i + 1);

        cout << "\n--- Proses " << p.nama << " ---\n";
        cout << "Arrival Time (AT): ";
        while (!(cin >> p.AT) || p.AT < 0) {
            cout << "Input tidak valid. Masukkan angka non-negatif: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Burst Time (BT): ";
        while (!(cin >> p.BT) || p.BT <= 0) {
            cout << "Input tidak valid. Masukkan angka positif: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Queue Level (1 atau 2): ";
        while (!(cin >> p.queueLevel) || (p.queueLevel != 1 && p.queueLevel != 2)) {
            cout << "Input tidak valid. Masukkan 1 atau 2: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        p.RT_sisa = p.BT;
        processes.push_back(p);
    }
}

int main() {
    vector<Proses> processesCustom;
    
    inputProses(processesCustom);
    
    if (!processesCustom.empty()) {
        sort(processesCustom.begin(), processesCustom.end(), [](const Proses& a, const Proses& b) {
            return a.AT < b.AT;
        });
        
        jalankanMLQ(processesCustom);
    }
    
    return 0;
}