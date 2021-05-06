#include<bits/stdc++.h>
#include<windows.h>
#define width 4

using namespace std;
string board;
vector<string> boards = {"0000001101100100","0111001010111000","1011111001111011","1010001110001101","1111000101110000"}; // 自动初始化板块库
set<string> bovis;
// 颜色模块
void color(const unsigned short color1)
{
    if(color1>=0&&color1<=15)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color1);
        /*如果不在0-15的范围颜色，那么改为默认的颜色白色；*/
    else
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
// 输出模块
bool print() {
    bool flag = false;
    cout << endl;
    int dic;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < width; ++j) {
            color(1);
            dic = i * width + j;
            if ((board[dic]) == '1') {
                flag = true;
                cout << "[  ";
                color(4);
                cout<< "*" ;
                color(1);
                cout << "  ]" ;
            }else {
                cout << "[     ]";
            }
            color(16);
        }
        cout << endl;
        for (int j = 0; j < width; ++j) {
            int num = i * width + j + 1;
            if (num < 10) {
                cout << "   " << num << "   ";
            }else {
                cout << "   " << num << "  ";
            }
        }
        cout << endl;
        cout << endl;
        cout << endl;
    }
    cout << endl;
    return flag;
}


// 自动打地鼠模块
int dx[5] = {0,-1,0,1,0};
int dy[5] = {0,0,1,0,-1};
void turn(int dic) {
    int x = dic / width;
    int y = dic % width;
    for (int i = 0; i < 5; ++i) {
        int a = x + dx[i];
        int b = y + dy[i];
        int dic = a * width + b;
        if (a >= 0 && a < width && b >= 0 && b < width) {
            if (board[dic] == '1') board[dic] = '0';
            else board[dic] = '1';
        }
    }
}

map<string,pair<string,int >> track;
vector<int> ret;
void work() {

    queue<pair<string,int>> q; // 对应状态 对应操作
    set<string> vis; // 记录访问过的状态
    for (int i = 0; i < 1 << width; ++i) {
        if (board[i] == '1' ) q.push(make_pair(board,i));
    }
    string start = board;
    string end;
    for (int i = 0; i < 1 << width; ++i) end += "0";
    while (!q.empty()) {
        pair<string,int> cur = q.front();
        q.pop();
        board = cur.first;
        turn(cur.second);

        if (vis.count(board)) continue;
        vis.insert(board);

        track[board] = {cur.first,cur.second};
        if (board == end) break;
        for (int i = 0; i < 1 << width; ++i) {
            if (board[i] == '1') q.push(make_pair(board,i));
        }

    }
    if (board == end)
        while (board != start) {
            ret.push_back(track[board].second);
            board = track[board].first;
            if (boards.size() < 1000 && bovis.count(board)) {
                boards.push_back(board);
                bovis.insert(board);
            }
            
        }
    reverse(ret.begin(),ret.end());

}

void aiplayer() {
    work();
    for (int i = 0; i < (int)ret.size(); ++i) {
        cout << "打 " << ret[i] + 1 << " 上的地鼠后:" << endl;
        int t = ret[i];
        turn(t);
        print();
    }
    if (ret.size() == 0) cout << "无解" << endl;
    ret.clear();

}

// 手动打地鼠模块
void player() {
    bool flag = true;
    int tot = 0;
    while (flag) {
        int dic;
        cout << "请输入击打地鼠序号(0为弃权)" << endl;
        cin >> dic;
        if(dic == 0) {
            cout << "AI 操作如下" << endl;
            aiplayer();
            break;
        }
        else if (dic > 0 && dic <= 16) {
            --dic;
            turn(dic);
            cout << "打 " << dic + 1 << " 上的地鼠后: " << endl;
            cout << endl;
            flag = print();
            ++tot;
        }else {
            cout << "输入不合法，请重新输入" << endl;
        }
    }
    cout << "游戏结束" << endl;
}



// 初始化模块
void init(int dic) {
    board[dic] = '1';
}
int RangedRandDemo( int range_min, int range_max)
{

    int u = (double)rand() / (RAND_MAX + 1) *(range_max - range_min) // RAND_MAX = 32767
            + range_min;
    return u;

}
void autoinit() {
    int n = RangedRandDemo(0,boards.size());
    board = boards[n];
}
void playerinit() {
    int n,t;
    cout << "请输入有多少只地鼠？" << endl;
    cin >> n;
    cout << endl;
    cout << "输入地鼠分布" << endl;
    while (n --) {
        cin >> t;
        --t;
        init(t);
    }
}

// 游戏主体
void game() {
    int f;
    cout << "1.手动初始化地鼠分布图" << endl;
    cout << "2.自动初始化地鼠分布图" << endl;
    cout << "请输入对应序号" << endl;
    cin >> f;
    if (f == 1) {
        playerinit();
    }else if (f == 2){
        autoinit();
    }else{
        cout << "输入有误，已为你自动初始化" << endl;
        autoinit();
    }
    cout << "初始化成功，地鼠分布图" << endl;
    print();

    cout << "1.自动打地鼠" << endl;
    cout << "2.手动打地鼠" << endl;
    cout << "3.退出游戏" << endl;
    cout << "请输入对应序号" << endl;
    cout << endl;
    cin >> f;
    if (f == 1) {
        aiplayer();
    }
    else if (f == 2) {
        player();
    }
}

int main() {


    int f;
    while (true) {
        board = "";
        for (int i = 0; i < width * width; ++i) {
            board += "0";
        }
        cout << "1.开始游戏" << endl;
        cout << "2.退出游戏" << endl;
        cout << "请输入对应序号" << endl;
        cin >> f;
        cout << endl;
        if (f == 1) {
            game();
        }
        else {
            break;
        }
    }
    
}
