
// termproject.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include<cstdio>
#include <sstream>
#include <locale.h>
using namespace std;
class fileclass {

private:
    static fileclass* instances;
    int log_val;
    fileclass(int v = 0) {
        log_val = v;
    }
public:
    static fileclass* instance() {
        if (!instances)
            instances = new fileclass;
        return instances;
    }
    int get_user() {
        return log_val;
    }
    void set_user(int v) {
        log_val = v;
    }
    std::vector<std::string> vecword; // 단어로 나눈 벡터
    std::vector<std::string> result; // 단어로 나워서 문장으로 만든 벡터
    std::string str = "";
    char c;
    int linenum = 0;
    string strss = "";
    string stringbuffer;
    void savefile() { // 단어로 나눠 바이트로 자르기 처음
        locale::global(locale("ko_kr.utf-8"));
        ifstream file2("C:\\Users\\default.DESKTOP-VP765EN\\Desktop\\test.txt");
        string sinput = "";
        string sinput2 = "";

        while (file2.peek() != EOF) {
            getline(file2, sinput2);
            sinput += sinput2;
        }
        file2.close();
        std::vector<std::string> s1 = makevector(sinput);
        std::vector<std::string> s2 = makeresult(s1);
        result = reset(s2);
    }
    std::vector<std::string> makevector(string vec) { // 문자열을 단어벡터로
        std::vector<std::string> vecstr;
        istringstream ssa(vec);
        string stringbuffer2;
        while (getline(ssa, stringbuffer2, ' ')) {
            vecstr.push_back(stringbuffer2);
        }
        return vecstr;
    }
    std::vector<std::string> makeresult(std::vector<std::string> vecstr) { // 단어벡터를 문장벡터로
        std::vector<std::string> vvec; // 문장벡터
        string str = "";
        for (int i = 0; i < vecstr.size() - 1; i++) {
            str += vecstr[i] + " ";
            if (i == vecstr.size() - 2) { // 마지막 전 원소 비교
                if ((str + vecstr[vecstr.size() - 1]).size() >= 75) { // 마지막 원소가 다음줄로 넘어감
                    vvec.push_back(str);
                    vvec.push_back(vecstr[vecstr.size() - 1]);
                }
                else { // 마지막 원소가 같은 줄에 출력
                    str += vecstr[vecstr.size() - 1] + " ";
                    vvec.push_back(str);
                }
            }
            else if ((str + vecstr[i + 1]).size() >= 75 && i != vecstr.size() - 1) { // 클 때 
                vvec.push_back(str);
                str = "";
            }
        }
        return vvec;
    }

    void makefile(vector<std::string> rvec) { // result출력, 벡터로 받은거 파일에 출력
        locale::global(locale("ko_kr.utf-8"));
        std::ofstream file;
        file.open("C:\\Users\\default.DESKTOP-VP765EN\\Desktop\\test.txt");
        if (file.is_open()) {
            for (int w = 0; w < rvec.size(); w++) {
                file << rvec[w] << endl;
            }
            file.close();
        }
    }
    std::vector<std::string>  reset(std::vector<std::string> strvec) {
        std::vector<std::string> vec1; // 단어벡터
        std::vector<std::string> vec2; // 문장벡터
        string strnull = "";
        for (int i = 0; i < strvec.size(); i++) {
            strnull += strvec[i]; // 한문장으로 만들기
        }
        vec1 = makevector(strnull);
        vec2 = makeresult(vec1);
        return vec2;
    }
    bool isnumber(const string& str) {
        for (char const& c : str) {
            if (std::isdigit(c) == 0)
                return false;
        }
        return true;
    }

};
fileclass* fileclass::instances = 0;
void user(void) {
    fileclass::instance()->set_user(1);
}
int main() {
    fileclass* f = fileclass::instance();
    f->savefile();
    std::cout << "n : next page, p : previous page, i : insert, d : delete, c : change, s : search, t : save and quit" << endl;
    string inputStr;
    std::cout << "input : ";
    std::cin >> inputStr;
    string mode;
    int pagenum = 0;
    mode = inputStr.substr(0, 1);
    int i1;
    int i2;
    string s1;
    string s2;
    int check = 1;
    int checkfirst = 0;

    std::vector<string> v1 = f->result;
    while (1) {
        string print = ""; // error
        mode = inputStr.substr(0, 1);
        string newinput;
        if (inputStr.size() > 1)
            newinput = inputStr.substr(2, inputStr.size() - 3);
        istringstream ss(newinput);
        string stringbuffer;
        vector<string> input;
        while (getline(ss, stringbuffer, ',')) {
            input.push_back(stringbuffer);
        }
        if ((mode == "i" || mode == "d" || mode == "s" || mode == "c")) { // 인자가 필요한 mode
            if ((inputStr.substr(1, 1) != "(") || (inputStr.substr(inputStr.size() - 1, 1) != ")")) {
                print = "ERROR! Please type it again!";
            }
            int count = 1;
            if (mode != "s") {
                if (mode == "i" && input.size() == 3) { //insert ok
                    std::vector<string> vectemp;
                    std::stringstream ssint(input[0]);
                    ssint >> i1;
                    std::stringstream ssint2(input[1]);
                    ssint2 >> i2;
                    if (!f->isnumber(input[0]) || i1 > 20 || !f->isnumber(input[1])) {
                        print = "ERROR! Please type it again!";
                    }
                    s1 = input[2];
                    if (s1.size() > 75)
                        print = "ERROR! Please type it again!";
                    if (print != "ERROR! Please type it again!") {
                        vectemp = f->makevector(v1[pagenum + i1 - 1]);
                        if (i2 > vectemp.size()) {
                            print = "ERROR! Please type it again!";
                        }
                        else {
                            vector<std::string>::iterator it = vectemp.begin();
                            it = vectemp.insert(it + i2, s1);
                        }
                    }
                    string temps = "";
                    if (print != "ERROR! Please type it again!") {
                        for (int i = 0; i < vectemp.size(); i++) {
                            temps += vectemp[i] + " "; // 양식 다시
                        }
                        v1[i1 - 1] = temps;
                        v1 = f->reset(v1);
                    }
                }
                else if (mode == "d" && input.size() == 2) { // delete ok
                    std::vector<string> vectemp;
                    std::stringstream ssint(input[0]);
                    ssint >> i1;
                    std::stringstream ssint2(input[1]);
                    ssint2 >> i2;
                    if (!f->isnumber(input[0]) || !f->isnumber(input[1])) {
                        print = "ERROR! Please type it again!";
                    }
                    if (print != "ERROR! Please type it again!") {
                        vectemp = f->makevector(v1[pagenum + i1 - 1]);
                        if (vectemp.size() < i2 || i1 > 20) {
                            print = "ERROR! Please type it again!";
                        }
                        else
                            vectemp.erase(vectemp.begin() + i2 - 1, vectemp.begin() + i2);
                    }
                    if (print != "ERROR! Please type it again!") {
                        string temps = "";
                        for (int i = 0; i < vectemp.size(); i++) {
                            temps += vectemp[i] + " ";
                        }
                        v1[i1 - 1] = temps; // 양식 다시
                        v1 = f->reset(v1);
                    }
                }
                else if (mode == "c" && input.size() == 2) { // change ok
                    int count = 0;
                    s1 = input[0];
                    s2 = input[1];
                    if (s1.size() > 75 || s2.size() > 75)
                        print = "ERROR! Please type it again!";
                    if (print != "ERROR! Please type it again!") {
                        std::vector<string> vectemp;
                        for (int i = 0; i < f->result.size(); i++) {
                            vectemp = f->makevector(v1[i]);
                            for (int j = 0; j < vectemp.size(); j++) {
                                if (vectemp[j] == s1) {
                                    vectemp[j] = s2;
                                    count++;
                                }
                            }
                            if (count == 0) {
                                print = "ERROR! Please type it again!";
                            }
                            string temps = "";
                            for (int w = 0; w < vectemp.size(); w++) {
                                temps += vectemp[w] + " ";
                            }
                            v1[i] = temps; // 양식다시
                        }
                    }
                    v1 = f->reset(v1);
                }
                else {
                    print = "ERROR! Please type it again!";
                }
            }
            if (input.size() == 1 && mode == "s") { // s일 때
                s1 = newinput;
                std::vector<string> vectemp;
                int check = 0;
                int count = 0;
                for (int i = 0; i < v1.size(); i++) {
                    vectemp = f->makevector(v1[i]);
                    for (int d = 0; d < vectemp.size(); d++) {
                            if (vectemp[d] == s1 && check == 0) {
                                check = 1;
                                count++;
                                pagenum += i;
                            }
                    }
                }
                if (count == 0) {
                    print = "ERROR! Please type it again!";
                }
                v1 = f->reset(v1);
            }
            if (print != "ERROR! Please type it again!") {
                int t = 0;
                for (int i = pagenum; i < 20 + pagenum; i++) {
                    if (i < v1.size()) {
                        std::cout << " " << t + 1 << "| " << v1[i] << "\n";
                        t++;
                    }
                }
            }
        }
        else if (mode == "p") { //ok
            if (pagenum - 20 < 0) {
            print = "first page";
                int t = 0;
                for (int i = 0; i < 20; i++) {
                    std::cout << " " << t + 1 << "| " << v1[i] << "\n";
                    t++;
                }             
            }
            else if (pagenum > 0) {
                pagenum -= 20;
                int t = 0;
                for (int j = pagenum; j < 20 + pagenum; j++) {
                    if (j < v1.size() && v1[j].size() != 0) {
                        std::cout << " " << t + 1 << "| " << v1[j] << "\n";
                        t++;
                    }
                }
            }
            else if (pagenum == 0) {
                int t = 0;
                for (int i = pagenum; i < 20 + pagenum; i++) {
                    if (i < v1.size() && v1[i].size() != 0) {
                        std::cout << " " << t + 1 << "| " << v1[i] << "\n";
                        t++;
                    }
                }
                print = "first page";
            }
            else if (v1.size() - pagenum < 20) {
                int t = 0;
                for (int i = pagenum; i < v1.size(); i++) {
                    std::cout << " " << t + 1 << "| " << v1[i] << "\n";
                    t++;
                }
            }
        }
        else if (mode == "n") { // ok
            if (v1.size() - pagenum > 20) {
                pagenum += 20;
                int t = 0;
                for (int e = pagenum; e < 20 + pagenum; e++) {
                    if (e < v1.size() && v1[e].size() != 0) {
                        std::cout << " " << t + 1 << "| " << v1[e] << "\n";
                        t++;
                    }
                }
            }
            if (v1.size() - pagenum < 20) {
                int t = 0;
                for (int i = 20 - v1.size(); i < v1.size(); i++) {
                    std::cout << " " << t + 1 << "| " << v1[i] << "\n";
                    t++;
                }
            }
            else {
                print = "last page";
            }
        }
        else if (mode == "t" && inputStr == "t") { //ok
            f->makefile(v1);
            //저장 후 종료 구현
            break;
        }
        else { // 다른 알파벳
            print = "ERROR! Please type it again!";
        }
        if (mode != "t") {
            std::cout << print << endl;
            std::cout << "----------------------------------------------------------------------------------------------------" << endl;;
            std::cout << "n : next page, p : previous page, i : insert, d : delete, c : change, s : search, t : save and quit" << endl;
            std::cout << "input : ";
            std::cin >> inputStr;
            mode = inputStr.substr(0, 1);
        }
        else {
            print = "ERROR! Please type it again!";
        }
    }
}