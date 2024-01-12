#include<bits/stdc++.h>
using namespace std;
unordered_map<string,int>mp;
map<int,int>jmp;
int str2int(string s){
	int res=0;
	for (char ch:s){
		res=res*10+ch-'0';
	}
	return res;
}
string remove_rubbish_info(string s){
	string res="";
	for (char ch:s){
		if (ch=='#') return res;
		if (ch!=' ' && ch!='\t') res+=ch;
	}
	return res;
}
int numeral_eval(string s){
	if (s[0]=='-') s="0"+s;
	// cerr<<"evaling "<<s<<endl;
	stack<int>num;
	stack<char>op;
	map<char,int>prio;
	prio['+']=1;
	prio['-']=1;
	prio['*']=2;
	prio['/']=2;
	prio['(']=0;
	prio[')']=0;
	int i=0;
	while (i<(int)s.size()){
		if (s[i]>='0' && s[i]<='9'){
			int sum=0;
			while (s[i]>='0' && s[i]<='9'){
				sum=sum*10+(s[i]-'0');
				i++;
			}
			num.push(sum);
		}
		else{
			if (s[i]=='(') op.push(s[i]);
			else if (s[i]==')'){
				while (op.size() && op.top()!='('){
					char op_now=op.top();op.pop();
					int b=num.top();num.pop();
					int a=num.top();num.pop();
					if (op_now=='+') num.push(a+b);
					else if (op_now=='-') num.push(a-b);
					else if (op_now=='*') num.push(a*b);
					else if (op_now=='/') num.push(a/b);
					// else assert(!"Invalid operator!");
				}
				op.pop();
			}
			else{
				while (op.size() && prio[op.top()]>=prio[s[i]]){
					char op_now=op.top();op.pop();
					int b=num.top();num.pop();
					int a=num.top();num.pop();
					if (op_now=='+') num.push(a+b);
					else if (op_now=='-') num.push(a-b);
					else if (op_now=='*') num.push(a*b);
					else if (op_now=='/') num.push(a/b);
					// else assert(!"Invalid operator!");
				}
				op.push(s[i]);
			}
			i++;
		}
	}
	while (op.size()){
		char op_now=op.top();op.pop();
		int b=num.top();num.pop();
		int a=num.top();num.pop();
		if (op_now=='+') num.push(a+b);
		else if (op_now=='-') num.push(a-b);
		else if (op_now=='*') num.push(a*b);
		else if (op_now=='/') num.push(a/b);
		// else assert(!"Invalid operator!");
	}
	return num.top();
}
int eval(string s){
	s=remove_rubbish_info(s);
	for (int i=0;i<(int)s.size();i++){
		if (s[i]>='a' && s[i]<='z'){
			int l=i,r=i;
			string name="";
			while (r<(int)s.size() && s[r]>='a' && s[r]<='z'){
				name+=s[r];
				r++;
			}
			r--;
			int val=mp[name];
			string val_s=to_string(val);
			if (l && val<0) val_s="(0"+val_s+")";
			s.replace(l,r-l+1,val_s);
			i=l+(int)val_s.size()-1;
			continue;
		}
	}
	// cerr<<s<<endl;
	return numeral_eval(s);
}
bool has_null_content(string s){
	for (char ch:s){
		if (ch=='#') return true;
		if (ch!=' ' && ch!='\n' && ch!='\t' && ch!='\r') return false;
	}
	return true;
}
int execute_command(string s){
	// assert(s.find("end")==string::npos);
	// assert(s.find("loop")==string::npos);
	if (has_null_content(s)) return 2;
	if (s=="continue") return 1;
	if (s=="break") return 0;
	if (s.find("=")!=string::npos){
		string v=remove_rubbish_info(s.substr(0,s.find("=")));
		s.erase(0,s.find("=")+1);
		int val=eval(s);
		mp[v]=val;
	}
	else{
		// cerr<<s<<endl;
		int pos=0;
		string op="";
		while (s[pos]==' ') pos++;
		while (s[pos]!=' ') op+=s[pos++];
		s.erase(0,pos);
		s=remove_rubbish_info(s);
		cout<<eval(s)<<'\n';
	}
	return 2;
}
vector<string>full;
bool execute(int l,int r){
	int pos=l;
	while (pos<=r){
		// cerr<<pos<<" "<<full[pos]<<" "<<has_null_content(full[pos])<<endl;
		if (has_null_content(full[pos])){
			pos++;
			continue;
		}
		string str=full[pos];
		if (str.find("loop")!=string::npos){
			str.erase(0,str.find("loop")+4);
			int times=eval(str);
			if (pos+1<=jmp[pos]-1){
				for (int i=1;i<=times;i++){
					if (!execute(pos+1,jmp[pos]-1)) break;
				}
			}
			pos=jmp[pos]+1;
		}
		else{
			int res=execute_command(str);
			if (res==0) return false;
			if (res==1) return true;
			pos++;
		}
	}
	return true;
}
vector<string>split_by(string s,char c){
	vector<string>res={};
	string cur="";
	for (int i=0;i<(int)s.size();i++){
		if (s[i]==c){
			if (cur!=""){
				res.emplace_back(cur);
				cur="";
			}
		}
		else cur+=s[i];
	}
	if (cur!=""){
		res.emplace_back(cur);
	}
	return res;
}
void init(){
	string str,concat="";
	while (getline(cin,str)){
		concat+=str+" ";
	}
	vector<string>temp=split_by(concat,' ');
	for (int i=0;i<(int)temp.size();i++){
		if (temp[i]=="loop" || temp[i]=="write"){
			full.emplace_back(temp[i]+" "+temp[i+1]);
			i++;
		}
		else full.emplace_back(temp[i]);
	}
	full.erase(full.begin());
	full.erase(--full.end());
}
signed main(){
	init();
	stack<int>stk;
	for (int i=0;i<(int)full.size();i++){
		if (full[i].find("loop")!=string::npos){
			stk.push(i);
		}
		else if (full[i].find("end")!=string::npos){
			jmp[stk.top()]=i;
			stk.pop();
		}
	}
	execute(0,full.size()-1);
	return 0;
}