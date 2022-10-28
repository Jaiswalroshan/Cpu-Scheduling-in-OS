#include <iostream>
#include <algorithm>
using namespace std;

class pcb
{
public:
    int pid, arrival, burst, complete, waiting, turnaround;
};

bool compareBur(pcb a, pcb b)
{
    int x = a.burst;
    int y = b.burst;
    return x < y;
}

bool compareArr(pcb a, pcb b)
{
    int x = a.arrival;
    int y = b.arrival;
    return x < y;
}
// ------------------------------------------------------------------------------------------------------------------

int main()
{
    float tot_wait = 0, avg_wait = 0;
    float tot_turn = 0, avg_turn = 0;
    float sum = 0;
    int num;
    cout << "enter the number of process" << endl;
    cin >> num;

    pcb p[10];
    // entering the arrival and burst time of process
    for (int i = 0; i < num; i++)
    {
        cout << "enter the arrival and burst time of process " << i + 1 << endl;
        cin >> p[i].arrival;
        cin >> p[i].burst;
        p[i].pid = i + 1;
    }
    // ------------------------------------------------------------------------------------------------------------------

    // arranging the process according to their burst time
    // confuse state for the first time

    // for(int i=0;i<num;i++){

    //     for(int j=0;j<num-i-1;j++){

    //         if(p[j].burst>p[j+1].burst){
    //             swap(p[j],p[j+1]);
    //         }
    //     }

    // }

    sort(p, p + num, compareBur);
    // ------------------------------------------------------------------------------------------------------------------

    // find the turnaround and waiting time
    for (int i = 0; i < num; i++)
    {
        // p[i].waiting=sum;
        sum += p[i].burst;
        p[i].complete = sum;
        p[i].turnaround = p[i].complete - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
    }

    // sort(p, p + num, compareArr);
    // ------------------------------------------------------------------------------------------------------------------

    cout << "pid\t arrivial\t burst\t complete\t turnarround\t waiting\t" << endl;

    // printing the data in table
    for (int i = 0; i < num; i++)
    {
        cout << p[i].pid << "\t" << p[i].arrival << "\t" << p[i].burst << "\t" << p[i].complete << "\t" << p[i].turnaround << "\t" << p[i].waiting << "\t" << endl;
        tot_wait += p[i].waiting;
        tot_turn += p[i].turnaround;
    }
    // ------------------------------------------------------------------------------------------------------------------

    // printing the avg turnaround and waiting time
    cout << "total turnaround time = " << tot_turn << endl;
    cout << "average turnaround time = " << tot_turn / num << endl;
    cout << "total waiting time = " << tot_wait << endl;
    cout << "average waiting time = " << tot_wait / num << endl;
}
