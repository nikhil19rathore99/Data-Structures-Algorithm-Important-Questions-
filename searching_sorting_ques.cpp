#include<bits/stdc++.h>
using namespace std;
int findMajorityElement(vector<int>& arr){
    int maj=0,c=0;
    for(int i=1;i<arr.size();i++){
        if(arr[maj]==arr[i]) c++;
        else c--;
        if(!c){
            maj=i;
            c=1;
        }
    }
    int ct=0;
    for(int i=0;i<arr.size();i++){
        if(arr[maj]==arr[i]) ct++;
    }
    return ct >= arr.size()/2 ? arr[maj] : -1;
}
int searchInDifferAtMostK(vector<int>& arr, int k, int x){
    int i=0;
    while(i<arr.size()){
        if(arr[i]==x) return i;
        i = i+max(1,abs(arr[i]-x)/k);
    }
    return -1;
}
pair<int,int> repeatAndMissing(vector<int>& arr){
    auto findRepeat=[&](vector<int> arr){
        for(int i=0;i<arr.size();i++){
            if(arr[abs(arr[i])-1] > 0) arr[abs(arr[i])-1] = -arr[abs(arr[i])-1];
            else return abs(arr[i]);
        }
        return -1;
    };
    int x = findRepeat(arr);
    int s = arr.size();
    s = s*(s+1)/2;
    int arrsum=0;
    for(int i : arr) arrsum+=i;
    return {x,s-(arrsum-x)};
}
int ceil(vector<int>& arr, int l, int r, int x){
    if(x<=arr[l]) return l;
    if(x>arr[r]) return -1;
    int m = (l+r)/2;
    if(arr[m]>x){
        if(m-1>=l && x > arr[m-1]) return m;
        else return ceil(arr,l,m-1,x);  
    }else{
        if(m+1<=r && x <=arr[m+1]) return m+1;
        else return ceil(arr,m+1,r,x);
    }
}
void findFourElementSumToGivenValue(vector<int>& arr,int x){
    auto pairSum=[](vector<int>&arr){
        map<int,pair<int,int>> m;
        for(int i=0;i<arr.size();i++){
            for(int j=i+1;j<arr.size();j++){
                m[arr[i]+arr[j]].first=i;
                m[arr[i]+arr[j]].second=j;
            }
        }
        return m;
    };
    map<int,pair<int,int>> m=pairSum(arr);
    for(int i=0;i<arr.size()-1;i++){
        for(int j=i+1;j<arr.size();j++){
            int curr=arr[i]+arr[j];
            if(m.find(x-curr)!=m.end()){
                pair<int,int> now = m[x-curr];
                if(now.first!=i && now.second!=j && now.first!=j && now.second!=i){
                    cout<<arr[i]<<" "<<arr[j]<<" "<<arr[now.first]<<" "<<arr[now.second]<<endl;
                    return;
                }
            }
        }
    }
}
double findMedianTwoDiffSizeArr(vector<int>& arr1, vector<int>& arr2){
    int n=arr1.size(),m=arr2.size();
    if(n>m) return findMedianTwoDiffSizeArr(arr2,arr1);
    int l=0,h=n;
    while(l<=h){
        int parX=(l+h)/2;
        int parY=(n+m+1)/2-parX;
        int maxLeftX = parX==0 ? INT_MIN : arr1[parX-1];
        int minRightX = parX==n ? INT_MAX : arr1[parX];
        int maxLeftY = parY==0 ? INT_MIN : arr2[parY-1];
        int minRightY = parY==m ? INT_MAX : arr2[parY]; 
        if(maxLeftX<=minRightY && maxLeftY<=minRightX){
            if((n+m)%2==0){
                return (double)(max(maxLeftX,maxLeftY)+min(minRightX,minRightY))/2;
            }else{
                return (double)max(maxLeftX,maxLeftY);
            }
        }else if(maxLeftX>minRightY) h=parX-1;
        else l=parX+1;
    }
    return -1.0;
}
int maxSumNoAdjacentElement(vector<int>& arr){
    int inc=arr[0],exc=0;
    for(int i=1;i<arr.size();i++){
        int oinc=inc;
        inc = exc+arr[i];
        exc = max(exc,oinc);
    }
    return max(inc,exc);
}
void mergeWithoutExtraSpace(vector<int>& arr1, vector<int>& arr2){
    int i=arr1.size()-1;
    int j=0;
    auto swap=[&](int *a,int* b){
        int t=*a; *a=*b; *b=t;
    };
    while(i>=0 && j < arr2.size()){
        if(arr1[i]>arr2[j]){
            swap(&arr1[i],&arr2[j]);
            i--;j++;
        }else break;
    }
    sort(arr1.begin(),arr1.end());
    sort(arr2.begin(),arr2.end());
    for(int i : arr1) cout<<i<<" ";
    cout<<endl;
    for(int i : arr2) cout<<i<<" ";
    cout<<endl;
}
class medianpq{
    private:
        priority_queue<int> left;
        priority_queue<int,vector<int>,greater<int>> right;
        void handle(){
            if(left.size()-right.size()==2){
                right.push(left.top()); left.pop();
            }else if(right.size()-left.size()==2){
                left.push(right.top()); right.pop();
            }
        }
    public:
        void push(int x){
           if(right.size() && x > right.top()) right.push(x);
           else left.push(x);
           handle();
        }
        void pop(){
            if(left.size() > right.size()) left.pop();
            else right.pop();
        }
        int top(){
            if(left.size()>=right.size()) return left.top();
            else return right.top();
        }
        int size(){
            return abs((int)left.size()-(int)right.size());
        }
};
void sortAccordingToSetBits(vector<int>& arr){
    vector<vector<int>> ct(32);
    for(int i : arr){
        int x = __builtin_popcount(i);
        ct[x].push_back(i);
    }    
    for(int i=31;i>=0;i--){
        if(ct[i].size()){
            for(int x : ct[i]) cout<<x<<" ";
        }
    }
    cout<<endl;
}
void sortedInsertionInterval(vector<vector<int>>& intervals, vector<int> &newInterval){
    vector<vector<int>> res;
    for(vector<int> t : intervals){
        if(!newInterval.size() || t[1]<newInterval[0]) res.push_back(t);
        else if(t[0] > newInterval[1]){
            res.push_back(newInterval);
            newInterval.clear();
            res.push_back(t);
        }else{
            newInterval[0]=min(newInterval[0],t[0]);
            newInterval[1]=max(newInterval[1],t[1]);
        }
    }
    if(newInterval.size())res.push_back(newInterval);
    for(vector<int> t : res){
        cout<<t[0]<<" "<<t[1]<<endl;
    }
}
int countPairsXpowYgreaterYpowX(vector<int>&X, vector<int>&Y){
    // Brute-Force
    // int c=0;
    // for(int x : X){
    //     if(x!=1){
    //         for(int y : Y){
    //             if(y==1)c++;
    //             else if(x==2 && y>=5) c++;
    //             else if(x==3 && (y==2 || y>=4))c++;
    //             else if(y>x) c++;
    //         }
    //     }
    // }
    // return c;
    //Optimal NlogN
    auto bs=[](vector<int>& arr,int x){
        int l=0,h=arr.size()-1;
        int ans=-1;
        while(l<=h){
            int m = (l+h)/2;
            if(arr[m]>x){
                ans=m;
                h=m-1;
            }else l=m+1;
        }
        return ans;
    };
    int c0=0,c1=0,c2=0,c3=0,c4=0;
    sort(X.begin(),X.end());
    sort(Y.begin(),Y.end());
    for(int i : X){
        c0+=i==0;
        c1+=i==1;
        c2+=i==2;
        c3+=i==3;
        c4+=i==4;
    }
    int ans=0;
    for(int i=0;i<X.size();i++){
        if(!X[i])continue;
        else if(X[i]==1){
            ans += c0;
        }else if(X[i]==2){
            int ind=bs(Y,2);
            if(ind!=-1) ans += Y.size()-ind;
            ans += c0+c1;
            ans -= c3-c4;
        }else{
            int ind=bs(Y,X[i]);
            if(ind!=-1) ans += Y.size()-ind;
            ans += c0+c1;
            if(X[i]==3) ans += c2;
        }
    }
    return ans;
}
int minSwapsRequiredToSort(vector<int>& arr){
    vector<pair<int,int>> v(arr.size());
    for(int i=0;i<arr.size();i++){
        v[i].first=arr[i];
        v[i].second=i;
    }
    sort(v.begin(),v.end());
    vector<bool> vis(arr.size(),false);
    int i=0,c=0,ans=0;
    for(int i=0;i<arr.size();i++){
        int j=i;
        int c=0;
        if(vis[j] || j==v[j].second) continue;
        while(!vis[j]){
                vis[j]=1;
                c++;
                j=v[j].second;
        }
        if(c) ans += (c-1);
    }
    return ans;
}
string largestMultipleOfThree(vector<int>& arr){
    vector<int> table(10,0);
    int s=0;
    for(int i : arr) {
        table[i]++; s+=i;
    }
    s %= 3;
    if(s){
        if(table[s]+table[s+3]+table[s+6]) table[s]--;
        else table[3-s]-=2;
    }
    for(int i=0;i<10;i++){
        if(table[i] < 0){
            table[i+3]+=table[i],table[i]=0;
        }
    }
    string r;
    for(int i=9;i>=0;i--){
        while(table[i]--)r.push_back(char(i+'0'));
    }
    return r[0]=='0' ? "0" : r;
}
int maxProductPairInArray(vector<int>& arr){
    map<int,int> m;
    for(int i : arr) m[i]++;
    sort(arr.begin(),arr.end());
    for(int i=arr.size()-1;i>=0;i--){
        for(int j=0;j<i&&arr[j]<sqrt(arr[i]);j++){
            if(arr[i]%arr[j]==0){
                int res = arr[i]/arr[j];
                if(res!=arr[j] && m[res]) return arr[i];
                else if(res==arr[j] && m[res]>1) return arr[i];
            }
        }
    }
    return -1;
}
int main(){
    // vector<int> marr{3, 3, 4, 2, 4, 4, 2, 4, 4};
    // cout<<findMajorityElement(marr)<<endl;
    // vector<int> sarr{20, 40, 50, 70, 70, 60};
    // cout<<searchInDifferAtMostK(sarr,20,60)<<endl;
    // pair<int,int> res;
    // vector<int> rmarr{1,2,4,4};
    // res = repeatAndMissing(rmarr);
    // cout<<res.first<<" "<<res.second<<endl;
    // vector<int> carr{1, 2, 8, 10, 10, 12, 19};
    // cout<<ceil(carr,0,carr.size()-1,11)<<endl;
    // vector<int> farr{ 10, 20, 30, 40, 1, 2};
    // findFourElementSumToGivenValue(farr,91);
    // vector<int>arr1{2, 3, 5, 8},arr2{10, 12, 14, 16, 18, 20};
    // cout<<findMedianTwoDiffSizeArr(arr1,arr2)<<endl;
    // vector<int> maxarr{5, 5, 10, 100, 10, 5};
    // cout<<maxSumNoAdjacentElement(maxarr)<<endl;
    // vector<int> mergearr1{1, 5, 9, 10, 15, 20},mergearr2{2,3,8,13};
    // mergeWithoutExtraSpace(mergearr1,mergearr2);
    // medianpq pq;
    // pq.push(20);
    // pq.push(5);
    // pq.push(3);
    // pq.push(17);
    // pq.push(8);
    // cout<<pq.top()<<endl;
    // pq.push(9);
    // pq.push(19);
    // cout<<pq.top()<<endl;
    // pq.push(11);
    // cout<<pq.top()<<endl;
    // pq.pop();
    // pq.push(15);
    // cout<<pq.top()<<endl;
    // pq.pop();
    // pq.push(77);
    // pq.push(32);
    // cout<<pq.top()<<endl;
    // vector<int> sbarr{5, 2, 3, 9, 4, 6, 7, 15, 32};
    // sortAccordingToSetBits(sbarr);
    // vector<vector<int>> intervals{{1,3},{6,9}};
    // vector<int> newInterval{2,5};
    // sortedInsertionInterval(intervals,newInterval);
    // vector<int>x{2,1,6}, y{1,5} ;
    // cout<<countPairsXpowYgreaterYpowX(x,y)<<endl;
    // vector<int> minarr{1, 5, 4, 3, 2};
    // cout<<minSwapsRequiredToSort(minarr)<<endl;
    // vector<int> arr{8,9,1};
    // cout<<largestMultipleOfThree(arr)<<endl;
    vector<int> arr{17, 2, 1, 15, 30};
    cout<<maxProductPairInArray(arr)<<endl;
}