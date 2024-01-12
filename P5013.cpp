#include<bits/stdc++.h>
using namespace std;
namespace Header{
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
	template<typename T,const T base,const T mod>class single_mod_hash{
		private:
		public:
			single_mod_hash(){}
			~single_mod_hash(){}
			inline T gethash(string x){
				T ans=0xdeadbeefu;
				for (char i:x){
					ans=(ans*base+i)%mod;
				}
				return ans;
			}
	};
	template<typename T,const T base,const T mod1,const T mod2>class double_mod_hash{
		private:
		public:
			double_mod_hash(){}
			~double_mod_hash(){}
			inline T gethash1(string x){
				T ans=0x8badf00du;
				for (char i:x){
					ans=(ans*base+i)%mod1;
				}
				return ans;
			}
			inline T gethash2(string x){
				T ans=0xdeaddeadu;
				for (char i:x){
					ans=(ans*base+i)%mod2;
				}
				return ans;
			}
			inline pair<T,T> gethash(string x){
				return make_pair(gethash1(x),gethash2(x));
			}
	};
	template<typename T>inline void readmain(T &x){
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
	inline void readmain(string &x){
		char ch=getchar();x="";
		while (ch=='\n' || ch=='\r' || ch=='\t' || ch==' ') ch=getchar();
		while (ch!='\n' && ch!='\r' && ch!='\t' && ch!=' '){
			x+=ch;
			ch=getchar();
		}
	}
	inline void readmain(char &x){
		x=getchar();
		while (x=='\n' || x=='\r' || x=='\t' || x==' ') x=getchar();
	}
	template<typename T>inline void read(T &x){
		readmain(x);
	}
	template<typename T,typename ...Ts>inline void read(T &x,Ts&... r){
		readmain(x);
		read(r...);
	}
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
	template<typename T>inline T getinv(T a,T mod){
		return quickpow(a,mod-2,mod);
	}
	inline void writemain(__int128_t x){
		if (x<0){
			x=~(x-1);
			putchar('-');
		}
		if (x>9) writemain(x/10);
		putchar(x%10+'0');
	}
	inline void writemain(unsigned long long x){
		if (x>9) writemain(x/10);
		putchar(x%10+'0');
	}
	inline void writemain(unsigned int x){
		if (x>9) writemain(x/10);
		putchar(x%10+'0');
	}
	inline void writemain(long long x){
		if (x<0){
			x=~(x-1);
			putchar('-');
		}
		if (x>9) writemain(x/10);
		putchar(x%10+'0');
	}
	inline void writemain(int x){
		if (x<0){
			x=~(x-1);
			putchar('-');
		}
		if (x>9) writemain(x/10);
		putchar(x%10+'0');
	}
	inline void writemain(double x){
		if (x<0){
			x=-x;
			putchar('-');
		}
		int wid=15;
		x+=5e-16; // adjust the final digit
		__int128_t num=(__int128_t)x;
		writemain(num);
		putchar('.');
		x-=num;
		while (wid--){
			putchar((int)(x*=10)+'0');
			x-=(int)(x);
		}
	}
	inline void writemain(bool x){
		putchar('0'+x);
	}
	inline void writemain(string x){
		for (char i:x){
			putchar(i);
		}
	}
	inline void writemain(const char* x){
		int sz=strlen(x);
		for (int i=0;i<sz;i++){
			putchar(x[i]);
		}
	}
	template<typename T>inline void write(T x){
		writemain(x);
	}
	template<typename T,typename ...Ts>inline void write(T x,Ts... r){
		writemain(x);
		write(r...);
	}
	template<typename T>inline void writeln(T x){
		writemain(x);
		putchar('\n');
	}
	template<typename T,typename ...Ts>inline void writeln(T x,Ts... r){
		writemain(x);
		putchar('\n');
		writeln(r...);
	}
	template<typename T>inline void writesp(T x){
		writemain(x);
		putchar(' ');
	}
	template<typename T,typename ...Ts>inline void writesp(T x,Ts... r){
		writemain(x);
		putchar(' ');
		writesp(r...);
	}
	template<typename T>inline void writesp(vector<T> v){
		for (T i:v){
			writesp(i);
		}
		putchar('\n');
	}
	template<typename T>inline T fastabs(T x){
		return (x<=0? -x:x);
	}
	template<typename T>inline T lowbit(T x){
		return x&(~(x-1));
	}
	template<typename T>inline T fastmaxmain(T x,T y){
		return (x>y? x:y);
	}
	template<typename T>inline T fastmax(T x,T y){
		return fastmaxmain(x,y);
	}
	template<typename T,typename... Ts>inline T fastmax(T x,Ts... args){
		return fastmaxmain(x,fastmax(args...));
	}
	template<typename T>inline T fastminmain(T x,T y){
		return (x<y? x:y);
	}
	template<typename T>inline T fastmin(T x,T y){
		return fastminmain(x,y);
	}
	template<typename T,typename... Ts>inline T fastmin(T x,Ts... args){
		return fastminmain(x,fastmin(args...));
	}
	template<typename T>inline void fastswap(T &x,T &y){
		x^=y^=x^=y;
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
}
#define int long long
using namespace Header;
unordered_map<string,int> idx;
string names[100010];
int score[100010];
int id,T,n;
int str2int(string s){
	int res=0;
	for (char ch:s){
		res=res*10+ch-'0';
	}
	return res;
}
int get_score(int grade,bool hastb){
	if (grade==11) return 100;
	if (grade==10 && hastb) return 60;
	if (grade==10) return 30;
	if (grade>=7 && hastb) return 40;
	if (grade>=7) return 20;
	if (hastb) return 20;
	return 10;
}
pair<int,bool> get_grade(int* cnt,int* c){
	// for (int i=1;i<=5;i++){
	// 	writesp(c[i]);
	// }
	// putchar('\n');
	for (int i=1;i<=10;i++){
		if (cnt[i]==4) return make_pair(11,false);
	}
	bool maxhastb=false;
	int maxn=0;
	for (int i=1;i<=5;i++){
		for (int j=i+1;j<=5;j++){
			int sum=0,flag=0;
			for (int k=1;k<=5;k++){
				if (k!=i && k!=j){
					sum+=c[k];
					if (!flag) flag=c[k];
					else if (c[k]!=flag) flag=-1;
				}
			}
			if (sum%10==0 && (c[i]+c[j]-1)%10+1>maxn){
				maxn=fastmax(maxn,(c[i]+c[j]-1)%10+1);
				maxhastb=false;
			}
			if (flag>0 && (c[i]+c[j]-1)%10+1>=maxn){
				maxn=fastmax(maxn,(c[i]+c[j]-1)%10+1);
				maxhastb=true;
			}
		}
	}
	return make_pair(maxn,maxhastb);
}
pair<int,int> compare(string* a,string* b){
	static int cnta[11],cntb[11],ca[6],cb[6];
	memset(cnta,0,sizeof(cnta));
	memset(cntb,0,sizeof(cntb));
	memset(ca,0,sizeof(ca));
	memset(cb,0,sizeof(cb));
	for (int i=1;i<=5;i++){
		ca[i]=str2int(a[i].substr(1));
		cnta[ca[i]]++;
	}
	for (int i=1;i<=5;i++){
		cb[i]=str2int(b[i].substr(1));
		cntb[cb[i]]++;
	}
	pair<int,bool> pa=get_grade(cnta,ca);
	pair<int,bool> pb=get_grade(cntb,cb);
	// cerr<<pa.first<<" "<<pa.second<<endl;
	// cerr<<pb.first<<" "<<pb.second<<endl;
	if (pa.first>pb.first){
		int score=get_score(pa.first,pa.second);
		return make_pair(score,-score);
	}
	else if (pa.first<pb.first){
		int score=get_score(pb.first,pb.second);
		return make_pair(-score,score);
	}
	else{
		if (pa.first==11){
			int bomba=0,bombb=0;
			for (int i=1;i<=10;i++){
				if (cnta[i]==4) bomba=i;
				if (cntb[i]==4) bombb=i;
			}
			if (bomba>bombb) return make_pair(100,-100);
			else return make_pair(-100,100);
		}
		if (pa.second && pb.second){
			int tba=0,tbb=0;
			for (int i=1;i<=10;i++){
				if (cnta[i]==3) tba=i;
				if (cntb[i]==3) tbb=i;
			}
			int score=get_score(pa.first,true);
			if (tba>tbb) return make_pair(score,-score);
			else return make_pair(-score,score);
		}
		else if (pa.second){
			int score=get_score(pa.first,true);
			return make_pair(score,-score);
		}
		else if (pb.second){
			int score=get_score(pa.first,true);
			return make_pair(-score,score);
		}
		else{
			int score=get_score(pa.first,false);
			int biggesta=0,biggestb=0;
			for (int i=10;i>=1;i--){
				if (cnta[i]){
					biggesta=i;
					break;
				}
			}
			for (int i=10;i>=1;i--){
				if (cntb[i]){
					biggestb=i;
					break;
				}
			}
			if (biggesta>biggestb){
				return make_pair(score,-score);
			}
			else if (biggesta<biggestb){
				return make_pair(-score,score);
			}
			else{
				int mina=4,minb=4;
				for (int i=1;i<=5;i++){
					if (ca[i]==biggesta){
						mina=fastmin(mina,a[i][0]-'a'+1ll);
					}
					if (cb[i]==biggesta){
						minb=fastmin(minb,b[i][0]-'a'+1ll);
					}
				}
				if (mina<minb){
					return make_pair(score,-score);
				}
				else{
					return make_pair(-score,score);
				}
			}
		}
	}
}
void fastIO(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
}
signed main(){
	fastIO();
	cin>>id>>T>>n;
	for (int i=1;i<=n;i++){
		cin>>names[i];
		idx[names[i]]=i;
	}
	while (T--){
		static string a,b,c,cards[4][6];
		for (int i=1;i<=3;i++){
			if (i==1) cin>>a;
			if (i==2) cin>>b;
			if (i==3) cin>>c;
			for (int j=1;j<=5;j++){
				cin>>cards[i][j];
				if (cards[i][j][cards[i][j].size()-1]=='A'){
					cards[i][j][cards[i][j].size()-1]='1';
				}
			}
		}
		pair<int,int>p;
		p=compare(cards[1],cards[2]);
		score[idx[a]]+=p.first;
		score[idx[b]]+=p.second;
		// cerr<<setw(5)<<p.first<<setw(5)<<p.second<<endl;
		p=compare(cards[1],cards[3]);
		score[idx[a]]+=p.first;
		score[idx[c]]+=p.second;
		// cerr<<setw(5)<<p.first<<"     "<<setw(5)<<p.second<<endl;
		p=compare(cards[2],cards[3]);
		score[idx[b]]+=p.first;
		score[idx[c]]+=p.second;
		// cerr<<"     "<<setw(5)<<p.first<<setw(5)<<p.second<<endl;
	}
	for (int i=1;i<=n;i++){
		cout<<names[i]<<" "<<score[i]<<'\n';
	}
	return 0;
}