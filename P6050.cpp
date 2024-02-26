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
int mp[12][12],n,k;
void init_board(){
	for (int i=1;i<=n;i++){
		mp[i][1]=1;
		mp[i][n]=2;
	}
	for (int j=1;j<=n/2;j++){
		mp[1][j]=1;
		mp[n][j]=1;
	}
	for (int j=n/2+1;j<=n;j++){
		mp[1][j]=2;
		mp[n][j]=2;
	}
}
bool valid(int x,int y){
	return (x>=1 && x<=n && y>=1 && y<=n);
}
int count_pos(int property){
	int cnt=0;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			if (mp[i][j]==property) cnt++;
		}
	}
	return cnt;
}
void print_board(){
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			if (mp[i][j]==1) putchar('h');
			else if (mp[i][j]==2) putchar('l');
			else putchar('.');
		}
		putchar('\n');
	}
}
void trans_single(int turn,int id,bool is_line,int xx,int yy){
	if (is_line && xx!=id) return;
	if (!is_line && yy!=id) return;
	int cnt1=0,cnt2=0;
	for (int i=1;i<=n;i++){
		if (is_line){
			cnt1+=(mp[id][i]==1);
			cnt2+=(mp[id][i]==2);
		}
		else{
			cnt1+=(mp[i][id]==1);
			cnt2+=(mp[i][id]==2);
		}
	}
	if (n==4){
		if (cnt1==1 && cnt2==2 && turn==2);
		else if (cnt1==2 && cnt2==1 && turn==1);
		else return;
		// cout<<"EAT! "<<cnt1<<" "<<cnt2<<" "<<turn<<endl;
		int minpos=10,maxpos=0;
		for (int i=1;i<=n;i++){
			if (is_line && mp[id][i]==turn){
				minpos=fastmin(minpos,i);
				maxpos=fastmax(maxpos,i);
			}
			if (!is_line && mp[i][id]==turn){
				minpos=fastmin(minpos,i);
				maxpos=fastmax(maxpos,i);
			}
		}
		if (is_line && maxpos-minpos+1==2 && (mp[id][minpos-1]==3-turn || mp[id][maxpos+1]==3-turn)){
			for (int i=1;i<=n;i++){
				if (mp[id][i]==3-turn){
					mp[id][i]=0;
				}
			}
		}
		if (!is_line && maxpos-minpos+1==2 && (mp[minpos-1][id]==3-turn || mp[maxpos+1][id]==3-turn)){
			for (int i=1;i<=n;i++){
				if (mp[i][id]==3-turn){
					mp[i][id]=0;
				}
			}
		}
	}
	else{
		if (cnt1+cnt2!=n-1 && cnt1+cnt2!=n-2) return;
		if (cnt1==1 && cnt2==n-2 && turn==2);
		else if (cnt1==1 && cnt2==n-3 && turn==2);
		else if (cnt1==n-2 && cnt2==1 && turn==1);
		else if (cnt1==n-3 && cnt2==1 && turn==1);
		else if (cnt1==n-3 && cnt2==2 && turn==1);
		else if (cnt1==2 && cnt2==n-3 && turn==2);
		else return;
		// cout<<"EAT! "<<cnt1<<" "<<cnt2<<" "<<turn<<endl;
		int minpos=10,maxpos=0,minpos2=10,maxpos2=0;
		for (int i=1;i<=n;i++){
			if ((is_line && mp[id][i]==turn) || (!is_line && mp[i][id]==turn)){
				minpos=fastmin(minpos,i);
				maxpos=fastmax(maxpos,i);
			}
			else if ((is_line && mp[id][i]==3-turn) || (!is_line && mp[i][id]==3-turn)){
				minpos2=fastmin(minpos2,i);
				maxpos2=fastmax(maxpos2,i);
			}
		}
		if (is_line && maxpos-minpos+1==fastmax(cnt1,cnt2) && maxpos2-minpos2+1==fastmin(cnt1,cnt2) && (mp[id][minpos-1]==3-turn || mp[id][maxpos+1]==3-turn)){
			for (int i=1;i<=n;i++){
				if (mp[id][i]==3-turn){
					mp[id][i]=0;
				}
			}
		}
		if (!is_line && maxpos-minpos+1==fastmax(cnt1,cnt2) && maxpos2-minpos2+1==fastmin(cnt1,cnt2) && (mp[minpos-1][id]==3-turn || mp[maxpos+1][id]==3-turn)){
			for (int i=1;i<=n;i++){
				if (mp[i][id]==3-turn){
					mp[i][id]=0;
				}
			}
		}
	}
}
void trans(int turn,int xx,int yy){
	for (int i=1;i<=n;i++) trans_single(turn,i,true,xx,yy);
	for (int i=1;i<=n;i++) trans_single(turn,i,false,xx,yy);
}
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,-1,1};
bool cant_move(int player){
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++){
			if (mp[i][j]==player){
				for (int k=0;k<4;k++){
					int x=i+dx[k],y=j+dy[k];
					if (valid(x,y) && mp[x][y]==0) return false;
				}
			}
		}
	}
	return true;
}
signed main(){
	read(n,k);
	init_board();
	int turn=1;
	while (k--){
		static int a,b,c,d;
		read(a,b,c,d);
		swap(a,b);swap(c,d);
		if (!valid(a,b) || !valid(c,d)){
			writeln(0);
			return 0;
		}
		if (mp[a][b]!=turn){
			writeln(0);
			return 0;
		}
		if (mp[c][d]){
			writeln(0);
			return 0;
		}
		if (abs(a-c)+abs(b-d)!=1){
			writeln(0);
			return 0;
		}
		mp[c][d]=mp[a][b];
		mp[a][b]=0;
		trans(turn,c,d);
		if (count_pos(1)<=n/2){
			writeln(2);
			writeln("blue");
			print_board();
			return 0;
		}
		if (count_pos(2)<=n/2){
			writeln(2);
			writeln("red");
			print_board();
			return 0;
		}
		if (cant_move(1)){
			writeln(2);
			writeln("blue");
			print_board();
			return 0;
		}
		if (cant_move(2)){
			writeln(2);
			writeln("red");
			print_board();
			return 0;
		}
		// print_board();
		turn=3-turn;
	}
	writeln(1);
	print_board();
	return 0;
}