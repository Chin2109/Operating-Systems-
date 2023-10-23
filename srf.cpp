#include <iostream>
using namespace std;

struct process {
    int id;
    int time_input;    // equivalent to arrival time (at)
    int time_process;  // equivalent to burst time (bt)
    int remaining_time;
    int waiting_time;
    int finished_time;
    int minus;
};

struct Grantt {
    int *name;
    int *mark;
    int amount;
};

Grantt sjf_nonpreemtive(process *a, int n) {
    int sum_bt = 0, smallest, time = 0;
    float ave;
    Grantt G;
    G.name = new int[n];
    G.mark = new int[n+1];
    G.amount = 0;

    process *X = new process[n+1];
    for(int i = 0; i < n; i++) {
        X[i] = a[i];
        X[i].minus = X[i].time_process;
        X[i].waiting_time = 0;
    }
    X[n].time_process = 9999;  // sentinel value

    while(G.amount != n) {
        smallest = n;  // Using the sentinel value to find the smallest
        for(int i=0; i<n; i++) {
            if(X[i].time_input <= time && X[i].time_process < X[smallest].time_process && X[i].time_process > 0) {
                smallest = i;
            }
        }
        if(smallest == n) {     //no process has arrived (has update smallest)
            time++;
            continue;
        }

        G.name[G.amount] = X[smallest].id;
        G.mark[G.amount] = time;
        X[smallest].finished_time = time - X[smallest].time_input;
        time += X[smallest].time_process;
        X[smallest].time_process = 0;
        G.mark[G.amount + 1] = time;
        G.amount++;
    }

    cout << "Waiting time: " << endl;
    for(int i = 0; i < n; i++) {
        X[i].waiting_time = X[i].finished_time - X[i].minus;
        cout << "P" << "   " << X[i].id << endl;
        cout << X[i].waiting_time << "   " << endl;
        ave += X[i].waiting_time;
    }
    cout << "Average waiting time: " << (ave/(float)n) << endl;
    
    delete[] X;
    return G;
}

Grantt sjf_preemptive(process *a, int n) {
    int current = -1, time = 0, smallest, count = 0; //count để đếm những process đã chạy xong
    float ave = 0.0;
    Grantt G;
    G.name = new int[n*2];  // Increased due to possible preemptions
    G.mark = new int[n*2+1];
    G.amount = 0;
    G.mark[0] = 0;

    for(int i=0; i<n; i++) {
        a[i].remaining_time = a[i].time_process;
    }

    process *X = new process[n+1];
    for(int i = 0; i < n; i++) {
        X[i] = a[i];
        X[i].waiting_time = 0;
    }
    X[n].time_process = 9999;  // sentinel value
    X[n].remaining_time = 9999;  // sentinel value

    while(count != n) {
        smallest = n;


        for(int i=0; i<n; i++) {
            if(X[i].time_input <= time && X[i].remaining_time < X[smallest].remaining_time && X[i].remaining_time > 0) {
                smallest = i;
            }
        }
        if(current != smallest) { //bị thay thế khi đứa đang chạy (curent) ko còn nhỏ nhất nữa
            if(current != -1 && X[current].remaining_time > 0) {
                G.name[G.amount] = X[current].id;
                X[current].waiting_time += G.mark[G.amount] - X[current].time_input;
                G.mark[G.amount+1] = time;
                G.amount++;
            }
            current = smallest;
        }
        if(current != -1) { //đang chạy
            if(current == n) {  //no processes has arrived
                time++;
                continue;
            }
            
            X[current].remaining_time--;
            time++;
            
            if(X[current].remaining_time == 0) { //chạy hết
                count++;
                G.name[G.amount] = X[current].id;
                X[current].finished_time = time - X[current].time_input;
                G.mark[G.amount+1] = time;
                
                G.amount++;
                current = -1;
            }
        }
    }

    cout << "Waiting time: " << endl;
    for(int i = 0; i < n; i++) {
        X[i].waiting_time = X[i].finished_time - X[i].time_process;
        cout << "P" << X[i].id << endl;
        cout << X[i].waiting_time << "   " << endl;
        ave += X[i].waiting_time;
    }
    cout << "Average waiting time: " << ave/n << endl;

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
    
    Grantt G;

    int it, average_waitingtime;
    cout << "Enter preemtive(1) or nonpreemtive(2): ";
    cin >> it;
    switch (it)
    {
    case 1:
        G = sjf_preemptive(a,n);
        break;

    case 2:
        G = sjf_nonpreemtive(a,n);
        break;
    
    default:
        break;
    }


    cout << "SHORTEST JOURNEY FIRST" << endl;
    for(int i = 0; i < G.amount; i++) {
        cout << "P" << G.name[i] <<"   " << endl;
        cout << G.mark[i] << "   " << endl;
    }

    delete[] a;
    delete[] G.name;
    delete[] G.mark;

    return 0;
}