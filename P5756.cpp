#include<bits/stdc++.h>
using namespace std;
unordered_map<string,int>mp;
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
struct Line{
	string type,val;
	int id,v;
	Line():type(""),val(""),id(0),v(0){}~Line(){}
	Line(string _type,string _val,int _id,int _v):type(_type),val(_val),id(_id),v(_v){}
	friend bool operator<(const Line &l,const Line &r){
		return l.id<r.id;
	}
	const Line& operator=(const Line l){
		type=l.type;val=l.val;
		id=l.id;v=l.v;
		return *this;
	}
}l[110];
int n,cnt;
unordered_map<int,int> idx;
void fastIO(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
}
signed main(){
	idx.clear();
	mp.clear();
	fastIO();
	string s;
	while (getline(cin,s)){
		n++;
		l[n].id=str2int(s.substr(0,s.find(" ")));
		s.erase(0,s.find(" ")+1);
		if (s.find("?")!=string::npos){
			l[n].type="output";
			l[n].val=remove_rubbish_info(s);
			continue;
		}
		else if (s.find("+")!=string::npos){
			l[n].type="add";
			s=remove_rubbish_info(s);
			l[n].val=s.substr(0,s.find("+"));
			l[n].v=str2int(s.substr(s.find("+")+1));
			continue;
		}
		else if (s.find("IF")!=string::npos){
			l[n].type="if";
			s.erase(0,s.find(" ")+1);
			l[n].val=remove_rubbish_info(s.substr(0,s.find(" ")));
			s.erase(0,s.find(" ")+1);
			s.erase(0,s.find(" ")+1);
			l[n].v=str2int(s);
		}
		else if (s.find("GO")!=string::npos){
			l[n].type="goto";
			l[n].v=str2int(remove_rubbish_info(s.substr(s.find(" ")+1)));
		}
		else l[n].type="end";
	}
	sort(l+1,l+n+1);
	for (int i=1;i<=n;i++){
		idx[l[i].id]=i;
	}
	int pos=1;
	while (pos<=n){
		// cerr<<pos<<" "<<l[pos].id<<"\n";
		// for (int i=1;i<=INT_MAX/2;i++) i=i;
		if (l[pos].type=="goto"){
			pos=idx[l[pos].v];
			cnt++;
		}
		else if (l[pos].type=="end"){
			cout<<cnt+1<<'\n';
			return 0;
		}
		else if (l[pos].type=="add"){
			mp[l[pos].val]+=l[pos].v;
			pos++;cnt++;
		}
		else if (l[pos].type=="output"){
			pos++;cnt++;
		}
		else{
			string cond_v=l[pos].val.substr(0,l[pos].val.find("="));
			int cond_val=str2int(l[pos].val.substr(l[pos].val.find("=")+1));
			if (mp[cond_v]==cond_val) pos=idx[l[pos].v];
			else pos++;
			cnt++;
		}
		if (cnt>=10000000){
			cout<<"-1\n";
			return 0;
		}
	}
	cerr<<"Program ends without keyword END!\n";
	return 0;
}