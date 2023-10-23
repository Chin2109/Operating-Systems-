#include<iostream>
#include<vector>

using namespace std;

int main() {
    int n,m;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resources: ";
    cin >> m;

    int it;
    vector<int> Available;
    for(int i = 0; i < m; i++) {
        cout << "Enter Available: ";
        cin >> it;
        Available.push_back(it);
    }

    vector<vector<int>> Max;
    vector<int> that;
    for(int i = 0; i < n; i++) {
        cout << "Enter Max: " <<i <<" ";
        for(int j = 0; j < m; j++) {
            cin >> it;
            that.push_back(it);
        }
        Max.push_back(that);
        that.clear();
    }

    vector<vector<int>> Alloc;
    for(int i = 0; i < n; i++) {
        cout << "Enter Alloc: " <<i<<" ";
        for(int j = 0; j < m; j++) {
            cin >> it;
            that.push_back(it);
        }
        Alloc.push_back(that);
        that.clear();
    }

    vector<vector<int>> Need;    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            it = Max[i][j] - Alloc[i][j];
            that.push_back(it);
        }
        Need.push_back(that);
        that.clear();
    }

    vector<int> Work(Available);
    vector<bool> Finish(n,false);

    int index;
    vector<int> Request;
    cout << "Enter process index you want to add: ";
    cin >> index;
    cout << "Enter value: ";
    for(int i = 0; i < m; i++) {
        cin >> it;
        Request.push_back(it);
    }
    vector<int> String;
    
    bool Resource(int index, vector<int> &Request, vector<vector<int>> &Need, vector<int> &Available, vector<vector<int>> &Alloc);
    bool safe(int index, vector<int> &Request, vector<vector<int>> &Need, vector<int> &Available, vector<vector<int>> &Alloc, vector<bool> &Finish, vector<int> &String);


    bool ris = Resource(index,Request,Need,Available,Alloc);
    bool res = safe(index,Request,Need,Available,Alloc,Finish,String);

    cout << "==== NEED ====" << endl;
    for(int i = 0; i < Need.size(); i++) {
        cout << "Need[" << i << "] = ";
        for(int j = 0; j < m; j++) {
            cout << Need[i][j] << " ";
        }
        cout << endl;
    }

    if(!ris || !res) {
        cout << "Unsuccessfully!";
    }
    else {
        cout << "Successfully!" << endl;
        for(int i = 0; i < String.size(); i++) {
            cout << "P" << String[i] << " ";
        }
    }

    return 0;
}

bool smaller_equal(vector<int> a, vector<int> b) {
    for(int i = 0; i < a.size(); i++) {
        if(a[i] > b[i]) {
            return false;
        }
    }
    return true;
}

bool Resource(int index, vector<int> &Request, vector<vector<int>> &Need, vector<int> &Available, vector<vector<int>> &Alloc) {
    if(smaller_equal(Request,Need[index])) {
        if(smaller_equal(Request,Available)) {
            for(int i = 0; i < Request.size(); i++) {
                Available[i] -= Request[i];
                Alloc[index][i] += Request[i];
                Need[index][i] -= Request[i];
            }
        }
    }
    else {
        return false;
    }
    
    return true;
}

bool safe(int index, vector<int> &Request, vector<vector<int>> &Need, vector<int> &Available, vector<vector<int>> &Alloc, vector<bool> &Finish, vector<int> &String) {
    vector<int> Work(Available);
    cout << "==== WORK ====" << endl;
    for(int i = 0; i < Work.size(); i++) {
        cout << Available[i] << " ";
    }
    cout << endl;
    for(int j = 0; j < Alloc.size(); j++) {
        for(int i = 0; i < Alloc.size(); i++) {
            if(Finish[i] == false && smaller_equal(Need[i],Work)) {
                cout << "P[" << i << "] = ";
                for(int h = 0; h < Work.size(); h++) {
                    Work[h] += Alloc[i][h];
                    Finish[i] = true;
                    cout << Work[h] << " ";
                }
                String.push_back(i);
                cout << endl;
            }
        }
    }
    for(int i = 0; i < Alloc.size(); i++) {
        if(Finish[i] == false) {
            return false;
        }
    }
    
    return true;
}