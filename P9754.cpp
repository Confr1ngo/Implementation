#include<bits/stdc++.h>
using namespace std;
void fastIO(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
}
void fileIO(){
	const string probname="struct";
	const string suff_in ="in";
	const string suff_out="out";
	const string file_in =probname+"."+suff_in;
	const string file_out=probname+"."+suff_out;
	freopen(file_in.c_str(),"r",stdin);
	freopen(file_out.c_str(),"w",stdout);
}
inline long long fastmin(long long x,long long y){
	return (x<y? x:y);
}
inline long long fastmax(long long x,long long y){
	return (x>y? x:y);
}
map<string,vector<pair<string,string> > >strt;
map<string,pair<long long,long long> >sz;
map<string,pair<string,long long> >addr;
long long minAvailAddr;
int T;
inline void init(){
	sz["byte"]=make_pair(1,1);
	sz["short"]=make_pair(2,2);
	sz["int"]=make_pair(4,4);
	sz["long"]=make_pair(8,8);
}
inline bool isBasicType(string s){
	if (s=="byte") return true;
	if (s=="short") return true;
	if (s=="int") return true;
	if (s=="long") return true;
	return false;
}
inline vector<string> spl(string s){
	vector<string>result;
	string now="";
	for (int i=0;i<(int)s.size();i++){
		if (s[i]=='.'){
			result.emplace_back(now);
			now="";
		}
		else{
			now+=s[i];
		}
	}
	if (now!="") result.emplace_back(now);
	return result;
}
int main(){
	fastIO();
	init();cin>>T;
	while (T--){
		static int op;
		cin>>op;
		if (op==1){
			static long long align,sznow;
			static string name;
			static int n;
			align=1;sznow=0;
			cin>>name>>n;
			vector<pair<string,string> >temp;
			while (n--){
				static string s1,s2;
				cin>>s1>>s2;
				temp.emplace_back(make_pair(s1,s2));
				align=fastmax(align,sz[s1].second);
				if (sznow%sz[s1].second) sznow=(sznow/sz[s1].second+1)*sz[s1].second+sz[s1].first;
				else sznow+=sz[s1].first;
			}
			if (sznow%align) sznow=(sznow/align+1)*align;
			strt[name]=temp;
			sz[name]=make_pair(sznow,align);
			cout<<sznow<<" "<<align<<"\n";
		}
		else if (op==2){
			static long long startAddr;
			static string tp,name;
			cin>>tp>>name;
			if (minAvailAddr%sz[tp].second){
				startAddr=(minAvailAddr/sz[tp].second+1)*sz[tp].second;
			}
			else{
				startAddr=minAvailAddr;
			}
			cout<<startAddr<<"\n";
			addr[name]=make_pair(tp,startAddr);
			minAvailAddr=startAddr+sz[tp].first;
		}
		else if (op==3){
			static string element_raw;
			static long long nowAddr;
			static string typenow;
			cin>>element_raw;
			vector<string> obj=spl(element_raw);
			for (auto it=addr.begin();it!=addr.end();it++){
				if ((*it).first==obj[0]){
					typenow=(*it).second.first;
					nowAddr=(*it).second.second;
					break;
				}
			}
			for (int i=1;i<(int)obj.size();i++){
				for (auto j:strt[typenow]){
					if (j.second==obj[i]){
						if (nowAddr%sz[j.first].second){
							nowAddr=(nowAddr/sz[j.first].second+1)*sz[j.first].second;
						}
						typenow=j.first;
						break;
					}
					else{
						if (nowAddr%sz[j.first].second){
							nowAddr=(nowAddr/sz[j.first].second+1)*sz[j.first].second;
						}
						nowAddr+=sz[j.first].first;
					}
				}
			}
			cout<<nowAddr<<"\n";
		}
		else{
			static long long targetAddr;
			static long long nowAddr;
			static string typenow;
			vector<string>path;
			cin>>targetAddr;
			if (targetAddr>=minAvailAddr){
				cout<<"ERR\n";
				continue;
			}
			nowAddr=0;
			string root="";
			static long long addrBegin0,addrEnd0;
			for (auto it=addr.begin();it!=addr.end();it++){
				addrBegin0=(*it).second.second;
				addrEnd0=addrBegin0+sz[(*it).second.first].first-1;
				if (addrBegin0<=targetAddr && targetAddr<=addrEnd0){
					typenow=((*it).second.first);
					nowAddr=((*it).second.second);
					root=(*it).first;
					path.emplace_back((*it).first);
					break;
				}
			}
			if (root==""){
				cout<<"ERR\n";
				continue;
			}
			bool outputErr=false;
			while (true){
				if (isBasicType(typenow)){
					static long long addrBegin,addrEnd;
					if (nowAddr%sz[typenow].second) addrBegin=(nowAddr/sz[typenow].second+1)*sz[typenow].second;
					else addrBegin=nowAddr;
					addrEnd=addrBegin+sz[typenow].first-1;
					if (!(addrBegin<=targetAddr && targetAddr<=addrEnd)){
						cout<<"ERR\n";
						outputErr=true;
					}
					break;
				}
				else{
					bool flag=false;
					for (pair<string,string> i:strt[typenow]){
						static long long addrBegin,addrEnd;
						if (nowAddr%sz[i.first].second) addrBegin=(nowAddr/sz[i.first].second+1)*sz[i.first].second;
						else addrBegin=nowAddr;
						addrEnd=addrBegin+sz[i.first].first-1;
						if (addrBegin<=targetAddr && targetAddr<=addrEnd){
							nowAddr=addrBegin;
							path.emplace_back(i.second);
							typenow=i.first;
							flag=true;
							break;
						}
						nowAddr=addrEnd+1;
					}
					if (!flag){
						cout<<"ERR\n";
						outputErr=true;
						break;						
					}
				}
			}
			if (!outputErr){
				for (int i=0;i<(int)path.size();i++){
					cout<<path[i];
					if (i!=(int)path.size()-1) cout<<".";
					else cout<<"\n";
				}
			}
		}
	}
	return 0;
}