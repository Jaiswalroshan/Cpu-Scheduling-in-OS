// C++ program to implement Round Robin CPU Scheduling Algorithm

#include <iostream>
#include <algorithm>
#include <queue>
// #include<iomanip>      // cout << fixed << setprecision(2);
using namespace std;

struct process_struct
{
    int pid;
    int at;
    int bt;
    int ct, wt, tat, rt, start_time;
    int bt_remaining;
} ps[100];

bool comparatorAT(struct process_struct a, struct process_struct b)
{
    int x = a.at;
    int y = b.at;
    return x < y;
}

bool comparatorPID(struct process_struct a, struct process_struct b)
{
    int x = a.pid;
    int y = b.pid;
    return x < y;
}
// ------------------------------------------------------------------------------------------------------------------

int main()
{

    int n, index;
    // int cpu_utilization;
    int current_time = 0, max_completion_time;
    int completed = 0;
    float sum_tat = 0, sum_wt = 0, sum_rt = 0;
    cout << "Enter total number of processes: ";
    cin >> n;
    // ------------------------------------------------------------------------------------------------------------------

    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter Process " << i << " Arrival Time: ";
        cin >> ps[i].at;
        ps[i].pid = i;
    }

    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter Process " << i << " Burst Time: ";
        cin >> ps[i].bt;
        ps[i].bt_remaining = ps[i].bt;
    }

    int tq;
    cout << "\nEnter time quanta: ";
    cin >> tq;

    // sort structure on the basis of Arrival time in increasing order
    sort(ps, ps + n, comparatorAT);

    // ------------------------------------------------------------------------------------------------------------------
    bool visited[100] = {false};
    queue<int> q;
    q.push(0);
    visited[0] = true;

    while (completed != n)
    {
        index = q.front();
        q.pop();

        // if (ps[index].bt_remaining == ps[index].bt) // a process picked for the first time
        // {
        //     // ps[index].start_time = max(current_time, ps[index].at);
        //     current_time = ps[index].start_time;
        // }

        if (ps[index].bt_remaining - tq > 0)
        {
            ps[index].bt_remaining -= tq;
            current_time += tq;
        }
        else
        {
            current_time += ps[index].bt_remaining;
            ps[index].bt_remaining = 0;
            completed++;

            ps[index].ct = current_time;
            ps[index].tat = ps[index].ct - ps[index].at;
            ps[index].wt = ps[index].tat - ps[index].bt;
            // ps[index].rt = ps[index].start_time - ps[index].at;

            sum_tat += ps[index].tat;
            sum_wt += ps[index].wt;
            // sum_rt += ps[index].rt;
        }
        // ------------------------------------------------------------------------------------------------------------------

        // check which new Processes needs to be pushed to Ready Queue from Input list
        for (int i = 1; i < n; i++)
        {
            if (ps[i].bt_remaining > 0 && ps[i].at <= current_time && visited[i] == false)
            {
                q.push(i);
                visited[i] = true;
            }
        }
        // check if Process on CPU needs to be pushed to Ready Queue
        if (ps[index].bt_remaining > 0)
            q.push(index);

        // if queue is empty, just add one process from list, whose remaining burst time > 0
        if (q.empty())
        {
            for (int i = 1; i < n; i++)
            {
                if (ps[i].bt_remaining > 0)
                {
                    q.push(i);
                    visited[i] = true;
                    break;
                }
            }
        }
    }

    // ------------------------------------------------------------------------------------------------------------------

    sort(ps, ps + n, comparatorPID);

    // Output
    cout << "\nProcess No.\tAT\tCPU Burst Time\tStart Time\tCT\tTAT\tWT\tRT\n";
    for (int i = 0; i < n; i++)
        cout << i << "\t\t" << ps[i].at << "\t" << ps[i].bt << "\t\t" << ps[i].start_time << "\t\t" << ps[i].ct << "\t" << ps[i].tat << "\t" << ps[i].wt << "\t" << ps[i].rt << endl;
    cout << endl;

    cout << "\nAverage Turn Around time= " << (float)sum_tat / n;
    cout << "\nAverage Waiting Time= " << (float)sum_wt / n;
    // cout << "\nAverage Response Time= " << (float)sum_rt / n;
    return 0;
}