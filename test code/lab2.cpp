#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<string.h>
#include<vector>
#include<stack>
#include<stdio.h> 
using namespace std;
void GetKeyWord(string s);
void level12(string a[]);
void level34();
void OutputLevel(int Level);
int keyword_num = 0,switch_num = 0,ifelse_num = 0;
int cnt1=0,cnt2=0,case_cnt=0,ie_num=0,iee_num=0;
int casenum[200] = { 0 };
string temp1[200];
string temp2[200];
vector <string> getWord;
string keyword[32] = {
	"auto","break","case","char","const","continue","default"
,"do","double","else","enum","extern","float","for","goto","if"
,"int","long","register","return","short","signed","sizeof","static"
,"struct","switch","typedef","union","unsigned","void","volatile","while" };
	
int main(){
	int level;
	string filename, temp;
	char buffer[1];
	cout << "please input file name:";
	cin >> filename;
	ifstream fin(filename.c_str());
	if (!fin){
		cout << "we can not open the file successfully" << endl;
	}
	else{
		while (getline(fin, temp)){         
			GetKeyWord(temp);
		}
		fin.close();     
	}
	level12(temp1);  
	level34();          
	cout << "please enter the input level you choose:";
	cin >> level;
	OutputLevel(level);
}	
//Extract keywords from the test.cpp	
void GetKeyWord(string s){
	int len=s.length();
	string word;
	int num=0;
	const char*p =s.data();
	for(int i=0;i<len;i++){
		if(p[i]=='{'){ num=1;
		}
		if(p[i]=='}'){ num=2;
		}
		//search for the letter of the code to extract
		if ((p[i] >= 'a' && p[i] <= 'z' || p[i] >= 'A' && p[i] <= 'Z')){ 
			word += p[i];  
		} 
		else{
			if(word==""){
				if(num==1)getWord.push_back("{");
				if(num==2)getWord.push_back("}");
				num=0;
				continue;
			}
			cnt1++;
			temp1[cnt1]=word;
			//judge elseif and else
			if (word == "else"){
				int j = i;
				while (p[j] == ' ' && j <= len)j++; 
				if (p[j] == 'i' && p[j + 1] == 'f'){
					getWord.push_back("else_if");
					i = j + 2;
					keyword_num++;
				}
				else getWord.push_back("else");

			}
			if (word == "if"){

				if (getWord.back() != "else")getWord.push_back("if");
			}
			if (num == 1)getWord.push_back("{");
			if (num == 2)getWord.push_back("}");
			num = 0;
			word = "";
			continue;
		}
	}
}
//calculate the switch and case number
void level12(string a[]){
	int i, j;
	for (i = 0; i < cnt1; i++){
		for (j = 0; j <= 31; j++){
			if (a[i] == keyword[j]){
				keyword_num++;       
				temp2[cnt2++] = a[i]; 
			}
		}
		if (a[i] == "switch"){
			switch_num++;
			case_cnt++;
		}
		if (a[i] == "case"){
			casenum[case_cnt]++;
		}
	}
}
//calculate the ifelse and if-elseif-else number 
void level34(){
	stack <string> s;
	stack <int> have_elseif;
	for (int i = 0; i < getWord.size(); i++)
	{
		if (getWord[i] == "{"){
			s.push("{");
			have_elseif.push(0);
		}
		else if (getWord[i] == "}"){
			while (s.top() != "{"){
				s.pop();
			}
			s.pop();
			have_elseif.pop();
		}
		else if (getWord[i] == "if"){
			s.push("if");
			have_elseif.pop();
			have_elseif.push(0);
		}
		else if (getWord[i] == "else_if"){
			have_elseif.pop();
			have_elseif.push(1);
		}
		else if (getWord[i] == "else"){
			if (have_elseif.top()){
				iee_num++;
			}
			else{
				ie_num++;
			}
			have_elseif.pop();
			have_elseif.push(0);
			while (s.top() != "if"){
				s.pop();
			}
			s.pop();
		}
	}
}
//choose the level of the lab2	
void OutputLevel(int Level){	
	if (Level == 1){
		cout << "total num: " << keyword_num << endl;
	}
	if (Level == 2){
		cout << "total num: " << keyword_num << endl;
		cout << "switch num: " << switch_num << endl;
		cout << "case num: ";
		for (int i = 1; i <= case_cnt; i++){
			cout << casenum[i] << " ";
		}
		cout << endl;
	}
	if (Level == 3){
		cout << "total num: " << keyword_num << endl;
		cout << "switch num: " << switch_num << endl;
		cout << "case num: ";
		for (int i = 1; i <= case_cnt; i++){
			cout << casenum[i] << " ";
		}
		cout << endl;
		cout << "if-else num: " << ie_num << endl;
	}
	if (Level == 4){
		cout << "total num: " << keyword_num << endl;
		cout << "switch num: " << switch_num << endl;
		cout << "case num: ";
		for (int i = 1; i <= case_cnt; i++){
			cout << casenum[i] << " ";
		}
		cout << endl;
		cout << "if-else num: " << ie_num << endl;
		cout << "if-elseif-else num: " << iee_num << endl;
	}
}
