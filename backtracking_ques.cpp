// #include<iostream>
#include<bits/stdc++.h>
using namespace std;

void knightTour(vector<vector<int>>& chess, int r, int c, int m){
    if(r<0 || c < 0 || r >= chess.size() || c >= chess[0].size() || chess[r][c]!=0) return;
    if(m == chess.size()*chess[0].size()){
        chess[r][c]=m;
        for(vector<int> r : chess){
            for(int c : r) cout<<c<<" ";
            cout<<endl;
        }
        cout<<"__________________________"<<endl;
        chess[r][c] = 0;
        return;
    }
    chess[r][c] = m;
    knightTour(chess, r-2,c+1,m+1);
    knightTour(chess, r+2,c+1,m+1);
    knightTour(chess, r-2,c-1,m+1);
    knightTour(chess, r+2,c-1,m+1);
    knightTour(chess, r-1,c+2,m+1);
    knightTour(chess, r+1,c+2,m+1);
    knightTour(chess, r-1,c-2,m+1);
    knightTour(chess, r+1,c-2,m+1);
    chess[r][c] =0;
}

bool ratInMaze(vector<vector<int>>& maze, int r, int c){
    if(r<0 || c<0 || r>=maze.size() || c>=maze[0].size() || maze[r][c]==0||maze[r][c]==2) return 0;
    if(r==maze.size()-1 && c == maze[0].size()-1) {maze[r][c]=2;return 1;}
    maze[r][c]=2;
    bool res = ratInMaze(maze,r+1,c)||ratInMaze(maze,r-1,c) || ratInMaze(maze,r,c+1)||ratInMaze(maze,r,c-1);
    // maze[r][c]=1;
    return res;
}

void removeInvalidParanthesis(string s){
    set<string> vis;
    auto check =[](string s){
        int ct=0;
        for(char c : s){
            ct += c=='(';
            ct -= c==')';
            if(ct<0) return false;
        }
        return true;
    };
    vis.insert(s);
    queue<string> q;
    bool l=0;
    q.push(s);
    while(q.size()){
        string r = q.front(); q.pop();
        if(check(r)){
            cout<<r<< endl;
            l=1;
        }
        if(l) continue;
        for(int i=0;i<s.length();i++){
            string t = s.substr(0,i)+s.substr(i+1);
            if(vis.find(t)==vis.end()){
                q.push(t);
                vis.insert(t);
            }
        }
    }
}

int wordBreakUtil(unordered_set<string> st,string ques, string ans ){
    if(ques.length()==0){
        cout<<ans<<endl;
        return 1;
    }
    int ct=0;
    for(int i=1;i<=ques.size();i++){
        string prefix = ques.substr(0,i);
        if(st.count(prefix)==1){
            ct += wordBreakUtil(st, ques.substr(i),ans+" "+prefix);
        }
    }
    return ct;
}
void wordBreak(vector<string> str, string q){
    unordered_set<string> st(str.begin(), str.end());
    cout<<wordBreakUtil(st,q,"")<<endl;
}

bool checkPalindrome(string s){
    int l=0,r=s.size() - 1;
    while(l<r){
        if(s[l]!=s[r]) return false;
        l++;r--;
    }
    return true;
}
int allPalindromePartition(string q, string a){
    if(q.size()==0){
        cout<<a<<endl;
        return 1;
    }
    int c=0;
    for(int i=0;i<q.length();i++){
        string p = q.substr(0,i+1);
        if(checkPalindrome(p)){
            c +=allPalindromePartition(q.substr(i+1),a+"("+p+")");
        }
    }
    return c;
}

void findShortestPathToLandmines(vector<vector<int>>& mat, int i, int j, int& mind, int dist){
    if(i<0||j<0||i>=mat.size() || j>=mat[0].size() || mat[i][j]!=1) return;
    if(j==mat[0].size()-1){
        mind = min(mind, dist); 
        return;
    }   
    if(mind<dist) return;
    mat[i][j]=0;
    findShortestPathToLandmines(mat,i+1,j,mind, dist+1);
    findShortestPathToLandmines(mat,i,j+1,mind, dist+1);
    findShortestPathToLandmines(mat,i-1,j,mind, dist+1);
    findShortestPathToLandmines(mat,i,j-1,mind, dist+1);
    mat[i][j]=1;
}
void shortestSafePathInLandmines(vector<vector<int>>& mat){
    auto check=[mat](int i, int j){
        return (i>=0 &&j>=0&&i<mat.size()&& j<mat[0].size());
    };
    for(int i=0;i<mat.size();i++){
        for(int j=0;j<mat[0].size();j++){
            if(!mat[i][j]){
                if(check(i+1,j)) mat[i+1][j]=-1;
                if(check(i,j+1)) mat[i][j+1]=-1;
                if(check(i,j-1)) mat[i][j-1]=-1;
                if(check(i-1,j)) mat[i-1][j]=-1;
            }
        }
    }
    for(int i=0;i<mat.size();i++){
        for(int j=0;j<mat[0].size();j++){
            if(mat[i][j]==-1){
                mat[i][j]=0;
            }
        }
    }
    int fdist=INT_MAX;
    for(int i=0;i<mat.size();i++){
        if(mat[i][0]==1){
            int mind=INT_MAX;
            findShortestPathToLandmines(mat,i,0,mind,0);
            fdist=min(fdist,mind);
        }
    }
    cout<<fdist<<endl;
}

int shortestPathInGridWithObstacleElimination(vector<vector<int>>& mat, int k){
    vector<vector<int>> vis(mat.size(),vector<int>(mat[0].size(),-1));
    queue<vector<int>>q;
    q.push({0,0,k});
    int ans=0;
    while(!q.empty()){
        int sz=q.size();
        for(int i=0;i<sz;i++){
            vector<int> rem = q.front(); 
            q.pop();
            int r=rem[0],c=rem[1],kv=rem[2];
            if(c>=mat[0].size()||r>=mat.size()||c<0||r<0 || kv<=vis[r][c]) continue;
            if(c==mat[0].size()-1 && r==mat.size()-1) return ans;
            kv -= mat[r][c];
            vis[r][c]=kv;
            q.push({r-1,c,kv});
            q.push({r+1,c,kv});
            q.push({r,c-1,kv});
            q.push({r,c+1,kv});
        }
        ans++;
    }
    return -1;
}

int combinationalSum(vector<int>& arr,vector<int> temp, int tar, int idx){
    if(tar==0){
        for(int i : temp) cout<<i<<" ";
        cout<<endl;
        return 1;
    }
    if(tar<0) return 0;
    int c=0;
    for(int k=idx;k<arr.size();k++){
        temp.push_back(arr[k]);
        c += combinationalSum(arr,temp,tar-arr[k],k);
        temp.pop_back();
    }
    return c;
}

int partitionKSubsetsEqualSum(vector<int>& arr, int idx, vector<vector<int>>& temp,vector<int>& ssum, int psf, int k){
    if(idx == arr.size()){
        if(psf == k){
           bool f=0;
           for(int i=0;i<ssum.size()-1;i++){
               if(ssum[i]!=ssum[i+1]) {f=1;break;}
           }
           if(!f){
                for(vector<int> t : temp){
                    for(int i : t) cout<<i<<" ";
                    cout<<endl;
                }
                return 1;
           }else return 0;
        }
        return 0;
    }
    int c=0;
    for(int i=0;i<temp.size();i++){
        if(temp[i].size()>0){
            temp[i].push_back(arr[idx]);
            ssum[i] += arr[idx];
            c += partitionKSubsetsEqualSum(arr,idx+1, temp,ssum,psf,k);
            temp[i].pop_back();
            ssum[i] -= arr[idx];
        }else{
            temp[i].push_back(arr[idx]);
            ssum[i] += arr[idx];
            c += partitionKSubsetsEqualSum(arr,idx+1, temp,ssum,psf+1,k);
            temp[i].pop_back();
            ssum[i] -= arr[idx];
            break;
        }
    }
    return c;
}

pair<bool,int> longestPathInHurdles(vector<vector<int>>& mat, int i, int j, int dx, int dy){
    if(i==dx && j==dy){
        return {true,0};
    }
    if(i<0||j<0||i>=mat.size()||j>=mat[0].size()||mat[i][j]!=1) return {false,INT_MAX};
    mat[i][j]=2;
    int res = INT_MIN;
    pair<bool,int> sol  = longestPathInHurdles(mat,i+1,j,dx,dy);
    if(sol.first) res = max(res, sol.second);
    sol  = longestPathInHurdles(mat,i-1,j,dx,dy);
    if(sol.first) res = max(res, sol.second);
    sol  = longestPathInHurdles(mat,i,j+1,dx,dy);
    if(sol.first) res = max(res, sol.second);
    sol  = longestPathInHurdles(mat,i,j-1,dx,dy);
    if(sol.first) res = max(res, sol.second);
    // mat[i][j]=1;
    if(res != INT_MIN){
        return {true,res+1};
    }else return {false,INT_MAX};
}

void patternMatchesString(string str, string pat, map<char,string>& m, string opat){
    if(pat.length()==0){
        if(str.length()==0){
            set<char> st;
            for(char c : opat){
                if(st.find(c)==st.end()){
                    cout<<c<<" -> "<< m[c]<<", "<<endl;
                    st.insert(c);
                }
            }
        }
        return;
    }
    char c = pat[0];
    string rop = pat.substr(1);
    if(m.find(c)!=m.end()){
        string prev = m[c];
        if(str.length()>=prev.length()){
            string l = str.substr(0,prev.length());
            string r = str.substr(prev.length());
            if(prev == l) patternMatchesString(r,rop,m,opat); 
        }
    }else{
        for(int i=0;i<str.length();i++){
            string l = str.substr(0,i+1);
            string r = str.substr(i+1);
            m[c] = l;
            patternMatchesString(r,rop,m,opat);
            m.erase(c);
        }
    }
}

vector<int> fs1,fs2;
void tugOfWar(vector<int>& arr, int idx, int s1, int s2, vector<int>& set1, vector<int>& set2, int& mind){
    if(idx == arr.size()){
        if(mind > (int)abs(s1-s2)){
            mind=(int)abs(s1-s2);
            fs1=set1; fs2=set2;
        }
        return;
    }
    if(set1.size()<(arr.size()+1)/2){
        set1.push_back(arr[idx]);
        tugOfWar(arr,idx+1,s1+arr[idx],s2,set1,set2,mind);
        set1.pop_back();
    }

    if(set2.size()<(arr.size()+1)/2){
        set2.push_back(arr[idx]);
        tugOfWar(arr,idx+1,s1,s2+arr[idx],set1,set2,mind);
        set2.pop_back();
    }
}

void maxNumberWithKSwaps(string s, int k, int& mx){
    if(stoi(s)>mx){
        mx = stoi(s);
    }
    if(!k) return;

    for(int i=0;i<s.length();i++){
        for(int j=i+1;j<s.length();j++){
            char t = s[i];
            s[i]=s[j];
            s[j]=t;
            maxNumberWithKSwaps(s,k-1,mx);
            char x = s[i];
            s[i]=s[j];
            s[j]=x;
        }
    }
}

bool findPathWithMoreThanK(vector<vector<pair<int,int>>>& graph, int src, int k,vector<bool>& vis, string& path){
    if(k<=0) return true;
    for(auto x : graph[src]){
        if(vis[x.first]==true) continue;

        if(x.second>=k) {path.push_back((char)(x.first+'0')); return true;}

        vis[x.first]=1;
        path.push_back((char)(x.first+'0'));
        if(findPathWithMoreThanK(graph,x.first,k-x.second,vis,path)) return true;
        vis[x.first]=0;
        path.pop_back();
    }
    return false;
}

void printPathfromCornerToMiddleInMaze(vector<vector<int>>& maze, int i, int j, string path){
    if(i==maze.size()/2 && j==maze[0].size()/2){
        path +=  "("+to_string(i)+","+to_string(j)+")-> MID";
        cout<<path<<endl;
        return;
    }
    if(!maze[i][j]) return;
    int k = maze[i][j];
    maze[i][j]=0;
    if(j+k<maze[0].size()) printPathfromCornerToMiddleInMaze(maze,i,j+k,path+"("+to_string(i)+","+to_string(j+k)+")->");
    if(i+k<maze.size()) printPathfromCornerToMiddleInMaze(maze,i+k,j,path+"("+to_string(i+k)+","+to_string(j)+")->");
    if(j-k>=0) printPathfromCornerToMiddleInMaze(maze,i,j-k,path+"("+to_string(i)+","+to_string(j-k)+")->");
    if(i-k>=0) printPathfromCornerToMiddleInMaze(maze,i-k,j,path+"("+to_string(i-k)+","+to_string(j)+")->");
    maze[i][j]=k;
}

int main(){
    // vector<vector<int>> chess(5, vector<int>(5,0));
    // knightTour(chess, 1,3,1);

    // vector<vector<int>> maze{{1, 0, 0, 0},
    //                         {1, 1, 0, 1},
    //                         {0, 1, 0, 0},
    //                         {1, 1, 1, 1}
    //                         };
    // cout<<ratInMaze(maze,0,0)<<endl;
    // removeInvalidParanthesis("()())()");
    // vector<string> str{"mobile","samsung","sam","sung", "man","mango", "icecream","and", "go","i","love","ice","cream"};
    // wordBreak(str,"iloveicecreamandmango");   
    // cout<<allPalindromePartition("pep","")<<endl;
    // vector<vector<int>> mat{
    //     { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    //     { 1, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
    //     { 1, 1, 1, 0, 1, 1, 1, 1, 1, 1 },
    //     { 1, 1, 1, 1, 0, 1, 1, 1, 1, 1 },
    //     { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    //     { 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 },
    //     { 1, 0, 1, 1, 1, 1, 1, 1, 0, 1 },
    //     { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    //     { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    //     { 0, 1, 1, 1, 1, 0, 1, 1, 1, 1 },
    //     { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    //     { 1, 1, 1, 0, 1, 1, 1, 1, 1, 1 }
    // };
    // shortestSafePathInLandmines(mat);
    // vector<vector<int>> grid{{0,0,0},
    //                         {1,1,0},
    //                         {0,0,0},
    //                         {0,1,1},
    //                         {0,0,0}};
    // cout<<shortestPathInGridWithObstacleElimination(grid,1)<<endl;
    // vector<int> pr{2,4,6,8};
    // cout<<combinationalSum(pr,{},8,0)<<endl;
    // vector<int> arr{2, 1, 4, 5, 6};
    // vector<int> ssum(3,0);
    // vector<vector<int>>temp(3);
    // cout<<partitionKSubsetsEqualSum(arr, 0, temp, ssum,0, 3)<<endl;
    // vector<vector<int>> hurdles { { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
    //                             { 1, 1, 0, 1, 1, 0, 1, 1, 0, 1 }, 
    //                             { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } };
    // cout<<longestPathInHurdles(hurdles,0,0,1,7).second<<endl;

    // vector<int> tgarr{1,2,3,4,5,6};
    // vector<int> set1,set2;
    // int mind=INT_MAX;
    // tugOfWar(tgarr,0,0,0,set1,set2,mind);
    // cout<<mind<<endl;
    // for(int i : fs1) cout<<i<<" ";
    // cout<<endl;
    // for(int i : fs2) cout<<i<<" ";
    // cout<<endl;
    // int mx =INT_MIN;
    // maxNumberWithKSwaps("7599",2,mx);
    // cout<<mx<<endl;
    
    // map<char,string> m;
    // patternMatchesString("GeeksforGeeksforGeeks","GFGFG",m,"GFGFG");
    // for(auto x : m) cout<<x.first<<" "<<x.second<<endl;

    // vector<vector<pair<int,int>>> graph(9);
    // graph[0].push_back({1,4});
    // graph[0].push_back({7,8});
    // graph[1].push_back({0,4});
    // graph[1].push_back({2,8});
    // graph[1].push_back({7,11});
    // graph[2].push_back({8,2});
    // graph[2].push_back({3,7});
    // graph[2].push_back({5,4});  
    // graph[2].push_back({1,8});
    // graph[3].push_back({5,14});
    // graph[3].push_back({4,9});  
    // graph[3].push_back({2,7});
    // graph[4].push_back({5,10});  
    // graph[4].push_back({3,9});
    // graph[5].push_back({4,10});
    // graph[5].push_back({3,4});
    // graph[5].push_back({2,4});
    // graph[5].push_back({6,2});
    // graph[6].push_back({5,2});
    // graph[6].push_back({8,6});
    // graph[6].push_back({8,6});
    // graph[7].push_back({8,7});  
    // graph[7].push_back({1,11});  
    // graph[7].push_back({8,7});  
    // graph[7].push_back({8,7});  
    // graph[8].push_back({2,2});  
    // graph[8].push_back({6,6});  
    // graph[8].push_back({7,7});  
    // vector<bool>vis(9,false);
    // vis[0]=1;
    // string pat;
    // pat += "0";
    // cout<<findPathWithMoreThanK(graph,0,50,vis,pat)<<endl;
    // cout<<pat<<endl;

    vector<vector<int>> maze{{ 3, 5, 4, 4, 7, 3, 4, 6, 3 },
                            { 6, 7, 5, 6, 6, 2, 6, 6, 2 },
                            { 3, 3, 4, 3, 2, 5, 4, 7, 2 },
                            { 6, 5, 5, 1, 2, 3, 6, 5, 6 },
                            { 3, 3, 4, 3, 0, 1, 4, 3, 4 },
                            { 3, 5, 4, 3, 2, 2, 3, 3, 5 },
                            { 3, 5, 4, 3, 2, 6, 4, 4, 3 },
                            { 3, 5, 1, 3, 7, 5, 3, 6, 4 },
                            { 6, 2, 4, 3, 4, 5, 4, 5, 1 }
                        };
    printPathfromCornerToMiddleInMaze(maze,0,0,"");
}