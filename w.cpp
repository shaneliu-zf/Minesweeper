#include<iostream>
#include<vector>
#include<cstdlib>

#define N 9
#define M 9
#define MAX_COUNT 9
using namespace std;


vector<vector<int> >v;
vector<vector<bool> >boom;
vector<vector<int> >ma;

int mark = 0;

void init(){
    v.resize(N+2);
    boom.resize(N+2);
    ma.resize(N+2);

    for(int i=0;i<=N+1;i++){
        v[i].resize(M+2);
        boom[i].resize(M+2);
        ma[i].resize(M+2);
        for(int j=0;j<=M+1;j++){
            if(i==0 || i==N+1 || j==0 ||j==M+1)boom[i][j] = 0;
            else{
                ma[i][j] = -1;
                boom[i][j] = 0;
             }
        }
    }

    for(int i=0;i<MAX_COUNT;i++){
        int x = (rand()%9)+1;
        int y = (rand()%9)+1;
        while(boom[x][y]==1){
            x = (rand()%9)+1;
            y = (rand()%9)+1;
        }
        boom[x][y] = 1;
    }


    for(int i=1;i<=N;i++){
        for(int j=1;j<=M;j++){
            v[i][j] = boom[i+1][j]+boom[i-1][j]+boom[i][j-1]+boom[i][j+1]
            +boom[i+1][j+1]+boom[i-1][j-1]+boom[i+1][j-1]+boom[i-1][j+1];
        }
    }
}
void dfs(int i,int j){
    if(i==0 || i==N+1 || j==0 ||j==M+1)return;
    if(ma[i][j]!=-1)return;
    ma[i][j] = v[i][j];
    if(v[i][j]==0){
        dfs(i+1,j);
        dfs(i,j+1);
        dfs(i-1,j);
        dfs(i,j-1);
        dfs(i+1,j+1);
        dfs(i+1,j-1);
        dfs(i-1,j+1);
        dfs(i-1,j-1);
    }
}


void printMap(){
    cout<<" |1|2|3|4|5|6|7|8|9|\n";
    for(int i=1;i<=N;i++){
        cout<<i<<"|";
        for(int j=1;j<=M;j++){
            if(ma[i][j]==0)cout<<" ";
            else if(ma[i][j]==-1)cout<<"▦";
            else if(ma[i][j]==-2)cout<<"\033[1;31mx\033[1;0m";
            else cout<<ma[i][j];
            cout<<"|";
        }
        cout<<endl;
    }
}

bool loops(){
    system("clear");
    printMap();
    int x,y;
    int mode;
    cout<<endl;
    cout<<"mode 1:touch it"<<endl;
    cout<<"mode 2:mark it"<<endl;
    cout<<"mode 3:peek"<<endl;
    cout<<"input mode:";
    cin>>mode;
    while(!(mode==1 || mode==2 || mode==3)){
        cout<<"bad input,please re-input mode:";
        cin>>mode;
    }
    if(mode==3){
        for(int i=1;i<=N;i++){
            for(int j=1;j<=M;j++){
                if(v[i][j]==-1)cout<<"x";
                else if(v[i][j]==-2)cout<<"y";
                else cout<<v[i][j];
                cout<<" \n"[j==M];
            }
        }
        system("read");
        return 1;
    }

    cout<<"input x y:";
    cin>>x>>y;
    while(x==0 || x==N+1 || y==0 ||y==M+1){
        cout<<"bad input,please re-input x y:";
        cin>>x>>y;
    }

    if(mode == 1){
        if(boom[x][y]){
            cout<<"you lose!"<<endl;
            return 0;
        }
        dfs(x,y);
        if(ma[x][y]!=-1 && ma[x][y]!=-2){
            int c = 0;
            if(ma[x-1][y]==-2)c++;
            if(ma[x][y-1]==-2)c++;
            if(ma[x+1][y]==-2)c++;
            if(ma[x][y+1]==-2)c++;
            if(ma[x-1][y-1]==-2)c++;
            if(ma[x-1][y+1]==-2)c++;
            if(ma[x+1][y-1]==-2)c++;
            if(ma[x+1][y+1]==-2)c++;
            if(c==ma[x][y]){
                if(ma[x-1][y]!=-2)ma[x-1][y] = v[x-1][y];
                if(ma[x][y-1]!=-2)ma[x][y-1] = v[x][y-1];
                if(ma[x+1][y]!=-2)ma[x+1][y] = v[x+1][y];
                if(ma[x][y+1]!=-2)ma[x][y+1] = v[x][y+1];
                if(ma[x-1][y-1]!=-2)ma[x-1][y-1] = v[x-1][y-1];
                if(ma[x-1][y+1]!=-2)ma[x-1][y+1] = v[x-1][y+1];
                if(ma[x+1][y-1]!=-2)ma[x+1][y-1] = v[x+1][y-1];
                if(ma[x+1][y+1]!=-2)ma[x+1][y+1] = v[x+1][y+1];
            }

        }
    }
    else if(mode == 2){
        if(!boom[x][y]){
            cout<<"you lose!"<<endl;
            return 0;
        }
        ma[x][y] = -2;
        mark++;
        if(mark==MAX_COUNT){
            cout<<"you win!"<<endl;
            return 0;
        }
    }
    else{
        cout<<"bad input"<<endl;
        return 0;
    }
    return 1;
}


int main(){
    srand(time(NULL));
    init();
    while(loops());
    return 0;
}
