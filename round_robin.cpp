#include <iostream>
using namespace std;

struct process {
    int id;
    int time_input;
    int time_process;
    int waiting_time;
    int finished_time;
    int minus;
};

struct Grantt {
    int *name;
    int *mark;
    int amount;
};

Grantt round_robin(process *a, int n, int quantum) {
    int time = 0, remain = n, flag, i;
    float ave = 0.0;
    Grantt G;
    G.name = new int[n*3];
    G.mark = new int[n*3+1];
    G.amount = 0;
    G.mark[0] = 0;

    process *X = new process[n];
    for(int i = 0; i < n; i++) {
        X[i] = a[i];
        X[i].waiting_time = 0;
        X[i].minus = X[i].time_process;
    }

    while(remain != 0) {
        int flag = 0;
        for(i = 0; i < n; i++) {                                                                        
            if(X[i].time_input <= time && X[i].time_process > 0) { //appeared equal before time
                if(X[i].time_process > quantum) { 
                    time += quantum;
                    X[i].time_process -= quantum;
                    G.name[G.amount] = X[i].id;
                    G.mark[G.amount + 1] = time;    //nếu có trường hợp xuất hiện sau time, thì tự nó cũng cập nhật lại time khi nó <= time
                    G.amount++;                    //G.amount chỉ tăng khi có process xuất hiện <= time -> nó vẫn cập nhật cho cái hiện tại nếu phải đợi process xuất hiện
                    flag = 1;

                } else {                                           
                    time += X[i].time_process;
                    X[i].time_process = 0;
                    G.name[G.amount] = X[i].id;
                    G.mark[G.amount + 1] = time;
                    G.amount++;
                    remain--;
                    X[i].finished_time = time - X[i].time_input;
                    flag = 1;
                }
            }
        }
        if(flag == 0) {
            time++;
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
    int n, quantum;
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

    cout << "Enter quantum: ";
    cin >> quantum;

    Grantt G = round_robin(a, n, quantum);
    cout << "ROUND ROBIN" << endl;
    for(int i = 0; i < G.amount; i++) {
        cout << "P" << G.name[i] <<"   " << endl;
        cout << G.mark[i] << "   " << endl;
    }

    delete[] a;
    delete[] G.name;
    delete[] G.mark;

    return 0;
}
