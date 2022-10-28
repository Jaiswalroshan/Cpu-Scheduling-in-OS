#include <iostream>
#include <string.h>
using namespace std;

class process
{
    public:
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completition_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};
    // ------------------------------------------------------------------------------------------------------------------

int main()
{

    int n;
    struct process p[100];

    int tot_turnaround_time = 0;
    int tot_waiting_time = 0;
    int tot_response_time = 0;
    int tot_idle_time = 0;

    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    // float cpu_utilization;

    // float throughput;

    int burst_remaining[100];
    int is_completed[100];

    memset(is_completed, 0, sizeof(is_completed)); // memset is to set 0 value in all is_completed array;
    // ------------------------------------------------------------------------------------------------------------------

    // enter the number of process
    cout << "enter the number of process: " << endl;
    cin >> n;

    // enter the arrival and burst time of process
    for (int i = 0; i < n; i++)
    {
        cout << "enter the arrival time of process " << i + 1 << ": ";
        cin >> p[i].arrival_time;

        cout << "enter the burst time of process " << i + 1 << ": ";
        cin >> p[i].burst_time;

        p[i].pid = i + 1;
        burst_remaining[i] = p[i].burst_time;
        cout << endl;
    }
    // ------------------------------------------------------------------------------------------------------------------

    int current_time = 0;
    int completed = 0;
    // int prev = 0; // tracking the total idle time

    while (completed != n)
    {
        int idx = -1;
        int mn = 100000;

        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival_time <= current_time && is_completed[i] == 0)
            {
                if (burst_remaining[i] < mn)
                {
                    mn = burst_remaining[i];
                    idx = i;
                }

                if (burst_remaining[i] == mn)
                {
                    if (p[i].arrival_time < p[idx].arrival_time)
                    {
                        mn = burst_remaining[i];
                        idx = i;
                    }
                }
            }
        }
            // ------------------------------------------------------------------------------------------------------------------

        // if the process is found
        if (idx != -1)
        {
            // if the process is allocated for the first time
            // if (burst_remaining[idx] == p[idx].burst_time)
            // {
            //     p[idx].start_time = current_time;
            //     // tot_idle_time += p[idx].start_time - prev;
            // }

            burst_remaining[idx]--;
            current_time++;
            // prev = current_time;
            // if the process is completed
            if (burst_remaining[idx] == 0)
            {
                p[idx].completition_time = current_time;
                p[idx].turnaround_time = p[idx].completition_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                // p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

                tot_turnaround_time += p[idx].turnaround_time;
                tot_waiting_time += p[idx].waiting_time;
                // tot_response_time += p[idx].response_time;

                is_completed[idx] = 1;
                completed++;
            }
        }
        else
        {
            current_time++;
        }
    }
        // ------------------------------------------------------------------------------------------------------------------


    avg_turnaround_time = (float)tot_turnaround_time / n;
    avg_waiting_time = (float)tot_waiting_time / n;
    // avg_response_time = (float)tot_response_time / n;

    // ------------------------------------------------------------------------------------------------------------------


    cout << "p\t"
         << "AT\t"
         << "BT\t"
         << "ST\t"
         << "CT\t"
         << "TAT\t"
         << "WT\t"
        //  << "RT\t"
         << "\n"
         << endl;

    for (int i = 0; i < n; i++)
    {
        cout << p[i].pid << "\t"
             << p[i].arrival_time << "\t"
             << p[i].burst_time << "\t"
             << p[i].start_time << "\t"
             << p[i].completition_time << "\t"
             << p[i].turnaround_time << "\t"
             << p[i].waiting_time << "\t"
            //  << p[i].response_time << "\t"
             << endl;
    }

    cout << "average turnaround time = " << avg_turnaround_time << endl;
    cout << "average waiting time = " << avg_waiting_time << endl;
    // cout << "average response time = " << avg_response_time << endl;
}