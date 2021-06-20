#include<bits/stdc++.h>

using namespace std;

class Student { // ѧ����
private:
    string name; // ����
    vector<double> score;  // �ɼ�
    vector<vector<double> > scores;
    string id;    // ѧ��
    string Class;   // �༶
    vector<int> schoolRank; // У����
    vector<int> classRank; // ������

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

class Trie { // �� ���� �� ǰ׺��
private:
    map<string, Trie *> TrieMap;
    set<string> ID;
public:
    // ����һλ����Ϊ vs ͬѧ�� id
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

    // ɾ��һλ����Ϊ vs ͬѧ�� id
    void Delete(vector<string> vs, string id) {
        Trie *cur = this;
        for (int i = 0; i < (int) vs.size(); ++i) {
            cur = cur->TrieMap[vs[i]];
        }
        set<string>::iterator it = cur->ID.find(id);
        cur->ID.erase(it);
    }

    // �ж�ĳ��ǰ׺�Ƿ���� ����ĳ��ǰ׺
    bool is_exist(vector<string> vs, Trie *&t) {
        Trie *cur = this;
        for (int i = 0; i < (int) vs.size(); ++i) {
            if (!cur->TrieMap.count(vs[i])) return false;
            cur = cur->TrieMap[vs[i]];
        }
        t = cur;
        return true;
    }

    // ��ȡ �����ַ��� �� ÿ�����֣���װ��˳������
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

    // ����
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

class Data { // ���ݿ�
private:

    vector<vector<vector<Student> > > DataTotal; // һά���༶�� ��ά�������� ��ά��ѧ������
    /**
   * DataTotal[1][1][1] : һ�� ��һ�ο��� ��һ��ͬѧ
   */

    map<string, Student> StudentsMap;
    Trie Tried;


public:
    bool is_exist(string id) {
        return StudentsMap.count(id);
    }

    // ��������
    void importData() {
        int ClassNum, ExamNum; // �༶���� ��������
        bool isFlag = true;

        while (isFlag) {
            system("cls");
            cout << "������༶����(0�˳�): ";
            cin >> ClassNum;
            if (ClassNum == 0) break;
            string sclass;
            cout << "������רҵ����(�����������)" << endl;
            cin >> sclass;
            for (int i = 1; i <= ClassNum;) {

                vector<vector<Student> > Exam;
                system("cls");
                cout << "������ " << sclass << " " << i << " �࿼������(0����): ";
                cin >> ExamNum;
                if (ExamNum == 0 && i == 1) break;
                char *file_name;

                for (int j = 1; j <= ExamNum;) {
                    system("cls");
                    cout << "������ " << sclass << " " << i << " ��� " << j << " �ο��Գɼ�Ŀ¼(0����)��" << endl;

                    string filet;
                    cin >> filet;

                    file_name = (char *) filet.data();

                    if (file_name[0] == '0') {
                        break;
                    } else {

                        ifstream in_file(file_name);
                        if (!in_file) {
                            cout << "������ĵ�ַ�����������������" << endl;
                            _sleep(2000);
                        } else {
                            vector<Student> Students;
                            cout << "��ʼ��������" << endl;
                            isFlag = false;
                            string name, id;
                            double score;
                            while (in_file >> id) {
                                Student st;
                                stringstream ss;
                                ss << i;
                                string t;
                                ss >> t;
                                st.set_Class(sclass + t + "��");
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
                            cout << "�������ݳɹ�" << endl;
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

    // ���ݻ���
    void DataSummary() {
        cout << "��ǰϵͳѧ������: " << StudentsMap.size() << endl;
        cout << endl;
        cout << "��ǰϵͳ�༶����: " << DataTotal.size() << endl;
        cout << endl;
        if (DataTotal.size() != 0) {
            cout << "��ǰϵͳÿ����Ŀ�������: " << DataTotal[0].size() << endl;
        }

    }

    struct Pair {
        int total;
        string id;

        bool operator<(const Pair &t) const {
            return total > t.total;
        }
    };
    // ��ʼ�����������
    void init() {

        for (int i = 0; i < DataTotal.size(); ++i) { // �༶

            for (int j = 0; j < DataTotal[i].size(); ++j) { // ������
                vector<Pair> v;
                for (int k = 0; k < DataTotal[i][j].size(); ++k) { // ����
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
                        StudentsMap[id].set_classRank(k);// ��Ӱ�����
                    else
                        StudentsMap[id].set_classRank(k + 1);
                }

            }

        }
        for (int j = 0; j < DataTotal[0].size(); ++j) { // ������
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

    // �ı�����
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

    // չʾѧ��
    void showStudent(string id) {
        Student student = StudentsMap[id];
        cout << "������" << student.get_name() << endl;
        cout << "�༶: " << student.get_Class() << endl;
        cout << "ѧ�ţ�" << student.get_id() << endl;

        vector<vector<double> > scores = student.get_scores();
        vector<int> classRank = student.get_classRank();
        vector<int> schoolRank = student.get_schoolRank();
        for (int i = 0; i < (int) scores.size(); ++i) {
            cout << "�� " << i + 1 << " �ο��ɼ�: ";
            for (int j = 0; j < (int) scores[i].size(); ++j) {
                cout << scores[i][j] << " ";
            }
            cout << "������: " << classRank[i] << " У����: " << schoolRank[i] << endl;
        }
    }

    // �ı�����
    void changeName(string id, string name) {
        Student &student = StudentsMap[id];
        string namey = student.get_name();
        Tried.insert(Tried.names(name), id);
        Tried.Delete(Tried.names(namey), id);
        student.set_name(name);
    }

    // �ı�id
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

    // �ı����
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

    // ��������
    void serarchName(string name) {

        set<string> ID = Tried.searchName(Tried.names(name));
        if (ID.size() == 0) {
            cout << "�����ѧ��������" << endl;
            return;
        }
        cout << "�ҵ�����ѧ��: " << endl;

        for (set<string>::iterator it = ID.begin(); it != ID.end(); ++it) {
            showStudent(*it);
            cout << endl;
        }

    }

    // ��ʽ��д��ɼ����а�
    void writeStudents(vector<Pair> students, int idx, char *file_name) {
        ofstream outf;
        outf.open(file_name);
        outf << "ѧ��" << setw(35) << "����" << setw(20)
             << "��һ��" << setw(10) << "�ڶ���" << setw(10) << "������" << setw(10) << "���Ŀ�" << setw(10) << "�����" << setw(10)
             << "������" << setw(10) << "�ܷ�" << setw(10)
             << "������" << setw(10) << "У����" << setw(10) << endl;
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

    // ���ɰ༶�ɼ����а�
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

    // ����У�ɼ����а�
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

    // ��ʽ��д��������а�
    void writeStudentsProgress(int idx1, int idx2, vector<Pair> students, char *file_name) {
        ofstream outf;
        outf.open(file_name);
        outf << "ѧ��" << setw(35) << "����" << setw(20)
             << "�� " << idx1 + 1 << " �ΰ�����" << setw(15) << "�� " << idx2 + 1 << " �ΰ�����" << setw(15) << "���������"
             << setw(10)
             << "�� " << idx1 + 1 << " ��У����" << setw(15) << "�� " << idx2 + 1 << " ��У����" << setw(15) << "У��������" << endl;
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

    // ���ɰ༶�ɼ��������а�
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

    // ����У�ɼ��������а�
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

    // ��ʽ��д������ɼ����а�
    void writeStudentsExcellent(int line, char *file_name, vector<vector<Pair> > students) {
        ofstream outf;
        outf.open(file_name);
        outf << "���������: " << line << endl;
        outf << "ѧ��" << setw(35) << "����" << setw(28)
             << "�����Ŀ����" << setw(19) << "�ܷ�" << endl;
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

    // ���ɰ༶�ɼ��������а�
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

    // ����У�ɼ��������а�
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

    // ��ʽ��д��ҿ����а�
    void writeStudentsHangSection(int line, char *file_name, vector<vector<Pair> > students) {
        ofstream outf;
        outf.open(file_name);
        outf << "�ҿƷ�����: " << line << endl;
        outf << "ѧ��" << setw(35) << "����" << setw(28)
             << "�ҿƿ�Ŀ����" << setw(19) << "�ܷ�" << endl;
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

    // ���ɰ༶�ҿƳɼ����а�
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

    // ����У�ҿƳɼ����а�
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

    // ���˵�
    void StartMenu() {
        system("cls");
        cout << endl;
        cout << "\t ";
        cout << " ******** ѧ������ϵͳV1.0 ********** " << endl;
        cout << "\t ";
        printf("**                                  **\n");
        cout << "\t ";
        printf("**   1.���ݹ���      2.�ɼ���ѯ     **\n");
        cout << "\t ";
        printf("**                                  **\n");
        cout << "\t ";
        printf("**   3.�ɼ����а�    4.�������а�   **\n");
        cout << "\t ";
        printf("**                                  **\n");
        cout << "\t ";
        printf("**   5.�������а�    6.�ҿ����а�   **\n");
        cout << "\t ";
        printf("**                                  **\n");
        cout << "\t ";
        printf("**   7.ʹ��˵��      8.�˳�         **\n");
        cout << "\t ";
        printf("**                                  **\n");
        cout << "\t ";
        printf("  **********************************\n");
        cout << endl;
    }

    // ���������
    void start() {
        bool isFlag = true;
        while (isFlag) {
            string cz;
            StartMenu();
            cout << "���������: ";
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
                cout << "�˳��ɹ�" << endl;
                isFlag = false;
            }
        }
    }

    // ���ݹ������
    void startData() {
        bool isFlag = true;
        while (isFlag) {
            string cz;
            DataMenu();
            cout << "������������: ";
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
        cout << "  *********   ���ݹ�������   ***********" << endl;
        cout << "\t ";
        printf("**                                    **\n");
        cout << "\t ";
        printf("**   1.���ݻ���      2.��������       **\n");
        cout << "\t ";
        printf("**                                    **\n");
        cout << "\t ";
        printf("**   3.�޸�����      4.����           **\n");
        cout << "\t ";
        printf("**                                    **\n");
        cout << "\t ";
        printf("  ************************************\n");
    }

    // ���ݻ���
    void DataSummary() {
        cout << endl;
        data.DataSummary();
        system("pause");

    }

    // ��������
    void ImportData() {
        data.importData();
    }

    // �޸�����
    void changeData() {
        system("cls");
        string id;
        while (true) {
            cout << "������Ҫ�޸�ѧ����ѧ��(0�˳�): ";
            cin >> id;
            if (id == "0") break;
            if (!data.is_exist(id)) {
                cout << "��ѧ��ѧ�������ڣ��������������" << endl;
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
            cout << "��ǰѧ������: " << endl;
            data.showStudent(id);
            cout << endl;
            cout << "\t";
            cout << "  *************************************" << endl;
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("**   1.����              2.ѧ��       **\n");
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("**   3.�ɼ�              4.����       **\n");
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("  ************************************\n");
            cout << "������Ҫ�޸���: ";
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

    // �޸�����
    void changeName(string id) {
        string name;
        cout << "�������޸ĺ������(0����): ";
        cin >> name;
        if (name == "0") return;
        cout << endl;
        data.changeName(id, name);
        cout << "�޸ĳɹ�" << endl;
        system("pause");

    }

    // �޸�id
    void changeId(string &id) {
        string tid;
        cout << "�������޸ĺ��ѧ��(0����): ";
        cin >> tid;
        if (tid == "0") return;
        if (data.is_exist(tid)) {
            cout << "��ѧ������ѧ�����������������" << endl;
            system("pause");
            return;
        }
        data.changeId(id, tid);
        cout << endl;
        cout << "�޸ĳɹ�" << endl;
        id = tid;
        system("pause");

    }

    // �޸ĳɼ�
    void changeScore(string id) {
        int a, b;
        double c;
        cout << "������Ҫ�޸ĵĿ������,��Ŀ���,���޸ĺ�ĳɼ�(0�˳�): ";
        cin >> a;
        if (a == 0) return;
        cin >> b;
        if (b == 0) return;
        cin >> c;
        if (data.changeScore(id, a, b, c)) {
            cout << "�޸ĳɹ�" << endl;
            system("pause");
        } else {
            cout << "������������������������" << endl;
            system("pause");
        }


    }

    // �ɼ���ѯ
    void InquireScore() {
        bool isFlag = true;
        while (isFlag) {
            system("cls");
            string cz;
            cout << "\t";
            cout << "  ************ �ɼ���ѯ ***************" << endl;
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("**   1.����              2.ѧ��       **\n");
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("**   3.����                           **\n");
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("  ************************************\n");
            cout << "�������ѯ��ʽ" << endl;
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

    // ��������
    void searchName() {
        string name;
        cout << "�������������: ";
        cin >> name;
        data.serarchName(name);
        system("pause");
    }

    // ID ��ѯ
    void searchID() {
        string id;
        cout << "�������ѧ��ѧ��: ";
        cin >> id;
        if (!data.is_exist(id)) {
            cout << "��ѧ�������ڣ��������������" << endl;
            system("pause");
            return;
        }
        data.showStudent(id);
        system("pause");
    }

    // �ɼ����а�
    void AchievementRanking() {
        bool isFlag = true;
        while (isFlag) {
            system("cls");
            string cz;
            cout << "\t";
            cout << "  ************ �ɼ����а� *************" << endl;
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("**   1.�༶              2.ѧУ       **\n");
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("**   3.����                           **\n");
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("  ************************************\n");
            cout << "�������ѯ��ʽ" << endl;
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

    // �༶�ɼ����а�
    void AchieveRankClass() {
        string Class;
        int idx;
        cout << "�����뿼����(0����): ";
        cin >> idx;
        if (idx == 0) return;
        cout << "������Ҫ��ѯ�İ༶(0����): ";
        cin >> Class;
        if (Class == "0") return;
        string file_name = Class + "���Գɼ����а�.txt";
        if (data.generateClassRank(idx - 1, Class, (char *) file_name.data())) {
            cout << "���а��������ڱ�����Ŀ¼�� " << file_name << " �ļ���" << endl;
        } else {
            cout << "��Ĳ�ѯ�����������������" << endl;
        }
        system("pause");
    }

    //У�ɼ����а�
    void AchieveRankSchool() {
        int idx;
        cout << "�����뿼����(0����): ";
        cin >> idx;
        if (idx == 0) return;
        stringstream ss;
        ss << "��_" << idx << "_�ο��Գɼ����а�.txt";
        string file_name;
        ss >> file_name;
        if (data.generateSchoolRank(idx - 1, (char *) file_name.data())) {
            cout << "���а��������ڱ�����Ŀ¼�� " << file_name << " �ļ���" << endl;
        } else {
            cout << "��Ĳ�ѯ�����������������" << endl;
        }
        system("pause");

    }

    // �������а�
    void ProgressRank() {
        bool isFlag = true;
        while (isFlag) {
            system("cls");
            string cz;
            cout << "\t";
            cout << "  ************ �������а� *************" << endl;
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("**   1.�༶              2.ѧУ       **\n");
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("**   3.����                           **\n");
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("  ************************************\n");
            cout << "�������ѯ��ʽ" << endl;
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

    // �༶�������а�
    void progressRankClass() {
        string Class;
        int idx1, idx2;
        cout << "���������ο�����(0����): ";
        cin >> idx1;
        if (idx1 == 0) return;
        cin >> idx2;
        if (idx2 == 0) return;
        cout << "������Ҫ��ѯ�İ༶(0����): ";
        cin >> Class;
        if (Class == "0") return;
        stringstream ss;
        ss << Class << "��_" << idx1 << "_�����_" << idx2 << "_�ο��Գɼ��������а�.txt";
        string file_name;
        ss >> file_name;
        if (data.generateProgressClassRank(idx1 - 1, idx2 - 1, Class, (char *) file_name.data())) {
            cout << "���а��������ڱ�����Ŀ¼�� " << file_name << " �ļ���" << endl;
        } else {
            cout << "��Ĳ�ѯ�����������������" << endl;
        }
        system("pause");
    }

    // У�������а�
    void progressRankSchool() {
        int idx1, idx2;
        cout << "���������ο�����(0����): ";
        cin >> idx1;
        if (idx1 == 0) return;
        cin >> idx2;
        if (idx2 == 0) return;
        stringstream ss;
        ss << "��_" << idx1 << "_�����_" << idx2 << "_�ο��Գɼ��������а�.txt";
        string file_name;
        ss >> file_name;
        if (data.generateProgressSchoolRank(idx1 - 1, idx2 - 1, (char *) file_name.data())) {
            cout << "���а��������ڱ�����Ŀ¼�� " << file_name << " �ļ���" << endl;
        } else {
            cout << "��Ĳ�ѯ�����������������" << endl;
        }
        system("pause");
    }

    // �������а�
    void ExcellentRank() {
        bool isFlag = true;
        while (isFlag) {
            system("cls");
            string cz;
            cout << "\t";
            cout << "  ************ �������а� *************" << endl;
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("**   1.�༶              2.ѧУ       **\n");
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("**   3.����                           **\n");
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("  ************************************\n");
            cout << "�������ѯ��ʽ" << endl;
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

    // �༶�������а�
    void ExcellentClassRank() {
        int idx;
        string Class;
        int line;
        cout << "�����뿼����(0�˳�): ";
        cin >> idx;
        if (idx == 0) return;
        cout << "�������ѯ�༶��0�˳�): ";
        cin >> Class;
        if (Class == "0") return;
        cout << "���������������(0�˳�): ";
        cin >> line;
        if (line == 0) return;
        stringstream ss;
        ss << Class << "��_" << idx << "_�ο��Գɼ��������а�.txt";
        string file_name;
        ss >> file_name;
        if (data.generateExcellentClasstRank(idx - 1, Class, line, (char *) file_name.data())) {
            cout << "���а��������ڱ�����Ŀ¼�� " << file_name << " �ļ���" << endl;
        } else {
            cout << "��Ĳ�ѯ�����������������" << endl;
        }
        system("pause");
    }

    // У�������а�
    void ExcellentSchoolRank() {
        int idx;
        int line;
        cout << "�����뿼����(0�˳�): ";
        cin >> idx;
        if (idx == 0) return;
        cout << "���������������(0�˳�): ";
        cin >> line;
        if (line == 0) return;
        stringstream ss;
        ss << "��_" << idx << "_�ο��Գɼ��������а�.txt";
        string file_name;
        ss >> file_name;
        if (data.generateExcellentSchoolRank(idx - 1, line, (char *) file_name.data())) {
            cout << "���а��������ڱ�����Ŀ¼�� " << file_name << " �ļ���" << endl;
        } else {
            cout << "��Ĳ�ѯ�����������������" << endl;
        }
        system("pause");
    }

    // �ҿ����а�
    void HangSectionRank() {
        bool isFlag = true;
        while (isFlag) {
            system("cls");
            string cz;
            cout << "\t";
            cout << "  ************ �ҿ����а� *************" << endl;
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("**   1.�༶              2.ѧУ       **\n");
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("**   3.����                           **\n");
            cout << "\t ";
            printf("**                                    **\n");
            cout << "\t ";
            printf("  ************************************\n");
            cout << "�������ѯ��ʽ" << endl;
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

    // �༶У�ҿ����а�
    void HangSectionClassRank() {
        int idx;
        string Class;
        int line;
        cout << "�����뿼����(0�˳�): ";
        cin >> idx;
        if (idx == 0) return;

        cout << "������Ҫ��ѯ�İ༶(0�˳�): ";
        cin >> Class;
        if (Class == "0") return;

        cout << "������ҿƷ�����(0�˳�): ";
        cin >> line;
        if (line == 0) return;
        stringstream ss;
        ss << Class << "��_" << idx << "_�ο��Գɼ��ҿ����а�.txt";
        string file_name;
        ss >> file_name;
        if (data.generateHangSectionClassRank(idx - 1, Class, line, (char *) file_name.data())) {
            cout << "���а��������ڱ�����Ŀ¼�� " << file_name << " �ļ���" << endl;
        } else {
            cout << "��Ĳ�ѯ�����������������" << endl;
        }
        system("pause");
    }

    // У�ҿ����а�
    void HangSectionSchoolRank() {
        int idx;
        int line;
        cout << "�����뿼����(0�˳�): ";
        cin >> idx;
        if (idx == 0) return;
        cout << "������ҿƷ�����(0�˳�): ";
        cin >> line;
        if (line == 0) return;
        stringstream ss;
        ss << "��_" << idx << "_�ο��Գɼ��ҿ����а�.txt";
        string file_name;
        ss >> file_name;
        if (data.generateHangSectionSchoolRank(idx - 1, line, (char *) file_name.data())) {
            cout << "���а��������ڱ�����Ŀ¼�� " << file_name << " �ļ���" << endl;
        } else {
            cout << "��Ĳ�ѯ�����������������" << endl;
        }
        system("pause");
    }

    // ʹ��˵��
    void Introduction() {
        system("cls");
        cout << "1.��������" << endl;
        cout << "2.�������ݹ�������" << endl; 
		cout << "3.һ���Ե���ȫ�����ݣ������й̶���ʽ���������������Ŀ¼��ʾ�����ݸ�ʽ��" << endl;
        cout << "4.����Ž�����ع��ܲ���" << endl;
        system("pause");
    }

};

int main() {

    System s;
    s.start();

}
