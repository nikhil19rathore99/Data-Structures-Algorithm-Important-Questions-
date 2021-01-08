#include <bits/stdc++.h>
#define debug(T) cout<<"debug : "<<T<<endl;
using namespace std;
void groupingSameSetOfCharaters(vector<string> &arr)
{
    auto stringSort = [](string s) {
        string res;
        vector<bool> vis(26, 0);
        for (char c : s)
        {
            vis[c - 'a'] = 1;
        }
        for (int i = 0; i < 26; i++)
        {
            if (vis[i])
                res.push_back(char(i + 'a'));
        }
        return res;
    };
    map<string, vector<string>> m;
    for (string s : arr)
    {
        string t = stringSort(s);
        m[t].push_back(s);
    }
    for (auto x : m)
    {
        for (string s : x.second)
        {
            cout << s << ", ";
        }
        cout << endl;
    }
}
int genereateAllBinaries(string s, int i)
{
    //DFS
    if (i == s.size())
    {
        cout << s << endl;
        return 1;
    }
    int c = 0;
    if (s[i] == '?')
    {
        s[i] = '0';
        c += genereateAllBinaries(s, i + 1);
        s[i] = '1';
        c += genereateAllBinaries(s, i + 1);
    }
    else
    {
        c += genereateAllBinaries(s, i + 1);
    }
    return c;

    //BFS
    // queue<string> q;
    // q.push(s);
    // while(q.size()){
    //     string t= q.front();
    //     q.pop();
    //     size_t pos = t.find('?');
    //     if(pos != string::npos){
    //         t[pos]='1';
    //         q.push(t);
    //         t[pos]='0';
    //         q.push(t);
    //     }else cout<<t<<endl;
    // }
}
int smallestWindowsContainingItself(string s)
{
    vector<int> vis(26, 0);
    for (char c : s)
        vis[c - 'a']++;
    int st = 0;
    for (int i : vis)
        if (i)
            st++;
    map<char, int> fs;
    int start = 0, minl = INT_MAX;
    for (int i = 0; i < s.size(); i++)
    {
        fs[s[i]]++;
        if (fs.size() == st)
        {
            minl = min(i - start + 1, minl);
            while (fs.size() == st)
            {
                fs[s[start]]--;
                if (fs[s[start]] == 0)
                    fs.erase(s[start]);
                minl = min(i - start + 1, minl);
                start++;
            }
        }
    }
    return minl;
}
int countWaysToIncreaseLCSByOne(string a, string b)
{
    vector<vector<int>> dpl(a.size() + 2, vector<int>(b.size() + 2, 0)), dpr(a.size() + 2, vector<int>(b.size() + 2, 0));
    vector<int> pos[256];
    for (int i = 0; i < b.size(); i++)
    {
        pos[b[i]].push_back(i + 1);
    }
    for (int i = 1; i <= a.size(); i++)
    {
        for (int j = 1; j <= b.size(); j++)
        {
            dpl[i][j] = a[i - 1] == b[j - 1] ? dpl[i - 1][j - 1] + 1 : max(dpl[i - 1][j], dpl[i][j - 1]);
        }
    }
    for (int i = a.size(); i >= 1; i--)
    {
        for (int j = b.size(); j >= 1; j--)
        {
            dpr[i][j] = a[i - 1] == b[j - 1] ? dpr[i + 1][j + 1] + 1 : max(dpr[i + 1][j], dpr[i][j + 1]);
        }
    }
    int lcs = dpl[a.size()][b.size()];
    int c = 0;
    for (int i = 0; i <= a.size(); i++)
    {
        for (int j = 0; j < 256; j++)
        {
            for (auto x : pos[j])
            {
                if (dpl[i][x - 1] + dpr[i + 1][x + 1] == lcs)
                {
                    c++;
                    break;
                }
            }
        }
    }
    return c;
}
void AnagramicSubstringSearch(string src, string pat)
{
    auto cmp = [](vector<int> arr1, vector<int> arr2) {
        for (int i = 0; i < 256; i++)
        {
            if (arr1[i] != arr2[i])
                return false;
        }
        return true;
    };
    int n = src.size(), m = pat.size();
    vector<int> srcarr(256, 0), patarr(256, 0);
    for (int i = 0; i < m; i++)
    {
        srcarr[src[i]]++;
        patarr[pat[i]]++;
    }
    for (int i = m; i < n; i++)
    {
        if (cmp(srcarr, patarr))
            cout << "Found at " << (i - m) << endl;
        srcarr[src[i]]++;
        srcarr[src[i - m]]--;
    }
    if (cmp(srcarr, patarr))
        cout << "Found at " << (n - m) << endl;
}
bool checkKAnagram(string a, string b, int k)
{
    vector<int> amap(256, 0), bmap(256, 0);
    for (char c : a)
        amap[c - 'a']++;
    for (char c : b)
        bmap[c - 'a']++;
    int ans = 0;
    for (int i = 0; i < 256; i++)
    {
        if (abs(amap[i] - bmap[i]) >= 1)
            ans += abs(amap[i] - bmap[i]);
    }
    return ans <= k;
}
string longestPalindromeSubString(string s)
{
    auto check = [](string s, int l, int r) {
        if (s.size() == 0 || l > r)
            return 0;
        while (l >= 0 && r < s.size() && s[l] == s[r])
        {
            l--;
            r++;
        }
        return r - l - 1;
    };
    int st = 0, ed = 0, ml = 0;
    for (int i = 0; i < (int)s.size() - 1; i++)
    {
        int len1 = check(s, i, i);
        int len2 = check(s, i, i + 1);
        int l = max(len1, len2);
        if (l > ed - st)
        {
            st = i - (l - 1) / 2;
            ed = i + (l / 2);
        }
    }
    return s.substr(st, ed + 1);
}
string smallestWindowContainingAnotherString(string s, string t)
{
    string ans;
    map<char, int> m1, m2;
    for (char c : t)
        m2[c]++;
    int mct = 0, dcmt = t.size();
    int i = -1, j = -1;
    while (1)
    {
        bool f1 = false, f2 = false;
        //aqquire
        while (i < s.size() - 1 && mct < dcmt)
        {
            i++;
            m1[s[i]]++;
            if (m1[s[i]] <= m2[s[i]])
            {
                mct++;
            }
            f1 = 1;
        }
        //ans and release
        while (j < i && mct == dcmt)
        {
            string tans = s.substr(j + 1, i + 1);
            if (ans.length() == 0 || tans.size() < ans.size())
            {
                ans = tans;
            }
            j++;
            if (m1[s[j]] == 1)
                m1.erase(s[j]);
            else
                m1[s[j]]--;
            if (m1[s[j]] < m2[s[j]])
                mct--;
            f2 = 1;
        }
        if (!f1 && !f2)
            break;
    }
    return ans;
}
void palindromeAndPermutations(string s)
{
    vector<int> arr[26], t;
    for (int i = 0; i < s.size(); i++)
    {
        arr[s[i] - 'a'].push_back(i + 1);
    }
    int check = 0;
    for (int i = 0; i < 26; i++)
    {
        if (arr[i].size() % 2 != 0)
            check++;
    }
    if (check > 1)
        cout << "-1" << endl;
    else
    {
        for (int i = 0; i < 26; i++)
        {
            if (arr[i].size() % 2 == 0 && arr[i].size())
            {
                for (int j = 0; j < arr[i].size() / 2; j++)
                {
                    t.push_back(arr[i][j]);
                }
            }
            else
            {
                for (int j = 0; j < arr[i].size(); j++)
                {
                    t.push_back(arr[i][j]);
                }
            }
        }
        for (int i = 25; i >= 0; i--)
        {
            if (arr[i].size() % 2 == 0 && arr[i].size())
            {
                for (int j = arr[i].size() - 1; j >= arr[i].size() / 2; j--)
                {
                    t.push_back(arr[i][j]);
                }
            }
        }
        for (int i : t)
            cout << i << " ";
    }
    cout << endl;
}
void largestPalindromeChangingkDigits(string s, int k)
{
    int l = 0, r = s.size() - 1;
    string pal = s;
    while (l < r)
    {
        if (s[l] != s[r])
        {
            pal[l] = pal[r] = max(s[l], s[r]);
            k--;
        }
        l++;
        r--;
    }
    l = 0;
    r = s.length() - 1;
    if (k < 0)
    {
        cout << "-1" << endl;
        return;
    }
    while (l <= r)
    {
        if (l == r)
        {
            if (k > 0)
                pal[l] = '9';
        }
        if (pal[l] < '9')
        {
            if (k >= 2 && pal[l] == s[l] && pal[r] == s[r])
            {
                pal[l] = pal[r] = '9';
                k -= 2;
            }
            else if (k >= 1 && (pal[l] != s[l] || pal[r] != s[r]))
            {
                k--;
                pal[l] = pal[r] = '9';
            }
        }
        l++;
        r--;
    }
    cout << pal << endl;
}
void lexicographicallyFirstPalindrome(string s)
{
    vector<int> map(26, 0);
    for (char c : s)
        map[c - 'a']++;
    int oddcheck = 0;
    for (int i : map)
        if (i & 1)
            oddcheck++;
    if (oddcheck > 1)
    {
        cout << "No palindrome" << endl;
        return;
    }
    string res;
    for (int i = 0; i < map.size(); i++)
    {
        if (map[i])
        {
            if (map[i] % 2 == 0)
            {
                res += string(map[i] / 2, (char)(i + 'a'));
            }
            else
            {
                res += string(map[i], (char)(i + 'a'));
            }
        }
    }
    string p = res;
    reverse(p.begin(), p.end());
    if (s.length() % 2 == 0)
    {
        cout << res + p << endl;
    }
    else
    {
        for (int i = 1; i < p.size(); i++)
            res.push_back(p[i]);
        cout << res << endl;
    }
}
void longestNonPalindrom(string s)
{
    auto done = [](string s) {
        int l = 0, r = s.size() - 1;
        if (s.length() == 1)
            return 1;
        while (l < r)
        {
            if (s[l] == s[r])
            {
                l++;
                r--;
            }
            else
                return 0;
        }
        return 1;
    };
    bool d = done(s);
    if (d)
        cout << s.length() - 1 << endl;
    else
        cout << s.length() << endl;
}
void stringMerging(string s1, string s2)
{
    auto lcs = [](string s1, string s2) {
        int dp[s1.length() + 1][s2.length() + 1];
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= s1.length(); i++)
        {
            for (int j = 1; j <= s2.length(); j++)
            {
                dp[i][j] = s1[i - 1] == s2[j - 1] ? dp[i - 1][j - 1] + 1 : max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[s1.length()][s2.length()];
    };
    cout << s1.length() + s2.length() - lcs(s1, s2) << endl;
}
void kthCharaterDecryptedString(string s, int k)
{
    auto decrypt = [](string s) {
        stack<char> st;
        string res;
        for (int i = 0; i < s.length(); i++)
        {
            if (isdigit(s[i]))
            {
                string t;
                while (st.size())
                {
                    t = st.top() + t;
                    st.pop();
                }
                cout<<"debug : "<<s[i]<<"<<<<"<<endl;
                int sz=s[i]-'0';
                for (int i = 0; i <sz; i++)
                {
                    res += t;
                }
                t.clear();
            }
            else
                st.push(s[i]);
        }
        while (st.size())
        {
            res = st.top() + res;
            st.pop();
        }
        return res;
    };
    cout << decrypt(s)[k-1] << endl;
}
void printAllPalindromicSubstrings(string s){
    int dp[s.length()][s.length()];
    map<string,int> m;
    memset(dp,0,sizeof(dp));
    set<string> st;
    for(int g=0;g<s.length();g++){
        for(int i=0;i<s.length()-g;i++){
            int j=i+g;
            if(g==0) dp[i][j]=1;
            else if(g==1) dp[i][j]=s[i]==s[j]?1:0;
            else dp[i][j] = s[i]==s[j] ? dp[i+1][j-1] : 0;
            if(dp[i][j]==1){
                st.insert(s.substr(i,g+1));
            }
        }
    }
    for(auto x : st) cout<<x<<endl;
}
int countTotalAnagramicSubstrings(string s){
    map<vector<int>, int>m;
    for(int i=0;i<s.length();i++){
        vector<int> f(26,0);
        for(int j=i;j<s.length();j++){
            f[s[j]-'a']++;
            m[f]++;
        }
    }
    int r=0;
    for(auto x : m){
        r += x.second*(x.second-1)/2;
    }
    return r;
}
int minFlipsContinousToMakeAllEquals(string s){
    int mo=0,m1=0;
    for(int i=0;i<s.length();){
        if(s[i]=='1'){
            m1++;
            while(s[i]=='1')i++;
        }else{
            mo++;
            while(s[i]=='0')i++;
        }
    }
    return min(mo,m1);
}
int countBinaryWithKAdjacentOnes(int n, int k){
    int dp[n+1][k+1][2];
    //starting at i with j adjacent ones ending at 0 or 1
    memset(dp,0,sizeof(dp));
    dp[1][0][0]=1;
    dp[1][0][1]=1;
    for(int i=2;i<=n;i++){
        for(int j=0;j<=k;j++){
            dp[i][j][0] = dp[i-1][j][0]+dp[i-1][j][1];
            dp[i][j][1] = dp[i-1][j][0];
            if(j-1>=0) dp[i][j][1]+=dp[i-1][j-1][1];
        }
    }
    return dp[n][k][0]+dp[n][k][1];
}
int longestCommonSubsequence(string s1, string s2, int l1, int l2,vector<vector<int>>&dp){
     for(int i=s1.length()-1;i>=0;i--){
         for(int j=s2.length()-1;j>=0;j--){
             dp[i][j] = s1[i]==s2[j] ? dp[i+1][j+1]+1 : max(dp[i+1][j],dp[i][j+1]);
         }
     }
     return dp[l1][l2];
}
int printAllLCS(string s1, string s2 ,int l1, int l2, string ans, int cl ,int lcsl,vector<vector<int>>&dp){
    if(cl==lcsl){
        cout<<ans<<endl;
        return 1;
    }
    if(l1==s1.length() || l2==s2.length()) return 0;
    int c=0;
    for(char ch='a';ch<='z';ch++){
        bool d=false;
        for(int i=l1;i<s1.length();i++){
            if(ch==s1[i]){
                for(int j=l2;j<s2.length();j++){
                    if(ch==s2[j] && dp[i][j] == lcsl-cl){
                        ans.push_back(ch);
                        c += printAllLCS(s1,s2,i+1,j+1,ans,cl+1,lcsl,dp);
                        ans.pop_back();   
                        d=true;
                        break;
                    }
                }
            }
            if(d) break;
        }    
    }
    return c;
}
bool findIfS1isSubsequenceofS2(string s1, string s2){
    int i=0,j=0;
    while(i<s1.length() && j < s2.length()){
        if(s1[i]==s2[j]){
            i++;j++;
        }else j++;
    }
    return i==s1.length();
}
string largestWordFormedByDictionary(vector<string> dic, string p){
    string res;
    int maxct=INT_MIN;
    for(string s : dic){
        int ct=0,pi=0;
        debug(s);
        for(int j=0;j<p.length();j++){
            if(p[j]==s[pi]) {
                pi++;
                ct++;
            }
        }
        debug(ct);
        if(ct>maxct) {
            maxct= ct;
            res=s;
        }
    }
    return res;
}
void searchWordIn2DMatrix(vector<string> grid, string word){
    vector<int> r{ -1, -1, -1, 0, 0, 1, 1, 1 }; 
    vector<int> c{ -1, 0, 1, -1, 1, -1, 0, 1 }; 
    auto searchWordIn2DGrid=[r,c](vector<string>& grid, string word, int ro, int co){
        if(word[0]!=grid[ro][co]) return false;
        for(int d=0;d<8;d++){
            int cr=ro+r[d], cc = co+c[d];
            int l;
            for(l=1;l<word.size();l++){
                if(cr>=grid.size() || cc>=grid[0].size() || cr<0 || cc<0) break;
                if(grid[cr][cc]!=word[l]) break;
                cr+=r[d];cc+=c[d];
            }
            if(l==word.size()) return true;
        }
        return false;
    };
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[i].size();j++){
            if(searchWordIn2DGrid(grid,word,i,j)){
                cout<<i<<" "<< j<< endl;
            }
        }
    }
}
int countSubSequenceAiBjCk(string s){
    int a=0,b=0,c=0;
    for(int i=0;i<s.length();i++){
        if(s[i]=='a') a = 1+2*a;
        else if(s[i]=='b') b = a+2*b;
        else if(s[i]=='c') c = b+2*c;
    }
    return c;
}
int numberOfTimesStringOccursAsSubsequence(string s, string p, int si, int pi){
    if(si==0 && pi==0) return 1;
    if(pi==0) return 1;
    if(si==0) return 0;
    if(s[si-1]==p[pi-1]) return numberOfTimesStringOccursAsSubsequence(s,p,si-1,pi-1)+ numberOfTimesStringOccursAsSubsequence(s,p,si-1,pi);
    else return numberOfTimesStringOccursAsSubsequence(s,p,si-1,pi);
}
int countDistintSubsequence(string s){
    string t = "$"+s;
    vector<int> dp(t.length());
    dp[0]=1;
    for(int i=1;i<t.length();i++){
        dp[i] = 2*dp[i-1];
        for(int j=i-1;j>=1;j--){
            if(t[i]==t[j]){
                dp[i]-=dp[j-1];
                break;
            }
        }
    }
    return dp.back();
}
int countPatten1O1(string s){
    int ct=0;
    for(int i=0;i<s.length();){
        if(s[i]=='1'){
            int j=i+1;
            debug(j);
            bool f=false;
            while(j<s.length() && s[j]=='0') {j++; f=1;}
            debug(j);
            if(j<s.length() && s[j]=='1' && f==1) ct++;
            i=j;
        }
        else i++;
    }
    return ct;
}
int firstNonRepeatingCharacter(string s){
    pair<int,int> map[256];
    for(int i=0;i<s.length();i++){
        map[s[i]-'a'].first++;
        map[s[i]-'a'].second=i;
    }
    int ans=INT_MAX;
    for(pair<int,int> p : map){
        if(p.first==1)ans=min(ans,p.second); 
    }
    return ans==INT_MAX ? -1 : ans;
}
string rearrangeKdistanceApart(string s, int k){
    vector<int> map(26,0);
    for(char c : s) map[c-'a']++;
    auto cmp=[&](pair<int,int> &x, pair<int,int> &y){
        return x.second==y.second ? x.first>y.first : y.second>x.second;
    };
    priority_queue<pair<int,int>,vector<pair<int,int>>, decltype(cmp)> pq(cmp);
    for(int i=0;i<26;i++){
        if(map[i]) pq.push({i,map[i]});
    }
    
    string ans;
    while(pq.size()){
        vector<int> t;
        for(int i=0;i<k;i++){
            pair<int,int> r = pq.top();
            pq.pop();
            ans.push_back((r.first+'a'));
            t.push_back(r.first);
            if(pq.empty()){
                if(i!=k-1 && ans.length()!=s.length()) return "";
                break;
            }
        }
        for(int i : t){
            if(--map[i]) pq.push({i,map[i]});
        }
    }
    return ans; 
    // return "";
}
string recursivelyRemoveAllAdjacent(string s){
    for(int i=0;i<s.length()-1;i++){
        if(s[i]==s[i+1]){
            return recursivelyRemoveAllAdjacent(s.substr(0,i)+s.substr(i+2));
        } 
    }
    return s;
}
bool wildCardMatching(string first, string second){
    if(first.length()==0 && second.length()==0) return 1;
    if(first.size()>1 && first[0]=='*' && second.length()==0) return 0;
    if((first.length()>1 && first[0]=='?' )|| 
               first.length()!=0 && second.length()!=0  && first[0]==second[0]) 
                    return wildCardMatching(first.substr(1),second.substr(1));
    if(first.length() && first[0]=='*') return wildCardMatching(first.substr(1),second) || wildCardMatching(first,second.substr(1));
    return false;
}
int lexicographicallyRankOfString(string s){
    string t =s;
    int i=1;
    sort(s.begin(),s.end());
    do{
        if(s==t) break;
        i++;
    }while(next_permutation(s.begin(),s.end()));
    return i;
}
void dfs(vector<vector<int>>& g, stack<int>& st, int s, vector<bool>& vis){
    vis[s]=1;
    for(int x : g[s])  if(!vis[x]) dfs(g,st,x,vis);
    st.push(s);
}
void alienDictionary(vector<string> words, int x){
    stack<int> st;
    vector<vector<int>> graph(x);
    auto addEdje=[&](int u, int v){
        graph[u].push_back(v);
    };
    for(int i=0;i<words.size()-1;i++){
        for(int j=0;j<min(words[i].size(),words[i+1].size());j++){
            if(words[i][j]!=words[i+1][j]) {addEdje(words[i][j]-'a', words[i+1][j]-'a'); break;}
        }
    }
    vector<bool> vis(x,false);
    for(int i=0;i<graph.size();i++){
        if(!vis[i]) dfs(graph,st,i,vis);
    }
    while(!st.empty()){
        cout<<(char)(st.top()+'a')<<" ";
        st.pop();
    }
    cout<<endl;
}
int longestSubstringWithKUniqueCharacters(string s, int k){
    map<char,int> mp;
    int bs=0;
    int st=0;
    for(int i=0;i<s.length();i++){
        mp[s[i]]++;
        while(mp.size()>k){
            if(mp[s[st]]>1) mp[s[st]]--;
            else mp.erase(s[st]);
            st++;
        }
        if(i-st+1>bs) bs=i-st+1;
    }
    return bs;
}
int lengthOfLongestValidSubstring(string s){
    auto effecient=[](string s){
        int l=0,r=0,res=0;
        for(int i=0;i<s.length();i++){
            if(s[i]=='(')l++;
            else r++;
            if(l==r) res=max(res,2*r);
            if(r>l)r=l=0;
        }
        l=r=0;
        for(int i=s.length()-1;i>=0;i--){
            if(s[i]=='(')l++;
            else r++;
            if(l==r) res=max(res,2*l);
            if(l>r) l=r=0;
        }
        return res;
    };
    // stack<int> st;
    // st.push(-1);
    // int res=0;
    // for(int i=0;i<s.length();i++){
    //     if(s[i]=='(') st.push(i);
    //     else{
    //         if(!st.empty()) st.pop();
    //         if(!st.empty()) res=max(res, i-st.top());
    //         else st.push(i);
    //     }
    // }
    // return res;
    return effecient(s);
}
void printAllWaysInBrackets(string s, int idx, string ans){
    if(idx==s.length()) cout<<ans<<endl;
    for(int i=idx;i<s.length();i++){
        printAllWaysInBrackets(s,i+1, ans+"("+s.substr(idx,i+1-idx)+")");
    }
}
void printZigZag(string s, int n){
    if(n==1) cout<<s<< endl;
    bool d;
    int r=0;
    vector<string> arr(n);
    for(int i=0;i<s.length();i++){
        arr[r].push_back(s[i]);
        if(r==n-1) d=0;
        if(!r) d=1;

        if(d) r++;
        else r--;
    }
    for(int i=0;i<n;i++){
        cout<<arr[i]<<endl;
    }
}
void kMP(string s, string p){
    auto lpss = [&](string s){
        int l=0;
        int i=1;
        vector<int> lp(s.length(),0);
        while(i<s.length()){
            if(s[i]==s[l]) {
                lp[i++]=++l;
            }else{
                if(l) l=lp[l-1];
                else lp[i++]=0;
            }
        }
        return lp;
    };
    vector<int> lps = lpss(s);
    int i=0,j=0;
    while(i<s.length()){
        if(s[i]==p[j]){
            i++;j++;
        }
        if(j==p.length()) {cout<<"Found : "<<(i-j)<<" to "<<(i-j+p.length())<<endl; j = lps[j-1];}
        else if(i<s.length() && s[i]!=p[j]){
            if(j) j=lps[j-1];
            else i++;
        }
    }
}
int minOperationConvertA2B(string a, string b){
    vector<int> ca(256,0);
    for(char c : a) ca[c-'a']++;
    for(char c : b) ca[c-'b']--;
    for(int i : ca) if(i) return -1;
    int r=0;
    for(int i=a.length()-1, j=b.length()-1;i>=0;){
        while(i>=0 && a[i]!=b[j]){
            i--;r++;
        }
        if(i>=0) {i--;j--;}
    }
    return r;
}
int main()
{
    // vector<string> v{"may", "student", "students", "dog",
    //              "studentssess", "god", "cat", "act",
    //              "tab", "bat", "flow", "wolf", "lambs",
    //              "amy", "yam", "balms", "looped",
    //              "poodle"};
    // groupingSameSetOfCharaters(v);
    // string bins="1??0?101";
    // cout<<genereateAllBinaries(bins,0)<<endl;
    // cout<<smallestWindowsContainingItself("aaab")<<endl;
    // cout<<countWaysToIncreaseLCSByOne("aa","baaa")<<endl;
    // AnagramicSubstringSearch("BACDGABCDA","ABCD");
    // cout<<longestPalindromeSubString("racecar")<<endl;
    // cout<<smallestWindowContainingAnotherString("hisisateststring","tist")<<endl;
    // palindromeAndPermutations("abc");
    // largestPalindromeChangingkDigits("43435",1);
    // lexicographicallyFirstPalindrome("apple");
    // longestNonPalindrom("aaabaaa");
    // stringMerging("abab","baba");
    // kthCharaterDecryptedString("ab4c2ed3",9);
    // printAllPalindromicSubstrings("abaaa");
    // cout<<countTotalAnagramicSubstrings("geeg")<<endl;
    // cout<<minFlipsContinousToMakeAllEquals("010101100011")<<endl;
    // cout<<countBinaryWithKAdjacentOnes(4,2)<<endl;
    // vector<vector<int>> dp(100, vector<int>(100,0));
    // int lcs = longestCommonSubsequence("abcabcaa","acbacba",0,0,dp);
    // cout<<lcs<<endl;
    // cout<<printAllLCS("abcabcaa","acbacba",0,0,"",0,lcs,dp)<<endl;
    // cout<<findIfS1isSubsequenceofS2("gksrek","geeksforgeeks")<<endl;
    // cout<<largestWordFormedByDictionary({"ale", "apple", "monkey", "plea"},"abpcplea")<<endl;
    // searchWordIn2DMatrix({"GEEKSFORGEEKS", "GEEKSQUIZGEEK","IDEQAPRACTICE"},"GEEKS");
    // cout<<countSubSequenceAiBjCk("abbc")<<endl;
    // cout<<numberOfTimesStringOccursAsSubsequence("GeeksforGeeks","Gks",13, 3)<<endl;
    // cout<<countDistintSubsequence("ggg")<<endl;
    // cout<<countPatten1O1("100001abc101")<<endl;
    // cout<<firstNonRepeatingCharacter("geeksforgeeks")<<endl;
    // cout<<rearrangeKdistanceApart("aabbcc",3)<<endl;
    // cout<<recursivelyRemoveAllAdjacent("geeksforgeeg")<<endl;
    // cout<<wildCardMatching("g*ks", "geeks")<<endl;
    // cout<<lexicographicallyRankOfString("abc")<<endl;
    // alienDictionary({"baa", "abcd", "abca", "cab", "cad"},4);
    // cout<<longestSubstringWithKUniqueCharacters("aabbcc",2)<<endl;
    // cout<<lengthOfLongestValidSubstring("((()")<<endl;
    // printAllWaysInBrackets("abcd",0,"");
    // printZigZag("ABCDEFGH",2);
    // kMP("ABABDABACDABABCABAB","ABABCABAB");
    cout<<minOperationConvertA2B("EACBD","EABCD")<<endl;
}