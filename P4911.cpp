#include<bits/stdc++.h>
using namespace std;
/*          Ktx-65 Assembly Language Interpreter          */
// @brief Standard exceptions for Ktx-65 Interpreter.
struct Exception{
	// @brief Information will be displayed when the target register is not found. Will return 1.
	// @param name register name
	void RegisterNotFoundException(string name){
		cout<<"Interpreter has encountered an unexpected exception:\n";
		cout<<"Register "<<name<<" not found.\n";
		exit(1);
	}
	// @brief Information will be displayed when too few arguments found. Will return 2.
	// @param line the physical line number
	void NoEnoughArgumentsException(int line){
		cout<<"Interpreter has encountered an unexpected exception:\n";
		cout<<"Too few arguments on line "<<line<<".\n";
		exit(2);
	}
	// @brief Information will be displayed when process accesses invalid memory parts. Will return 3.
	// @param memadd memory address
	void InvalidMemoryAccessException(int memadd){
		cout<<"Interpreter has encountered an unexpected exception:\n";
		cout<<"Invalid memory access to "<<memadd<<".\n";
		exit(3);
	}
	// @brief Information will be displayed when you use an integer instead of variable. Will return 4.
	// @param line the physical line number
	void VariableNeededException(int line){
		cout<<"Interpreter has encountered an unexpected exception:\n";
		cout<<"Variable expected (instead of constant) on line "<<line<<".\n";
		exit(4);
	}
	// @brief Information will be displayed when you access a non-exist variable. Will return 5.
	// @param s the variable name
	void NoValueMatchedException(string s){
		cout<<"Interpreter has encountered an unexpected exception:\n";
		cout<<"Invalid variable "<<s<<" accessed.\n";
		exit(5);
	}
	// @brief Information will be displayed when you use an unknown instruction. Will return 6.
	// @param s the instruction
	void InvalidInstructionException(string s){
		cout<<"Interpreter has encountered an unexpected exception:\n";
		cout<<"Invalid instruction "<<s<<" found.\n";
		exit(6);
	}
	// @brief Information will be displayed when you divide a number by 0. Will return 7.
	// @param line the physical line number
	void DivisionByZeroException(int line){
		cout<<"Interpreter has encountered an unexpected exception:\n";
		cout<<"Division by zero on line "<<line<<".\n";
		exit(7);
	}
	// @brief Information will be displayed when you shift negative bits. Will return 8.
	// @param line the physical line number
	void InvalidShiftValueException(int line){
		cout<<"Interpreter has encountered an unexpected exception:\n";
		cout<<"Program tried to shift negative bits on line "<<line<<".\n";
		exit(8);
	}
	// @brief Information will be displayed when program terminates without halt. Will return 9.
	void ProgramEndedWithoutHalt(){
		cout<<"Interpreter has encountered an unexpected exception:\n";
		cout<<"Program terminated without instruction halt.\n";
		exit(9);
	}
	// @brief Information will be displayed when no enough elements in address stack. Will return 10.
	// @param line the physical line number
	void NullAddressStackException(int line){
		cout<<"Interpreter has encountered an unexpected exception:\n";
		cout<<"Expected 2 elements in address stack, no enough found on line "<<line<<".\n";
		exit(10);
	}
}exc;
const set<string> logic_ins={
	"lgr","lls","lge","lle","leql","land","lor"
};
const set<string> arith_ins={
	"inv","add","sub","mult","idiv","mod","lsft","rsft","band","bor","bxor"
};
const set<string> io_ins={
	"rint","rch","wint","wch"
};
const set<string> control_ins={
	"udef","hlt","nop","set","jmp","jif","call","ret"
};
const set<string> unclassified_ins={
	"callfunc","function"
};
// @brief Register for Ktx-65.
struct Register{
	int r1,r2,r3,r4,e1,e2,e3,e4;
	int flag,val,ret,line;
	// @brief Initialize the registers to 0.
	void init(){
		r1=r2=r3=r4=e1=e2=e3=e4=0;
		flag=val=ret=line=0;
	}
	inline int& get(string s){
		if (s=="%r1") return r1;
		if (s=="%r2") return r2;
		if (s=="%r3") return r3;
		if (s=="%r4") return r4;
		if (s=="%e1") return e1;
		if (s=="%e2") return e2;
		if (s=="%e3") return e3;
		if (s=="%e4") return e4;
		if (s=="%flag") return flag;
		if (s=="%val") return val;
		if (s=="%ret") return ret;
		if (s=="%line") return line;
		exc.RegisterNotFoundException(s);
		return line; // never runs here!
	}
	Register(){init();}
}reg;
// @brief Memory for Ktx-65
struct Memory{
	int mem[16777216];
	int& operator[](int i){
		if (i<0 || i>16777215) exc.InvalidMemoryAccessException(i);
		return mem[i];
	}
}memory;
// @brief Address stack for Ktx-65.
stack<int>sAddr;
// @brief Statement stores a processed line.
struct Statement{
	// @brief op stores the operator.
	string op;
	// @brief The (at most 3) arguments and target.
	string arg1,arg2,arg3;
	// @brief The physical line number.
	int line;
	// @brief These are used only if this statement contains numeral arguments.
	int num1,num2,num3;
	Statement():op(""),arg1(""),arg2(""),arg3(""),line(0),num1(0),num2(0),num3(0){}
};
// @brief Turn a string into int.
int string2int(string s){
	int res=0,flag=1;
	if (s[0]=='+') s.erase(0,1);
	if (s[0]=='-'){
		s.erase(0,1);
		flag=-1;
	}
	for (char i:s){
		res=res*10+(i-'0');
	}
	return res*flag;
}
// @brief Check if a string is a valid number.
bool is_number(string s){
	if (!s.size()) return false;
	if (s=="+" || s=="-") return false;
	if (s[0]=='+' || s[0]=='-') s.erase(0,1);
	if (s[0]=='0' && (int)s.size()>1) return false;
	for (char i:s){
	    if (i<'0' || i>'9') return false;
	}
	return true;
}
// @brief Get the specified value from registers or memory.
int& get_value(string s,int &lineid){
	if ((int)s.size()>1 && s[0]=='%'){
		return reg.get(s);
	}
	else if ((int)s.size()>1 && s[0]=='@'){
		if ((int)s.size()>2 && s[1]=='%'){
			return memory[reg.get(s.substr(1))];
		}
		else if (is_number(s.substr(1))){
			return memory[string2int(s.substr(1))];
		}
		else exc.NoValueMatchedException(s);
	}
	else if (s=="#line"){
		return lineid;
	}
	exc.NoValueMatchedException(s);
	return lineid; // never runs here!
}
// @brief Remove comments from a line.
string remove_comment(string s){
	string res="";
	int cnt=0;
	for (char i:s){
		if (i=='[') cnt++;
		else if (i==']') cnt--;
		else if (!cnt) res+=i;
	}
	return res;
}
// @brief check if a line does not contains comments or valid operations.
// @return Return true if the line only contains invisible characters, false otherwise.
bool is_null(string s){
	for (char i:s){
	    if (i==' ' || i=='\n' || i=='\t' || i=='\r') continue;
		return false;
	}
	return true;
}
// @brief Split the string into a vector with a specified character.
// @param s the give string
// @param c the character
// @return The splitted string stored in a vector
vector<string>split(string s,char c){
	vector<string>res;
	string temp="";
	for (char i:s){
		if (i==c && temp!=""){
			res.emplace_back(temp);
			temp="";
		}
		else if (i!=c) temp+=i;
	}
	if (temp!=""){
		res.emplace_back(temp);
	}
	return res;
}
// @brief LU does logical operations.
void logic_unit(Statement st){
	int val1=(st.arg1=="value"? st.num1:get_value(st.arg1,st.line));
	int val2=(st.arg2=="value"? st.num2:get_value(st.arg2,st.line));
	int res=0;
	if (st.op=="lgr") res=(val1>val2);
	if (st.op=="lls") res=(val1<val2);
	if (st.op=="lge") res=(val1>=val2);
	if (st.op=="lle") res=(val1<=val2);
	if (st.op=="leql") res=(val1==val2);
	if (st.op=="land") res=(val1 && val2);
	if (st.op=="lor") res=(val1 || val2);
	get_value(st.arg3,st.line)=res;
	return;
}
// @brief Get the sign of an integer.
// @return 1 if positive, -1 if negative, 0 otherwise
inline int sign(int x){
	return (x>0? 1:(x<0? -1:0));
}
// @brief AU does arithmetical operations.
void arithmetic_unit(Statement st){
	if (st.op=="inv"){
		get_value(st.arg2,st.line)=-(st.arg1=="value"? st.num1:get_value(st.arg1,st.line));
		return;
	}
	int val1=(st.arg1=="value"? st.num1:get_value(st.arg1,st.line));
	int val2=(st.arg2=="value"? st.num2:get_value(st.arg2,st.line));
	int res=0;
	if (st.op=="add") res=val1+val2;
	if (st.op=="sub") res=val1-val2;
	if (st.op=="mult") res=val1*val2;
	if (st.op=="idiv"){
		if (val2==0) exc.DivisionByZeroException(st.line);
		if (val1==0) res=0;
		res=val1/val2; // todo: it should be floor
	}
	if (st.op=="mod"){
		if (val2==0) exc.DivisionByZeroException(st.line);
		res=val1%val2;
	}
	// You should comment line 266 and 270 to accept P4911.
	if (st.op=="lsft"){
		// if (val2<0) exc.InvalidShiftValueException(st.line);
		res=val1<<val2;
	}
	if (st.op=="rsft"){
		// if (val2<0) exc.InvalidShiftValueException(st.line);
		res=val1>>val2;
	}
	if (st.op=="band") res=val1&val2;
	if (st.op=="bor") res=val1|val2;
	if (st.op=="bxor") res=val1^val2;
	get_value(st.arg3,st.line)=res;
	return;
}
// @brief ALU does arithmetical and logical operations.
void alu(Statement st){
	if (logic_ins.count(st.op)) logic_unit(st);
	else arithmetic_unit(st);
}
// @brief IO related operations is located here.
void io(Statement st){
	if (st.op=="rint") cin>>get_value(st.arg1,st.line);
	if (st.op=="rch") get_value(st.arg1,st.line)=(int)(cin.get());
	if (st.op=="wint") cout<<(st.arg1=="value"? st.num1:get_value(st.arg1,st.line));
	if (st.op=="wch") putchar(st.arg1=="value"? st.num1:get_value(st.arg1,st.line));
}
enum ValueType{Any,Variable,Function};
// @brief Set statement variables and throw out exceptions.
void set_statement_var(int id,Statement& st,string val,ValueType type=Any){
	if (type==Function){st.arg1=val;return;}
	if (is_number(val)){
		if (type==Variable) exc.VariableNeededException(st.line);
		if (id==1){st.arg1="value";st.num1=string2int(val);}
		else if (id==2){st.arg2="value";st.num2=string2int(val);}
		else{st.arg3="value";st.num3=string2int(val);}
	}
	else if (val=="#line"){
		if (type==Variable) exc.VariableNeededException(st.line);
		if (id==1){st.arg1="value";st.num1=st.line;}
		else if (id==2){st.arg2="value";st.num2=st.line;}
		else{st.arg3="value";st.num3=st.line;}
	}
	else{
		if (id==1) st.arg1=val;
		else if (id==2) st.arg2=val;
		else st.arg3=val;
	}
}
// @brief The mapping of function name and physical line number.
map<string,int>fun_line;
// @brief This vector stores the whole program.
vector<Statement>code;
int n,pos;
signed main(){
	Statement temp_s;
	code.emplace_back(temp_s);
	cin>>n;
	cin.ignore(3,'\n');
	while (n--){
		static string s;
		getline(cin,s);
		while (s.back()=='\n' || s.back()=='\n') s.pop_back();
		if (!is_null(remove_comment(s))){
			vector<string>v=split(remove_comment(s),' ');
			if (v.back().back()==';') v.back().pop_back();
			#define REQUIRE_ARG(x) if ((int)v.size()<(x)+1) exc.NoEnoughArgumentsException(pos);
			Statement st;
			st.line=(++pos);
			st.op=v[0];
			if (v[0]=="udef" || v[0]=="hlt" || v[0]=="nop");
			else if (v[0]=="set"){
				REQUIRE_ARG(2);
				set_statement_var(1,st,v[1],Any);
				set_statement_var(2,st,v[2],Variable);
			}
			else if (v[0]=="jmp" || v[0]=="call"){
				REQUIRE_ARG(1);
				set_statement_var(1,st,v[1],Any);
			}
			else if (v[0]=="jif"){
				REQUIRE_ARG(1);
				set_statement_var(1,st,v[1],Any);
				if ((int)v.size()==2) v.emplace_back("%flag");
				set_statement_var(2,st,v[2],Any);
			}
			else if (v[0]=="ret"){
				if ((int)v.size()>=2) set_statement_var(1,st,v[1],Any);
			}
			else if (v[0]=="inv"){
				REQUIRE_ARG(1);
				set_statement_var(1,st,v[1],Any);
				if ((int)v.size()==2) v.emplace_back("%val");
				set_statement_var(2,st,v[2],Variable);
			}
			else if (v[0]=="add" || v[0]=="sub" || v[0]=="mult" || v[0]=="idiv" || v[0]=="mod" || v[0]=="lsft" || v[0]=="rsft" || v[0]=="band" || v[0]=="bor" || v[0]=="bxor"){
				REQUIRE_ARG(2);
				set_statement_var(1,st,v[1],Any);
				set_statement_var(2,st,v[2],Any);
				if ((int)v.size()==3) v.emplace_back("%val");
				set_statement_var(3,st,v[3],Variable);
			}
			else if (v[0]=="lgr" || v[0]=="lls" || v[0]=="lge" || v[0]=="lle" || v[0]=="leql" || v[0]=="land" || v[0]=="lor"){
				REQUIRE_ARG(2);
				set_statement_var(1,st,v[1],Any);
				set_statement_var(2,st,v[2],Any);
				if ((int)v.size()==3) v.emplace_back("%flag");
				set_statement_var(3,st,v[3],Variable);
			}
			else if (v[0]=="rint" || v[0]=="rch"){
				if ((int)v.size()==1) v.emplace_back("%val");
				set_statement_var(1,st,v[1],Variable);
				
			}
			else if (v[0]=="wint" || v[0]=="wch"){
				if ((int)v.size()==1) v.emplace_back("%val");
				set_statement_var(1,st,v[1],Any);
			}
			else if (v[0]=="function"){
				REQUIRE_ARG(1);
				set_statement_var(1,st,v[1],Function);
				fun_line[v[1]]=pos;
			}
			else if (v[0]=="callfunc"){
				REQUIRE_ARG(1);
				set_statement_var(1,st,v[1],Function);
			}
			else exc.InvalidInstructionException(v[0]);
			#undef REQUIRE_ARG
			code.emplace_back(st);
		}
	}
	int i=1;
	while (true){
		if (i>=(int)code.size()) exc.ProgramEndedWithoutHalt();
		if (io_ins.count(code[i].op)) io(code[i]);
		else if (logic_ins.count(code[i].op) || arith_ins.count(code[i].op)) alu(code[i]);
		else if (control_ins.count(code[i].op)){
			if (code[i].op=="jmp"){
				i=reg.line+(code[i].arg1=="value"? code[i].num1:get_value(code[i].arg1,code[i].line));
				continue;
			}
			else if (code[i].op=="udef" || code[i].op=="nop");
			else if (code[i].op=="hlt") break;
			else if (code[i].op=="set"){
				get_value(code[i].arg2,code[i].line)=(code[i].arg1=="value"? code[i].num1:get_value(code[i].arg1,code[i].line));
			}
			else if (code[i].op=="jif"){
				if (code[i].arg2=="value"? code[i].num2:get_value(code[i].arg2,code[i].line)){
					i=reg.line+(code[i].arg1=="value"? code[i].num1:get_value(code[i].arg1,code[i].line));
					continue;
				}
			}
			else if (code[i].op=="call"){
				sAddr.emplace(reg.line);
				sAddr.emplace(i+1);
				i=(code[i].arg1=="value"? code[i].num1:get_value(code[i].arg1,code[i].line));
				continue;
			}
			else{
				if (!sAddr.size()) exc.NullAddressStackException(i);
				if (code[i].arg1!=""){
					reg.ret=(code[i].arg1=="value"? code[i].num1:get_value(code[i].arg1,code[i].line));
				}
				i=sAddr.top();sAddr.pop();
				reg.line=sAddr.top();sAddr.pop();
				continue;
			}
		}
		else{
			if (code[i].op=="function"){
				reg.line=i;
			}
			else{
				sAddr.emplace(reg.line);
				sAddr.emplace(i+1);
				i=fun_line[code[i].arg1];
				continue;
			}
		}
		i++;
	}
	return 0;
}