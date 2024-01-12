#include<bits/stdc++.h>
using namespace std;
set<string>reserved={"and","break","do","else","elseif","end","false","for","function","if","in","local","nil","not","or","repeat","return","then","true","not","until","while"};
set<string>symbol={"+","-","*","/","%","^","#","==",">=","<=",">","<","~=","(",")","{","}","[","]",";",":",",",".","..","...","="};
void fastIO(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
}
signed main(){
	fastIO();
	string s;
	while (getline(cin,s)){
		while (s.size()){
			int pos=0;
			while (pos<(int)s.size() && (s[pos]==' ' || s[pos]=='\t')) pos++;
			if (pos==(int)s.size()) break;
			s.erase(0,pos);
			if ((int)s.size()>1 && s.substr(0,2)=="--") break;
			if (s[0]=='"' || s[0]=='\''){
				cout<<"[STRING] "<<s[0];
				int pos=1;
				while (true){
					if (s[pos]=='\\'){
						cout<<s[pos]<<s[pos+1];
						pos+=2;
					}
					else if (s[pos]==s[0]){
						cout<<s[0]<<'\n';
						break;
					}
					else{
						cout<<s[pos];
						pos++;
					}
				}
				s.erase(0,pos+1);
			}
			else if ((s[0]>='a' && s[0]<='z') || (s[0]>='A' && s[0]<='Z') || s[0]=='_'){
				string str="";
				pos=0;
				while ((pos<(int)s.size()) && ((s[pos]>='a' && s[pos]<='z') || (s[pos]>='A' && s[pos]<='Z') || (s[pos]>='0' && s[pos]<='9') || s[pos]=='_')){
					str+=s[pos];
					pos++;
				}
				if (reserved.count(str)){
					cout<<"[RESERVED] "<<str<<'\n';
				}
				else{
					cout<<"[NAME] "<<str<<'\n';
				}
				s.erase(0,pos);
			}
			else if ((s[0]<'0' || s[0]>'9') && s[0]!='.'){
				string now="";
				while (s.size() && ((s[0]<'0' || s[0]>'9') && (s[0]<'a' || s[0]>'z') && (s[0]<'A' || s[0]>'Z') && s[0]!='_' && s[0]!='.' && s[0]!='"' && s[0]!='\'' && s[0]!=' ')){
					if (now=="") now+=s[0];
					else if (!symbol.count(now+s[0])){
						cout<<"[SYMBOL] "<<now<<'\n';
						now="";now+=s[0];
					}
					else now+=s[0];
					s.erase(0,1);
				}
				if (now!="") cout<<"[SYMBOL] "<<now<<'\n';
			}
			else if (s.size()>2 && s.substr(0,3)=="..."){
				cout<<"[SYMBOL] ...\n";
				s.erase(0,3);
			}
			else if (s.size()>1 && s.substr(0,2)==".."){
				cout<<"[SYMBOL] ..\n";
				s.erase(0,2);
			}
			else if (s[0]=='.' && (s[1]<'0' || s[1]>'9')){
				cout<<"[SYMBOL] .\n";
				s.erase(0,1);
			}
			else if (s.size()>1 && s[0]=='0' && (s[1]=='x' || s[1]=='X')){
				int pos=2;
				string str="0";str+=s[1];
				while (pos<(int)s.size() && ((s[pos]>='0' && s[pos]<='9') || (s[pos]>='a' && s[pos]<='f') || (s[pos]>='A' && s[pos]<='F'))){
					str+=s[pos];
					pos++;
				}
				s.erase(0,pos);
				cout<<"[NUMBER] "<<str<<'\n';
			}
			else{
				cout<<"[NUMBER] ";
				while (s.size() && (s[0]>='0' && s[0]<='9')){
					cout<<s[0];
					s.erase(0,1);
				}
				if (!s.size()){
					cout<<"\n";
					break;
				}
				if (s[0]=='.'){
					cout<<s[0];
					s.erase(0,1);
				}
				while (s.size() && (s[0]>='0' && s[0]<='9')){
					cout<<s[0];
					s.erase(0,1);
				}
				if (s[0]!='e'){
					while (s.size() && (s[0]>='0' && s[0]<='9')){
						cout<<s[0];
						s.erase(0,1);
					}
				}
				else{
					cout<<s[0];
					s.erase(0,1);
					if (s[0]=='+' || s[0]=='-'){
						cout<<s[0];
						s.erase(0,1);
					}
					while (s.size() && (s[0]>='0' && s[0]<='9')){
						cout<<s[0];
						s.erase(0,1);
					}
				}
				cout<<'\n';
			}
		}
		cout<<"[EOL]\n";
	}
	return 0;
}