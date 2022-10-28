#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

struct process
{
public:
    int pid, arrival, priority, burst, complete, turnaround, waiting, response;
};
// ------------------------------------------------------------------------------------------------------------------

bool comparePri(process a, process b)
{
    int x = a.priority;
    int y = b.priority;
    return x < y;
}

bool compareArr(process a, process b)
{
    int x = a.arrival;
    int y = b.arrival;
    return x < y;
}
// ------------------------------------------------------------------------------------------------------------------

int main()
{
    float tot_turnaround = 0;
    float tot_waiting = 0;

    int n;
    cout << "enter the number of process" << endl;
    cin >> n;

    cout << fixed << setprecision(2);

    process p[10];

    for (int i = 0; i < n; i++)
    {
        cout << "enter the arrival time of " << i + 1 << " process : ";
        cin >> p[i].arrival;

        cout << "enter the burst time of " << i + 1 << " process : ";
        cin >> p[i].burst;

        cout << "enter the priority of " << i + 1 << " process : ";
        cin >> p[i].priority;

        p[i].pid = i + 1;
    }
    // ------------------------------------------------------------------------------------------------------------------

    sort(p, p + n, comparePri);

    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += p[i].burst;
        p[i].complete = sum;
        p[i].turnaround = p[i].complete - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
    }

    sort(p, p + n, compareArr);
    // ------------------------------------------------------------------------------------------------------------------

    cout << "\npid\tarrival\tburst\tpriority\tCT\tTAT\tWT\tRT\t\n";
    for (int i = 0; i < n; i++)
    {
        cout << p[i].pid << "\t" << p[i].arrival << "\t" << p[i].burst << "\t" << p[i].priority << "\t" << p[i].complete << "\t" << p[i].turnaround << "\t" << p[i].waiting << "\t" << p[i].response << "\t" << endl;
        tot_turnaround += p[i].turnaround;
        tot_waiting += p[i].waiting;
    }
    // ------------------------------------------------------------------------------------------------------------------

    cout << endl;
    cout << "average turn = " << tot_turnaround / n << endl;
    cout << "avg waiting = " << tot_waiting / n << endl;
}