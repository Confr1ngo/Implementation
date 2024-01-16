#include<bits/stdc++.h>
using namespace std;
namespace Header{
	template<typename T> struct Integral:public is_integral<T>{};
	template<> struct Integral<__int128_t>:public true_type{};  
	template<> struct Integral<__uint128_t>:public true_type{};
	template<typename T> struct FloatingPoint:public is_floating_point<T>{};
	template<> struct FloatingPoint<__float128>:public true_type{};
	template<typename T>inline void to_lower(T &x){
		for (char &i:x){
			if (i>='A' && i<='Z') i+='a'-'A';
		}
	}
	template<typename T>inline void to_upper(T &x){
		for (char &i:x){
			if (i>='a' && i<='z') i-='a'-'A';
		}
	}
	template<typename T>inline T quickpow(T a,T b,T mod){
		T res=1;
		while (b){
			if (b&1) res=res*a%mod;
			a=a*a%mod;
			b>>=1;
		}
		return res;
	}
	template<typename T>inline enable_if_t<Integral<T>::value,T> getinv(T a,T mod){
		return quickpow(a,mod-2,mod);
	}
	template<typename T>inline enable_if_t<Integral<T>::value,T> lowbit(T x){
		return x&(~(x-1));
	}
	template<typename T>inline enable_if_t<Integral<T>::value,void> readmain(T &x){
		x=0;bool flag=1;
		char ch=getchar();
		while (ch<'0' || ch>'9'){
			if (ch=='-') flag=0;
			ch=getchar();
		}
		while (ch>='0' && ch<='9'){
			x=(x<<1)+(x<<3)+ch-'0';
			ch=getchar();
		}
		if (!flag) x=~(x-1);
	}
	void readmain(string &x){
		char ch=getchar();x="";
		while (ch=='\n' || ch=='\r' || ch=='\t' || ch==' ') ch=getchar();
		while (ch!='\n' && ch!='\r' && ch!='\t' && ch!=' '){
			x+=ch;
			ch=getchar();
		}
	}
	void readmain(char &x){
		x=getchar();
		while (x=='\n' || x=='\r' || x=='\t' || x==' ') x=getchar();
	}
	template<typename T>void read(T &x){
		readmain(x);
	}
	template<typename T,typename ...Ts>void read(T &x,Ts&... r){
		readmain(x);
		read(r...);
	}
	template<typename T>enable_if_t<Integral<T>::value,void> writemain(T x){
		if (x<0){
			x=~(x-1);
			putchar('-');
		}
		if (x>9) writemain(x/10);
		putchar(x%10+'0');
	}
	template<typename T>enable_if_t<FloatingPoint<T>::value,void> writemain(T x){
		if (x<0){
			x=-x;
			putchar('-');
		}
		int wid=15;x+=5e-16;
		__int128_t num=(__int128_t)x;
		writemain(num);
		putchar('.');
		x-=num;
		while (wid--){
			putchar((int)(x*=10)+'0');
			x-=(int)(x);
		}
	}
	void writemain(string x){
		for (char i:x){
			putchar(i);
		}
	}
	void writemain(const char* x){
		int sz=strlen(x);
		for (int i=0;i<sz;i++){
			putchar(x[i]);
		}
	}
	template<typename T>void write(T x){
		writemain(x);
	}
	template<typename T,typename ...Ts>void write(T x,Ts... r){
		writemain(x);
		write(r...);
	}
	void writeln(){
		putchar('\n');
	}
	template<typename T>void writeln(T x){
		writemain(x);
		putchar('\n');
	}
	template<typename T,typename ...Ts>void writeln(T x,Ts... r){
		writemain(x);
		putchar('\n');
		writeln(r...);
	}
	template<typename T>void writesp(T x){
		writemain(x);
		putchar(' ');
	}
	template<typename T,typename ...Ts>void writesp(T x,Ts... r){
		writemain(x);
		putchar(' ');
		writesp(r...);
	}
	template<typename T>void writesp(vector<T> v){
		for (T i:v){
			writesp(i);
		}
		putchar('\n');
	}
	template<typename T> T fastmaxmain(T x,T y){
		return (x>y? x:y);
	}
	template<typename T> T fastmax(T x,T y){
		return fastmaxmain(x,y);
	}
	template<typename T,typename... Ts> T fastmax(T x,Ts... args){
		return fastmaxmain(x,fastmax(args...));
	}
	template<typename T> T fastminmain(T x,T y){
		return (x<y? x:y);
	}
	template<typename T> T fastmin(T x,T y){
		return fastminmain(x,y);
	}
	template<typename T,typename... Ts> T fastmin(T x,Ts... args){
		return fastminmain(x,fastmin(args...));
	}
	enum YesNoVariants{Capital,Lowercase,FirstCapital};
	inline void yesno(bool x,YesNoVariants variant=FirstCapital){
		if (variant==Capital) writeln(x? "YES":"NO");
		else if (variant==Lowercase) writeln(x? "yes":"no");
		else writeln(x? "Yes":"No");
	}
	unsigned long long operator"" _kw(unsigned long long x){
		return x*10000000;
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
string s;
int n;
struct Node{
	int x,y,id;
	Node(int x=0,int y=0,int id=0):x(x),y(y),id(id){}
	bool operator<(const Node &rhs)const{
		if (x<rhs.x) return true;
		if (x>rhs.x) return false;
		if (y<rhs.y) return true;
		return false;
	}
	// Not greater than.
	// Just use y as the first sorting key.
	bool operator>(const Node &rhs)const{
		if (y<rhs.y) return true;
		if (y>rhs.y) return false;
		if (x<rhs.x) return true;
		return false;
	}
}node[250010],t[250010];
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,-1,1};
signed main(){
	read(n,s);
	for (int i=1;i<=n;i++){
		int way=0;
		if (s[i-1]=='S') way=1;
		if (s[i-1]=='W') way=2;
		if (s[i-1]=='E') way=3;
		t[i]=Node(t[i-1].x+dx[way],t[i-1].y+dy[way],i);
		node[i]=Node(node[i-1].x+dx[way],node[i-1].y+dy[way],i);
	}
	sort(node+1,node+n+1,[=](Node a,Node b){return a<b;});
	int len=1e6,st=0,ed=0;
	char dir='\0';
	for (int i=1;i<=n;i++){
		if (node[i].x==node[i-1].x){
			int a=fastmin(node[i-1].id,node[i].id);
			int b=fastmax(node[i-1].id,node[i].id);
			if (b-a==1) continue;
			int l=abs(node[i].y-node[i-1].y);
			if (l<len || (l==len && (a<st || (a==st && b>ed)))){
				len=l;st=a;ed=b;
				if (t[a].y<t[b].y) dir='E';
				else dir='W';
			}
		}
	}
	sort(node+1,node+n+1,[=](Node a,Node b){return a>b;});
	for (int i=1;i<=n;i++){
		if (node[i].y==node[i-1].y){
			int a=fastmin(node[i-1].id,node[i].id);
			int b=fastmax(node[i-1].id,node[i].id);
			if (b-a==1) continue;
			int l=abs(node[i].x-node[i-1].x);
			if (l<len || (l==len && (a<st || (a==st && b>ed)))){
				len=l;st=a;ed=b;
				if (t[a].x<t[b].x) dir='N';
				else dir='S';
			}
		}
	}
	writesp(len);
	writesp(st);
	writesp(ed);
	putchar(dir);
	putchar('\n');
	return 0;
}