#include <bits/stdc++.h>
#include "src.hpp"
using namespace std;

string get_data () {
    string ret = "" , line;
    string linebuf;
    getline(cin, linebuf); // consume endline after previous read if any
    while (getline(cin , line)) {
        if (line.length() == 0) continue;
        if (line == "#####") break;
        ret += line + "\n";
    }
    return ret;
}

int main(){
    {
        // ICPC sample
        string input = "ICPCJudger\n1000 1000\nabcd\ndcba\n#####\n500 1001\nabcd\ndcba\n#####\n500 500\nabcd\ndcba\n#####\n";
        istringstream iss(input);
        cin.rdbuf(iss.rdbuf());
        char judger_name[100];
        cin >> judger_name; size_t tl, ml; cin >> tl >> ml; string tmp; BaseJudger* j=nullptr; tmp=get_data(); j=new ICPCJudger(tl,ml,tmp.c_str()); size_t t,m; while (cin>>t>>m){ tmp=get_data(); j->Submit(t,m,tmp.c_str()); }
        cout << j->GetScore() << "\n"; delete j;
    }
    {
        // OIJudger trim trailing spaces per line
        string input = "OIJudger\n100 100\na b  \nc  \n#####\n50 50\na b\nc\n#####\n";
        istringstream iss(input);
        cin.rdbuf(iss.rdbuf());
        char judger_name[100]; cin>>judger_name; size_t tl,ml; cin>>tl>>ml; string tmp; BaseJudger* j=nullptr; tmp=get_data(); j=new OIJudger(tl,ml,tmp.c_str()); size_t t,m; while (cin>>t>>m){ tmp=get_data(); j->Submit(t,m,tmp.c_str()); }
        cout << j->GetScore() << "\n"; delete j;
    }
    {
        // SpacialJudger linear scoring
        string input = "SpacialJudger\n100 200\n50 100\nans\n#####\n75 150\nans\n#####\n";
        istringstream iss(input);
        cin.rdbuf(iss.rdbuf());
        char judger_name[100]; cin>>judger_name; size_t tl,ml; cin>>tl>>ml; size_t fst,fsm; cin>>fst>>fsm; string tmp; BaseJudger* j=nullptr; tmp=get_data(); j=new SpacialJudger(tl,ml,fst,fsm,tmp.c_str()); size_t t,m; while (cin>>t>>m){ tmp=get_data(); j->Submit(t,m,tmp.c_str()); }
        cout << j->GetScore() << "\n"; delete j;
    }
}
