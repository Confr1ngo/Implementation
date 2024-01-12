#include<bits/stdc++.h>
using namespace std;
int var[10000010],cnt;
unordered_map<string,int>mp,offset;
map<int,int>jmp;
bool is_number(string s){
	for (char ch:s){
		if (ch<'0' || ch>'9') return false;
	}
	return true;
}
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
					else assert(!"Invalid operator!");
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
					else assert(!"Invalid operator!");
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
		else assert(!"Invalid operator!");
	}
	return num.top();
}
int eval(string s){
	s=remove_rubbish_info(s);
	while (s.find("[")!=string::npos){
		int l=s.find("["),r=s.find("]");
		int num=eval(s.substr(l+1,r-l-1));
		string name="";
		int pos=l-1;
		while (pos>=0 && s[pos]>='a' && s[pos]<='z'){
			name=s[pos]+name;
			pos--;
		}
		pos++;
		int val=var[mp[name]+num-offset[name]];
		string val_s=to_string(val);
		if (pos && s[pos-1]=='-' && val<0) val_s="(0"+val_s+")";
		s.replace(pos,r-pos+1,val_s);
	}
	for (int i=0;i<(int)s.size();i++){
		if (s[i]>='a' && s[i]<='z'){
			int l=i,r=i;
			string name="";
			while (r<(int)s.size() && s[r]>='a' && s[r]<='z'){
				name+=s[r];
				r++;
			}
			r--;
			int val=var[mp[name]];
			string val_s=to_string(val);
			if (l && s[l-1]=='-' && val<0) val_s="(0"+val_s+")";
			s.replace(l,r-l+1,val_s);
			i=l+(int)val_s.size()-1;
			continue;
		}
	}
	return numeral_eval(s);
}
bool binary_compare(string op,int a,int b){
	if (op=="lt") return a<b;
	if (op=="gt") return a>b;
	if (op=="le") return a<=b;
	if (op=="ge") return a>=b;
	if (op=="eq") return a==b;
	if (op=="neq") return a!=b;
	assert(!"It will never run here!");
}
bool has_null_content(string s){
	for (char ch:s){
		if (ch=='#') return true;
		if (ch!=' ' && ch!='\n' && ch!='\t' && ch!='\r') return false;
	}
	return true;
}
void execute_command(string s){
	if (has_null_content(s)) return;
	int pos=0;
	string op="";
	while (s[pos]==' ') pos++;
	while (s[pos]!=' ') op+=s[pos++];
	s.erase(0,pos);
	s=remove_rubbish_info(s);
	if (op==":yosoro"){
		cout<<eval(s)<<' ';
	}
	else if (op==":set"){
		string name=s.substr(0,s.find(','));
		s.erase(0,s.find(',')+1);
		if (name.find("[")!=string::npos){
			string bs=name.substr(0,name.find("["));
			int idx=eval(name.substr(name.find("[")+1,name.size()-2-name.find("[")));
			var[mp[bs]+idx-offset[bs]]=eval(s);
		}
		else{
			var[mp[name]]=eval(s);
		}
	}
	else{
		// cerr<<op<<"\n";
		assert(!"Invalid command!");
	}
}
vector<string>full;
void execute(int l,int r){
	int pos=l;
	while (pos<=r){
		// cerr<<pos<<" "<<full[pos]<<" "<<has_null_content(full[pos])<<endl;
		if (has_null_content(full[pos])){
			pos++;
			continue;
		}
		string str=full[pos];
		if (str.find("{")!=string::npos){
			if (str.find("vars")!=string::npos){
				while (++pos){
					str=full[pos];
					if (str.find("}")!=string::npos) break;
					string info=remove_rubbish_info(str);
					int pos=info.find(":");
					string name=info.substr(0,pos);
					string val=info.substr(pos+1);
					// cerr<<'"'<<name<<'"'<<endl<<'"'<<val<<'"'<<endl<<endl;
					if (val=="int") var[mp[name]=cnt++]=0;
					else{
						string range=val.substr(val.find(",")+1);
						range.erase(range.size()-1,1);
						range=remove_rubbish_info(range);
						int l=str2int(range.substr(0,range.find("..")));
						int r=str2int(range.substr(range.find("..")+2));
						// cerr<<l<<" "<<r<<" "<<cnt<<endl;
						mp[name]=cnt;
						for (int i=cnt;i<=cnt+r-l;i++){
							var[i]=0;
						}
						offset[name]=l;
						cnt+=(r-l+1);
					}
				}
				pos++;
			}
			else if (str.find("ihu")!=string::npos){
				string op,val1,val2;
				str.erase(0,str.find("ihu")+3);
				op=str.substr(0,str.find(","));
				str.erase(0,str.find(",")+1);
				val1=str.substr(0,str.find(","));
				str.erase(0,str.find(",")+1);
				val2=str;
				op=remove_rubbish_info(op);
				val1=remove_rubbish_info(val1);
				val2=remove_rubbish_info(val2);
				if (binary_compare(op,eval(val1),eval(val2))){
					execute(pos+1,jmp[pos]-1);
				}
				pos=jmp[pos]+1;
			}
			else if (str.find("while")!=string::npos){
				string op,val1,val2;
				str.erase(0,str.find("while")+5);
				op=str.substr(0,str.find(","));
				str.erase(0,str.find(",")+1);
				val1=str.substr(0,str.find(","));
				str.erase(0,str.find(",")+1);
				val2=str;
				op=remove_rubbish_info(op);
				val1=remove_rubbish_info(val1);
				val2=remove_rubbish_info(val2);
				while (binary_compare(op,eval(val1),eval(val2))){
					execute(pos+1,jmp[pos]-1);
				}
				pos=jmp[pos]+1;
			}
			else if (str.find("hor")!=string::npos){
				string va,val1,val2;
				str.erase(0,str.find("hor")+3);
				va=str.substr(0,str.find(","));
				str.erase(0,str.find(",")+1);
				val1=str.substr(0,str.find(","));
				str.erase(0,str.find(",")+1);
				val2=str;
				va=remove_rubbish_info(va);
				val1=remove_rubbish_info(val1);
				val2=remove_rubbish_info(val2);
				int v1=eval(val1),v2=eval(val2);
				for (var[mp[va]]=v1;var[mp[va]]<=v2;var[mp[va]]++){
					execute(pos+1,jmp[pos]-1);
				}
				pos=jmp[pos]+1;
			}
			else assert(!"Invalid operator!");
		}
		else{
			execute_command(str);
			pos++;
		}
	}
}
signed main(){
	string str;
	while (getline(cin,str)){
		full.emplace_back(str);
	}
	stack<int>stk;
	for (int i=0;i<(int)full.size();i++){
		if (full[i].find("{")!=string::npos){
			stk.push(i);
		}
		else if (full[i].find("}")!=string::npos){
			jmp[stk.top()]=i;
			stk.pop();
		}
	}
	execute(0,full.size()-1);
	return 0;
}