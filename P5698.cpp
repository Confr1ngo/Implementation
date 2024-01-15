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
	template<typename T> T fmaxmain(T x,T y){
		return (x>y? x:y);
	}
	template<typename T> T fmax(T x,T y){
		return fmaxmain(x,y);
	}
	template<typename T,typename... Ts> T fmax(T x,Ts... args){
		return fmaxmain(x,fmax(args...));
	}
	template<typename T> T fminmain(T x,T y){
		return (x<y? x:y);
	}
	template<typename T> T fmin(T x,T y){
		return fminmain(x,y);
	}
	template<typename T,typename... Ts> T fmin(T x,Ts... args){
		return fminmain(x,fmin(args...));
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
#define int long long
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
struct Int{
	vector<int>v;
	Int(){v.clear();v.emplace_back(0);}
	~Int(){}
	friend Int operator+(Int &a,Int &b){
		Int res;
		res.v.clear();
		for (int i=0;i<max((int)a.v.size(),(int)b.v.size());i++){
			int val1=0,val2=0;
			if (i<(int)a.v.size()) val1=a.v[i];
			if (i<(int)b.v.size()) val2=b.v[i];
			res.v.emplace_back(val1+val2);
		}
		return res;
	}
	friend Int operator*(Int &a,Int &b){
		Int res;
		res.v.clear();
		res.v.resize(a.v.size()+b.v.size()-1);
		for (int i=0;i<(int)a.v.size();i++){
			for (int j=0;j<(int)b.v.size();j++){
				res.v[i+j]+=a.v[i]*b.v[j];
			}
		}
		while (res.v.back()==0 && (int)res.v.size()>1) res.v.pop_back();
		res.v.shrink_to_fit();
		return res;
	}
	const Int& operator=(Int& i){
		v=i.v;
		return *this;
	}
};
Int numeral_eval(string s){
	if (s[0]=='-' || s[0]=='+') s="0"+s;
	// cerr<<"evaling "<<s<<endl;
	stack<Int>num;
	stack<char>op;
	map<char,int>prio;
	prio['+']=1;
	prio['*']=2;
	prio['(']=0;
	prio[')']=0;
	int i=0;
	while (i<(int)s.size()){
		if (s[i]=='n'){
			Int t;t.v.emplace_back(1);
			num.push(t);
			i++;
		}
		else if (s[i]>='0' && s[i]<='9'){
			int sum=0;
			while (s[i]>='0' && s[i]<='9'){
				sum=sum*10+(s[i]-'0');
				i++;
			}
			Int t;t.v.clear();
			t.v.emplace_back(sum);
			num.push(t);
		}
		else{
			if (s[i]=='(') op.push(s[i]);
			else if (s[i]==')'){
				while (op.size() && op.top()!='('){
					char op_now=op.top();op.pop();
					Int b=num.top();num.pop();
					Int a=num.top();num.pop();
					if (op_now=='+') num.push(a+b);
					else if (op_now=='*') num.push(a*b);
					else assert(!"Invalid operator!");
				}
				op.pop();
			}
			else{
				while (op.size() && prio[op.top()]>=prio[s[i]]){
					char op_now=op.top();op.pop();
					Int b=num.top();num.pop();
					Int a=num.top();num.pop();
					if (op_now=='+') num.push(a+b);
					else if (op_now=='*') num.push(a*b);
					else assert(!"Invalid operator!");
				}
				op.push(s[i]);
			}
			i++;
		}
	}
	while (op.size()){
		char op_now=op.top();op.pop();
		Int b=num.top();num.pop();
		Int a=num.top();num.pop();
		if (op_now=='+') num.push(a+b);
		else if (op_now=='*') num.push(a*b);
		else assert(!"Invalid operator!");
	}
	return num.top();
}
vector<string>split_by(string s,char c){
	vector<string>res;
	res.clear();
	string now="";
	for (auto i:s){
		if (i==c){
			if (now!=""){
				res.emplace_back(now);
				now="";
			}
		}
		else now+=i;
	}
	if (now!="") res.emplace_back(now);
	return res;
}
signed main(){
	string full((istreambuf_iterator<char>(cin)),istreambuf_iterator<char>()),eval="";
	for (int i=0;i<(int)full.size();i++){
		if (full[i]=='\r'){
			full.replace(i,1," ");
			i--;
			continue;
		}
		if (full[i]=='\n'){
			full.replace(i,1," ");
			i--;
			continue;
		}
	}
	vector<string>ss=split_by(full,' ');
	ss.erase(ss.begin());
	ss.erase(--ss.end());
	for (int i=0;i<(int)ss.size();i++){
		if (ss[i]=="loop"){
			if (ss[i+1]=="0"){
				ss[i+1]="n";
			}
			// ????? wtf is that
			// upd: data fixed
		}
		if (ss[i]=="break"){
			bool flag=false;
			int pos=i,cnt=0;
			while (pos>=0){
				if (ss[pos]=="continue" && !cnt) flag=true;
				if (ss[pos]=="loop" && !cnt) break;
				if (ss[pos]=="loop") cnt++;
				if (ss[pos]=="end") cnt--;
				pos--;
			}
			if (pos==-1) continue;
			if (!flag){
				pos++;
				ss[pos]="1";
			}
		}
	}
	int cnt=0;
	for (int i=0;i<(int)ss.size();i++){
		if (ss[i]=="loop"){
			eval+="+"+ss[++i]+"*(0";
			cnt++;
		}
		else if (ss[i]=="op") eval+="+"+ss[++i];
		else if (ss[i]=="break" || ss[i]=="continue"){
			if (!cnt) continue;
			int cnt2=0;
			while (i<(int)ss.size()){
				if (ss[i]=="end" && !cnt2) break;
				if (ss[i]=="end") cnt2--;
				if (ss[i]=="loop") cnt2++;
				i++;
			}
			eval+="+0)";
			cnt--;
		}
		else{
			eval+="+0)";
			cnt--;
		}
	}
	// cerr<<eval<<endl;
	Int ans=numeral_eval(eval);
	// writesp(ans.v);
	bool flag=true;
	for (int i=ans.v.size()-1;i>=0;i--){
		if (i==0){
			if (ans.v[i]){
				if (!flag) write("+");
				write(ans.v[i]);
			}
			else if (flag){
				write(0);
			}
		}
		else if (i==1){
			if (ans.v[i]){
				if (!flag) write("+");
				else flag=false;
				if (ans.v[i]>1) write(ans.v[i]);
				write("n");
			}
		}
		else{
			if (ans.v[i]){
				if (!flag) write("+");
				else flag=false;
				if (ans.v[i]>1) write(ans.v[i]);
				write("n^");
				write(i);
			}
		}
	}
	writeln();
	return 0;
}