#include<bits/stdc++.h>
using namespace std;
namespace Header{
	const long long inf64=0x3f3f3f3f3f3f3f3fll,Inf64=0x9f9f9f9f9f9f9f9fll,inf32=0x3f3f3f3f,Inf32=0x9f9f9f9f;
	template<typename T> struct Integral:public is_integral<T>{};
	template<> struct Integral<__int128_t>:public true_type{};  
	template<> struct Integral<__uint128_t>:public true_type{};
	template<typename T> struct FloatingPoint:public is_floating_point<T>{};
	template<> struct FloatingPoint<__float128>:public true_type{};
	inline bool is_invisible(char c){return (c<=32 || c>126);}
	template<typename T>inline void to_lower(T &x){for (char &i:x) if (i>='A' && i<='Z') i+='a'-'A';}
	template<typename T>inline void to_upper(T &x){for (char &i:x) if (i>='a' && i<='z') i-='a'-'A';}
	template<typename T>inline enable_if_t<Integral<T>::value,T> quickpow(T a,T b,T mod){T res=1;while (b){if (b&1) res=res*a%mod;a=a*a%mod;b>>=1;}return res;}
	template<typename T>inline enable_if_t<Integral<T>::value,T> getinv(T a,T mod){return quickpow(a,mod-2,mod);}
	template<typename T>inline enable_if_t<Integral<T>::value,T> lowbit(T x){return x&(~(x-1));}
	template<typename T>inline enable_if_t<Integral<T>::value,void> readmain(T &x){x=0;bool flag=1;char ch=getchar();while (ch<'0' || ch>'9'){if (ch=='-') flag=0;ch=getchar();}while (ch>='0' && ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}if (!flag) x=~(x-1);}
	template<typename T>inline enable_if_t<FloatingPoint<T>::value,void> readmain(T &x){x=0;bool flag=1;char ch=getchar();while (ch<'0' || ch>'9'){if (ch=='-') flag=0;ch=getchar();}while (ch>='0' && ch<='9'){x=x*10+ch-'0';ch=getchar();}if (ch=='.'){ch=getchar();T prec=1;while (ch>='0' && ch<='9'){x+=(prec/=10)*(ch-'0');ch=getchar();}}if (!flag) x=-x;}
	inline void readmain(string &x){char ch=getchar();x="";while (is_invisible(ch)) ch=getchar();while (!is_invisible(ch)){x+=ch;ch=getchar();}}
	inline void readmain(char &x){x=getchar();while (is_invisible(x)) x=getchar();}
	template<typename T>void read(T &x){readmain(x);}
	template<typename T,typename ...Ts>void read(T &x,Ts&... r){readmain(x);read(r...);}
	template<typename T>enable_if_t<Integral<T>::value,void> writemain(T x){if (x<0){x=~(x-1);putchar('-');}if (x>9) writemain(x/10);putchar(x%10+'0');}
	template<typename T>enable_if_t<FloatingPoint<T>::value,void> writemain(T x){if (x<0){x=-x;putchar('-');}int wid=15;x+=5e-16;__int128_t num=(__int128_t)x;writemain(num);putchar('.');x-=num;while (wid--){putchar((int)(x*=10)+'0');x-=(int)(x);}}
	inline void writemain(string x){for (char i:x) putchar(i);}
	inline void writemain(const char* x){int sz=strlen(x);for (int i=0;i<sz;i++) putchar(x[i]);}
	template<typename T>void write(T x){writemain(x);}
	template<typename T,typename ...Ts>void write(T x,Ts... r){writemain(x);write(r...);}
	inline void writeln(){putchar('\n');}
	template<typename T>void writeln(T x){writemain(x);putchar('\n');}
	template<typename T,typename ...Ts>void writeln(T x,Ts... r){writemain(x);putchar('\n');writeln(r...);}
	template<typename T>void writesp(T x){writemain(x);putchar(' ');}
	template<typename T,typename ...Ts>void writesp(T x,Ts... r){writemain(x);putchar(' ');writesp(r...);}
	template<typename T>void writesp(vector<T> v){for (T i:v) writesp(i);putchar('\n');}
	template<typename T> T fastmaxmain(T x,T y){return (x>y? x:y);}
	template<typename T> T fastmax(T x,T y){return fastmaxmain(x,y);}
	template<typename T,typename... Ts> T fastmax(T x,Ts... args){return fastmaxmain(x,fastmax(args...));}
	template<typename T> T fastminmain(T x,T y){return (x<y? x:y);}
	template<typename T> T fastmin(T x,T y){return fastminmain(x,y);}
	template<typename T,typename... Ts> T fastmin(T x,Ts... args){return fastminmain(x,fastmin(args...));}
	unsigned long long operator"" _kw(unsigned long long x){return x*10000000;}
	enum YesNoVariants{Capital,Lowercase,FirstCapital};
	inline void yesno(bool x,YesNoVariants variant=FirstCapital){
		if (variant==Capital) writeln(x? "YES":"NO");
		else if (variant==Lowercase) writeln(x? "yes":"no");
		else writeln(x? "Yes":"No");
	}
	template<typename T,size_t S,T mod>class combinatics_utility{
		private:
			vector<T> fact;
			vector<T> inv;
		public:
			inline void init(){
				fact.resize(S+10);
				inv.resize(S+10);
				fact[0]=1;
				for (int i=1;i<=(long long)S;i++) fact[i]=i*fact[i-1]%mod;
				inv[S]=quickpow(fact[S],mod-2,mod);
				for (int i=S;i>=1;i--) inv[i-1]=i*inv[i]%mod;			
			}
			combinatics_utility(){init();}
			inline size_t size(){return S;}
			inline T C(int n,int m){
				return (n<m? 0:fact[n]*inv[m]%mod*inv[n-m]%mod);
			}
			inline T P(int n,int m){
				return (n<m? 0:fact[n]*inv[m]%mod);
			}
			inline T getinv(T x){
				if (x<=0) return -1;
				if (x>S) return quickpow(x,mod-2,mod);
				return inv[x];
			}
			inline T getfact(T x){
				if (x<=0) return -1;
				if (x>S) return -1;
				return fact[x];
			}
	};
	template<typename T,size_t S>class prime_sieve{
		private:
			bitset<S+10> pr;
			vector<T> prv;
			vector<T> cnt;
			size_t prsz;
			inline void init(){
				if ((int)S<=100000) prv.resize(100000);
				else if ((int)S<=10000000) prv.resize(1000000);
				else prv.resize(S/15);
				cnt.resize(S+10);
				pr[1]=1;prsz=0;
				for (int i=2;i<=(int)S;i++){
					if (!pr[i]) prv[++prsz]=i;
					for (int j=1;j<=(int)prsz && i*prv[j]<=(int)S;j++){
						pr[i*prv[j]]=1;
						if (i%prv[j]==0) break;
					}
				}
				cnt[0]=0;
				for (int i=1;i<=(int)S;i++){
					cnt[i]=cnt[i-1]+(!pr[i]);
				}
			}
		public:
			prime_sieve(){init();}
			~prime_sieve(){}
			inline size_t size(){return prsz;}
			inline bool query(T k){return !pr[k];}
			inline T query_kth(T k){
				size_t sz=prv.size();
				if (k<=0) return -1;
				if (k>(int)sz) return -1;
				return prv[k];
			}
			inline T count_k(int k){
				if (k>(int)S || k<0) return -1;
				return cnt[k];
			}
	};
}
using namespace Header;
int mp[51][51],attr[51][51],n,m,k,q;
vector<int>v1,v2,v3,v4,v5;
vector<pair<int,int>>maincolor;
// for debug reasons stored full changelog of score
int minround=INT_MAX;
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,-1,1};
inline int& first(tuple<int,int,int> &x){return get<0>(x);}
inline int& second(tuple<int,int,int> &x){return get<1>(x);}
inline int& third(tuple<int,int,int> &x){return get<2>(x);}
void falldown(){
	for (int j=1;j<=m;j++){
		vector<int>v1,v2;
		for (int i=1;i<=n;i++){
			if (mp[i][j]){
				v1.emplace_back(mp[i][j]);
				v2.emplace_back(attr[i][j]);
			}
			mp[i][j]=0;
			attr[i][j]=0;
		}
		int pos=n;
		while (!v1.empty()){
			mp[pos][j]=v1.back();
			attr[pos][j]=v2.back();
			v1.pop_back();
			v2.pop_back();
			pos--;
		}
	}
}
void print_map(){
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			writesp(mp[i][j]);
			writesp(attr[i][j]);
			putchar(' ');
		}
		writeln();
	}
}
bool in_range(int x,int y){
	return (x>=1 && x<=n && y>=1 && y<=m);
}
bool do_remove(int roundnow){
	bool del[51][51],flag=false;
	bool vis[51][51];
	memset(del,0,sizeof(del));
	memset(vis,0,sizeof(vis));
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			if (in_range(i,j+2) && mp[i][j]==mp[i][j+1] && mp[i][j]==mp[i][j+2] && mp[i][j]){
				del[i][j]=del[i][j+1]=del[i][j+2]=flag=true;
			}
			if (in_range(i+2,j) && mp[i][j]==mp[i+1][j] && mp[i][j]==mp[i+2][j] && mp[i][j]){
				del[i][j]=del[i+1][j]=del[i+2][j]=flag=true;
			}
		}
	}
	if (!flag) return false;
	int prize_3=0;
	for (int i=1;i<=n;i++){
	    for (int j=1;j<=m;j++){
			if (del[i][j] && !vis[i][j] && mp[i][j]){
				int sz=0;
				queue<pair<int,int>>q;
				q.emplace(i,j);
				vis[i][j]=true;
				while (!q.empty()){
					pair<int,int>now=q.front();q.pop();sz++;
					for (int k=0;k<4;k++){
					    int x=now.first+dx[k],y=now.second+dy[k];
						if (in_range(x,y) && mp[x][y]==mp[i][j] && del[x][y] && !vis[x][y]){
							vis[x][y]=true;
							q.emplace(x,y);
						}
					}
				}
				if (sz>3) prize_3+=50*(sz-3)*(sz-3);
			}
		}
	}
	v3.emplace_back(prize_3);
	if (!roundnow){
		pair<int,int>res={-1,-1};
		for (int i=1;i<=n;i++){
			for (int j=1;j<=m;j++){
				if (del[i][j]){
					if (res.first==-1) res.first=mp[i][j];
					else if (res.first==mp[i][j]);
					else if (res.second==-1) res.second=mp[i][j];
					else if (res.second==mp[i][j]);
					else;
				}
			}
		}
		maincolor.emplace_back(res);
	}
	queue<tuple<int,int,int>>q;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			if (del[i][j] && attr[i][j]){
				q.emplace(i,j,attr[i][j]);
				attr[i][j]=0;
			}
		}
	}
	while (!q.empty()){
		tuple<int,int,int>now=q.front();q.pop();
		if (third(now)==1){
			for (int i=1;i<=m;i++){
				del[first(now)][i]=true;
				if (attr[first(now)][i]){
					q.emplace(first(now),i,attr[first(now)][i]);
					attr[first(now)][i]=0;
				}
			}
		}
		else if (third(now)==2){
			for (int i=1;i<=n;i++){
				del[i][second(now)]=true;
				if (attr[i][second(now)]){
					q.emplace(i,second(now),attr[i][second(now)]);
					attr[i][second(now)]=0;
				}
			}
		}
		else if (third(now)==3){
			for (int i=1;i<=m;i++){
				del[first(now)][i]=true;
				if (attr[first(now)][i]){
					q.emplace(first(now),i,attr[first(now)][i]);
					attr[first(now)][i]=0;
				}
			}
			for (int i=1;i<=n;i++){
				del[i][second(now)]=true;
				if (attr[i][second(now)]){
					q.emplace(i,second(now),attr[i][second(now)]);
					attr[i][second(now)]=0;
				}
			}
		}
		else if (third(now)==4){
			for (int i=first(now)-1;i<=first(now)+1;i++){
				for (int j=second(now)-1;j<=second(now)+1;j++){
					if (in_range(i,j)){
						del[i][j]=true;
						if (attr[i][j]){
							q.emplace(i,j,attr[i][j]);
							attr[i][j]=0;
						}
					}
				}
			}
		}
		else if (third(now)==5){
			for (int i=first(now)-2;i<=first(now)+2;i++){
				for (int j=second(now)-2;j<=second(now)+2;j++){
					if (in_range(i,j)){
						del[i][j]=true;
						if (attr[i][j]){
							q.emplace(i,j,attr[i][j]);
							attr[i][j]=0;
						}
					}
				}
			}
		}
		else{
			for (int i=1;i<=n;i++){
				for (int j=1;j<=m;j++){
					if (mp[i][j]==mp[first(now)][second(now)]){
						del[i][j]=true;
						if (attr[i][j]){
							q.emplace(i,j,attr[i][j]);
							attr[i][j]=0;
						}
					}
				}
			}
		}
	}
	int sum=0;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			if (del[i][j]){
				sum+=mp[i][j];
				mp[i][j]=0;
				attr[i][j]=0;
			}
		}
	}
	v1.emplace_back((roundnow+1)*sum);
	falldown();
	// print_map();
	return true;
}
bool full_clear(){
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			if (mp[i][j]) return false;
		}
	}
	return true;
}
bool is_five_of_a_kind(vector<int>choice){
	for (int i=1;i<=4;i++){
		if (choice[i]!=choice[i-1]) return false;
	}
	return true;
}
bool is_four_of_a_kind(vector<int>choice){
	if (choice[0]==choice[1] && choice[1]==choice[2] && choice[2]==choice[3]) return true;
	if (choice[1]==choice[2] && choice[2]==choice[3] && choice[3]==choice[4]) return true;
	return false;
}
bool is_fullhouse(vector<int>choice){
	if (choice[0]==choice[1] && choice[1]==choice[2] && choice[3]==choice[4]) return true;
	if (choice[0]==choice[1] && choice[2]==choice[3] && choice[3]==choice[4]) return true;
	return false;
}
bool is_three_of_a_kind(vector<int>choice){
	if (choice[0]==choice[1] && choice[1]==choice[2]) return true;
	if (choice[1]==choice[2] && choice[2]==choice[3]) return true;
	if (choice[2]==choice[3] && choice[3]==choice[4]) return true;
	return false;
}
bool is_two_pairs(vector<int>choice){
	if (choice[0]==choice[1] && choice[2]==choice[3]) return true;
	if (choice[0]==choice[1] && choice[3]==choice[4]) return true;
	if (choice[1]==choice[2] && choice[3]==choice[4]) return true;
	return false;
}
bool is_one_pair(vector<int>choice){
	if (choice[0]==choice[1]) return true;
	if (choice[1]==choice[2]) return true;
	if (choice[2]==choice[3]) return true;
	if (choice[3]==choice[4]) return true;
	return false;
}
int dfs_v4(int stp,vector<pair<int,int>>colors,vector<int>choice){
	if (stp==5){
		sort(choice.begin(),choice.end());
		if (choice[0]==-1) return 0;
		if (is_five_of_a_kind(choice)) return 1000+choice[0]*10;
		if (is_four_of_a_kind(choice)) return 750+choice[1]*5;
		if (is_fullhouse(choice)) return 500+choice[2]*3+(choice[0]==choice[2]? choice[4]:choice[0]);
		if (is_three_of_a_kind(choice)) return 300+choice[2]*3;
		if (is_two_pairs(choice)) return 200+choice[3]*2+choice[1];
		if (is_one_pair(choice)){
			for (int i=0;i<4;i++){
				if (choice[i]==choice[i+1]) return 100+choice[i]*2;
			}
		}
		return 50+choice[4];
	}
	choice.emplace_back(colors[stp].first);
	int ans=dfs_v4(stp+1,colors,choice);
	choice.pop_back();
	choice.emplace_back(colors[stp].second);
	ans=fastmax(ans,dfs_v4(stp+1,colors,choice));
	return ans;
}
void update_v4(){
	for (int i=0;i+4<(int)maincolor.size();i+=5){
		vector<pair<int,int>>temp;
		for (int j=i;j<=i+4;j++){
			temp.emplace_back(maincolor[j]);
		}
		v4.emplace_back(dfs_v4(0,temp,{}));
	}
}
signed main(){
	read(n,m,k,q);
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			read(mp[i][j]);
		}
	}
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			read(attr[i][j]);
		}
	}
	while (q--){
		static int x1,y1,x2,y2;
		read(x1,y1,x2,y2);
		if (!mp[x1][y1] || !mp[x2][y2] || abs(x1-x2)+abs(y1-y2)!=1){
			minround=0;
			continue;
		}
		swap(mp[x1][y1],mp[x2][y2]);
		swap(attr[x1][y1],attr[x2][y2]);
		int roundnow=0;
		while (do_remove(roundnow)) roundnow++;
		minround=fastmin(minround,roundnow);
		if (!roundnow){
			swap(mp[x1][y1],mp[x2][y2]);
			swap(attr[x1][y1],attr[x2][y2]);
			continue;
		}
		v2.emplace_back(80*(roundnow-1)*(roundnow-1));
		if (maincolor.size()==5){
			update_v4();
			maincolor.clear();
		}
		// print_map();
	}
	if (minround) v5.emplace_back(1000);
	if (full_clear()) v5.emplace_back(10000);
	int sum1=accumulate(v1.begin(),v1.end(),0);
	int sum2=accumulate(v2.begin(),v2.end(),0);
	int sum3=accumulate(v3.begin(),v3.end(),0);
	int sum4=accumulate(v4.begin(),v4.end(),0);
	int sum5=accumulate(v5.begin(),v5.end(),0);
	writeln(sum1+sum2+sum3+sum4+sum5);
	// print_map();
	return 0;
}