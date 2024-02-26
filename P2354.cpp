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
int x0,a,b,c,d,n,m,q,cnt,ans[10010];
int p[5010][5010],idx[25000010];
bitset<5010>vis[5010];
struct RandomGen{
	int x,a,b,c,d;
	RandomGen(int xx,int aa,int bb,int cc,int dd):x(xx),a(aa),b(bb),c(cc),d(dd){}
	int next(){return x=(1ll*x*x*a+1ll*b*x+c)%d;}
};
pair<int,int> id_to_pos(int id){
	return make_pair((id-1)/m+1,(id-1)%m+1);
}
int pos_to_id(int x,int y){
	return (x-1)*m+y;
}
signed main(){
	read(x0,a,b,c,d,n,m,q);
	RandomGen rng(x0,a,b,c,d);
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			p[i][j]=pos_to_id(i,j);
		}
	}
	for (int i=1;i<=n*m;i++){
		pair<int,int>p1=id_to_pos(i);
		pair<int,int>p2=id_to_pos(rng.next()%i+1);
		swap(p[p1.first][p1.second],p[p2.first][p2.second]);
	}
	while (q--){
		static int u,v;
		read(u,v);
		pair<int,int>p1=id_to_pos(u);
		pair<int,int>p2=id_to_pos(v);
		swap(p[p1.first][p1.second],p[p2.first][p2.second]);
	}
	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			idx[p[i][j]]=pos_to_id(i,j);
		}
	}
	int i=1;
	while (cnt<n+m-1){
		pair<int,int>p=id_to_pos(idx[i]);
		if (!vis[p.first][p.second]){
			ans[++cnt]=i;
			// set (1,p.second+1) ~ (p.first-1,m) to 1
			// set (p.first+1,1) ~ (n,p.second-1) to 1
			for (int i=1;i<p.first;i++){
				for (int j=p.second+1;j<=m;j++){
					if (vis[i][j]) break;
					vis[i][j]=1;
				}
			}
			for (int i=p.first+1;i<=n;i++){
				for (int j=p.second-1;j>=1;j--){
					if (vis[i][j]) break;
					vis[i][j]=1;
				}
			}
		}
		i++;
	}
	for (int i=1;i<n+m;i++){
		writesp(ans[i]);
	}
	writeln();
	return 0;
}