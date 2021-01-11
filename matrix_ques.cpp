#include<bits/stdc++.h>
#define debug(T) cout<<"debug : "<<T<<endl;
using namespace std;
void daigonalTraversal(vector<vector<int>>& mat){
    for(int i=0;i<mat.size();i++){
        for(int r=i,c=0;r>=0 && c<mat[0].size();r--,c++){
            cout<<mat[r][c]<<" ";
        }
        cout<<endl;
    }
    for(int i=1;i<mat[0].size();i++){
        int r=mat.size()-1;
        int c=i;
        while(r>=0&&c<mat[0].size()){
            cout<<mat[r--][c++]<<" ";
        }
        cout<<endl;
    }
}
void buildMatrixwithAlternatingOX(int n, int m){
    int minr=0,minc=0,maxr=n-1,maxc=m-1;
    vector<vector<int>> mat(n,vector<int>(m));
    int tc = n*m;
    int cnt=0;
    bool f=0;
    while(cnt<tc){
       if(!f){
            for(int i=minc;i<=maxc;i++){
                mat[minr][i]=1; cnt++;
            }
            minr++;
            for(int i=minr;i<=maxr;i++){
                mat[i][maxc]=1; cnt++;
            }
            maxc--;
            for(int i=maxc;i>=minc;i--){
                mat[maxr][i]=1; cnt++;
            }
            maxr--;
            for(int i=maxr;i>=minr;i--){
                mat[i][minc]=1; cnt++;
            }
            minc++;
       }else{
            for(int i=minc;i<=maxc;i++){
                mat[minr][i]=0; cnt++;
            }
            minr++;
            for(int i=minr;i<=maxr;i++){
                mat[i][maxc]=0; cnt++;
            }
            maxc--;
            for(int i=maxc;i>=minc;i--){
                mat[maxr][i]=0; cnt++;
            }
            maxr--;
            for(int i=maxr;i>=minr;i--){
                mat[i][minc]=0; cnt++;
            }
            minc++;
       }
       f=!f;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) cout<<mat[i][j]<<" ";
        cout<<endl;
    }
}
#define pr pair<int,pair<int,int>> 
void printSortedMatrixRowColWise(vector<vector<int>>& mat){
    int r=0,c=0;
    auto cmp = [](pr x, pr y){
        return x.first>y.first;
    };
    priority_queue<pr, vector<pr>, decltype(cmp)> pq(cmp);
    pq.push({mat[r][c],{r,c}});
    vector<vector<bool>> vis(mat.size(),vector<bool>(mat[0].size(),false));
    while(!pq.empty()){
        pr rem= pq.top();
        pq.pop();
        int nr = rem.second.first, nc = rem.second.second;
        if(!vis[nr][nc]) cout<<rem.first<<" ";
        else continue;
        vis[nr][nc]=1;
        if(nr+1<mat.size()){
            pq.push({mat[nr+1][nc],{nr+1,nc}});
        }
        if(nc+1<mat[0].size()){
            pq.push({mat[nr][nc+1],{nr,nc+1}});
        }
    }
}
void done(vector<vector<int>>& mat, int i, int j){
    if(i<0||j<0||i>=mat.size()||j>=mat[0].size()||!mat[i][j]) return;
    mat[i][j]=0;
    done(mat,i+1,j);
    done(mat,i-1,j);
    done(mat,i,j+1);
    done(mat,i+1,j-1);
}
int findNoOfIsland(vector<vector<int>>& mat){
    int n=0;
    for(int i=0;i<mat.size();i++){
        for(int j=0;j<mat[0].size();j++){
            if(mat[i][j]){
                done(mat,i,j);
                n++;
            }
        }
    }
    return n;
}
void done(vector<vector<char>>& mat, int i, int j, char prev, char newchar){
    if(i<0||j<0||i>=mat.size() || j>=mat[0].size()||mat[i][j]!=prev) return;
    mat[i][j]=newchar;
    done(mat,i+1,j,prev,newchar);
    done(mat,i-1,j,prev,newchar);
    done(mat,i,j+1,prev,newchar);
    done(mat,i,j-1,prev,newchar);
}
void replaceOwithXSurroundsX(vector<vector<char>>& mat){
    for(vector<char>& a: mat){
        for(char &c: a) if(c=='O') c='-';
    }
    for(int i=0;i<mat.size();i++) {if(mat[i][0]=='-') done(mat,i,0,'-','O');}
    for(int i=0;i<mat.size();i++) {if(mat[i][mat[0].size()-1]=='-') done(mat,i,mat[0].size()-1,'-','O');}
    for(int i=0;i<mat[0].size();i++) {if(mat[0][i]=='-') done(mat,0,i,'-','O');}
    for(int i=0;i<mat[0].size();i++) {if(mat[mat.size()-1][0]=='-') done(mat,mat.size()-1,0,'-','O');}
    for(vector<char>& a: mat){
        for(char &c: a){ 
            if(c=='-'){ 
                c='X';
            }
            cout<<c<<" ";
        }
        cout<<endl;
    }
}
void kthSmallestInMatrix(vector<vector<int>>& mat,int k){
    auto cmp = [](pr x, pr y){
        return x.first>y.first;
    };
    priority_queue<pr,vector<pr>, decltype(cmp)> pq(cmp);
    pq.push({mat[0][0],{0,0}});
    int ct=0;
    vector<vector<bool>> vis(mat.size(), vector<bool>(mat[0].size(),false));
    while(!pq.empty()){
        pr rem = pq.top();
        pq.pop();
        int r = rem.second.first,c=rem.second.second;
        if(vis[r][c]) continue;
        ct++;
        if(ct==k) {cout<<rem.first<<endl; break;}
        vis[r][c]=1;
        if(r+1<mat.size()){
            pq.push({mat[r+1][c],{r+1,c}});
        }
        if(c+1<mat[0].size()){
            pq.push({mat[r][c+1],{r,c+1}});
        }
    }
}
int maximumSizeRectangleBinarySubMatrix(vector<vector<int>>& mat){
    auto maxAreaUnderHistogram = [](vector<int>& arr){
        stack<int> st;
        vector<int> lb(arr.size()),rb(arr.size());
        lb[0]=-1;
        rb[arr.size()-1]= arr.size();
        st.push(0);
        for(int i=1;i<arr.size();i++){
            while(st.size() && arr[st.top()]>arr[i]){
                st.pop();
            }
            lb[i] = st.size() ? st.top() : -1;
            st.push(i);
        }
        while(st.size()) st.pop();
        st.push(arr.size());
        for(int i=arr.size()-2;i>=0;i--){
            while(st.size() && arr[st.top()]>arr[i]){
                st.pop();
            }
            rb[i] = st.size() ? st.top() : arr.size();
            st.push(i);
        }
        int mx = 0;
        for(int i=0;i<arr.size();i++) mx=max(mx, arr[i]*(rb[i]-lb[i]-1));
        return mx;
    };
    vector<int> temp(mat[0].begin(), mat[0].end());
    int mx = maxAreaUnderHistogram(temp);
    for(int i=1;i<mat.size();i++){
        for(int j=0;j<mat[0].size();j++){
            temp[j] = !mat[i][j] ? 0 : temp[j]+mat[i][j];
        }
        int curr = maxAreaUnderHistogram(temp);
        if(curr>mx){
            mx=curr;
        }
    }
    return mx;
}
void shortestPathInAMaze(vector<vector<int>>& maze,int sr,int sc, int dr, int dc){
    queue<pair<pair<int,int>,string> > q;
    q.push({{sr,sc},to_string(sr)+to_string(sc)+"->"});
    vector<vector<bool>> vis(maze.size(),vector<bool>(maze[0].size(),false));
    while(q.size()){
        pair<pair<int,int>,string> rem = q.front();
        q.pop();
        if(rem.first.first==dr && rem.first.second==dc){
            cout<<rem.second<<endl;
            break;
        }
        if(vis[rem.first.first][rem.first.second]) continue;
        
        int r=rem.first.first,c=rem.first.second;
        vis[r][c]=1;
        if(r+1<maze.size() && maze[r+1][c]==1) q.push({{r+1,c},rem.second+to_string(r+1)+to_string(c)+"->"});
        if(c+1<maze[0].size() && maze[r][c+1]==1) q.push({{r,c+1},rem.second+to_string(r)+to_string(c+1)+"->"});
        if(r-1>=0 && maze[r-1][c]==1) q.push({{r-1,c},rem.second+to_string(r-1)+to_string(c)+"->"});
        if(c-1>=0 && maze[r][c-1]==1) q.push({{r,c-1},rem.second+to_string(r)+to_string(c-1)+"->"});   
    } 
}
int main(int argc, char** argv){
    // vector<vector<int>> mat{ {10, 20, 30, 40}, 
    //                         {15, 25, 35, 45}, 
    //                         {25, 29, 37, 48}, 
    //                         {32, 33, 39, 50}, 
    //                     }; 
    // daigonalTraversal(mat);
    // buildMatrixwithAlternatingOX(6,7);
    // printSortedMatrixRowColWise(mat);
    // vector<vector<int>> mat{{ 0, 1, 1, 0 },
    //                         { 1, 1, 1, 1 },
    //                         { 1, 1, 1, 1 },
    //                         { 1, 1, 0, 0 }};
    // cout<<findNoOfIsland(mat)<<endl;
    // vector<vector<char>> mat{{'X', 'O', 'X', 'X', 'X', 'X'},
    //                         {'X', 'O', 'X', 'X', 'O', 'X'},
    //                         {'X', 'X', 'X', 'O', 'O', 'X'},
    //                         {'O', 'X', 'X', 'X', 'X', 'X'},
    //                         {'X', 'X', 'X', 'O', 'X', 'O'},
    //                         {'O', 'O', 'X', 'O', 'O', 'O'},
    //                         };
    // replaceOwithXSurroundsX(mat);
    // kthSmallestInMatrix(mat,7); 
    // cout<<maximumSizeRectangleBinarySubMatrix(mat)<<endl;
    vector<vector<int>> maze    {{1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                                {1, 0, 1, 0, 1, 1, 1, 0, 1, 1 },
                                {1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
                                {0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
                                {1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
                                {1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
                                {1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
                                {1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                                {1, 1, 0, 0, 0, 0, 1, 0, 0, 1 }
                                };
    shortestPathInAMaze(maze, 0,0,3,4);

}