#include <bits/stdc++.h>
using namespace std;
int kConcatenation(vector<int> &arr, int k)
{
    auto getKadanes = [](vector<int> &arr) {
        int curr = arr[0], maxs = arr[0];
        for (int i = 1; i < arr.size(); i++)
        {
            if (curr >= 0)
            {
                curr += arr[i];
            }
            else
            {
                curr = arr[i];
            }
            maxs = max(maxs, curr);
        }
        return maxs;
    };
    int sum = 0;
    for (int i : arr)
        sum += i;
    vector<int> twoarr(arr.size() * 2);
    for (int i = 0; i < 2 * arr.size(); i++)
    {
        twoarr[i] = arr[i];
        twoarr[i + arr.size()] = arr[i];
    }
    int twokadaneSum = getKadanes(twoarr);
    int kadaneSum = getKadanes(arr);
    if (k == 1)
    {
        return kadaneSum;
    }
    else if (sum < 0)
    {
        return twokadaneSum;
    }
    else
    {
        return twokadaneSum + (k - 2) * sum;
    }
}
int maxSumCircularSubarray(vector<int> &arr)
{
    auto getKadanes = [](vector<int> &arr) {
        int curr = arr[0], maxs = arr[0];
        for (int i = 1; i < arr.size(); i++)
        {
            if (curr >= 0)
            {
                curr += arr[i];
            }
            else
            {
                curr = arr[i];
            }
            maxs = max(maxs, curr);
        }
        return maxs;
    };
    int sum = 0;
    int kadane = getKadanes(arr);
    for (int &i : arr)
    {
        sum += i;
        i = -i;
    }
    int nowkadane = getKadanes(arr);
    return max(sum + nowkadane, kadane);
}
void subarrayWithGivenSum(vector<int> &arr, int req)
{
    int curr = 0;
    int st = 0;
    bool f = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        while (st < i - 1 && curr > req)
        {
            curr -= arr[st++];
        }
        if (curr < req && i < arr.size())
            curr += arr[i];
        if (curr == req)
        {
            cout << "Found from " << st << " to " << i - 1 << "( " << curr << " )" << endl;
            f = 1;
            return;
        }
    }
    if (!f)
        cout << "Not found" << endl;
}
int equilibriumIndex(vector<int> &arr)
{
    int ts=0;
    for(int i : arr) ts += i;
    int cs=0;
    for(int i=0;i<arr.size();i++){
        ts -= arr[i];
        if(cs==ts){
            return i;
        }
        cs += arr[i];
    }
    return -1;
}
int maxSumIncreasingSubarray(vector<int>& arr){
    vector<int> msis(arr);
    for(int i=1;i<arr.size();i++){
        for(int j=0;j<i;j++){
            if(arr[i]>arr[j] && msis[i]+arr[j] > msis[i]){
                msis[i] += arr[j];
            }
        }
    }
    return *max_element(msis.begin(),msis.end());
}
void convertZigZag(vector<int>& arr){
    auto swap=[](int*a,int*b){
        int t=*a;*a=*b;*b=t;
    };
    bool f=0;
    for(int i=0;i<arr.size()-1;i++){
        if(!f){
            if(arr[i]>arr[i+1]) swap(&arr[i],&arr[i+1]);
        }else{
            if(arr[i]<arr[i+1]) swap(&arr[i],&arr[i+1]);
        }
        f=!f;
    }
    for(int i : arr) cout<<i<<" ";
    cout<<endl;
}
int pairGivenDiff(vector<int>& arr, int diff){
   map<int,int> m;
   for(int i : arr){
       if(m.find(i-diff)!=m.end()) return 1;
       m[i]++;
   }
   return 0;
}
int chocolateDistributionProblem(vector<int>& arr, int m){
    sort(arr.begin(),arr.end());
    if(m==0 || arr.size()==0) return 0;
    int mdiff=INT_MAX;
    for(int i=0;i+m-1<arr.size();i++){
        mdiff=min(mdiff,arr[i+m-1]-arr[i]);
    }
    return mdiff;
}
int minplatform(vector<int>& arr, vector<int>& dep){
   vector<pair<int,char>> t;
   for(int i : arr) t.push_back({i,'a'});
   for(int i : dep) t.push_back({i,'d'});
   sort(t.begin(),t.end());
   int minp=0,res=1;
   for(pair<int,char> p : t){
       if(p.second=='a') minp++;
       else minp--;
       res=max(res,minp);
   }
   return res;
}
int tappingRainWater(vector<int>& arr){
    int lm=0,rm=0;
    int l=0,h=arr.size()-1;
    int res=0;
    while(l<=h){
        if(arr[l]<arr[h]){
            res += max(0,lm-arr[l]);
            lm=max(lm,arr[l]);
            l++;
        }else{
            res += max(0,rm-arr[h]);
            rm=max(rm,arr[h]);
            h--;
        }
    }
    return res;
}
void stockbuySell(vector<int>& arr){
    int i=0;
    while(i < arr.size()){
        if(i+1<arr.size() && arr[i]>=arr[i+1]){
            i++;
        }
        int b=i++;
        if(i==arr.size()) break;
        while(i+1<arr.size() && arr[i]<arr[i+1]) i++;
        int s=i;
        cout<<b<<" "<<s<<endl;
    }
}
void inplaceRotateMatrix(vector<vector<int>>& arr){
    auto swp=[&](int* a, int* b){
        int t = *a;
        *a = *b;
        *b = t;
    };
    auto rev = [&](vector<vector<int>>& arr){
        for(int j=0;j<arr[0].size();j++){
            int l=0,r=arr.size()-1;
            while(l<=r){
                swp(&arr[l][j],&arr[r][j]);
                l++;r--;
            }
        }
    };
    for(int i=0;i<arr.size();i++){
        for(int j=0;j<i;j++){
            swp(&arr[i][j],&arr[j][i]);
        }
    }
    rev(arr);
    for(vector<int> a: arr){
        for(int i : a){
            cout<<i<<" ";
        }
        cout<<endl;
    }
}
class kpair{
    public:
        int a,b;
        int sum;
        kpair(){};
        kpair(int sum, int a, int b){
            this->a=a;
            this->b=b;
            this->sum=sum;
        }
        bool operator>(const kpair& o) const{
            return this->sum > o.sum;
        }
        bool operator<(const kpair& o) const{
            return this->sum < o.sum;
        }
};
void kpairSmallestTwoArray(vector<int>& arr1, vector<int>& arr2,int k){
    priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>, greater<pair<int,pair<int,int>>>> pq;
    sort(arr1.begin(),arr1.end());
    sort(arr2.begin(),arr2.end());
    set<pair<int,int>> st;
    pq.push({arr1[0]+arr2[0],{arr1[0],arr2[0]}});
    st.insert({0,0});
    int i=0,j=0;
    for(int c=0;c<k;c++){
        pair<int,pair<int,int>> r = pq.top();
        pq.pop();
        cout<<r.second.first<<" "<<r.second.second<<" "<<r.first<<endl;
        pair<int,int> t = make_pair(i+1,j);
        if(st.find(t)==st.end()){
            pq.push({arr1[i+1]+arr2[j],{arr1[t.first],arr2[t.second]}});
            st.insert(t);
        }
        pair<int,int> t1 = make_pair(i,j+1);
        if(st.find(t1)==st.end()){
            pq.push({arr1[i]+arr2[j+1],{arr1[t1.first],arr2[t1.second]}});
            st.insert(t1);
        }
    }
}
int findInSortedRotatedArray(vector<int>& arr, int l, int h, int x){
    if(l>h) return -1;
    int m = (l+h)/2;
    if(arr[m]==x) return m;
    if(arr[l]<=arr[m]){
        if(x>=arr[l] && x<=arr[m]) return findInSortedRotatedArray(arr,l,m-1,x);
        return findInSortedRotatedArray(arr,m+1,h,x);
    }else{
        if(x>=arr[m] && x<=arr[h]) return findInSortedRotatedArray(arr,m+1,h,x);
        return findInSortedRotatedArray(arr, l,m-1,x);
    }
}
int maxixarri(vector<int>& arr){
    int currmax=0;
    int currsum=0;
    for(int i=0;i<arr.size();i++){
        currmax+=i*arr[i];
        currsum+=arr[i];
    }
    int res=currmax;
    for(int i=1;i<arr.size();i++){
        int nextmax = currmax-(currsum-arr[i-1])+arr[i-1]*(arr.size()-1);
        currmax=nextmax;
        res=max(res,currmax);
    }
    return res;
}
void rearrangePosNeg(vector<int>& arr){
    auto swap=[](int*a, int* b){
        int t=*a; *a=*b; *b=t;
    };
    int i=0,j=0;
    while(j<arr.size() && i < arr.size()){
        if(arr[j]<0){
            swap(&arr[i],&arr[j]);
            j++;i++;
        }else{
            j++;
        }
    }
    int p = i,n=0;
    while(p<arr.size() && n<p && arr[n]<0){
        swap(&arr[p],&arr[n]);
        p++;
        n+=2;
    }
    for(int i : arr) cout<<i<<" ";
    cout<<endl;
}
void threeWayPartitioning(vector<int>& arr, int l, int h){
    int lo=0,hi=arr.size()-1;
    auto swap=[&](int *a ,int *b){
        int t = *a; 
        *a = *b; 
        *b = t;
    };
    for(int m=0;m<hi;){
        if(arr[m]<l){
            swap(&arr[m++],&arr[lo++]);
        }else if(arr[m]>h){
            swap(&arr[m],&arr[hi--]);
        }else{
            m++;
        }
    }
    for(int i : arr) cout<<i<<" ";
    cout<<endl;
}
void largestSuabarray01(vector<int>& arr){
    for(int &i : arr) {if(!i) i=-1;}
    int psum=0;
    map<int,int> m;
    int maxL=0;
    for(int i=0;i<arr.size();i++){
        psum += arr[i];
        if(m.find(psum)!=m.end()){
            if(i-m[psum]>maxL){
                cout<<m[psum]<<" "<<i<<endl;
                maxL=i-m[psum];
            }
        }
        else m[psum]=i;
    }
    cout<<maxL<<endl;
}
int maxProductSubarray(vector<int>& arr){

    int currmax=arr[0],currmin=arr[0];
    int finalmax=arr[0];
    for(int i=0;i<arr.size();i++){
        int t=currmax;
        currmax=max(max(currmax*arr[i],currmin*arr[i]),arr[i]);
        currmin=min(min(t*arr[i],currmin*arr[i]),arr[i]);
        finalmax=max(finalmax,currmax);  
    }
    return finalmax;
}
void mergeOverLappingInterval(vector<int>& st,vector<int>& ed){
    vector<pair<int,int>> iv;
    for(int i=0;i<st.size();i++) iv.push_back({st[i],ed[i]});
    sort(iv.begin(),iv.end());
    vector<pair<int,int>> miv;
    miv.push_back(iv[0]);
    for(int i=1;i<iv.size();i++){
        if(miv[i-1].second > iv[i].first){
            miv[i-1].second=max(miv[i-1].second,iv[i].second);
        }else miv.push_back({iv[i].first,iv[i].second});
    }
    for(auto x : miv) cout<<x.first<<" "<<x.second<<endl;
    cout<<endl;
}
int stockBuySellAtMostTwice(vector<int>& arr){
    int on_t=INT_MIN,tw_t=INT_MIN;
    int pr = INT_MAX,tx=INT_MAX;
    for(int i=0;i<arr.size();i++){
        pr=min(pr,arr[i]);
        on_t=max(on_t,arr[i]-pr);
        tx=min(tx, arr[i]-on_t);
        tw_t=max(tw_t,arr[i]-tx);
    }
    return max(on_t,tw_t);
}
int stockBuySellAtMostKTimes(vector<int>& arr, int k){
    vector<vector<int>> dp(k+1,vector<int>(arr.size(),0));
    for(int i=1;i<=k;i++){
        int mx=INT_MIN;
        for(int j=1;j<arr.size();j++){
            mx=max(mx,dp[i-1][j-1]-arr[j-1]);
            // for(int l=0;l<j;l++){
            //     mx=max(mx, dp[i-1][l]+arr[i]-arr[l]);
            // }
            //optimization - n^2
            dp[i][j]=max(dp[i][j-1], arr[j]+mx);
        }
    }
    return dp[k][arr.size()-1];
}
int maxDiffBetweenTwoElements(vector<int>& arr){
    int mn=INT_MAX;
    int maxd=0;
    for(int i=0;i<arr.size();i++){
        mn=min(mn,arr[i]);
        maxd=max(maxd,arr[i]-mn);
    }
    return maxd;
}
int minSwapLessThanKtogether(vector<int>& arr,int k){
    int i=0,j=0;
    auto swap=[&](int *a, int* b){
        int t=*a;*a=*b;*b=t;
    };
    int ms=0;
    while(j<arr.size() && i <arr.size()){
        if(arr[j]<=k){
            if(i!=j) ms++;
            swap(&arr[i++],&arr[j++]);
            
        }else j++;
    }
    return ms;
}
int largestSumAtleastKNumber(vector<int>& arr, int k){
    vector<int>maxSum(arr.size());
    maxSum[0]=arr[0];
    int currmax=arr[0];
    for(int i=1;i<arr.size();i++){
        currmax=max(currmax+arr[i],arr[i]);
        maxSum[i]=currmax;
    }
    int sum=0;
    for(int i=0;i<k;i++){
        sum += arr[i];
    }
    int ls=sum;
    for(int i=k;i<arr.size();i++){
        int xs = sum+arr[i]-arr[i-k];
        ls = max({xs,ls,xs+maxSum[i-k]});
    }
    return ls;
}
int minimizeMaxDifferenceHeights(vector<int>& arr, int k){
    sort(arr.begin(),arr.end());
    int mx,mn,ans=arr.back()-arr[0];
    for(int i=0;i<arr.size();i++){
            mn=min(arr[0]+k,arr[i]-k);
            mx=max(arr.back()-k,arr[i-1]+k);
            ans=min(ans,mx-mn);
    }
    return ans;
}
void generateAllPossibleSortedArrays(vector<int>& arr1, vector<int>& arr2, vector<int> c, int i, int j, int k, bool f){
    if(f){
        if(k){
            for(int t: c) cout<<t<<" ";
            cout<<endl;
        }
        for(int t=i;t<arr1.size();t++){
            if(!k){
                c.push_back(arr1[t]);
                generateAllPossibleSortedArrays(arr1,arr2,c,t+1,j,k,!f);
            }else{
                if(c.back() < arr1[t]){
                    c.push_back(arr1[t]);
                    generateAllPossibleSortedArrays(arr1,arr2,c,t+1,j,k+1,!f);
                }
            }
        }
    }else{
        for(int t=j;t<arr2.size();t++){
            if(c.back() < arr2[t]){
                c.push_back(arr2[t]);
                generateAllPossibleSortedArrays(arr1,arr2,c,i,t+1,k+1,!f);
            }
        }
    }
}
int differenceIndex(vector<int>& arr){
    vector<int> lmin(arr.size());
    vector<int> rmax(arr.size());
    for(int i=0;i<arr.size();i++) {
        if(i) lmin[i]=min(lmin[i-1],arr[i]);
        else lmin[i]=arr[i];
    }
    for(int i=arr.size()-1;i>=0;i--) {
        if(i!=arr.size()-1) rmax[i]=max(rmax[i+1],arr[i]);
        else rmax[i]=arr[i];
    }
    int i=0,j=0;
    int mxdiff=-1;
    while(i<arr.size()&&j<arr.size()){
        if(lmin[i]<rmax[j]) {mxdiff=max(mxdiff,j-i); j++;}
        else i++;
    }
    return mxdiff;
}
void printNextPermutation(vector<int>& arr){
    auto swap=[](int* a, int* b){
        int t=*a;*a=*b;*b=t;
    };
    int i=arr.size()-2;
    while(i && arr[i]>=arr[i+1])i--;
    if(i){
        int j=arr.size()-1;
        while(j>=0 && arr[j]<=arr[i])j--;
        swap(&arr[i],&arr[j]);
    }
    reverse(arr.begin()+i+1,arr.end());
    for(int i : arr) cout<<i<<" ";
    cout<<endl;
}
void overlappingMax3SubarrayKSize(vector<int>& arr, int k){
    vector<int>dp(arr.size());
    vector<int> left(arr.size()),right(arr.size());
    int s=0;
    for(int i=0;i<arr.size();i++){
        s += arr[i];
        if(i>=k) s -= arr[i-k];
        if(i>=k-1) dp[i-k+1]=s;
    }
    int mxindex=0;
    for(int i=0;i<arr.size();i++){
        if(dp[i]>dp[mxindex]) mxindex=i;
        left[i]=mxindex;
    }
    mxindex=arr.size()-1;
    for(int i=arr.size()-1;i>=0;i--){
        if(dp[i]>=dp[mxindex])mxindex=i;
        right[i]=mxindex;
    }
    vector<int> result(3,-1);
    for(int i=k;i<arr.size()-k;i++){
        if(result[0]==-1 || dp[result[0]]+dp[result[1]]+dp[result[2]]<dp[left[i-k]]+dp[i]+dp[right[i+k]]){
            result[0]=left[i-k];
            result[1]=i;
            result[2]=right[i+k];
        }
    }
    for(int i : result) cout<<i<<" ";
    cout<<endl;
}
int subarraysWithMaxValueInGivenRange(vector<int>& arr, int l, int r){
    
    int mx=-1,mn=-1;
    int res=0;
    for(int i=0;i<arr.size();i++){
        if(arr[i]>=l && arr[i]<=r) mx=i;
        else if(arr[i]>r) mx=mn=i;
        res += mx-mn;
    }
    return res;
}
void rearrangeMaxMinConstantSpace(vector<int>& arr){
    int maxe=arr.size()+1;
    int maxi=arr.size()-1,mini=0;
    for(int i=0;i<arr.size();i++){
        if(i&1) arr[i]+=(arr[mini++]%maxe)*maxe;
        else arr[i] += (arr[maxi--]%maxe)*maxe;
    }
    for(int &i : arr) i = i/maxe;
    for(int i : arr) cout<<i<<" ";
    cout<<endl;
}
int printComb(vector<int>& arr, int i, int sz, vector<int> t){
    if(sz==0) {
         for(int i : t) cout<<i<<" ";
            cout<<endl;
            return 1;
    }
    if(i==arr.size()){
        return 0;
    }
    int c=0;
    for(int j=i;j<arr.size();j++){
        t.push_back(arr[j]);
        c += printComb(arr,j+1,sz-1,t);
        t.pop_back();
    }
    return c;
}
int main(){
    // vector<int> arr{1, 4, 0, 0, 3, 10, 5};
    // subarrayWithGivenSum(arr,7);
    // vector<int> eqarr{-7, 1, 5, 2, -4, 3, 0};
    // cout << equilibriumIndex(eqarr);
    // vector<int> msarr{1, 101, 2, 3, 100, 4, 5};
    // cout<<maxSumIncreasingSubarray(msarr)<<endl;
    // vector<int> zarr{4, 3, 7, 8, 6, 2, 1};
    // convertZigZag(zarr);
    // vector<int> parr{5, 20, 3, 2, 50, 80};
    // cout<<pairGivenDiff(parr,78)<<endl;
    // vector<int> carr{7, 3, 2, 4, 9, 12, 56};
    // cout<<chocolateDistributionProblem(carr,3)<<endl;
    // vector<int> marr{ 900, 940, 950, 1100, 1500, 1800 }; 
    // vector<int> mdep{ 910, 1200, 1120, 1130, 1900, 2000 };
    // cout<<minplatform(marr,mdep)<<endl;
    // vector<int> tarr{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    // cout<<tappingRainWater(tarr)<<endl;
    // vector<int> sbarr{100, 180, 260, 310, 40, 535, 695};
    // stockbuySell(sbarr);
    // vector<vector<int>> mat={ 
    //     { 1, 2, 3, 4 }, 
    //     { 5, 6, 7, 8 }, 
    //     { 9, 10, 11, 12 }, 
    //     { 13, 14, 15, 16 } 
    // }; 
    // inplaceRotateMatrix(mat);
    // vector<int> karr1{1,3,11};
    // vector<int> karr2{2,4,8};
    // kpairSmallestTwoArray(karr1,karr2,4);
    // vector<int> rarr{4, 5, 6, 7, 8, 9, 1, 2, 3};
    // cout<<findInSortedRotatedArray(rarr,0,rarr.size()-1,10);
    // vector<int> maxarr{8, 3, 1, 2};
    // cout<<maxixarri(maxarr)<<endl;
    // vector<int> pnarr{-1, 2, -3, 4, 5, 6, -7, 8, 9};
    // rearrangePosNeg(pnarr);
    // vector<int> tharr{1, 14, 5, 20, 4, 2, 54, 20, 87, 
    //             98, 3, 1, 32};
    // threeWayPartitioning(tharr, 10,20);
    // vector<int>larr{1, 0, 1, 1, 1, 0, 0};
    // largestSuabarray01(larr);
    // vector<int> parr{6,-3,-10,0,2};
    // cout<<maxProductSubarray(parr)<<endl;
    // vector<int> st{1,2,5,6};
    // vector<int> ed{3,4,7,8};
    // mergeOverLappingInterval(st,ed);
    // vector<int> bstw{10, 22, 5, 75, 65, 80};
    // cout<<stockBuySellAtMostTwice(bstw)<<endl;
    // vector<int> bskt{10, 22, 5, 75, 65, 80};
    // cout<<stockBuySellAtMostKTimes(bskt,2)<<endl;
    // vector<int>darr{7, 9, 5, 6, 3, 2};
    // cout<<maxDiffBetweenTwoElements(darr)<<endl;
    // vector<int>marr{2, 7, 9, 5, 8, 7, 4};
    // cout<<minSwapLessThanKtogether(marr,5)<<endl;
    // vector<int> sarr{1,1,1,1,1,1};
    // cout<<largestSumAtleastKNumber(sarr,2)<<endl;
    // vector<int> minarr{1, 5, 15, 10};
    // cout<<minimizeMaxDifferenceHeights(minarr, 3)<<endl;
    // vector<int>arr1{10,15,25},arr2{1,5,20,30};
    // generateAllPossibleSortedArrays(arr1,arr2,{},0,0,0,true);
    // vector<int>permarr{1,2,3};
    // printNextPermutation(permarr);
    // vector<int> djiarr{9, 2, 3, 4, 5, 6, 7, 8, 18, 0};
    // cout<<differenceIndex(djiarr)<<endl;
    // vector<int> arr{1,2,1,2,6,7,5,1};
    // overlappingMax3SubarrayKSize(arr,2);
    // vector<int> subarr{3,4,1};
    // cout<<subarraysWithMaxValueInGivenRange(subarr,2,4)<<endl;
    // vector<int>rearr{1,2,3,4,5,6,7,8,9};
    // rearrangeMaxMinConstantSpace(rearr);
    vector<int> combarr{1,2,3,4};
    cout<<printComb(combarr,0,2,{})<<endl;
}