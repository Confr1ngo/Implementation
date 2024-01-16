#include<bits/stdc++.h>
using namespace std;
const string days[8]={"",
	"Monday","Tuesday","Wednesday","Thursday",
	"Friday","Saturday","Sunday"
};
struct Statement{
	string str,name;
	int type;
	Statement():str(""),name(""),type(0){}
	~Statement(){}
	const Statement& operator=(const Statement& s){
		type=s.type;str=s.str;return *this;
	}
	const bool valid(const string guilty,const string day){
		if (type==0) assert(!"Uninitialized?");
		if (type==1) return guilty==name;
		if (type==2) return guilty!=name;
		if (type==3) return guilty==str;
		if (type==4) return guilty!=str;
		if (type==5) return str==day;
		assert(!"It will never run here!");
		return false;
	}
}s[1010];
string a[1010];
int n,m,p;
void fastIO(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
}
int get_type(string s){
	s.erase(0,s.find(":")+2);
	if (s=="I am guilty.") return 1;
	if (s=="I am not guilty.") return 2;
	for (int i=1;i<=7;i++){
		if (s=="Today is "+days[i]+".") return 5;
	}
	for (int i=1;i<=n;i++){
		if (s==a[i]+" is guilty.") return 3;
		if (s==a[i]+" is not guilty.") return 4;
	}
	return 0;
}
set<int>ans;
signed main(){
	fastIO();
	cin>>n>>m>>p;
	string temp;
	getline(cin,temp);
	for (int i=1;i<=n;i++){
		getline(cin,a[i]);
		while (a[i].back()=='\r' || a[i].back()=='\n'){
			a[i].pop_back();
		}
	}
	for (int i=1;i<=p;i++){
		getline(cin,temp);
		while (temp.back()=='\r' || temp.back()=='\n'){
			temp.pop_back();
		}
		int type=get_type(temp);
		if (!type){
			p--;i--;
			continue;
		}
		s[i].type=type;
		s[i].name=temp.substr(0,temp.find(":"));
		temp.erase(0,temp.find(":")+2);
		if (type==3 || type==4){
			s[i].str=temp.substr(0,temp.find(" "));
		}
		if (type==5){
			temp.erase(--temp.end());
			s[i].str=temp.substr(temp.rfind(" ")+1);
		}
	}
	for (int i=1;i<=n;i++){
		for (int j=1;j<=7;j++){
			int fakecnt=0,unknowncnt=0;
			bool flag=true;
			for (int k=1;k<=n;k++){
				int stat=2;
				for (int l=1;l<=p;l++){
					if (s[l].name==a[k]){
						if (s[l].valid(a[i],days[j])){
							if (stat==2) stat=1;
							else if (!stat){
								flag=false;
								break;
							}
						}
						else{
							if (stat==2) stat=0;
							else if (stat==1){
								flag=false;
								break;
							}
						}
					}
					if (!flag) break;
				}
				if (!flag) break;
				if (!stat) fakecnt++;
				if (stat==2) unknowncnt++;
			}
			if (!flag) continue;
			if (fakecnt<=m && m<=fakecnt+unknowncnt){
				ans.emplace(i);
			}
		}
	}
	if (!ans.size()) cout<<"Impossible\n";
	else if ((int)ans.size()==1) cout<<a[*ans.begin()]<<"\n";
	else cout<<"Cannot Determine\n";
	return 0;
}