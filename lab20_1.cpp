#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream fin(filename.c_str());
    string textline;
    char format[] = "%[^:]: %d %d %d";
    int a,b,c;
    char name[100];
    while(getline(fin, textline)){
        const char * textlineConverted = textline.c_str();
        sscanf(textlineConverted, format, name, &a, &b, &c);
        names.push_back(name);
        scores.push_back(a+b+c);
        grades.push_back(score2grade(a+b+c));
    }
    fin.close();
}

void getCommand(string &command,string &key){
    cout << "Please input your command: " ;
    char format[] = "%s %[^\n]";
    char d[100];
    char s[100];
    string text;
    getline(cin,text);
    sscanf(text.c_str(),format,d,s);
    command = d;
    key = s;
}

void searchName(vector<string> names,vector<int> scores,vector<char> grades,string key){
    cout << "---------------------------------\n";
    for (unsigned int i=0;i<names.size();i++) {
        if (toUpperStr(names[i]) == key) {
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            cout << "---------------------------------\n";
            return;
        }
    }
    cout << "Cannot found." << "\n";
    cout << "---------------------------------\n"; 
}

void searchGrade(vector<string> names,vector<int> scores,vector<char> grade,string key){
    unsigned int check=0;
    cout<<"---------------------------------\n";
    for(unsigned int i=0;i<scores.size();i++){
        char keyy=key[0];
        if(keyy == grade[i]){
         printf("%s (%d)\n",names[i].c_str(),scores[i]);
        }else{
            check++;
        }
    }

    if(check == scores.size()){
        cout<<"Cannot found.\n";
    }
    cout<<"---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}