#include<bits/stdc++.h>
using namespace std;
namespace Header{
	inline char getc(){
        static const int IN_LEN=1<<18|1;
        static char buf[IN_LEN],*s,*t;
        return (s==t)&&(t=(s=buf)+fread(buf,1,IN_LEN,stdin)),s==t?-1:*s++;
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
		char ch=getc();
		while (ch<'0' || ch>'9'){
			if (ch=='-') flag=0;
			ch=getc();
		}
		while (ch>='0' && ch<='9'){
			x=(x<<1)+(x<<3)+ch-'0';
			ch=getc();
		}
		if (!flag) x=~(x-1);
	}
	inline void readmain(double &x){
		x=0;bool flag=1;
		char ch=getc();
		while (ch<'0' || ch>'9'){
			if (ch=='-') flag=0;
			ch=getc();
		}
		while (ch>='0' && ch<='9'){
			x=x*10+ch-'0';
			ch=getc();
		}
		double p=.1;
		if (ch!='.') return;
		ch=getc();
		while (ch>='0' && ch<='9'){
			x=x+(ch-'0')*p;
			ch=getc();
			p*=.1;
		}
		if (!flag) x=-x;
	}
	inline void readmain(string &x){
		char ch=getc();x="";
		while (ch=='\n' || ch=='\r' || ch=='\t' || ch==' ') ch=getc();
		while (ch!='\n' && ch!='\r' && ch!='\t' && ch!=' '){
			x+=ch;
			ch=getc();
		}
	}
	inline void readmain(char &x){
		x=getc();
		while (x=='\n' || x=='\r' || x=='\t' || x==' ') x=getc();
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
using namespace Header;
struct Practice{
	string id;
	long long st,ed;
	int pause,dist;
	const Practice& operator=(const Practice& p){
		id=p.id;
		st=p.st;
		ed=p.ed;
		pause=p.pause;
		dist=p.dist;
		return *this;
	}
	Practice():id(""),st(0),ed(0),pause(0),dist(0){}
	~Practice(){}
	Practice(string id,long long st,long long ed,int pause,int dist):id(id),st(st),ed(ed),pause(pause),dist(dist){}
	friend bool operator<(const Practice& p1,const Practice& p2){return p1.st>p2.st;}
};
struct Person{
	char gender;
	int traincnt,a,b,c,d,e;
	priority_queue<Practice>pracrec;
	const Person& operator=(const Person& p){
		gender=p.gender;
		traincnt=p.traincnt;
		a=p.a;b=p.b;c=p.c;
		d=p.d;e=p.e;
		pracrec=p.pracrec;
		return *this;
	}
	Person():gender('M'),a(0),b(0),c(0),d(0),e(0){}
	~Person(){}
	Person(int s,int t,int p,int h,int pr,char g):gender(g),a(s),b(t),c(p),d(h),e(pr){}
};
set<string>ids;
unordered_map<string,Person>mp;
string get_grade(int score){
	if (score>=95) return "A";
	if (score>=90) return "A-";
	if (score>=85) return "B+";
	if (score>=80) return "B";
	if (score>=77) return "B-";
	if (score>=73) return "C+";
	if (score>=70) return "C";
	if (score>=67) return "C-";
	if (score>=63) return "D+";
	if (score>=60) return "D";
	return "F";
}
int get_total_points(Person p){
	return p.a+p.b+p.c+p.d+p.e;
}
int str2int(string s){
	int res=0;
	for (char ch:s){
		res=res*10+ch-'0';
	}
	return res;
}
long long string_to_timestamp(string s){
	int days[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	int M=str2int(s.substr(4,2));
	int D=str2int(s.substr(6,2));
	int hr=str2int(s.substr(9,2));
	int min=str2int(s.substr(12,2));
	int sec=str2int(s.substr(15,2));
	int daynow=0;
	for (int i=1;i<M;i++){
		daynow+=days[i];
	}
	daynow+=D;
	return daynow*24*60*60+hr*60*60+min*60+sec;
}
int maletime[10]={750,780,810,840,870,910,950,990,1030,1080};
int femaletime[10]={400,417,434,451,470,485,500,515,530,540};
int practimes[7]={21,19,17,14,11,7,3};
int pracscore[7]={1,1,1,1,2,2,2};
int projtimes[5]={18,15,12,9,6};
int T;
signed main(){
	read(T);
	while (T--){
		string id,gender,testtm,d;
		int a,e,train;
		read(id,gender,a,testtm,d,e,train);
		ids.insert(id);
		Person p;
		p.a=a;
		testtm.erase(testtm.size()-1,1);
		int tot=str2int(testtm.substr(0,testtm.find("'")))*60+str2int(testtm.substr(testtm.find("'")+1));
		p.gender=gender[0];
		if (gender=="M"){
			for (int i=1;i<=10;i++){
				if (tot<=maletime[i-1]) p.b+=2;
			}
		}
		else{
			for (int i=1;i<=10;i++){
				if (tot<=femaletime[i-1]) p.b+=2;
			}
		}
		if (d=="P") p.d=10;
		p.e=e;
		p.traincnt=train;
		mp[id]=p;
	}
	read(T);
	while (T--){
		string day,st,ed,id,pause;
		double dist;
		int steps;
		read(day,id,st,ed,dist,pause,steps);
		Practice p;
		p.dist=int(round(dist*1000));
		p.id=id;
		pause.erase(pause.size()-1,1);
		int pos=pause.find("'");
		p.pause=str2int(pause.substr(0,pos))*60+str2int(pause.substr(pos+1));
		p.st=string_to_timestamp(day+" "+st);
		p.ed=string_to_timestamp(day+" "+ed);
		if (mp[id].gender=='M'){
			if (p.dist<3000) continue;
		}
		else if (p.dist<1500) continue;
		if (double(p.dist)/(p.ed-p.st)<2) continue;
		if (double(p.dist)/(p.ed-p.st)>5) continue;
		if (p.pause>270) continue;
		if (double(p.dist)/steps>1.5) continue;
		mp[id].pracrec.push(p);
	}
	for (string id:ids){
		Practice lst;
		int cnt=0;
		auto pq=mp[id].pracrec;
		if (!pq.empty()){
			lst=pq.top();pq.pop();cnt=1;
			while (!pq.empty()){
				if (pq.top().st-lst.ed>=21600){
					lst=pq.top();
					cnt++;
				}
				pq.pop();
			}
		}
		// cout<<cnt<<'\n';
		for (int i=1;i<=7;i++){
			if (cnt>=practimes[i-1]){
				mp[id].c+=pracscore[i-1];
			}
		}
		for (int i=1;i<=5;i++){
			if (cnt+mp[id].traincnt>=projtimes[i-1]){
				mp[id].e++;
			}
		}
		writesp(id);
		writesp(mp[id].a+mp[id].b+mp[id].c+mp[id].d+mp[id].e);
		writeln(get_grade(mp[id].a+mp[id].b+mp[id].c+mp[id].d+mp[id].e));
	}
	return 0;
}