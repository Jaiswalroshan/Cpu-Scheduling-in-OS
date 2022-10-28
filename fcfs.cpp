#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

class pcb
{
public:
    int pid, arrival, burst, waiting, turnaround, complete;
};

// ------------------------------------------------------------------------------------------------------------------

bool compareArr(pcb a, pcb b)
{
    int x = a.arrival;
    int y = b.arrival;
    return x < y;
}

int main()
{
    int num;
    float sum = 0;
    float avg_turn = 0, total_turn = 0;
    float total_wait = 0, avg_wait = 0;
    pcb p[10];
    cout << "enter the number of process" << endl;
    cin >> num;

    // for the entering the arrival and burst time
    for (int i = 0; i < num; i++)
    {
        cout << "enter the arrival and burst time for process" << i + 1 << endl;
        cin >> p[i].arrival;
        cin >> p[i].burst;
        p[i].pid = i + 1;
    }

    // arranging the process according to their arrival time
    // for (int i = 0; i < num - 1; i++)
    // {
    //     for (int j = 0; j - i - 1; j++)
    //     {
    //         if (p[j].arrival > p[j + 1].arrival)
    //         {
    //             swap(p[j], p[j + 1]);
    //         }
    //     }
    // }
    sort(p,p+num,compareArr);
    // ------------------------------------------------------------------------------------------------------------------

    // find the turnaround time and waiting time , and completion
    for (int i = 0; i < num; i++)
    {
        sum += p[i].burst;
        p[i].complete = sum;
        p[i].turnaround = p[i].complete - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
    }

    // ------------------------------------------------------------------------------------------------------------------

    cout << "pid \t arrival \t burst \t complete \t waiting \t turnaround\t" << endl;
    for (int i = 0; i < num; i++)
    {
        cout << p[i].pid << "\t" << p[i].arrival << "\t" << p[i].burst << "\t" << p[i].complete << "\t" << p[i].waiting << "\t" << p[i].turnaround << "\t" << endl;
        total_turn += p[i].turnaround;
        total_wait += p[i].waiting;
    }
    // ------------------------------------------------------------------------------------------------------------------


    cout << "total waiting time : " << total_wait << endl;
    cout << "total average-waiting time : " << total_wait / num << endl;
    cout << "total turnaround time is : " << total_turn << endl;
    cout << "average turnaround time is : " << total_turn / num << endl;
}
// ------------------------------------------------------------------------------------------------------------------

