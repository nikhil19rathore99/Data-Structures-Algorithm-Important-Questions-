#include<bits/stdc++.h>
using namespace std;
int main(){
    string s = "baa";
    map<char,int> m;
    map<int,vector<int>> mid;
    for(int i=0;i<s.length();i++) {
        m[s[i]]++;
        mid[s[i]].push_back(i);
    }
    int co=0;
    list<int> ans;
    vector<bool> vis(s.length(),false);
    for(auto x: m){
        if(x.second&1) co++;
    }
    if(co>1) cout<<"-1"<<endl;
    else{
        for(auto x : m){
            if(x.second%2==0){
                bool f=0;
                for(auto y : mid[x.first]){
                    if(!f) ans.push_front(y);
                    else ans.push_back(y);
                    vis[y]=true;
                }
            }else{
                bool f=0;
                for(auto y : mid[x.first]){
                    if(!f) ans.push_front(y);
                    else ans.push_back(y);
                    vis[y]=1;
                }
            }
        }
        int midid=-1;
        for(auto x : m){
            bool t=0;
            for(auto y : mid[x.first]){
                if(!vis[y]){midid=y; t=1; break;}
            }
            if(t) break;
        }
        for(int i : ans){
            cout<<i<<" ";
        }
    }
}