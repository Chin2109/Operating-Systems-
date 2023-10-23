#include <iostream>
using namespace std;

struct process {
    int id;
    int time_input;
    int time_process;
    int finished_time;
    int waiting_time;
    int minus;
};

struct Grantt {
    int *name;
    int *mark;
    int amount;
};

Grantt fcfs(process *a, int n) {
    int current = -1, smallest;
    float avr = 0.0;

    Grantt G;
    G.name = new int[n*2];  // Increased due to possible preemptions
    G.mark = new int[n*2+1];
    G.amount = 0;
    G.mark[0] = 0;

    process *X = new process[n+1];
    for(int i = 0; i < n; i++) {
        X[i] = a[i];
        X[i].minus = X[i].time_process;
    }
    X[n].time_input = 9999;  // sentinel value
    G.amount = 0;
    int time = 0;

    while(G.amount != n) {
        smallest = n;
        for(int i=0; i<n; i++) {    //find smallest
            if(X[i].time_input <= X[smallest].time_input && X[i].time_process > 0) {
                smallest = i;
            }
        }

        if(X[smallest].time_input <= time) {    //it has arrived -> update time -> update name for current -> update mark for next
            time += X[smallest].time_process;
            X[smallest].finished_time = time - X[smallest].time_input;
            G.name[G.amount] = X[smallest].id;
            G.mark[G.amount + 1] = time;
            G.amount++;
        }
        else {  //has not arrived
            time++;
            continue;
        }

        X[smallest].time_process = 0;
    }

    cout << "Waiting time: " << endl;
    for(int i = 0; i < n; i++) {
        X[i].waiting_time = X[i].finished_time - X[i].minus;
        cout << "P" << X[i].id << endl;
        cout << X[i].waiting_time << "   " << endl;
        avr += X[i].waiting_time;
    }
    cout << "Average waiting time: " << (avr/(float)n) << endl;

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
    }
    
    Grantt G = fcfs(a, n);
    cout << "FIRST COME FIRST SERVED" << endl;
    for(int i = 0; i < G.amount; i++) {
        cout << "P" << G.name[i] << "   " << endl;
        cout << G.mark[i] << "   " << endl;
    }

    delete[] a;
    delete[] G.name;
    delete[] G.mark;

    return 0;
}