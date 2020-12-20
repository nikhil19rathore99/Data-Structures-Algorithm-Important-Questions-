#include <bits/stdc++.h>
using namespace std;
vector<int> merge(vector<int> &arr1, vector<int> &arr2)
{
    vector<int> res(arr1.size() + arr2.size());
    int i = 0, j = 0, k = 0;
    while (i < arr1.size() && j < arr2.size())
    {
        if (arr1[i] < arr2[j])
        {
            res[k++] = arr1[i++];
        }
        else
        {
            res[k++] = arr2[j++];
        }
    }
    while (i < arr1.size())
    {
        res[k++] = arr1[i++];
    }
    while (j < arr2.size())
    {
        res[k++] = arr2[j++];
    }
    return res;
}
vector<int> msort(vector<int> &arr, int l, int r)
{
    if (l == r)
    {
        return {arr[l]};
    }
    int m = l + (r - l) / 2;
    vector<int> lh = msort(arr, l, m);
    vector<int> rh = msort(arr, m + 1, r);
    vector<int> fs = merge(lh, rh);
    return fs;
}
int partition(vector<int> &arr, int l, int r, int pivot)
{
    int j = l;
    for (int i = l; i <= r; i++)
    {
        if (arr[i] <= pivot)
        {
            int t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
            j++;
        }
    }
    return j - 1;
}
void quickSort(vector<int> &arr, int l, int h)
{
    if (l > h)
        return;
    int pi = partition(arr, l, h, arr[h]);
    quickSort(arr, l, pi - 1);
    quickSort(arr, pi + 1, h);
}
void sort01(vector<int> &arr)
{
    int i = 0, j = 0;
    while (j < arr.size())
    {
        if (arr[j] == 0)
        {
            int t = arr[j];
            arr[j] = arr[i];
            arr[i] = t;
            i++;
            j++;
        }
        else
        {
            j++;
        }
    }
}
void sort012(vector<int> &arr)
{
    auto swp = [](vector<int> &arr, int l, int h) {
        int t = arr[l];
        arr[l] = arr[h];
        arr[h] = t;
    };
    int l = 0, h = arr.size() - 1;
    for (int m = 0; m<=h;)
    {
        switch (arr[m])  
        {
            case 0:
                swp(arr, m, l);
                m++;
                l++;
                break;
            case 1:
                m++;
                break;
            case 2:
                swp(arr, m, h);
                h--;
                break;
        }
    }
}
void countSortForRadixSort(vector<int>& arr, int dv){
        vector<int> freq(10,0),res(10);
        for(int i : arr) freq[i/dv%10]++;
        for(int i=0;i<arr.size();i++){ if(i) freq[i]+=freq[i-1];}
        for(int i=arr.size()-1;i>=0;i--){
            res[--freq[arr[i]/dv%10]]=arr[i];
        }
        arr=res;
    }
void RadixSort(vector<int>& arr){
        int mx=*max_element(arr.begin(),arr.end());
        int dv=1;
        while(mx/dv){
            countSortForRadixSort(arr,dv);
            dv *= 10;
        }
    }
class pq{
    public:
        vector<int> data;
        bool minmax;
        pq(bool minmax, vector<int>& arr){
            this->minmax=minmax;
            for(int i : arr) data.push_back(i);
            for(int i=data.size()/2-1;i>=0;i--) downheapify(i);
        }
        pq(){}
        bool high(int i1,int i2){
            return minmax ? data[i1] > data[i2] : data[i1]<data[i2];
        }
        void swap(int i1, int i2){
            int temp=data[i1]; data[i1]=data[i2]; data[i2]=temp;
        }
        void upheapify(int i){
            if(i==0) return;
            int uc = (i-1)/2;
            if(high(i,uc)){
                swap(uc,i);
                upheapify(uc);
            }
        }
        void downheapify(int i){
            int lc = 2*i+1;
            int rc = 2*i+2;
            int hp=i;
            if(lc < data.size() && high(lc,hp)) hp=lc;
            if(rc < data.size() && high(rc,hp)) hp=rc;
            if(hp!=i){
                swap(hp,i);
                downheapify(hp);
            } 
        }
        void display(){
            for(int i : data) cout<<i<<" ";
            cout<<endl;
        }
        void push(int val){
            data.push_back(val);
            upheapify(data.size()-1);
        }
        int top(){
            return data[0];
        }
        void pop(){
            swap(0,data.size()-1);
            data.pop_back();
            downheapify(0);
        }
        bool size() {return data.size();}
};
int main()
{
    auto bubble = [](vector<int> &arr) {
        for (int i = 0; i < arr.size(); i++)
        {
            for (int j = 0; j < arr.size() - i - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    int t = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = t;
                }
            }
        }
    };
    auto selection = [](vector<int> &arr) {
        for (int i = 0; i < arr.size() - 1; i++)
        {
            int sidx = i;
            for (int j = i + 1; j < arr.size(); j++)
            {
                if (arr[sidx] > arr[j])
                    sidx = j;
            }
            if (sidx != i)
            {
                int t = arr[i];
                arr[i] = arr[sidx];
                arr[sidx] = t;
            }
        }
    };
    auto insertion = [](vector<int> &arr) {
        for (int i = 1; i < arr.size(); i++)
        {
            for (int j = i - 1; j >= 0; j--)
            {
                if (arr[j] > arr[j + 1])
                {
                    int t = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = t;
                }
            }
        }
    };
    auto countSort=[](vector<int>& arr){
        int mn=*min_element(arr.begin(),arr.end());
        int mx=*max_element(arr.begin(),arr.end());
        int range=mx-mn+1;
        vector<int> freq(range,0),res(arr.size());
        for(int i : arr) freq[i-mn]++;
        for(int i : freq) cout<<i<<" ";
        cout<<endl;
        for(int i=0;i<arr.size();i++){ if(i) freq[i]+=freq[i-1];}
        for(int i=arr.size()-1;i>=0;i--){
            res[--freq[arr[i]-mn]]=arr[i];
        }
        arr=res;
    };
    vector<int> arr{1, 2, 8, 4, 9, 2, 3};
    // insertion(arr);
    // vector<int> st=msort(arr,0,arr.size()-1);
    // quickSort(arr,0,arr.size()-1);
    // for (int i : arr)
    //     cout << i << " ";
    // vector<int> arr01{0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1};
    // sort01(arr01);
    // for(int i : arr01) cout<<i<<" ";
    // cout<<endl;

    // vector<int> arr012{0, 1, 1, 1, 0, 1, 2, 1, 0, 2, 1, 1, 2, 0, 2, 0, 1};
    // sort012(arr012);
    // for (int i : arr012)
    //     cout << i << " ";
    // cout << endl;
    
    // vector<int> csarr{9,6,3,5,3,4,3,9,6,4,6,5,8,9,9};
    // countSort(csarr);
    // for(int i: csarr) cout<<i<<" ";
    // cout<<endl;
    // vector<int> rsarr{257, 68, 347, 924, 136, 425, 719, 88, 463, 527, 634, 725, 978};
    // RadixSort(rsarr);
    // for(int i: rsarr) cout<<i<<" ";
    // cout<<endl;

    pq *t = new pq(1,arr);
    // for(int i : arr) t->push(i);
    while(t->size()){
        cout<<t->top()<<" ";
        t->pop();
    }
    // t->display();
}