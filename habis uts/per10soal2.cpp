#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

const int AGING_THRESHOLD = 5;
const int AGING_INCREMENT = 1;

struct Proses {
    string nama;
    int AT;
    int BT;
    int RT_sisa;
    int priority_awal;
    int priority_saat_ini;
    int CT = 0;
    int TAT = 0;
    int WT = 0;
    int RT = -1;
    int waktuMulai = -1;
    int waktuMenunggu = 0;
    int priorityChangeCount = 0;
    int preemptionCount = 0;
    bool isCompleted = false;
};

int cariPriorityTertinggi(vector<Proses>& proses, int currentTime) {
    int minPriority = numeric_limits<int>::max();
    int indexTerpilih = -1;

    for (int i = 0; i < proses.size(); ++i) {
        if (proses[i].AT <= currentTime && !proses[i].isCompleted && proses[i].priority_saat_ini < minPriority) {
            minPriority = proses[i].priority_saat_ini;
            indexTerpilih = i;
        }
    }
    return indexTerpilih;
}

void jalankanPriorityAging(vector<Proses>& proses) {
    int n = proses.size();
    int completed = 0;
    int currentTime = 0;
    int preemptionTotal = 0;
    int prevProcessIndex = -1;
    int totalPriorityChanges = 0;

    vector<pair<string, int>> ganttChart;

    while (completed < n) {
        for (int i = 0; i < n; ++i) {
            if (!proses[i].isCompleted && proses[i].AT <= currentTime) {
                
                if (i != prevProcessIndex) {
                    proses[i].waktuMenunggu++;
                }

                if (proses[i].waktuMenunggu > AGING_THRESHOLD && proses[i].priority_saat_ini > 1) {
                    proses[i].priority_saat_ini -= AGING_INCREMENT;
                    proses[i].waktuMenunggu = 0;
                    proses[i].priorityChangeCount++;
                    totalPriorityChanges++;
                }
            }
        }

        int currentIndex = cariPriorityTertinggi(proses, currentTime);

        if (currentIndex == -1) {
            int nextAT = numeric_limits<int>::max();
            for(const auto& p : proses) {
                if(!p.isCompleted && p.AT > currentTime) {
                    nextAT = min(nextAT, p.AT);
                }
            }
            if (nextAT != numeric_limits<int>::max()) {
                if (!ganttChart.empty() && ganttChart.back().first == "IDLE") {
                    ganttChart.back().second = nextAT;
                } else {
                    ganttChart.push_back({"IDLE", nextAT});
                }
                currentTime = nextAT;
                continue;
            } else {
                break;
            }
        }

        if (prevProcessIndex != -1 && prevProcessIndex != currentIndex && proses[prevProcessIndex].RT_sisa > 0) {
            proses[prevProcessIndex].preemptionCount++;
            preemptionTotal++;
            ganttChart.back().second = currentTime;
        }

        if (proses[currentIndex].waktuMulai == -1) {
            proses[currentIndex].waktuMulai = currentTime;
            proses[currentIndex].RT = currentTime - proses[currentIndex].AT;
        }
        
        proses[currentIndex].RT_sisa--;
        currentTime++;
        prevProcessIndex = currentIndex;
        
        proses[currentIndex].waktuMenunggu = 0; 

        if (!ganttChart.empty() && ganttChart.back().first == proses[currentIndex].nama) {
            
        } else {
            ganttChart.push_back({proses[currentIndex].nama, currentTime});
        }

        if (proses[currentIndex].RT_sisa == 0) {
            proses[currentIndex].isCompleted = true;
            completed++;
            proses[currentIndex].CT = currentTime;
            
            proses[currentIndex].TAT = proses[currentIndex].CT - proses[currentIndex].AT;
            proses[currentIndex].WT = proses[currentIndex].TAT - proses[currentIndex].BT;
        }
    }

    cout << "\n======================================================\n";
    cout << "        HASIL PRIORITY SCHEDULING (PREEMPTIVE + AGING)\n";
    cout << "Aging Rule: Priority naik 1 jika menunggu > " << AGING_THRESHOLD << " satuan waktu.\n";
    cout << "======================================================\n";

    cout << "Gantt Chart Dinamis:\n";
    cout << "|";
    int lastTime = 0;
    for (const auto& entry : ganttChart) {
        int duration = entry.second - lastTime;
        if (duration > 0) {
            cout << setw(duration * 2) << entry.first << "|";
            lastTime = entry.second;
        }
    }
    cout << "\n0";
    lastTime = 0;
    for (const auto& entry : ganttChart) {
        int duration = entry.second - lastTime;
        if (duration > 0) {
            cout << setw(duration * 2) << entry.second;
            lastTime = entry.second;
        }
    }
    cout << "\n\n";

    cout << "Tabel Hasil Lengkap:\n";
    cout << "-------------------------------------------------------------------------------------------------------\n";
    cout << "| Proses | AT | BT | Prio Awal | Prio Akhir | CT | TAT | WT | RT | P Change | Preempt | Starvation |\n";
    cout << "-------------------------------------------------------------------------------------------------------\n";

    double totalTAT = 0, totalWT = 0, totalRT = 0;

    for (const auto& p : proses) {
        totalTAT += p.TAT;
        totalWT += p.WT;
        totalRT += p.RT;
        
        string starvationStatus = (p.waktuMulai == -1 && p.isCompleted == false) ? "YA" : "TIDAK";

        cout << "| " << setw(5) << p.nama << " | " << setw(2) << p.AT << " | " << setw(2) << p.BT << " | "
             << setw(9) << p.priority_awal << " | " << setw(10) << p.priority_saat_ini << " | " 
             << setw(2) << p.CT << " | " << setw(3) << p.TAT << " | " << setw(2) << p.WT << " | "
             << setw(2) << p.RT << " | " << setw(8) << p.priorityChangeCount << " | " 
             << setw(7) << p.preemptionCount << " | " 
             << setw(10) << starvationStatus << " |\n";
    }
    cout << "-------------------------------------------------------------------------------------------------------\n";

    cout << fixed << setprecision(2);
    cout << "\n>> Rata-rata Turnaround Time (TAT): " << totalTAT / n << endl;
    cout << ">> Rata-rata Waiting Time (WT): " << totalWT / n << endl;
    cout << ">> Rata-rata Response Time (RT): " << totalRT / n << endl;

    cout << "\n------------------------------------------------------\n";
    cout << "Analisis Preemption dan Starvation:\n";
    cout << "a. Total Perubahan Prioritas (Aging): " << totalPriorityChanges << " kali.\n";
    cout << "b. Starvation:\n";
    cout << "   - Fitur Aging didesain untuk mencegah starvation. Tanpa Aging, proses berprioritas rendah bisa menunggu tak terbatas.\n";
    cout << "   - Dalam simulasi ini, tidak ada proses yang mengalami starvation berkat implementasi Aging.\n";
    cout << "------------------------------------------------------\n";
}

void inputProses(vector<Proses>& proses) {
    int n;
    cout << "Masukkan jumlah proses: ";
    while (!(cin >> n) || n <= 0) {
        cout << "Input tidak valid. Masukkan angka positif: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

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

        cout << "Priority (1=Tertinggi, Angka besar=Terendah): ";
        while (!(cin >> p.priority_awal) || p.priority_awal <= 0) {
            cout << "Input tidak valid. Masukkan angka positif: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        p.RT_sisa = p.BT;
        p.priority_saat_ini = p.priority_awal;
        proses.push_back(p);
    }
}

int main() {
    vector<Proses> prosesCustom;
    
    inputProses(prosesCustom);
    
    if (!prosesCustom.empty()) {
        jalankanPriorityAging(prosesCustom);
    }
    
    return 0;
}