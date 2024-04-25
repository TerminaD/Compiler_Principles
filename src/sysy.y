%code requires {
  #include <memory>
  #include <string>
  #include "ast.hpp"
}

%{

#include <iostream>
#include <memory>
#include <string>
#include "ast.hpp"

// 声明 lexer 函数和错误处理函数
int yylex();
void yyerror(std::unique_ptr<BaseAST> &ast, const char *s);

using namespace std;

%}

// 定义 parser 函数和错误处理函数的附加参数
// 我们需要返回一个字符串作为 AST, 所以我们把附加参数定义成字符串的智能指针
// 解析完成后, 我们要手动修改这个参数, 把它设置成解析得到的字符串
%parse-param { std::unique_ptr<BaseAST> &ast }

// yylval 的定义, 我们把它定义成了一个联合体 (union)
// 因为 token 的值有的是字符串指针, 有的是整数
// 之前我们在 lexer 中用到的 str_val 和 int_val 就是在这里被定义的
// 至于为什么要用字符串指针而不直接用 string 或者 unique_ptr<string>?
// 请自行 STFW 在 union 里写一个带析构函数的类会出现什么情况
%union {
  std::string *str_val;
  int int_val;
  BaseAST *ast_val;
}

// lexer 返回的所有 token 种类的声明
// 注意 IDENT 和 INT_CONST 会返回 token 的值, 分别对应 str_val 和 int_val
%token INT RETURN LESSEQUAL GREATEREQUAL EQUAL NOTEQUAL ANDOP OROP CONST
%token <str_val> IDENT
%token <int_val> INT_CONST

// 非终结符的类型定义
%type <ast_val> FuncDef FuncType Block Stmt Number Exp PrimaryExp UnaryExp UnaryOp AddExp MulExp BinPriOp BinOp LOrExp RelExp EqExp LAndExp RelOp EqOp Decl ConstDecl BType ConstDef ConstDefList ConstInitVal BlockItemList BlockItem LVal ConstExp

%%

// 开始符, CompUnit ::= FuncDef, 大括号后声明了解析完成后 parser 要做的事情
// 之前我们定义了 FuncDef 会返回一个 str_val, 也就是字符串指针
// 而 parser 一旦解析完 CompUnit, 就说明所有的 token 都被解析了, 即解析结束了
// 此时我们应该把 FuncDef 返回的结果收集起来, 作为 AST 传给调用 parser 的函数
// $1 指代规则里第一个符号的返回值, 也就是 FuncDef 的返回值
CompUnit
  : FuncDef {
    std::cout << "CompUnit" << std::endl;
    auto comp_unit = make_unique<CompUnitAST>();
    comp_unit->func_def = unique_ptr<BaseAST>($1);
    ast = move(comp_unit);
  }
  ;

// FuncDef ::= FuncType IDENT '(' ')' Block;
// 我们这里可以直接写 '(' 和 ')', 因为之前在 lexer 里已经处理了单个字符的情况
// 解析完成后, 把这些符号的结果收集起来, 然后拼成一个新的字符串, 作为结果返回
// $$ 表示非终结符的返回值, 我们可以通过给这个符号赋值的方法来返回结果
// 你可能会问, FuncType, IDENT 之类的结果已经是字符串指针了
// 为什么还要用 unique_ptr 接住它们, 然后再解引用, 把它们拼成另一个字符串指针呢
// 因为所有的字符串指针都是我们 new 出来的, new 出来的内存一定要 delete
// 否则会发生内存泄漏, 而 unique_ptr 这种智能指针可以自动帮我们 delete
// 虽然此处你看不出用 unique_ptr 和手动 delete 的区别, 但当我们定义了 AST 之后
// 这种写法会省下很多内存管理的负担
Decl
  : ConstDecl {
    std::cout << "Decl" << std::endl;
    auto ast = new DeclAST();
    ast->const_decl = unique_ptr<BaseAST>($1);
    $$ = ast;
  }
  ;

ConstDecl
  : CONST BType ConstDef ConstDefList ';' {
    std::cout << "ConstDecl" << std::endl;
    auto ast = new ConstDeclAST();
    ast->b_type = unique_ptr<BaseAST>($2);
    ast->const_def_list = unique_ptr<BaseAST>($3);
    $$ = ast;
  }
  ;

BType
  : INT {
    std::cout << "BType" << std::endl;
    auto ast = new BTypeAST();
    ast->type = "int";
    $$ = ast;
  }
  ;

ConstDefList
  : {
    std::cout << "ConstDefList1" << std::endl;
    auto ast = new ConstDefListAST();
    $$ = ast;
  }
  | ConstDefList ',' ConstDef {
    std::cout << "ConstDefList2" << std::endl;
    auto ast = new ConstDefListAST();
    // Since unique_ptr's can't be copied, we move them
    // Makes all ConstDefLists except the final one invalid
    ast->const_defs = move(unique_ptr<BaseAST>($1)->const_defs); 
    (ast->const_defs).push_back(unique_ptr<BaseAST>($3));
    $$ = ast;
  }
  ;

ConstDef
  : IDENT '=' ConstInitVal {
    std::cout << "ConstDef" << std::endl;
    auto ast = new ConstDefAST();
    ast->ident = *unique_ptr<string>($1);
    ast->const_init_val = unique_ptr<BaseAST>($3);
    $$ = ast;
  }
  ;

ConstInitVal
  : ConstExp {
    std::cout << "ConstInitVal" << std::endl;
    auto ast = new ConstInitValAST();
    ast->const_exp = unique_ptr<BaseAST>($1);
    $$ = ast;
  }
  ;

// -----------------------------------------------------------------

FuncDef
  : FuncType IDENT '(' ')' Block {
    std::cout << "FuncDef" << std::endl;
    auto ast = new FuncDefAST();
    ast->func_type = unique_ptr<BaseAST>($1);
    ast->ident = *unique_ptr<string>($2);
    ast->block = unique_ptr<BaseAST>($5);
    $$ = ast;
  }
  ;

FuncType
  : INT {
    std::cout << "FuncType" << std::endl;
    auto ast = new FuncTypeAST();
    ast->func_type = "int";
    $$ = ast;
  }
  ;

// -----------------------------------------------------------------

Block
  : '{' BlockItemList '}' {
    std::cout << "Block" << std::endl;
    auto ast = new BlockAST();
    ast->block_item_list = unique_ptr<BaseAST>($2);
    $$ = ast;
  }
  ;

BlockItemList
  : {
    std::cout << "BlockItemList1" << std::endl;
    auto ast = new BlockItemListAST();
    $$ = ast;
  }
  | BlockItem BlockItemList {
    std::cout << "BlockItemList2" << std::endl;
    auto ast = new BlockItemListAST();
    // Since unique_ptr's can't be copied, we move them
    // Makes all BlockItemLists except the final one invalid
    ast->block_items = move(unique_ptr<BaseAST>($2)->block_items);
    (ast->block_items).push_back(unique_ptr<BaseAST>($1));
    $$ = ast;
  }
  ;

BlockItem
  : Decl {
    std::cout << "BlockItem1" << std::endl;
    auto ast = new BlockItemAST1();
    ast->decl = unique_ptr<BaseAST>($1);
    $$ = ast;
  }
  | Stmt {
    std::cout << "BlockItem2" << std::endl;
    auto ast = new BlockItemAST2();
    ast->stmt = unique_ptr<BaseAST>($1);
    $$ = ast;
  }
  ;

Stmt
  : RETURN Exp ';' {
    std::cout << "Stmt" << std::endl;
    auto ast = new StmtAST();
    ast->exp = unique_ptr<BaseAST>($2);
    $$ = ast;
  }
  ;

// -----------------------------------------------------------------

Exp
  : LOrExp {
    std::cout << "Exp" << std::endl;
    auto ast = new ExpAST();
    ast->l_or_exp = unique_ptr<BaseAST>($1);
    $$ = ast;
  }
  ;

LVal
  : IDENT {
    std::cout << "LVal" << std::endl;
    auto ast = new LValAST();
    ast->ident = *unique_ptr<string>($1);
    $$ = ast;
  }
  ;

PrimaryExp
  : '(' Exp ')' {
    std::cout << "PrimaryExp1" << std::endl;
    auto ast = new PrimaryExpAST1();
    ast->exp = unique_ptr<BaseAST>($2);
    $$ = ast;
  }
  | LVal {
    std::cout << "PrimaryExp3" << std::endl;
    auto ast = new PrimaryExpAST3();
    ast->l_val = unique_ptr<BaseAST>($1);
    $$ = ast;
  }
  | Number {
    std::cout << "PrimaryExp2" << std::endl;
    auto ast = new PrimaryExpAST2();
    ast->number = unique_ptr<BaseAST>($1);
    $$ = ast;
  }
  ;

Number
  : INT_CONST {
    std::cout << "Number" << std::endl;
    auto ast = new NumberAST();
    ast->int_const = $1;
    $$ = ast;
  }
  ;

UnaryExp
  : PrimaryExp {
    std::cout << "UnaryExp1" << std::endl;
    auto ast = new UnaryExpAST1();
    ast->primary_exp = unique_ptr<BaseAST>($1);
    $$ = ast;
  }
  | UnaryOp UnaryExp {
    std::cout << "UnaryExp2" << std::endl;
    auto ast = new UnaryExpAST2();
    ast->unary_op = unique_ptr<BaseAST>($1);
    ast->unary_exp = unique_ptr<BaseAST>($2);
    $$ = ast;
  }
  ;

UnaryOp
  : '+' {
    std::cout << "UnaryOp1" << std::endl;
    auto ast = new UnaryOpAST();
    ast->op = positive_op;
    $$ = ast;
  }
  | '-' {
    std::cout << "UnaryOp2" << std::endl;
    auto ast = new UnaryOpAST();
    ast->op = negative_op;
    $$ = ast;
  }
  | '!' {
    std::cout << "UnaryOp3" << std::endl;
    auto ast = new UnaryOpAST();
    ast->op = not_op;
    $$ = ast;
  }
  ;

MulExp
  : UnaryExp {
    std::cout << "MulExp1" << std::endl;
    auto ast = new MulExpAST1();
    ast->unary_exp = unique_ptr<BaseAST>($1);
    $$ = ast;
  }
  | MulExp BinPriOp UnaryExp {
    std::cout << "MulExp2" << std::endl;
    auto ast = new MulExpAST2();
    ast->mul_exp = unique_ptr<BaseAST>($1);
    ast->bin_pri_op = unique_ptr<BaseAST>($2);
    ast->unary_exp = unique_ptr<BaseAST>($3);
    $$ = ast;
  }
  ;

BinPriOp
  : '*' {
    std::cout << "BinPriOp1" << std::endl;
    auto ast = new BinPriOpAST();
    ast->op = mul_op;
    $$ = ast;
  }
  | '/' {
    std::cout << "BinPriOp2" << std::endl;
    auto ast = new BinPriOpAST();
    ast->op = div_op;
    $$ = ast;
  }
  | '%' {
    std::cout << "BinPriOp3" << std::endl;
    auto ast = new BinPriOpAST();
    ast->op = mod_op;
    $$ = ast;
  }
  ;

AddExp
  : MulExp {
    std::cout << "AddExp1" << std::endl;
    auto ast = new AddExpAST1();
    ast->mul_exp = unique_ptr<BaseAST>($1);
    $$ = ast;
  }
  | AddExp BinOp MulExp {
    std::cout << "AddExp2" << std::endl;
    auto ast = new AddExpAST2();
    ast->add_exp = unique_ptr<BaseAST>($1);
    ast->bin_op = unique_ptr<BaseAST>($2);
    ast->mul_exp = unique_ptr<BaseAST>($3);
    $$ = ast;
  }
  ;

BinOp
  : '+' {
    std::cout << "BinOp1" << std::endl;
    auto ast = new BinOpAST();
    ast->op = add_op;
    $$ = ast;
  }
  | '-' {
    std::cout << "BinOp2" << std::endl;
    auto ast = new BinOpAST();
    ast->op = sub_op;
    $$ = ast;
  }
  ;

RelExp
  : AddExp {
    std::cout << "RelExp1" << std::endl;
    auto ast = new RelExpAST1();
    ast->add_exp = unique_ptr<BaseAST>($1);
    $$ = ast;
  }
  | RelExp RelOp AddExp {
    std::cout << "RelExp2" << std::endl;
    auto ast = new RelExpAST2();
    ast->rel_exp = unique_ptr<BaseAST>($1);
    ast->rel_op = unique_ptr<BaseAST>($2);
    ast->add_exp = unique_ptr<BaseAST>($3);
    $$ = ast;
  }
  ;

RelOp
  : '<' {
    std::cout << "RelOp1" << std::endl;
    auto ast = new RelOpAST();
    ast->op = less_op;
    $$ = ast;
  }
  | '>' {
    std::cout << "RelOp2" << std::endl;
    auto ast = new RelOpAST();
    ast->op = greater_op;
    $$ = ast;
  }
  | LESSEQUAL {
    std::cout << "RelOp3" << std::endl;
    auto ast = new RelOpAST();
    ast->op = less_equal_op;
    $$ = ast;
  }
  | GREATEREQUAL {
    std::cout << "RelOp4" << std::endl;
    auto ast = new RelOpAST();
    ast->op = greater_equal_op;
    $$ = ast;
  }
  ;

EqExp
  : RelExp {
    std::cout << "EqExp1" << std::endl;
    auto ast = new EqExpAST1();
    ast->rel_exp = unique_ptr<BaseAST>($1);
    $$ = ast;
  }
  | EqExp EqOp RelExp {
    std::cout << "EqExp2" << std::endl;
    auto ast = new EqExpAST2();
    ast->eq_exp = unique_ptr<BaseAST>($1);
    ast->eq_op = unique_ptr<BaseAST>($2);
    ast->rel_exp = unique_ptr<BaseAST>($3);
    $$ = ast;
  }
  ;

EqOp
  : EQUAL {
    std::cout << "EqOp1" << std::endl;
    auto ast = new EqOpAST();
    ast->op = equal_op;
    $$ = ast;
  }
  | NOTEQUAL {
    std::cout << "EqOp2" << std::endl;
    auto ast = new EqOpAST();
    ast->op = not_equal_op;
    $$ = ast;
  }
  ;

LAndExp
  : EqExp {
    std::cout << "LAndExp1" << std::endl;
    auto ast = new LAndExpAST1();
    ast->eq_exp = unique_ptr<BaseAST>($1);
    $$ = ast;
  }
  | LAndExp ANDOP EqExp {
    std::cout << "LAndExp2" << std::endl;
    auto ast = new LAndExpAST2();
    ast->l_and_exp = unique_ptr<BaseAST>($1);
    ast->eq_exp = unique_ptr<BaseAST>($3);
    $$ = ast;
  }
  ;

LOrExp
  : LAndExp {
    std::cout << "LOrExp1" << std::endl;
    auto ast = new LOrExpAST1();
    ast->l_and_exp = unique_ptr<BaseAST>($1);
    $$ = ast;
  }
  | LOrExp OROP LAndExp {
    std::cout << "LOrExp2" << std::endl;
    auto ast = new LOrExpAST2();
    ast->l_or_exp = unique_ptr<BaseAST>($1);
    ast->l_and_exp = unique_ptr<BaseAST>($3);
    $$ = ast;
  }
  ;

ConstExp
  : Exp {
    std::cout << "ConstExp" << std::endl;
    auto ast = new ConstExpAST();
    ast->exp = unique_ptr<BaseAST>($1);
    $$ = ast;
  }
  ;

%%

// 定义错误处理函数, 其中第二个参数是错误信息
// parser 如果发生错误 (例如输入的程序出现了语法错误), 就会调用这个函数
void yyerror(unique_ptr<BaseAST> &ast, const char *s) {
  cerr << "error: " << s << endl;
}
