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
map<string,string>mp;
struct Student{
	int cid,s[4];
	long long sid;
	string name;
}a[1010];
int cnt;
long long str2int(string s){
	long long res=0;
	for (char c:s){
		res=res*10+c-'0';
	}
	return res;
}
void init(){
	mp["spms"]="Welcome to Student Performance Management System (SPMS).\n\n1 - Add\n2 - Remove\n3 - Query\n4 - Show ranking\n5 - Show Statistics\n0 - Exit\n";
	mp["add"]="Please enter the SID, CID, name and four scores. Enter 0 to finish.";
	mp["siddup"]="Duplicated SID.";
	mp["sidorname"]="Please enter SID or name. Enter 0 to finish.";
	mp["remove"]=" student(s) removed.";
	mp["ranking"]="Showing the ranklist hurts students' self-esteem. Don't do that.";
	mp["inputcid"]="Please enter class ID, 0 for the whole statistics.";
}
int menu(){
	static int res;
	writeln(mp["spms"]);
	read(res);
	return res;
}
void write_score(int x){
	write(x/100);
	putchar('.');
	if (x%100<10) putchar('0');
	write(x%100);
}
void add(){
	writeln(mp["add"]);
	long long sid;
	read(sid);
	while (sid){
		int cid,sc[4];
		string name;
		read(cid,name,sc[0],sc[1],sc[2],sc[3]);
		bool dup=false;
		for (int i=1;i<=cnt;i++){
			if (a[i].sid==sid){
				writeln(mp["siddup"]);
				writeln(mp["add"]);
				read(sid);
				dup=true;
				break;
			}
		}
		if (dup) continue;
		a[++cnt].sid=sid;
		a[cnt].cid=cid;
		a[cnt].name=name;
		for (int i=0;i<4;i++){
			a[cnt].s[i]=sc[i];
		}
		writeln(mp["add"]);
		read(sid);
	}
}
void remove(){
	int ans;
	writeln(mp["sidorname"]);
	string res;
	read(res);
	while (res!="0"){
		ans=0;
		for (int i=1;i<=cnt;i++){
			if (res[0]>='0' && res[0]<='9'){
				long long sid=str2int(res);
				if (a[i].sid==sid){
					for (int j=i;j<cnt;j++){
						a[j].cid=a[j+1].cid;
						a[j].sid=a[j+1].sid;
						a[j].name=a[j+1].name;
						for (int k=0;k<4;k++){
							a[j].s[k]=a[j+1].s[k];
						}
					}
					cnt--;
					i--;
					ans++;
					continue;
				}
			}
			else{
				if (a[i].name==res){
					for (int j=i;j<cnt;j++){
						a[j].cid=a[j+1].cid;
						a[j].sid=a[j+1].sid;
						a[j].name=a[j+1].name;
						for (int k=0;k<4;k++){
							a[j].s[k]=a[j+1].s[k];
						}
					}
					cnt--;
					i--;
					ans++;
					continue;
				}
			}
		}
		write(ans);
		writeln(mp["remove"]);
		writeln(mp["sidorname"]);
		read(res);
	}
}
void query(){
	writeln(mp["sidorname"]);
	string res;
	read(res);
	while (res!="0"){
		for (int i=1;i<=cnt;i++){
			if ((res[0]>='0' && res[0]<='9' && a[i].sid==str2int(res)) || ((res[0]<'0' || res[0]>'9') && a[i].name==res)){
				int rk=1,sc=a[i].s[0]+a[i].s[1]+a[i].s[2]+a[i].s[3];
				for (int j=1;j<=cnt;j++){
					if (j==i) continue;
					if (a[j].s[0]+a[j].s[1]+a[j].s[2]+a[j].s[3]>sc) rk++;
				}
				writesp(rk);
				for (int j=to_string(a[i].sid).size();j<10;j++){
					putchar('0');
				}
				writesp(a[i].sid);
				writesp(a[i].cid);
				writesp(a[i].name);
				for (int j=0;j<4;j++){
					writesp(a[i].s[j]);
				}
				writesp(sc);
				write_score(int(round(sc*25)));
				writeln();
			}
		}
		writeln(mp["sidorname"]);
		read(res);
	}
}
void ranking(){
	writeln(mp["ranking"]);
}
void stat(){
	int sum[4],pass[4],passcnt[5],cid,tot=0;
	memset(sum,0,sizeof(sum));
	memset(pass,0,sizeof(pass));
	memset(passcnt,0,sizeof(passcnt));
	writeln(mp["inputcid"]);read(cid);
	for (int i=1;i<=cnt;i++){
		if (cid==0 || cid==a[i].cid){
			tot++;
			int temp=0;
			for (int j=0;j<4;j++){
				sum[j]+=a[i].s[j];
				if (a[i].s[j]>=60){
					pass[j]++;
					temp++;
				}
			}
			passcnt[temp]++;
		}
	}
	writeln("Chinese");
	writesp("Average Score:");
	write_score(int(round(sum[0]*100.0/tot+1e-5)));writeln();
	writesp("Number of passed students:");
	writeln(pass[0]);
	writesp("Number of failed students:");
	writeln(tot-pass[0]);
	writeln();
	
	writeln("Mathematics");
	writesp("Average Score:");
	write_score(int(round(sum[1]*100.0/tot+1e-5)));writeln();
	writesp("Number of passed students:");
	writeln(pass[1]);
	writesp("Number of failed students:");
	writeln(tot-pass[1]);
	writeln();
	
	writeln("English");
	writesp("Average Score:");
	write_score(int(round(sum[2]*100.0/tot+1e-5)));writeln();
	writesp("Number of passed students:");
	writeln(pass[2]);
	writesp("Number of failed students:");
	writeln(tot-pass[2]);
	writeln();

	writeln("Programming");
	writesp("Average Score:");
	write_score(int(round(sum[3]*100.0/tot+1e-5)));writeln();
	writesp("Number of passed students:");
	writeln(pass[3]);
	writesp("Number of failed students:");
	writeln(tot-pass[3]);
	writeln();

	writeln("Overall:");
	writesp("Number of students who passed all subjects:");
	writeln(passcnt[4]);
	writesp("Number of students who passed 3 or more subjects:");
	writeln(passcnt[3]+passcnt[4]);
	writesp("Number of students who passed 2 or more subjects:");
	writeln(passcnt[2]+passcnt[3]+passcnt[4]);
	writesp("Number of students who passed 1 or more subjects:");
	writeln(passcnt[1]+passcnt[2]+passcnt[3]+passcnt[4]);
	writesp("Number of students who failed all subjects:");
	writeln(passcnt[0]);
	writeln();
}
signed main(){
	init();
	int res=menu();
	while (res){
		if (res==1) add();
		else if (res==2) remove();
		else if (res==3) query();
		else if (res==4) ranking();
		else stat();
		res=menu();
	}
	return 0;
}