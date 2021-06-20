#include<bits/stdc++.h>

using namespace std;

class Student { // 学生类
private:
    string name; // 姓名
    vector<double> score;  // 成绩
    vector<vector<double> > scores;
    string id;    // 学号
    string Class;   // 班级
    vector<int> schoolRank; // 校排名
    vector<int> classRank; // 班排名

public:

    void set_id(string id) {
        this->id = id;
    }

    string get_id() {
        return this->id;
    }

    void set_name(string name) {
        this->name = name;
    }

    string get_name() {
        return name;
    }

    void set_Class(string x) {
        Class = x;
    }

    string get_Class() {
        return Class;
    }

    void set_score(double s) {
        this->score.push_back(s);
    }

    vector<double> get_score() {
        return this->score;
    }

    void set_scores(vector<double> s) {
        scores.push_back(s);
    }

    void set_scores(int a, int b, int c) {
        scores[a - 1][b - 1] = c;
    }


    vector<vector<double> > get_scores() {
        return this->scores;
    }

    void set_classRank(int k) {
        classRank.push_back(k);
    }

    void set_classRank(int idx, int k) {
        this->classRank[idx] = k;
    }

    vector<int> get_classRank() {
        return this->classRank;
    }

    void set_schoolRank(int k) {
        this->schoolRank.push_back(k);
    }

    void set_schoolRank(int idx, int k) {
        this->schoolRank[idx] = k;
    }

    vector<int> get_schoolRank() {
        return this->schoolRank;
    }

};

class Trie { // 以 名字 的 前缀树
private:
    map<string, Trie *> TrieMap;
    set<string> ID;
public:
    // 增加一位名字为 vs 同学的 id
    void insert(vector<string> vs, string id) {
        Trie *cur = this;
        for (int i = 0; i < (int) vs.size(); ++i) {
            if (!cur->TrieMap.count(vs[i])) {
                cur->TrieMap[vs[i]] = new Trie();
            }
            cur = cur->TrieMap[vs[i]];
        }
        cur->ID.insert(id);
    }

    // 删除一位名字为 vs 同学的 id
    void Delete(vector<string> vs, string id) {
        Trie *cur = this;
        for (int i = 0; i < (int) vs.size(); ++i) {
            cur = cur->TrieMap[vs[i]];
        }
        set<string>::iterator it = cur->ID.find(id);
        cur->ID.erase(it);
    }

    // 判断某个前缀是否存在 并找某个前缀
    bool is_exist(vector<string> vs, Trie *&t) {
        Trie *cur = this;
        for (int i = 0; i < (int) vs.size(); ++i) {
            if (!cur->TrieMap.count(vs[i])) return false;
            cur = cur->TrieMap[vs[i]];
        }
        t = cur;
        return true;
    }

    // 提取 汉字字符串 中 每个汉字，并装入顺序容器
    vector<string> names(string name) {
        vector<string> vs;
        for (int i = 0; i < name.size() - 1; i += 2) {
            stringstream ss;
            string t;
            ss << name[i] << name[i + 1];
            ss >> t;
            vs.push_back(t);
        }
        return vs;
    }

    // 查找
    set<string> searchName(vector<string> vs) {
        set<string> total;
        Trie *t;
        if (is_exist(vs, t)) {
            set<string> ans = searchHelp(t);
            for (set<string>::iterator it = ans.begin(); it != ans.end(); ++it) {
                total.insert(*it);
            }
            return total;
        }
        set<string> ss;
        for (int i = 0; i < (int) vs.size(); ++i) {
            ss.insert(vs[i]);
        }
        queue<Trie *> q;
        vector<Trie *> vh;
        q.push(this);
        while (!q.empty()) {
            Trie *cur = q.front();
            q.pop();

            for (map<string, Trie *>::iterator it = cur->TrieMap.begin(); it != cur->TrieMap.end(); ++it) {
                if (ss.count(it->first)) {
                    Trie *t = it->second;
                    vh.push_back(t);
                }
                q.push(it->second);
            }
        }

        for (int i = 0; i < (int) vh.size(); ++i) {
            set<string> t = searchHelp(vh[i]);
            for (set<string>::iterator it = t.begin(); it != t.end(); ++it) {
                total.insert(*it);
            }
        }
        return total;
    }

    set<string> searchHelp(Trie *t) {
        queue<Trie *> q;
        set<string> ans;
        q.push(t);

        while (!q.empty()) {
            Trie *cur = q.front();
            q.pop();
            for (set<string>::iterator it = cur->ID.begin(); it != cur->ID.end(); ++it) {
                ans.insert(*it);
            }

            for (map<string, Trie *>::iterator it = cur->TrieMap.begin(); it != cur->TrieMap.end(); ++it) {
                q.push(it->second);
            }
        }
        return ans;

    }

};

class Data { // 数据库
private:

    vector<vector<vector<Student> > > DataTotal; // 一维：班级， 二维：考试序， 三维：学生个体
    /**
   * DataTotal[1][1][1] : 一班 第一次考试 第一个同学
   */

    map<string, Student> StudentsMap;
    Trie Tried;


public:
    bool is_exist(string id) {
        return StudentsMap.count(id);
    }

    // 导入数据
    void importData() {
        int ClassNum, ExamNum; // 班级数量 考试数量
        bool isFlag = true;

        while (isFlag) {
            system("cls");
            cout << "请输入班级数量(0退出): ";
            cin >> ClassNum;
            if (ClassNum == 0) break;
            string sclass;
            cout << "请输入专业名称(例如软件工程)" << endl;
            cin >> sclass;
            for (int i = 1; i <= ClassNum;) {

                vector<vector<Student> > Exam;
                system("cls");
                cout << "请输入 " << sclass << " " << i << " 班考试数量(0返回): ";
                cin >> ExamNum;
                if (ExamNum == 0 && i == 1) break;
                char *file_name;

                for (int j = 1; j <= ExamNum;) {
                    system("cls");
                    cout << "请输入 " << sclass << " " << i << " 班第 " << j << " 次考试成绩目录(0返回)：" << endl;

                    string filet;
                    cin >> filet;

                    file_name = (char *) filet.data();

                    if (file_name[0] == '0') {
                        break;
                    } else {

                        ifstream in_file(file_name);
                        if (!in_file) {
                            cout << "你输入的地址有误，请检查后重新输入" << endl;
                            _sleep(2000);
                        } else {
                            vector<Student> Students;
                            cout << "开始导入数据" << endl;
                            isFlag = false;
                            string name, id;
                            double score;
                            while (in_file >> id) {
                                Student st;
                                stringstream ss;
                                ss << i;
                                string t;
                                ss >> t;
                                st.set_Class(sclass + t + "班");
                                st.set_id(id);
                                in_file >> name;
                                st.set_name(name);
                                for (int i = 0; i < 6; ++i) {
                                    in_file >> score;
                                    st.set_score(score);
                                }
                                Students.push_back(st);
                            }

                            Exam.push_back(Students);
                            cout << "导入数据成功" << endl;
                            ++j;
                            _sleep(1500);
                        }

                    }

                }
                if (!isFlag) {
                    DataTotal.push_back(Exam);
                    if (i++ != ClassNum) isFlag = true;
                }

            }
        }
        if (!isFlag) init();
    }

    // 数据汇总
    void DataSummary() {
        cout << "当前系统学生数量: " << StudentsMap.size() << endl;
        cout << endl;
        cout << "当前系统班级数量: " << DataTotal.size() << endl;
        cout << endl;
        if (DataTotal.size() != 0) {
            cout << "当前系统每个班的考试数量: " << DataTotal[0].size() << endl;
        }

    }

    struct Pair {
        int total;
        string id;

        bool operator<(const Pair &t) const {
            return total > t.total;
        }
    };
    // 初始化导入的数据
    void init() {

        for (int i = 0; i < DataTotal.size(); ++i) { // 班级

            for (int j = 0; j < DataTotal[i].size(); ++j) { // 考试序
                vector<Pair> v;
                for (int k = 0; k < DataTotal[i][j].size(); ++k) { // 个体
                    Student student = DataTotal[i][j][k];
                    string id = student.get_id();
                    vector<double> s = student.get_score();

                    if (!StudentsMap.count(id)) {
                        student.set_scores(s);
                        int total = accumulate(s.begin(), s.end(), 0);

                        v.push_back({total, id});
                        StudentsMap[id] = student;

                        string name = student.get_name();
                        Tried.insert(Tried.names(name), id);

                    } else {
                        Student &st = StudentsMap[id];
                        st.set_scores(s);
                        int total = accumulate(s.begin(), s.end(), 0);
                        v.push_back({total, id});
                    }

                }
                sort(v.begin(), v.end());

                for (int k = 0; k < v.size(); ++k) {
                    string id = v[k].id;
                    if (k != 0 && v[k].total == v[k - 1].total)
                        StudentsMap[id].set_classRank(k);// 添加班排名
                    else
                        StudentsMap[id].set_classRank(k + 1);
                }

            }

        }
        for (int j = 0; j < DataTotal[0].size(); ++j) { // 考试序
            vector<Pair> v;

            for (map<string, Student>::iterator it = StudentsMap.begin(); it != StudentsMap.end(); ++it) {

                Student student = it->second;
                vector<vector<double> > scores = student.get_scores();
                int total = accumulate(scores[j].begin(), scores[j].end(), 0);
                v.push_back({total, student.get_id()});
            }

            sort(v.begin(), v.end());

            for (int k = 0; k < (int) v.size(); ++k) {
                string id = v[k].id;
                if (k != 0 && v[k].total == v[k - 1].total) {
                    StudentsMap[id].set_schoolRank(k);
                } else {
                    StudentsMap[id].set_schoolRank(k + 1);
                }

            }
        }

    }

    // 改变排名
    void changeRank(int idx, string Class) {
        vector<Pair> vc;
        vector<Pair> vs;
        for (map<string, Student>::iterator it = StudentsMap.begin(); it != StudentsMap.end(); ++it) {
            Student student = it->second;
            vector<vector<double> > scores = student.get_scores();

            int total = accumulate(scores[idx - 1].begin(), scores[idx - 1].end(), 0);
            vs.push_back({total, student.get_id()});
            if (student.get_Class() == Class) {
                vc.push_back({total, student.get_id()});
            }
        }
        sort(vc.begin(), vc.end());
        sort(vs.begin(), vs.end());
        for (int k = 0; k < (int) vc.size(); ++k) {
            string id = vc[k].id;
            if (k != 0 && vc[k].total == vc[k - 1].total)
                StudentsMap[id].set_classRank(idx - 1, k);
            else
                StudentsMap[id].set_classRank(idx - 1, k + 1);
        }
        for (int k = 0; k < (int) vs.size(); ++k) {
            string id = vs[k].id;
            if (k != 0 && vs[k].total == vs[k - 1].total)
                StudentsMap[id].set_schoolRank(idx - 1, k);
            else
                StudentsMap[id].set_schoolRank(idx - 1, k + 1);

        }

    }

    // 展示学生
    void showStudent(string id) {
        Student student = StudentsMap[id];
        cout << "姓名：" << student.get_name() << endl;
        cout << "班级: " << student.get_Class() << endl;
        cout << "学号：" << student.get_id() << endl;

        vector<vector<double> > scores = student.get_scores();
        vector<int> classRank = student.get_classRank();
        vector<int> schoolRank = student.get_schoolRank();
        for (int i = 0; i < (int) scores.size(); ++i) {
            cout << "第 " << i + 1 << " 次考成绩: ";
            for (int j = 0; j < (int) scores[i].size(); ++j) {
                cout << scores[i][j] << " ";
            }
            cout << "班排名: " << classRank[i] << " 校排名: " << schoolRank[i] << endl;
        }
    }

    // 改变名字
    void changeName(string id, string name) {
        Student &student = StudentsMap[id];
        string namey = student.get_name();
        Tried.insert(Tried.names(name), id);
        Tried.Delete(Tried.names(namey), id);
        student.set_name(name);
    }

    // 改变id
    void changeId(string id, string tid) {

        Student student = StudentsMap[id];
        string name = student.get_name();

        Tried.insert(Tried.names(name), tid);
        Tried.Delete(Tried.names(name), id);

        map<string, Student>::iterator iter = StudentsMap.find(id);
        StudentsMap.erase(iter);
        student.set_id(tid);
        StudentsMap[tid] = student;

    }

    // 改变分数
    bool changeScore(string id, int a, int b, double c) {
        Student &student = StudentsMap[id];
        vector<vector<double> > scores = student.get_scores();
        string Class = student.get_Class();
        if (a > scores.size() || b > scores[0].size()) {

            return false;

        } else {
            student.set_scores(a, b, c);
            changeRank(a, Class);
            return true;
        }

    }

    // 查找名字
    void serarchName(string name) {

        set<string> ID = Tried.searchName(Tried.names(name));
        if (ID.size() == 0) {
            cout << "该相关学生不存在" << endl;
            return;
        }
        cout << "找到以下学生: " << endl;

        for (set<string>::iterator it = ID.begin(); it != ID.end(); ++it) {
            showStudent(*it);
            cout << endl;
        }

    }

    // 格式化写入成绩排行榜
    void writeStudents(vector<Pair> students, int idx, char *file_name) {
        ofstream outf;
        outf.open(file_name);
        outf << "学号" << setw(35) << "姓名" << setw(20)
             << "第一科" << setw(10) << "第二科" << setw(10) << "第三科" << setw(10) << "第四科" << setw(10) << "第五科" << setw(10)
             << "第六科" << setw(10) << "总分" << setw(10)
             << "班排名" << setw(10) << "校排名" << setw(10) << endl;
        for (int i = 0; i < (int) students.size(); ++i) {
            Student student = StudentsMap[students[i].id];
            string id = student.get_id();
            string name = student.get_name();
            vector<double> scores = student.get_scores()[idx];
            int classRank = student.get_classRank()[idx];
            int schoolRank = student.get_schoolRank()[idx];
            outf << id << setw(20) << name << setw(15);
            for (int i = 0; i < (int) scores.size(); ++i) outf << scores[i] << setw(12);
            outf << students[i].total << setw(10) << classRank << setw(10) << schoolRank << setw(10) << endl;
        }
        outf.close();
    }

    // 生成班级成绩排行榜
    bool generateClassRank(int idx, string Class, char *file_name) {
        vector<Pair> students;
        for (map<string, Student>::iterator it = StudentsMap.begin(); it != StudentsMap.end(); ++it) {
            Student student = it->second;
            if (student.get_Class() == Class) {
                vector<vector<double> > scores = student.get_scores();
                if (idx >= scores.size() || idx < 0) return false;
                int total = accumulate(scores[idx].begin(), scores[idx].end(), 0);
                students.push_back({total, student.get_id()});
            }
        }
        if (students.size() == 0) return false;
        sort(students.begin(), students.end());
        writeStudents(students, idx, file_name);
        return true;
    }

    // 生成校成绩排行榜
    bool generateSchoolRank(int idx, char *file_name) {
        vector<Pair> students;
        for (map<string, Student>::iterator it = StudentsMap.begin(); it != StudentsMap.end(); ++it) {
            Student student = it->second;
            vector<vector<double> > scores = student.get_scores();
            if (idx >= scores.size() || idx < 0) return false;
            int total = accumulate(scores[idx].begin(), scores[idx].end(), 0);
            students.push_back({total, student.get_id()});

        }
        if (students.size() == 0) return false;
        sort(students.begin(), students.end());
        writeStudents(students, idx, file_name);
        return true;
    }

    // 格式化写入进步排行榜
    void writeStudentsProgress(int idx1, int idx2, vector<Pair> students, char *file_name) {
        ofstream outf;
        outf.open(file_name);
        outf << "学号" << setw(35) << "姓名" << setw(20)
             << "第 " << idx1 + 1 << " 次班排名" << setw(15) << "第 " << idx2 + 1 << " 次班排名" << setw(15) << "班进步名次"
             << setw(10)
             << "第 " << idx1 + 1 << " 次校排名" << setw(15) << "第 " << idx2 + 1 << " 次校排名" << setw(15) << "校进步名次" << endl;
        for (int i = 0; i < (int) students.size(); ++i) {
            Student student = StudentsMap[students[i].id];
            string id = student.get_id();
            string name = student.get_name();
            int classRank1 = student.get_classRank()[idx1];
            int classRank2 = student.get_classRank()[idx2];
            int schoolRank1 = student.get_schoolRank()[idx1];
            int schoolRank2 = student.get_schoolRank()[idx2];
            outf << id << setw(20) << name << setw(25)
                 << classRank1 << setw(25) << classRank2 << setw(25) << classRank2 - classRank1 << setw(23)
                 << schoolRank1 << setw(25) << schoolRank2 << setw(25) << schoolRank2 - schoolRank1 << endl;

        }
        outf.close();
    }

    // 生成班级成绩进步排行榜
    bool generateProgressClassRank(int idx1, int idx2, string Class, char *file_name) {
        vector<Pair> students;
        for (map<string, Student>::iterator it = StudentsMap.begin(); it != StudentsMap.end(); ++it) {
            Student student = it->second;
            if (student.get_Class() == Class) {
                vector<int> classRank = student.get_classRank();
                if (idx2 >= classRank.size() || idx1 < 0) return false;
                int total = classRank[idx2] - classRank[idx1];
                students.push_back({total, student.get_id()});
            }
        }
        if (students.size() == 0) return false;
        sort(students.begin(), students.end());
        writeStudentsProgress(idx1, idx2, students, file_name);
        return true;
    }

    // 生成校成绩进步排行榜
    bool generateProgressSchoolRank(int idx1, int idx2, char *file_name) {
        vector<Pair> students;
        for (map<string, Student>::iterator it = StudentsMap.begin(); it != StudentsMap.end(); ++it) {
            Student student = it->second;
            vector<int> schoolRank = student.get_schoolRank();
            if (idx2 >= schoolRank.size() || idx1 < 0) return false;
            int total = schoolRank[idx2] - schoolRank[idx1];
            students.push_back({total, student.get_id()});
        }
        if (students.size() == 0) return false;
        sort(students.begin(), students.end());
        writeStudentsProgress(idx1, idx2, students, file_name);
        return true;
    }

    // 格式化写入优秀成绩排行榜
    void writeStudentsExcellent(int line, char *file_name, vector<vector<Pair> > students) {
        ofstream outf;
        outf.open(file_name);
        outf << "优秀分数线: " << line << endl;
        outf << "学号" << setw(35) << "姓名" << setw(28)
             << "优秀科目数量" << setw(19) << "总分" << endl;
        for (int i = 6; i >= 0; --i) {
            int size = students[i].size();
            for (int j = 0; j < size; ++j) {
                Student student = StudentsMap[students[i][j].id];
                string id = student.get_id();
                string name = student.get_name();
                int total = students[i][j].total;
                outf << id << setw(20) << name << setw(25)
                     << i << setw(25) << total << endl;
            }
        }
        outf.close();
    }

    // 生成班级成绩优秀排行榜
    bool generateExcellentClasstRank(int idx, string Class, int line, char *file_name) {
        vector<vector<Pair> > students(7);
        for (map<string, Student>::iterator it = StudentsMap.begin(); it != StudentsMap.end(); ++it) {
            Student student = it->second;
            if (student.get_Class() == Class) {
                if (idx >= student.get_scores().size() || idx < 0) return false;
                vector<double> scores = student.get_scores()[idx];
                int c = 0;
                int total = 0;
                for (int i = 0; i < scores.size(); ++i) {
                    total += scores[i];
                    if (scores[i] >= line) ++c;
                }
                students[c].push_back({total, student.get_id()});
            }
        }
        bool isFlag = false;
        for (int i = 0; i < students.size(); ++i) {
            if (students[i].size() != 0) isFlag = true;
            sort(students[i].begin(), students[i].end());
        }
        if (isFlag) writeStudentsExcellent(line, file_name, students);
        return isFlag;
    }

    // 生成校成绩优秀排行榜
    bool generateExcellentSchoolRank(int idx, int line, char *file_name) {
        vector<vector<Pair> > students(7);
        for (map<string, Student>::iterator it = StudentsMap.begin(); it != StudentsMap.end(); ++it) {
            Student student = it->second;
            if (idx >= student.get_scores().size() || idx < 0) return false;
            vector<double> scores = student.get_scores()[idx];
            int c = 0;
            int total = 0;
            for (int i = 0; i < scores.size(); ++i) {
                total += scores[i];
                if (scores[i] >= line) ++c;
            }
            students[c].push_back({total, student.get_id()});
        }
        bool isFlag = false;
        for (int i = 0; i < students.size(); ++i) {
            if (students[i].size() != 0) isFlag = true;
            sort(students[i].begin(), students[i].end());
        }
        if (isFlag) writeStudentsExcellent(line, file_name, students);
        return isFlag;
    }

    // 格式化写入挂科排行榜
    void writeStudentsHangSection(int line, char *file_name, vector<vector<Pair> > students) {
        ofstream outf;
        outf.open(file_name);
        outf << "挂科分数线: " << line << endl;
        outf << "学号" << setw(35) << "姓名" << setw(28)
             << "挂科科目数量" << setw(19) << "总分" << endl;
        for (int i = 6; i > 0; --i) {
            int size = students[i].size();
            for (int j = 0; j < size; ++j) {
                Student student = StudentsMap[students[i][j].id];
                string id = student.get_id();
                string name = student.get_name();
                int total = students[i][j].total;
                outf << id << setw(20) << name << setw(25)
                     << i << setw(25) << total << endl;
            }
        }
        outf.close();
    }

    // 生成班级挂科成绩排行榜
    bool generateHangSectionClassRank(int idx, string Class, int line, char *file_name) {
        vector<vector<Pair> > students(7);
        for (map<string, Student>::iterator it = StudentsMap.begin(); it != StudentsMap.end(); ++it) {
            Student student = it->second;
            if (student.get_Class() == Class) {
                if (idx >= student.get_scores().size() || idx < 0) return false;
                vector<double> scores = student.get_scores()[idx];
                int c = 0;
                int total = 0;
                for (int i = 0; i < scores.size(); ++i) {
                    total += scores[i];
                    if (scores[i] < line) ++c;
                }
                students[c].push_back({total, student.get_id()});
            }
        }
        bool isFlag = false;
        for (int i = 0; i < students.size(); ++i) {
            if (students[i].size() != 0) isFlag = true;
            sort(students[i].begin(), students[i].end());
        }
        if (isFlag) writeStudentsHangSection(line, file_name, students);
        return isFlag;
    }

    // 生成校挂科成绩排行榜
    bool generateHangSectionSchoolRank(int idx, int line, char *file_name) {
        vector<vector<Pair> > students(7);
        for (map<string, Student>::iterator it = StudentsMap.begin(); it != StudentsMap.end(); ++it) {
            Student student = it->second;

            if (idx >= student.get_scores().size() || idx < 0) return false;
            vector<double> scores = student.get_scores()[idx];
            int c = 0;
            int total = 0;
            for (int i = 0; i < scores.size(); ++i) {
                total += scores[i];
                if (scores[i] < line) ++c;
            }
            students[c].push_back({total, student.get_id()});

        }
        bool isFlag = false;
        for (int i = 0; i < students.size(); ++i) {
            if (students[i].size() != 0) isFlag = true;
            sort(students[i].begin(), students[i].end());
        }
        if (isFlag) writeStudentsHangSection(line, file_name, students);
        return isFlag;
    }

};

class System {
private:
    Data data;
public:

    // 主菜单
    void StartMenu() {
        system("cls");
        cout << endl;
        cout << "\t ";
        cout << " ******** 学生管理系统V1.0 ********** " << endl;
        cout << "\t ";
        printf("**                                  **\n");
        cout << "\t ";
        printf("**   1.数据管理      2.成绩查询     **\n");
        cout << "\t ";
        printf("**                                  **\n");
        cout << "\t ";
        printf("**   3.成绩排行榜    4.进步排行榜   **\n");
        cout << "\t ";
        printf("**                                  **\n");
        cout << "\t ";
        printf("**   5.优秀排行榜    6.挂科排行榜   **\n");
        cout << "\t ";
        printf("**                                  **\n");
        cout << "\t ";
        printf("**   7.使用说明      8.退出         **\n");
        cout << "\t ";
        printf("**                                  **\n");
        cout << "\t ";
        printf("  **********************************\n");
        cout << endl;
    }

    // 主程序入口
    void start() {
        bool isFlag = true;
        while (isFlag) {
            string cz;
            StartMenu();
            cout << "请输入操作: ";
            cin >> cz;
            if (cz == "1") {
                startData();
            } else if (cz == "2") {
                InquireScore();
            } else if (cz == "3") {
                AchievementRanking();
            } else if (cz == "4") {
                ProgressRank();
            } else if (cz == "5") {
                ExcellentRank();
            } else if (cz == "6") {
                HangSectionRank();
            } else if (cz == "7") {
                Introduction();
            } else if (cz == "8") {
                cout << endl;
                cout << "退出成功" << endl;
                isFlag = false;
            }
        }
    }

    // 数据管理程序
    void startData() {
        bool isFlag = true;
        while (isFlag) {
            string cz;
            DataMenu();
            cout << "请输入操作序号: ";
            cin >> cz;
            if (cz == "1") {
                DataSummary();
            } else if (cz == "2") {
                ImportData();
            } else if (cz == "3") {
                changeData();
            } else if (cz == "4") {
                isFlag = false;
            }
        }
    }

    void DataMenu() {
        system("cls");
        cout << endl;
        cout << "\t";
        cout << "  *********   数据管理中心   ***********" << endl;
        cout << "\t ";
        printf("**                                    **\n");
        cout << "\t ";
        printf("**   1.数据汇总      2.导入数据       **\n");
        cout << "\t ";
        printf("**                                    **\n");
        cout << "\t ";
        printf("**   3.修改数据      4.返回           **\n");
        cout << "\t ";
        printf("**                                    **\n");
        cout << "\t ";
        printf("  ************************************\n");
    }

    // 数据汇总
    void DataSummary() {
        cout << endl;
        data.DataSummary();
        system("pause");

    }

    // 导入数据
    void ImportData() {
        data.importData();
    }

    // 修改数据
    void changeData() {
        system("cls");
        string id;
        while (true) {
            cout << "请输入要修改学生的学号(0退出): ";
            cin >> id;
            if (id == "0") break;
            if (!data.is_exist(id)) {
                cout << "该学号学生不存在，请检查后重新输入" << endl;
                system("pause");
                return;
            }
            changeDatahelper(id);
        }

    }


    void changeDatahelper(string id) {
        bool isFlag = true;
        string cz;
        while (isFlag) {
            system("cls");
            cout << "当前学生数据: " << endl;
            data.showStudent(id);
            cout << endl;
            cout << "\t";
            cout << "  *************************************" << endl;
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("**   1.姓名              2.学号       **\n");
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("**   3.成绩              4.返回       **\n");
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("  ************************************\n");
            cout << "请输入要修改项: ";
            cin >> cz;
            if (cz == "1") {
                changeName(id);
            } else if (cz == "2") {
                changeId(id);
            } else if (cz == "3") {
                changeScore(id);
            } else if (cz == "4") {
                isFlag = false;
            }

        }

    }

    // 修改姓名
    void changeName(string id) {
        string name;
        cout << "请输入修改后的姓名(0返回): ";
        cin >> name;
        if (name == "0") return;
        cout << endl;
        data.changeName(id, name);
        cout << "修改成功" << endl;
        system("pause");

    }

    // 修改id
    void changeId(string &id) {
        string tid;
        cout << "请输入修改后的学号(0返回): ";
        cin >> tid;
        if (tid == "0") return;
        if (data.is_exist(tid)) {
            cout << "此学号已有学生，请检查后重新输入" << endl;
            system("pause");
            return;
        }
        data.changeId(id, tid);
        cout << endl;
        cout << "修改成功" << endl;
        id = tid;
        system("pause");

    }

    // 修改成绩
    void changeScore(string id) {
        int a, b;
        double c;
        cout << "请输入要修改的考试序号,科目序号,及修改后的成绩(0退出): ";
        cin >> a;
        if (a == 0) return;
        cin >> b;
        if (b == 0) return;
        cin >> c;
        if (data.changeScore(id, a, b, c)) {
            cout << "修改成功" << endl;
            system("pause");
        } else {
            cout << "你的输入有误，请检查后重新输入" << endl;
            system("pause");
        }


    }

    // 成绩查询
    void InquireScore() {
        bool isFlag = true;
        while (isFlag) {
            system("cls");
            string cz;
            cout << "\t";
            cout << "  ************ 成绩查询 ***************" << endl;
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("**   1.姓名              2.学号       **\n");
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("**   3.返回                           **\n");
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("  ************************************\n");
            cout << "请输入查询方式" << endl;
            cin >> cz;
            if (cz == "1") {
                searchName();
            } else if (cz == "2") {
                searchID();
            } else if (cz == "3") {
                isFlag = false;
            }

        }

    }

    // 姓名查找
    void searchName() {
        string name;
        cout << "请输入相关姓名: ";
        cin >> name;
        data.serarchName(name);
        system("pause");
    }

    // ID 查询
    void searchID() {
        string id;
        cout << "请输入该学生学号: ";
        cin >> id;
        if (!data.is_exist(id)) {
            cout << "该学生不存在，请检查后重新输入" << endl;
            system("pause");
            return;
        }
        data.showStudent(id);
        system("pause");
    }

    // 成绩排行榜
    void AchievementRanking() {
        bool isFlag = true;
        while (isFlag) {
            system("cls");
            string cz;
            cout << "\t";
            cout << "  ************ 成绩排行榜 *************" << endl;
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("**   1.班级              2.学校       **\n");
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("**   3.返回                           **\n");
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("  ************************************\n");
            cout << "请输入查询方式" << endl;
            cin >> cz;
            if (cz == "1") {
                AchieveRankClass();
            } else if (cz == "2") {
                AchieveRankSchool();
            } else if (cz == "3") {
                isFlag = false;
            }

        }
    }

    // 班级成绩排行榜
    void AchieveRankClass() {
        string Class;
        int idx;
        cout << "请输入考试序(0返回): ";
        cin >> idx;
        if (idx == 0) return;
        cout << "请输入要查询的班级(0返回): ";
        cin >> Class;
        if (Class == "0") return;
        string file_name = Class + "考试成绩排行榜.txt";
        if (data.generateClassRank(idx - 1, Class, (char *) file_name.data())) {
            cout << "排行榜已生成在本程序目录下 " << file_name << " 文件里" << endl;
        } else {
            cout << "你的查询有误，请检查后重新输入" << endl;
        }
        system("pause");
    }

    //校成绩排行榜
    void AchieveRankSchool() {
        int idx;
        cout << "请输入考试序(0返回): ";
        cin >> idx;
        if (idx == 0) return;
        stringstream ss;
        ss << "第_" << idx << "_次考试成绩排行榜.txt";
        string file_name;
        ss >> file_name;
        if (data.generateSchoolRank(idx - 1, (char *) file_name.data())) {
            cout << "排行榜已生成在本程序目录下 " << file_name << " 文件里" << endl;
        } else {
            cout << "你的查询有误，请检查后重新输入" << endl;
        }
        system("pause");

    }

    // 进步排行榜
    void ProgressRank() {
        bool isFlag = true;
        while (isFlag) {
            system("cls");
            string cz;
            cout << "\t";
            cout << "  ************ 进步排行榜 *************" << endl;
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("**   1.班级              2.学校       **\n");
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("**   3.返回                           **\n");
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("  ************************************\n");
            cout << "请输入查询方式" << endl;
            cin >> cz;
            if (cz == "1") {
                progressRankClass();
            } else if (cz == "2") {
                progressRankSchool();
            } else if (cz == "3") {
                isFlag = false;
            }


        }
    }

    // 班级进步排行榜
    void progressRankClass() {
        string Class;
        int idx1, idx2;
        cout << "请输入两次考试序(0返回): ";
        cin >> idx1;
        if (idx1 == 0) return;
        cin >> idx2;
        if (idx2 == 0) return;
        cout << "请输入要查询的班级(0返回): ";
        cin >> Class;
        if (Class == "0") return;
        stringstream ss;
        ss << Class << "第_" << idx1 << "_次与第_" << idx2 << "_次考试成绩进步排行榜.txt";
        string file_name;
        ss >> file_name;
        if (data.generateProgressClassRank(idx1 - 1, idx2 - 1, Class, (char *) file_name.data())) {
            cout << "排行榜已生成在本程序目录下 " << file_name << " 文件里" << endl;
        } else {
            cout << "你的查询有误，请检查后重新输入" << endl;
        }
        system("pause");
    }

    // 校进步排行榜
    void progressRankSchool() {
        int idx1, idx2;
        cout << "请输入两次考试序(0返回): ";
        cin >> idx1;
        if (idx1 == 0) return;
        cin >> idx2;
        if (idx2 == 0) return;
        stringstream ss;
        ss << "第_" << idx1 << "_次与第_" << idx2 << "_次考试成绩进步排行榜.txt";
        string file_name;
        ss >> file_name;
        if (data.generateProgressSchoolRank(idx1 - 1, idx2 - 1, (char *) file_name.data())) {
            cout << "排行榜已生成在本程序目录下 " << file_name << " 文件里" << endl;
        } else {
            cout << "你的查询有误，请检查后重新输入" << endl;
        }
        system("pause");
    }

    // 优秀排行榜
    void ExcellentRank() {
        bool isFlag = true;
        while (isFlag) {
            system("cls");
            string cz;
            cout << "\t";
            cout << "  ************ 优秀排行榜 *************" << endl;
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("**   1.班级              2.学校       **\n");
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("**   3.返回                           **\n");
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("  ************************************\n");
            cout << "请输入查询方式" << endl;
            cin >> cz;
            if (cz == "1") {
                ExcellentClassRank();
            } else if (cz == "2") {
                ExcellentSchoolRank();
            } else if (cz == "3") {
                isFlag = false;
            }

        }

    }

    // 班级优秀排行榜
    void ExcellentClassRank() {
        int idx;
        string Class;
        int line;
        cout << "请输入考试序(0退出): ";
        cin >> idx;
        if (idx == 0) return;
        cout << "请输入查询班级（0退出): ";
        cin >> Class;
        if (Class == "0") return;
        cout << "请输入优秀分数线(0退出): ";
        cin >> line;
        if (line == 0) return;
        stringstream ss;
        ss << Class << "第_" << idx << "_次考试成绩优秀排行榜.txt";
        string file_name;
        ss >> file_name;
        if (data.generateExcellentClasstRank(idx - 1, Class, line, (char *) file_name.data())) {
            cout << "排行榜已生成在本程序目录下 " << file_name << " 文件里" << endl;
        } else {
            cout << "你的查询有误，请检查后重新输入" << endl;
        }
        system("pause");
    }

    // 校优秀排行榜
    void ExcellentSchoolRank() {
        int idx;
        int line;
        cout << "请输入考试序(0退出): ";
        cin >> idx;
        if (idx == 0) return;
        cout << "请输入优秀分数线(0退出): ";
        cin >> line;
        if (line == 0) return;
        stringstream ss;
        ss << "第_" << idx << "_次考试成绩优秀排行榜.txt";
        string file_name;
        ss >> file_name;
        if (data.generateExcellentSchoolRank(idx - 1, line, (char *) file_name.data())) {
            cout << "排行榜已生成在本程序目录下 " << file_name << " 文件里" << endl;
        } else {
            cout << "你的查询有误，请检查后重新输入" << endl;
        }
        system("pause");
    }

    // 挂科排行榜
    void HangSectionRank() {
        bool isFlag = true;
        while (isFlag) {
            system("cls");
            string cz;
            cout << "\t";
            cout << "  ************ 挂科排行榜 *************" << endl;
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("**   1.班级              2.学校       **\n");
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("**   3.返回                           **\n");
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("  ************************************\n");
            cout << "请输入查询方式" << endl;
            cin >> cz;
            if (cz == "1") {
                HangSectionClassRank();
            } else if (cz == "2") {
                HangSectionSchoolRank();
            } else if (cz == "3") {
                isFlag = false;
            }


        }
    }

    // 班级校挂科排行榜
    void HangSectionClassRank() {
        int idx;
        string Class;
        int line;
        cout << "请输入考试序(0退出): ";
        cin >> idx;
        if (idx == 0) return;

        cout << "请输入要查询的班级(0退出): ";
        cin >> Class;
        if (Class == "0") return;

        cout << "请输入挂科分数线(0退出): ";
        cin >> line;
        if (line == 0) return;
        stringstream ss;
        ss << Class << "第_" << idx << "_次考试成绩挂科排行榜.txt";
        string file_name;
        ss >> file_name;
        if (data.generateHangSectionClassRank(idx - 1, Class, line, (char *) file_name.data())) {
            cout << "排行榜已生成在本程序目录下 " << file_name << " 文件里" << endl;
        } else {
            cout << "你的查询有误，请检查后重新输入" << endl;
        }
        system("pause");
    }

    // 校挂科排行榜
    void HangSectionSchoolRank() {
        int idx;
        int line;
        cout << "请输入考试序(0退出): ";
        cin >> idx;
        if (idx == 0) return;
        cout << "请输入挂科分数线(0退出): ";
        cin >> line;
        if (line == 0) return;
        stringstream ss;
        ss << "第_" << idx << "_次考试成绩挂科排行榜.txt";
        string file_name;
        ss >> file_name;
        if (data.generateHangSectionSchoolRank(idx - 1, line, (char *) file_name.data())) {
            cout << "排行榜已生成在本程序目录下 " << file_name << " 文件里" << endl;
        } else {
            cout << "你的查询有误，请检查后重新输入" << endl;
        }
        system("pause");
    }

    // 使用说明
    void Introduction() {
        system("cls");
        cout << "1.启动程序" << endl;
        cout << "2.进入数据管理中心" << endl; 
		cout << "3.一次性导入全部数据（数据有固定格式，详情请见本程序目录中示例数据格式）" << endl;
        cout << "4.按序号进行相关功能操作" << endl;
        system("pause");
    }

};

int main() {

    System s;
    s.start();

}
