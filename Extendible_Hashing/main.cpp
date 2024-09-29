#include<bits/stdc++.h>
using namespace std;

bool isint(string s){
    if(s.size() > 9) return false;
    for(auto c : s)
        if(c < '0' || c > '9') return false;
    return true;
}

class Bucket{
    int local_depth, size;
    vector<int> records;
public:
    Bucket(int size, int local_depth) : size(size), local_depth(local_depth) {}

    bool search(int key){
        return find(records.begin(), records.end(), key) != records.end();
    }

    void insert(int key){
        records.push_back(key);
    }

    int getDepth(){
        return local_depth;
    }

    vector<int> share(){
        vector<int> temp;
        for(auto x : records) temp.push_back(x >> local_depth - 1 & 1);
        return temp;
    }

    vector<int> copy(){
        return records;
    }

    void clear(){
        records.clear();
    }

    bool remove(int key){
        auto it = find(records.begin(), records.end(), key);
        if(it == records.end()) return false; // does not exist already
        records.erase(it);
        return true; // deleted successfully
    }

    int getSize(){
        return records.size();
    }

    int grow(){
        return ++local_depth;
    }

    void shrink(){
        local_depth--;
    }

    void print(){
        for(auto x : records) cout << x << ' ';
    }

    int getID(int b_no){
        return b_no & (1 << local_depth) - 1;
    }
};

class Directory{
    int global_depth, bucket_size;
    vector<Bucket*> buckets;
public:
    Directory(int size) : bucket_size(size) {
        global_depth = 1;
        buckets.resize(2);
        buckets[0] = new Bucket(bucket_size, 1);
        buckets[1] = new Bucket(bucket_size, 1);
    }

    int hash(int n){
        // take the last 'global_depth' bits of this remainder
        return n & (1 << global_depth) - 1;
    }

    int split_cnt(vector<int> temp, int local_depth){
        int cnt = local_depth;
        while(true){
            int f = 0;
            for(auto x : temp) f |= (x >> cnt & 1);
            if(f) break;
            cnt++;
        }
        return cnt - local_depth + 1;
    }

    void insert(int key){
        int dir_no = hash(key);
        if(buckets[dir_no] -> search(key)) return;
        if(buckets[dir_no] -> getSize() < bucket_size){
            buckets[dir_no] -> insert(key);
            return;
        }
        vector<int> rec = buckets[dir_no] -> copy();
        buckets[dir_no] -> clear();
        rec.push_back(key);
        int local_depth = buckets[dir_no] -> getDepth();
        int cnt = split_cnt(rec, local_depth);
        while(cnt--){
            if(local_depth == global_depth){
                grow();
                int pair_no = find_pair(dir_no);
                buckets[dir_no] -> grow();
                buckets[pair_no] = new Bucket(bucket_size, local_depth + 1);
            }
            else{
                int bucket_no = dir_no & (1 << local_depth) - 1;
                buckets[bucket_no] -> grow();
                int pair_no = bucket_no ^ 1 << local_depth;
                buckets[pair_no] = new Bucket(bucket_size, local_depth + 1);
                int dif = global_depth - local_depth;
                for(int i = 1; i < 1 << dif - 1; i++){
                    buckets[2 * i << local_depth | bucket_no] = buckets[bucket_no];
                    buckets[2 * i + 1 << local_depth | bucket_no] = buckets[pair_no];
                }
            }
            local_depth++;
        }
        for(auto x : rec) insert(x);
    }

    int find_pair(int b_no){
        return b_no ^ 1 << global_depth - 1;
    }

    void grow(){
        for(int i = 0; i < 1 << global_depth; i++) buckets.push_back(buckets[i]);
        global_depth++;
    }

    void remove(int key){
        int dir_no = hash(key);
        if(!buckets[dir_no] -> remove(key)) return;
        int local_depth = buckets[dir_no] -> getDepth();
        int pair_no = dir_no ^ 1 << local_depth - 1;
        if(dir_no > pair_no) swap(dir_no, pair_no);
        int b_size = buckets[dir_no] -> getSize();
        int p_size = buckets[pair_no] -> getSize();
        while(b_size + p_size <= bucket_size && local_depth > 1){
            merge(dir_no, pair_no);
            dir_no = hash(key);
            local_depth--;
            pair_no = dir_no ^ 1 << local_depth - 1;
            if(dir_no > pair_no) swap(dir_no, pair_no);
            b_size = buckets[dir_no] -> getSize();
            p_size = buckets[pair_no] -> getSize();
        }
        return;
    }

    void merge(int dir_no, int pair_no){
        vector<int> temp = buckets[pair_no] -> copy();
        for(auto x : temp) buckets[dir_no] -> insert(x);
        buckets[pair_no] -> clear();
        int local_depth = buckets[pair_no] -> getDepth();
        int pair_id = pair_no & (1 << local_depth) - 1;
        int dif = global_depth - local_depth;
        for(int i = 0; i < 1 << dif; i++)
            buckets[i << local_depth | pair_id] = buckets[dir_no];
        buckets[dir_no] -> shrink();
        shrink();
    }

    void shrink(){
        int max_depth = 0;
        for(auto i : buckets) max_depth = max(max_depth, i -> getDepth());
        if(max_depth == global_depth) return;
        global_depth--;
        buckets.resize(1 << global_depth);
    }

    int search(int key){
        int dir_no = hash(key);
        if(buckets[dir_no] -> search(key)) return buckets[dir_no] -> getID(dir_no);
        return -1;
    }

    void print(){
        cout << "Directory NO\tRecords\n";
        for(int i = 0; i < 1 << global_depth; i++){
            cout << i << "[" << buckets[i] -> getDepth() << "]" << "\t\t";
            buckets[i] -> print();
            cout << '\n';
        }
    }

    void print(int i){
        buckets[i] -> print();
    }
};

int main(){
    ios::sync_with_stdio(false);

    int max_bucket_size;
    cout << "Enter the maximum size of bucket : ";
    cin >> max_bucket_size;
    Directory d(max_bucket_size);
    cout << "\nMenu :\nI : Insert\nD : Delete\nS : Search\nP : Print\nE : Exit\n\n";
    cout << "Enter preferred operation : ";
    char op;
    while(true){
        cin >> op;
        switch(op){
            case 'I':{
                cout << "Enter the key to be inserted : ";
                string key; cin >> key;
                if(isint(key)) d.insert(stoi(key));
                else cout << "Please an integer\n";
                break;
            }
            case 'D':{
                cout << "Enter the key to be deleted : ";
                string key; cin >> key;
                if(isint(key)) d.remove(stoi(key));
                else cout << "Please an integer\n";
                break;
            }
            case 'S':{
                cout << "Enter the key to be searched for : ";
                string key; cin >> key;
                if(!isint(key)) cout << key << " has not been found\n";
                int bucket_no = d.search(stoi(key));
                if(bucket_no == -1) cout << key << " has not been found\n";
                else cout << key << " has been found in bucket " << bucket_no << '\n';
                break;
            }
            case 'P':{
                d.print();
                break;
            }
            default:{
                exit(0);
            }
        }
        cout << "Next Operation : ";
    }
    return 0;
}
