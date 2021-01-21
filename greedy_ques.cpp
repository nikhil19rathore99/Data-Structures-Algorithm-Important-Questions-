#include<bits/stdc++.h>
using namespace std;
#define debug(x) cout<<"val: "<<x<<endl;
void activitySelectionProblem(vector<int>& st, vector<int>& ed){
    int i=0,j=1;
    cout<<" "<<i;
    while(j<st.size()){
        if(st[j]>=ed[i]) {
            cout<<" "<<j; i=j;
        }
        j++;
    }
    cout<<endl;
}

class job{
    public:
        char id;
        int dl;
        int pr;
        job(char id, int dl, int pr){
            this->id = id; this->dl = dl; this->pr = pr;
        }
};
void jobSequencing(vector<job>& jobs){
    sort(jobs.begin(),jobs.end(),[](job &x, job &y) {return x.pr > y.pr;});
    int mxdl=INT_MIN;
    for(job j : jobs){
        mxdl=max(mxdl,j.dl);
    }
    int mxprofit=0;
    vector<char> ans(mxdl,'\0');
    for(int i=0;i<jobs.size();i++){
        for(int j=jobs[i].dl-1;j>=0;j--){
            if(ans[j]=='\0'){
                ans[j]=jobs[i].id;
                mxprofit += jobs[i].pr;
                break;
            }
        }
    }
    for(char c : ans) if(c!='\0') cout<<c<<'\n';

    cout<<"max profit "<<mxprofit<<endl;
}

void fractionalKnapSack(vector<int>& val, vector<int>& wts, int w){
    vector<pair<int,int>> ks;
    for(int i=0;i<val.size();i++) ks.push_back({val[i],wts[i]});
    sort(ks.begin(),ks.end(),[](pair<int,int>& x, pair<int,int>&y){
        return 1.0*x.first/x.second*1.0 > (1.0)*y.first/y.second*1.0; 
    });
    for(pair<int,int> p : ks) cout<<p.first<<" "<<p.second<<endl;
    cout<<endl;
    int mx=0;
    for(int i=0;i<val.size();i++){
        if(ks[i].second<=w){
            w-=ks[i].second;
            mx += ks[i].first;
        }else{
            mx += (1.0*w/ks[i].second*1.0)*ks[i].first;
            w = 0;
            break;
        }
    }
    cout<<mx<<endl;
}

void findMinNumberOfCoins(vector<int>& curr, int minf){
    vector<int> ans;
    for(int i=curr.size()-1;i>=0;i--){
        while(minf>=curr[i]){
            minf-=curr[i];
            ans.push_back(curr[i]);
        }
    }
    for(int i : ans) cout<<i<<" ";
    cout<<endl;
}

void maximumChainLengthofPairs(vector<pair<int,int>>& arr){
    vector<int> mcl(arr.size(),1);
    for(int i=1;i<arr.size();i++){
        for(int j=0;j<i;j++){
            if(arr[i].first>arr[j].second && mcl[j]+1>mcl[i]) mcl[i]=mcl[j]+1;
        }
    }
    cout<< *max_element(mcl.begin(),mcl.end())<<endl;
}

int findMinimumTimetoFinishJobs(vector<int>& job, int k, int t){
    auto check=[job, k](int t){
        int c=0;
        int ct=1;
        for(int i=0;i<job.size();){
            if(c+job[i]>t) {
                c=0;
                ct++;
            }else{
                c += job[i++];
            }
        }
        return ct<=k;
    };
    int ed=0;
    int mx =  *max_element(job.begin(),job.end());
    for(int i : job) ed += i;
    int st=0;
    int ans=ed;
    debug(ed);
    while(st<=ed){
        int m = (st+ed)/2;
        if(m >= mx && check(m)){
            ans=min(ans,m);
            ed=m-1;
        }else st=m+1;
    }
    return ans*t;
}

int minSumWithTwoNumberFormed(vector<int>& arr){
    sort(arr.begin(),arr.end());
    int n1=0,n2=0;
    for(int i=0;i<arr.size();i++){
        if(i&1) n1 = n1*10+arr[i];
        else n2 = n2*10+arr[i];
    }
    return n1+n2;
}

void minNumberformedWithSumAndDigits(int s, int d){
    if(s==0){
        if(d==1) cout<<'0'<<'\n';
        else cout<<"Not possible"<<'\n';
    }
    if(s > 9*d) cout<<"Not possible"<<'\n';
    int res[d];
    s -= 1;
    for(int i=d-1;i>0;i--){
        if(s > 9){
            res[i]=9;
            s-=9;
        }else{
            res[i]=s;
            s=0;
        }
    }
    res[0]=s+1;
    for(int i: res) cout<<i;
    cout<<endl;
}

void paperCutIntoMinimumSquares(int h ,int w){
    if(h<w) swap(h,w);
    int res=0;
    while(w){
        res += h/w;
        int r = h%w;
        h=w;
        w=r;
    }
    cout<<res<<endl;
}

void lexicographicallySmallerAfterKSwaps(vector<int>& arr, int k){\
    auto swap=[](int *a, int *b){
        int t=*a; *a=*b; *b=t;
    };
    for(int i=0;i<arr.size();i++){
        int p=i;
        for(int j=i+1;j<arr.size();j++){
            if(j-i > k) break;
            if(arr[j]<arr[p]) p=j;
        }
        for(int j=p;j>i;j--) swap(&arr[j],&arr[j-1]);

        k-=p-i;
    }
    for(int i : arr) cout<<i<<" ";
    cout<<endl;
}

void rearrangeStringNoTwoCharSame(string s){
    auto cmp=[&](pair<int,char>& a, pair<int,char>&b){
        return a.first<b.first;
    };
    priority_queue<pair<int,char>,vector<pair<int,char>>, decltype(cmp)> pq(cmp);
    vector<int> fr(26,0);
    for(char c : s) fr[c-'a']++;
    for(int i=0;i<26;i++) {
        if(fr[i]) pq.push({fr[i],(char)(i+'a')});
    }
    pair<int,char> prev {-1,'@'};
    debug(prev.first);
    debug(prev.second);
    string str;
    while(pq.size()>0){
        pair<int,char> r = pq.top();
        pq.pop();
        str.push_back(r.second);
        if(prev.first>0) pq.push(prev);
        (r.first)--; 
        prev=r;
    }
    if(str.size()!=s.length()) cout<<"Not possible"<<'\n';
    else cout<<str<<endl;
}

int maximumHeightPyramid(vector<int> arr){
    int prevh=arr[0];
    int prevw=1;
    int currh=0,currw=0;
    int ans=1;
    for(int i=1;i<arr.size();i++){
        currh += arr[i];
        currw += 1;
        if(currh>prevh && currw>prevw){
            prevh=currh; prevw=currw;
            currh=0;currw=0;
            ans++;
        }
    }
    return ans;
}

int minCoinsAquireAllCoinsWithKExtraAllowed(vector<int> arr, int k){
    sort(arr.begin(),arr.end());
    int r=0;
    for(int i=0;i<ceil((1.0*arr.size())/(k+1));i++) r += arr[i];
    return r;
}

int findMaximumSumPossibleOfThreeStacks(vector<int> arr1, vector<int> arr2, vector<int> arr3){
    int n1=arr1.size(),n2=arr2.size(),n3=arr3.size();
    int s1=0,s2=0,s3=0;
    for(int i : arr1) s1+=i;
    for(int i : arr2) s2+=i;
    for(int i : arr3) s3+=i;
    int t1=0,t2=0,t3=0;
    while(1){
        if(t1==n1 || t2==n2 || t3==n3) return 0;
        if(s1==s2 && s2==s3) return s1;
        while(s1 >= s2 && s1>=s3) s1-=(arr2[t2++]+arr3[t3++]);
        while(s2 >= s1 && s2>=s3) s2-=(arr1[t1++]+arr3[t3++]);
        while(s3 >= s1 && s3>=s2) s3-=(arr1[t1++]+arr2[t2++]);
    }
}

int maxSumAfterKNegation(vector<int> arr, int k){
    sort(arr.begin(),arr.end());
    int i=0;
    while(k){
        if(arr[i]>=0) k=0;
        else{
            arr[i] = (-1)*arr[i];
            k--;
        }
            i++;
    }
    int s=0;
    for(int i : arr) s+=i;
    return s; 
}

int minCostToCutSquareBoard(vector<int> x, vector<int> y){
    int ans=0;
    int i=0,j=0;
    int h=1,v=1;
    sort(x.rbegin(),x.rend());
    sort(y.rbegin(),y.rend());
    while(i<x.size() && j<y.size()){
        if(x[i]>y[j]){
            ans += x[i++]*v;
            h++;
        }else{
            ans += y[j++]*h;
            v++;
        }
    }
    int t=0;
    while(i<x.size()) t+= x[i++];
    ans += t*v;
    t=0;
    while(j<y.size()) t+= y[j++];
    ans += t*h;
    return ans;
}
int main(){
    // vector<int> st {1, 3, 0, 5, 8, 5};
    // vector<int> ed {2, 4, 6, 7, 9, 9};
    // activitySelectionProblem(st,ed);
    // vector<job> jobs{{'a',2,100}, {'b',1,19},{'c',2,27},{'d',1,25},{'e',3,15}};
    // jobSequencing(jobs);
    
    // vector<int> vals{60,40,100,120},wts{10,20,30,40};
    // fractionalKnapSack(vals,wts,50);

    // vector<int> curr{ 1, 2, 5, 10, 20, 50, 100, 500, 1000};
    // findMinNumberOfCoins(curr, 121);

    // vector<pair<int,int>> clarr{{5, 24}, {15, 25}, {27, 40}, {50, 60}};
    // maximumChainLengthofPairs(clarr);

    // vector<int> job{10, 7, 8, 12, 6, 8};
    // cout<<findMinimumTimetoFinishJobs(job,4,5)<<endl;
    // vector<int> arr{5, 3, 0, 7, 4};
    // cout<<minSumWithTwoNumberFormed(arr)<<endl;

    // minNumberformedWithSumAndDigits(20,3);

    // paperCutIntoMinimumSquares(13,29);

    // vector<int> arr{7, 6, 9, 2, 1};
    // lexicographicallySmallerAfterKSwaps(arr,3);

    // rearrangeStringNoTwoCharSame("aaabb");

    // cout<<maximumHeightPyramid({40, 100, 20, 30})<<endl;
    // cout<<minCoinsAquireAllCoinsWithKExtraAllowed({100, 20, 50, 10, 2, 5},3)<<endl;

    // cout<<findMaximumSumPossibleOfThreeStacks({3,10},{4,5},{2,1})<<endl;

    // cout<<maxSumAfterKNegation({-2, 0, 5, -1, 2},4)<<endl;
    cout<<minCostToCutSquareBoard({2, 1, 3, 1, 4},{4,1,2})<<endl;
}