#include <iostream>
using namespace std;

struct process {
    int id;
    int time_input;
    int time_process;
    int priority;
    int waiting_time;
    int finished_time;
    int minus;
};

struct Grantt {
    int *name;
    int *mark;
    int amount;
};

Grantt priority(process *a, int n) {
    int current = -1, smallest, count = 0; // count for counting finished process
    float ave = 0.0;
    Grantt G;
    G.name = new int[n*2];  // Increased due to possible preemptions
    G.mark = new int[n*2+1];
    G.amount = 0;
    G.mark[0] = 0;

    process *X = new process[n+1];
    for(int i = 0; i < n; i++) {
        X[i] = a[i];
        X[i].waiting_time = 0;
        X[i].minus = X[i].time_process;
    }
    X[n].priority = 9999;  // sentinel value
    G.amount = 0;
    int time = 0;

    while(count != n) {
        //finding which process has arrived first
        smallest = n;
        for(int i = 0; i < n; i++) {
            if(X[i].time_input <= time && X[i].priority < X[smallest].priority && X[i].time_process > 0) {
                smallest = i;
            }
        }

        //if hasn't update smallest -> no processes have arrived
        if(smallest == n) {
            time ++;
            continue;
        }

        if(current != smallest) {   //when the current is not the smallest prioriy, we've to update 
            if(current != -1 && X[current].time_process > 0) {
                G.name[G.amount] = X[current].id;
                G.mark[G.amount + 1] = time;
                G.amount++; 
                current = smallest;
            }
            else {
                current = smallest;
                G.name[G.amount] = X[current].id;
            }
        }
        
        //run
        if(current != -1) {
          X[current].time_process--;
          time++;
          
          if(X[current].time_process == 0) {
            G.name[G.amount]= X[current].id;
            G.mark[G.amount + 1] = time;
            X[current].finished_time = time - X[current].time_input;
            count++;
            G.amount++;
            current = -1;
          }
        }       
    }  

    cout << "Waiting time: " << endl;
    for(int i = 0; i < n; i++) {
        X[i].waiting_time = X[i].finished_time - X[i].minus;
        cout << "P" << X[i].id << endl;
        cout << X[i].waiting_time << "   " << endl;
        ave += X[i].waiting_time;
    }
    cout << "Average waiting time: " << (ave/(float)n) << endl;

    delete[] X;
    return G;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    
    process *a = new process[n];
    for(int i = 0; i < n; i++) {
        cout << "Enter id: ";
        cin >> a[i].id;
        cout << "Enter time arrival: ";
        cin >> a[i].time_input;
        cout << "Enter time processing: ";
        cin >> a[i].time_process;
        cout << "Enter priority: ";
        cin >> a[i].priority;
    }
    
    Grantt G = priority(a, n);
    cout <<"PRIORITY PREEMTIVE" << endl;
    for(int i = 0; i < G.amount; i++) {
        cout << "P" << G.name[i] << "   " << endl;
        cout << G.mark[i] << "   " << endl;
    }

    delete[] a;
    delete[] G.name;
    delete[] G.mark;

    return 0;
}