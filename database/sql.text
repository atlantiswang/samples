### SQL语言共分为四大类：数据查询语言DQL，数据操纵语言DML，数据定义语言DDL，数据控制语言DCL。

## DQL
from子句
select id,salary,nvl(manager_id,-1) from s_emp;
8.数据的排重显示 distinct
//select salary from s_emp;
select distinct salary from s_emp;
多字段排重:当所有字段的值相同时排除
//select salary,title from s_emp;
select distinct salary,title from s_emp;
特殊的where条件
select id,salary from s_emp;
select id,salary from s_emp where 1=1;//与上面的一样
select id,salary from s_emp where 1=2;//没有数据1=2,所以一条数据都没有
数字类型的数据的限制
列出月薪大于1400的员工的id first_name salary
select id,first_name from s_emp where salary>1400;//=,!=,<
select id from s_emp where first_name='Mai';//如果不加单引号，就把Mai当作一个字段
字符串的值是区分大小写的
sql语句不区分大小写
sql提供的运算符：
a.表达一个闭区间：where 字段 between a and b;
select id,first_name from s_emp where salary between 1500 and 2000;
b.表达一个值出现在一个列表中
where 字段 in(1,2,7);
select id,first_name,salary from s_emp where salary in(1400,2000,2500);//把出现概率高的放前
c.模糊查询
where 字段 like '通配串'
数据库中代表0-n个任意字符的是%、代表一个任意字符的是_
select id,first_name,salary from s_emp where first_name like '%a%';
查看数据库中有多少表：
desc user_tables;
select table_name from user_tables where table_name like 'S_%';//_当成了任意一字符了
select table_name from user_tables where table_name like 'S\_%' escape '\';
d.如何判断一个字段的值是否是NULL值
where 字段 is NULL;//只能这么来判断
select id,first_name,salary from s_emp where manager_id is NULL;
逻辑条件运算符:and or not
select id,first_name,salary from s_emp where salary>=1400 and salary <=2000;
not ../is not null
select id,first_name,commission_pct from s_emp where commission_pct is not null;
条件的组合顺序
select id,first_name,salary from s_emp where salary>1000 dept_id=41 or dept_id=42;
上面的容易混。最好加一个括号
select id,first_name,salary from s_emp where (salary>1000 dept_id=41) or dept_id=42;
order by 子句 数据排序
order by出现在sql语句最后
order by 排序标准 排序方式
排序方式：升序（默认的顺序,也叫自然顺序、字典顺序）asc、降序 desc
select id,first_name,salary from s_emp order by salary;
select id,first_name,manager_id from s_emp order by manager_id desc;
//null值在排序中当最大值处理
多字段排序：当按照第一个排序时，如果第一个字段的值相同，我们可以启用第二个字段，如果第二个也相同，可以启用到第三个
select id,first_name,salary from s_emp order by salary asc,first_name desc;

单行函数：
针对sql影响的每一行数据都做处理，每一行都会返回一个结果。sql语句影响多少行，就返回多少个结果
组函数：
针对一组数据做处理，返回一个结果。无论sql语句影响多少行，都返回一个结果。
select count(id) from s_emp where id<1;
单行函数：
upper:变大写
select upper(first_name) from s_emp where id>1;
为了测试单行函数，引入了测试表dual，此表单行单列
处理字符串的单行函数
upper(par1)
lower(par1)
select lower('HELLO') from dual;
initcap(par1)//首字母大字
length(par1)
substr(par1,par2,par3);par1 要处理的数据 par2从什么位置开始截取，编号从1开始 par3截取多少个字符
select substr('hello',1,2) from dual; par2可以是负数：-1代表最后一个字符
select substr(first_name,2,3) from s_emp;
select substr(first_name,-3,3) from s_emp;//把后三个字符显示出来
concat(par1,par2) 连接字符串，用的很少，因为有||而且比concat方便
select first_name||last_name from s_emp;
select concat(first_name,last_name) from s_emp;
处理字符串转换成数字的函数
to_number
select id,first_name from s_emp where id=1;//id='1';//id=to_number('1');
格式转换函数
to_char(par1,par2)
par2是显示格式，可以省略，省略时代表把一个类型变成字符串类型
par2以fm开头 format的缩写
9  0-9的任意数据//小数点前代表0-9，小数点后代表1-9
0  强制显示前导零//小数点后代表1-9
$  美元符号
L  本地货币符号//和系统的本地语言相关
,  分隔符号
.  小数点
select to_char(salary,'fm$099,999.00') from s_emp;
数字处理函数
round 四舍五入
trunc 截取函数
select round(9.58) from dual;//10
select round(9.58,1) from dual;//9.6
select trunc(9.585,2) from dual;//9.58
函数嵌套：把一个函数的返回值作为另一个函数的参数
多表查询：
select s_emp.id,first_name,dept_id,name from s_emp,s_dept;
//但这样做出来的是迪卡尔积，不符合要求
select s_emp.id,first_name,dept_id,name from s_emp,s_dept where s_emp.id=s_dept.id;
select s_dept.name,s_region.name from s_dept,s_region where region_id=s_region.id;
使用表的别名来简化sql
一旦给表起了别名 表原来的名字不再有效。
select d.name,r.name from s_dept d,s_region r where region_id=r.id;
执行顺序：from、where、select
多表查询的另一种写法：
a 表 join b 表 on 连接条件;
select d.name,r.name from s_dept join s_region on region_id=s_region.id;//不常用，可以不记
select first_name,name 
from s_emp e join s_dept d 
on dept_id=id;
多表查询的关键就是找出两张表的关系
上面讲的查询 两个表的连接条件都是用等号表达的，这种连接叫等值连接。
非等值连接
表达两张表的连接条件不使用等号
desc salgrade;//工资级别表

一张表中有多层含义的数据 就需要逻辑上把一张表看成多张表。//重点
select distinct m.id,m.first_name
from s_emp e,s_emp m where e.manager_id=m.id;
等值连接 非等值连接 自连接
这些连接都符合where条件的数据就被选中 不符合where条件的数据就被过滤掉，统称为内连接
外连接：外连接的结果集=内连接的结果集+匹配不上的记录（一个也不能少）
oracle 中使用(+)把不匹配的记录找回来
(+)对面表的所有的数据被匹配出来
select d.name,r.name from s_dept d,s_region r where region_id=r.id(+);
select first_name,name from s_emp,s_dept where dept_id=id(+);
update s_emp set dept_id=NULL;
	where id=1;
commit;//把老板的部门id设为NULL
select first_name,nvl(name,'no dept') from s_emp,s_dept where dept_id=id(+) and id is null;
select e.id,salary,s.id from s_emp e,salgrade s where salary between losal(+) and hisal(+) order by e.id;
连接：内连接 （等值连接，非等值连接，自连接）
外连接（等值连接，非等值连接，自连接）（+）相当于在本字段加了一些null字段值
（+）是oracle数据库的，SQL99里规定了内外连接的标准 (inner) join on
外连接： a left(right\full) outer join b on 连接条件;//注意on后面一定是两张表的连接条件，如果是过滤条件，就必须用where;
select e.id,salary,s.id
from s_emp e left outer join salgrade s on salary between losal and hisal order by e.id;//左边的都保存
55daymorning
initcap将第一个字母变成大写
to_char(par1,par2)par2以fm开头
全外连接：只是逻辑概念 全外连接的结果集等于左外连接的结果集+右外连接的结果集然后减去重复的记录。
oracle 不直接支持全外连接。（不是通过两端加（+）实现的）
union	合并两个结果集，并排重
union all 合并两个结果集。（通过这两个来达到全外连接的效果）
select id from s_emp union select id from s_emp;
select id from s_emp union all select id from s_emp;
---------------------------------
组函数和分组
组函数的概念：
1.对一组数据处理之后得到一个结果
2.常见组函数
count  max   min  sum  avg
3.统计s_emp表中有多少员工 员工的最高工资和最低工资。
select count(id),max(salary),min(salary) from s_emp;
4.统计s_emp表中 工资的和 和 工资的平均值。
select sum(salary),sum(distinct salary),avg(distinct salary),avg(salary) from s_emp;
5.组函数对NULL值的处理方式。
求s_emp表中提成的和 和 提成的个数
select sum(commission_pct),avg(commission_pct) from s_emp;//组函数对空值忽略
分组：
按照一定的标准把数据分成若干组
group by 分组标准;group by 出现在where之后
select dept_id,count(id) from s_emp group by dept_id;
select dept_id,avg(salary),sum(salary) from s_emp group by dept_id;
执行顺序：from, where, group by, having, select, order by
select count(id),dept_id from s_emp group by dept_id having count(id)>2;
//select name from s_emp s,s_dept d where e.dept_id=d.id group by dept_id,name having count(id)>2;
//人为分析后
select max(name) from s_emp s,s_dept d where e.dept_id=d.id group by dept_id having count(id)>2;
在分组语句中 select 后的字段要么是分组标准 要么是经过合适的组函数处理过的。
having 是对组数据过滤的。where是对表数据过滤的。on 是对表连接过滤的。

子查询
把一个查询的结果作为另一个查询的基础（sql嵌套）
1.where之后。
select distinct manager_id from s_emp;
select id,first_name from s_emp
where id in(select distinct manager_id from s_emp);
2.having 后
select dept_id ,avg(salary) from s_emp group by dept_id having avg(salary)>();
3.from 后
把select 语句当做一张内存表
## DDL：
1.建表语句
create table 表名(
	字段名	类型，
	字段名 	类型，
	字段名 	类型
);
2.删除表
drop table 表名;
3.数据类型
number 数字类型
number(7,2) 总共的位数是7位，小数占两位，整数位最多5位。
char  定长字符串 数据不够就补空格
varchar2 变长字符串 省空间
4.日期类型
a.date 类型
和系统语言相关
NLS_LANG
系统默认的日期格式
'dd-MON-yy'	'dd-n月-yy'
b.select start_date from s_emp;
以默认格式放入数据

insert into myorder_10086 values
('bj001','test',12.85,'17-OCT-14');
commit;
c.打破日期的默认表现
to_char(par1,par2)
par1 要处理的日期类型的数据
par2 要表现的日期格式字符串
yyyy 四位年	mm 两位月	dd 两位天	hh 12小时制的小时	hh24	mi 分钟 ss秒
mon 三位英文月	month 英文的全写 day 星期几	pm 上午还是下午		
select to_char(odate,'yyyy-mm-dd hh24:mi:ss day pm') from myorder_10086;
系统默认格式放入的日期 时分秒信息都是0
d.如何放入带时分秒信息的日期
sysdate 可以直接获得系统的当前时间
insert into myorder_10086 values
('bj002','test2',12.85,sysdate);
commit;
insert into myorder_10086 values
('bj2008','test2008',280000,to_date('2008-08-08 20:08:08','yyyy-mm-dd hh24:mi:ss'));l
to_date与to_char是一对
select to_char(odate,'yyyy-mm-dd hh24:mi:ss pm day')
from myorder_10086 where oid='bj2008';
f.日期调整
如何按照天来调整
select to_char(sysdate,'yyyy-mm-dd hh24:mi:ss'),
to_char(sysdate+1,'yyyy-mm-dd hh24:mi:ss') from dual;
如何按照小时调整
select to_char(sysdate,'yyyy-mm-dd hh24:mi:ss'),
to_char(sysdate+1/24,'yyyy-mm-dd hh24:mi:ss') from dual;
把当前时间向后调一秒
select to_char(sysdate,'yyyy-mm-dd hh24:mi:ss'),
to_char(sysdate+1/(24*60*60),'yyyy-mm-dd hh24:mi:ss') from dual;
g.当前时间往后调一个月
add_months(日期,n)
n为正数向后调，n是负数向前调
select to_char(sysdate,'yyyy-mm-dd hh24:mi:ss'),
to_char(add_months(sysdate,2),'yyyy-mm-dd hh24:mi:ss') from dual;
last_day(日期） 得到日期对应月最后一天的日期时间
select to_char(sysdate,'yyyy-mm-dd hh24:mi:ss'),
to_char(last_day(sysdate),'yyyy-mm-dd hh24:mi:ss') from dual;
next_day(日期，'星期几')
下一个星期几的时间点
select to_char(next_day(sysdate,'monday'),'yyyy-mm-dd hh24:mi:ss')
from dual;
h.对日期的一些数学操作
months_between(par1,par2) 两个日期相差了多少个月//不重要
select months_between(sysdate,to_date('2008-08-08 20:08:08,'yyyy-mm-dd hh24:mi:ss')) from dual;
round 对日期进行四舍五入
1.默认以天为单位进行四舍五入
select to_char(round(sysdate),'yyyy-mm-dd hh24:mi:ss') from dual;//过了半天了就到下一天去
2.指定四舍五入的单位
select to_char(round(sysdate,'dd'),'yyyy-mm-dd hh24:mi:ss') from dual;//与上面一样
trunc 对日期进行截取
1.默认以天为单位进行截取
2.。。
3.。。//都是对sysdate的操作
55天下午3:10:00
## DML
account
create table account007(
aid number not null,
aname varchar2(30),
apasswd varchar2(30)
);
1.增加数据//不加commit只能在当前终端进行操作
a.insert into 表名 values(值1，值2);//日期有日期的格式，或者to_date
insert into account007 values(1,'007','band');
b.选择一些字段进行数据插入
	insert into 表名（字段1，字段3） values(值1，值2）;
insert into account007 (aid,apasswd) values(2,'ss');//字段2为空值
2.删除数据
delete from 表名 where 条件;//如果不加where条件就把全部表都删除了
delete from account007 where aid=1;
3.更新数据
update 表名 set 字段名=值1,字段名=值2 where 条件;
update account007 set aid=100,aname='test100' where aid=2;
from where group by having (select) order by
//先得知道数据从哪里来，怎么分组，分组怎么过滤，然后查询，最后查询的数据按什么排序
date 类型
1.默认格式  'dd-MM-yy' 时分秒信息都为零
2.to_char yyyy mm dd hh24 mi ss    //mon month day pm
以指定格式显示日期
3.把日期的时分秒放入数据库
sysdate
to_date(日期字符串，日期格式字符串)
4.按照天 小时 分钟 秒为单位进行调整
5.add_months
last_day
next_day
6.日期的计算
months_between
round
trunc
DML 和 事务控制
DML操作是有事务特性的
事务也叫交易--transation 
原子性（不可分隔）
	create table account(
		id varchar2(10) primary key,
		money number
	);
	insert into account values('a',1000);
	insert into account values('b',1);
	commit;
update account set money=money-5000 where id='a';
update account set money=money+5000 where id='b';
if(a&&b) commit;else rollback;-- 一起成功，一起失败 
-- 单行注释
/* 多行注释*/
隔离性
事务中的操作在没有提交以前对另一个事务数据的变化是不可见的
但事务会锁定这条数据，没提交以前别的事务对这条数据的操作会产生锁定状态
commit或rollback//rollback只能撤销未提交的数据
一致性、持久性
-------------------
事务的原子性太严格，有时要做部分成功，部分失败。
insert into account values('E',1);
savepoint a;
insert into account values('F',2);
savepoint b;
insert into account values('G',1);
rollback to b;//只提交前面两条
commit;
-----------------------------------
数据库中的约束：constraints
对数据库表中的字段加的限制
5种具体的约束
a.主键约束 primary key-- 非空且为唯一
	一个表的主键只能有一个
b.唯一性约束 unique
值不能重复
c.非空约束 not null -- 值不能为空值
d.检察约束 check -- 表中的字段的值必须符合检查条件
e.外键约束 references(关联引用) foreign key
2.表中约束的分类
a.列级约束
在定义表的某一列时直接对表的这一列加约束限制
b.表级约束
在定义完表的所有列之后 再选择某些列加约束限制。
主键的列级约束
create table testcol_cons(
	id number primary key,
	name varchar2(30)
);
insert into testcol_cons values(1,'a');
insert into testcol_cons values (NULL,'b');
insert into testcol_cons values(1,'c');
//必须是唯一且非空
4.建立字段的约束时，自己给约束命名
create table testcol_cons(
	id number constraint
	testcol_cons_id_pk primary key,
	name varchar2(30)
	testcol_cons_id_uk unique,
	salary number constraint
	testcol_cons_salary_ck
	check(salary>3500)
);
pk uk nn ck fk
insert into testcol_cons values(1,'c',3400);
7.表级约束的主键约束
在定义完表的所有列之后 再选择某些列加约束限制。
create table testtable_cons(
	id number,
	fname varchar2(30),
	sname varchar2(30),
	salary number,
	constraint testtable_cons_id_pk
	primary key(id,fname),//可以建联合主键，比列级约束的优点
	constraint testtable_cons_sname_nn
	not null(sname),
	constraint testtable_cons_salary_ck
	check(salary>3500)
);
外键约束：涉及到两张有 一张叫父表（主表）另一张叫子表（从表）。子表中一个字段称之外键
子表里外键的值引用主表里的值：外键的取值 要么是NULL 要么是你主表中字段的取值。
create table parent(
	id number primary key,
	name varchar2(30)
);
create table child(
	id number primary key,
	name varchar2(30),
	fid number constraint child_fid_fk
	references parent(id) on delete cascade/on delete set null
);
1.先建父表 后建子表
//是不是两张表就是通过主、外键联系起来的？
2.插入数据一般先插入父表 后插入子表数据 除非子表的外键值是NULL
3.删除数据
先删子表数据后删父表数据 除非子表中没有和主表字段对应的数据
或者是设置了级联（on delete cascade、
		on delete set null）
4.修改数据 设置外键的值要么为空 要么设置成父表中字段对应的值
5.删除表
	先删子表后删父表 除非你使用先解除主外键关系 再删除表
	drop table parent cascade constraints;
取缔一个部门
delete from deptparent133 where id=1;
-------------------------------------------------
数据库的其它对象(与表同级别)
1.序列
生成主键的值
创建序列
create sequence 序列名;
create sequence testseq123;
测试序列
select testseq123.nextval from dual;
使用序列
create table testpkuseseq(
	id number primary key,
	name varchar2(30),	
);
insert into testpkuse_seq values(testseq123.nextval,'test'||testseq123.currval);
删除序列
drop sequence 序列名;
drop sequence testseq123;
2.索引
用来加速查询
消耗了大量的空间和时间来完成
3亿条数据 不用索引用7-8分钟
建立索引 半个多小时30G建立 查询用了0.01秒
如何建立索引
1.唯一性字段上系统会自动建立索引（唯一性索引）
2.在非唯一性字段上 可以人为地创建索引
create index 索引名 on 表名(字段);
3.删除索引
索引和表占的不是一个空间
drop index 索引名;
drop index testemp101_id_ind;
3.视图
视图本质上是一条sql 相对于视图对应的数据 视图的空间是可以忽略的
create or replace view myview
as select id,first_name,salary from s_emp;
create or replace view myview2
as select id,first_name,salary from s_emp;
可以对同一份物理数据 做不同的表现
使用：
select * from myview;
select * from myview2;
----------------------------------
三范式：
 第一范式：表中的字段不可再分
	任何的关系型数据库必须满足第一范式
 第二范式：满足第一范式的基础上，所有的非主属性 完全依赖主属性
	表中的数据 可以被唯一区分（只要有主键就可以）（记录而言）
	好处 方便查询
	坏处 数据冗余 增 删 改 不方便
 第三范式：第二范式的基础上，消除了传递依赖（..->..->..）
	消除传递依赖----拆表
-------------------------------------
分页技术：
在不同的数据库里实现技术不一样
oracle rownum
mysql  limit
sqlserver top
select id,first_name,salary from s_emp;
select rownum,first_name,salary from s_emp;//id不是有序的,但rownum是有序的
假设一页显示7条，要第一页数据
select rownum,first_name,salary from s_emp where rownum<8;
select rownum+7,first_name,salary from s_emp where rownum<8;
select * from(select rownum r,first_name,salary from s_emp where rownum<15)where r>7;
//因为rownum有个毛病：只要是不正确的就不往下走了。但给rownum起的别名没有这个问题
按照工资排序 每页显示7条 显示第二页数据:要先排序
select * from(
select rownum r,first_name,salary from
(select first_name,salary from s_emp order by salary)
where rownum<2*7+1)
where r>7;
----------------------------------
sql中和NULL相关的知识点：
----------------------------------
plsql:过程化语言的sql	procedure(存储过程)
1.plsql
2.proc/c++
3.odbc/ado	vc中访问数据库的技术
4.jdbc/sqlj	java访问数据库的技术
5.OCI		oracle底层连接接口
plsql：oracle客户端工具访问oracle服务器的操作语言
plsql扩展了sql
变量和数据类型
控制语句
过程和函数
plsql的程序结构：
declare
申明区
begin
执行区
exception
异常处理区
end;
申明区：用来定义变量 或者 类型的
执行区：用来执行sql语句或者plsql语句的
异常处理区：当sql语句出错之后自动转到异常处理区做错误处理
begin
	dbms_output.put_line('hello plsql!');
end;
plsql的开发工具：
sqlplus 命令行下的开发工具
sqlprogrammer\sqlnavigator\sqldeveleper图形界面的
打开输出
set serveroutput on
57天上1：00：00
标示符
最大长度为30个字符 字母开头
给变量 类型 过程 函数 游标等对象起名字的。
注释
-- 单行注释
/* 这是多行注释 */
----------------------
变量的定义
1.在申明区
变量名 类型;
2.举例
declare
 var_id number:=9527;
 var_name  varchar2(30):='tangbohu';
 -- 使用冒号初始化
begin
	dbms_output.put_line(var_id||':'||var_name);	
	var_id:=1234;
	var_name:='test';
	dbms_output.put_line(var_id||'@'||var_name);
end;
3.变量的修饰
constant	not null
declare
	var_id constant number:=9527;
	var_name varchar2(30) not null:='tangbohu';
begin
	dbms_output.put_line(var_id||':'||var_name);
	var_id:=1234;
	var_name:='test';
	dbms output.put_line(var_id||'@'||var_name);
end;
4.变量的数据类型
标量类型：
number 数字类型
binary_integer 二进制整数类型
char 定长字符串
date 日期类型	boolean 布尔类型
复合类型
record 记录类型
table 表类型
参考类型：
ref 参考类型
ref cursor
大类型：
BLOB 大二进制类型（了解）
CLOB 大字符类型
BFILE 文件类型
---------------------------
declare
	falg boolean:=true;
	jobno binary_integer:=123;
begin:
	if falg then
		dbms_output.put_line(jobno);
	end if;
end;
5.取得表中字段对应的类型 表名.字段名%type
定义两个变量 分别和s_emp表中 id 和 first_name 的类型相同 然后把id=1的first_name赋值给定义的变量
declare
	var_id s_emp.id%type:=1;
	var_name s_emp.first_name%type;
begin
	select first_name into var_name from s_emp where id=var_id;
	dbms_output.put_line(var_name);
end;
-------------------------------
6.类似于c语言结构体的类型 record类型
定义record类型
type 记录类型名 is record (
	字段名 类型,
	字段名 类型,
	字段名 类型,	
);
变量名 记录类型的名字;
declare
type emptype is record(
	var_id s_emp.id%type,
	var_name s_emp.first_name%type,
	salary s_emp.salary%type
);
var_emp emptype;
var_emp2 emptype;
begin
	select id, first_name,salary into var_emp from s_emp where id=3;
	-- 记录类型变量之间的赋值
	var_emp2:=var_emp;
	var_emp2.var_name:=var_emp.var_name;//局部赋值
	dbms_output.put_line(var_emp2.var_id||':'||var_emp2.var_name||':'||var_emp2.salary);
end;
把s_emp表中id=1的所有数据放入一个记录类型的变量中（如果用record太麻烦）
用 表名%rowtype 可以获得
declare
	var_emp s_emp%rowtype;
begin
	select * into var_emp from s_emp where id=1;
	dbms_output.put_line(var_emp.id||var_emp.first_name||..);
end;
把id=50部门信息放入一个rowtype类型的变量中
declare
var_emp s_dept%rowtype;
begin
select * into var_dept from s_dept where id=50;
dbms_output.put_line(var_dept.id||':'||var_dept.name||':'||var_dept.salary);
end;
8.table 类型
相当于C语言的数组类型
定义一个table类型
type 类型名 is table of 表中数据类型 index by binary_integer;
declare
-- 定义一个表类型
type numstype is  table of number index by binary_integer;
--使用表类型定义变量
var_nums numstype;
var_ind   binary_integer:=-1;
begin
var_nums(-1):=200;
var_nums(0):=400;
var_nums(1):=700;
dbms_output.put_line('var_nums('||var_ind||')='||var_nums(var_ind));
var_ind:=var_ind+1;
dbms_output.put_line('var_nums('||var_ind||')='||var_nums(var_ind));
end;
下标不连续时的访问
迭代器思想：根据一个元素的信息可以得到下一个元素的信息 三个函数
first()可以返回第一个元素对应的下标
next(n)n 是上一个元素的下标，根据一个元素的下标得到下一个元素的下标
last()得到最后一个元素对应的下标：跟C++中的end不一样
var_ind:=var_nums.first();
var_ind:=var_nums.next(var_ind); 
var_ind:=var_nums.last();
-----------------
declare 
type  emstype is table of s_emp%rowtype index by binary_integer;
var_emps empstype;
var_ind binary_integer:=1;
begin
	select * into var_emps(var_ind) from s_emp where id=var_ind; 
	var_ind:=5;
	select * into var_emps(var_ind) from s_emp where id=var_ind;
	var_ind:=11;
	select * into var_emps(var_ind) from s_emp where id-var_ind;
	var_ind:=var_emps.first();
	dbms_output.put_line(
	var_emps(var_ind).id||':'||var_emps(var_ind).salary
	);
	var_ind:=var_emp.next(var_ind);
	dbms_output.put_line(
	var_emps(var_ind).id||':'||var_emps(var_ind).salary
	);
	var_ind:=var_emp.next(var_ind);
	dbms_output.put_line(
	var_emps(var_ind).id||':'||var_emps(var_ind).salary
	);
end;
---------------------------
变量的作用域与可见性
plsql块的嵌套
<<outerblock>>
declare
var_m number:=1;
begin
------------------
delcare
var_m number:=100;
	begin
	dbms_output.put_line(outerblock.var_m);
	end;
----------------------------
end;
----------------------------
plsql中的控制语句
1.
if a>b then
end if;
if a>b then 
else
end if;
if a<b then
elsif a<c then
elsif a<d then
end if;
-- if后面必带then
if a<b then
elsif a<c then
elsif a<d then
else
end if;
--------------------
declare
	var_m number;
	var_n number;
begin
	if var_m>var_n then
		dbms_output.put_line('');
	elsif var_m<var_n then
		dbms_output.put_line('');
	elsif var_m=var_n then
		dbms_output.put_line('');
	elsif var_m is null and var_n is null then
		dbms_output.put_line('');
	else
		null;
	end if;
end;
循环
a.简单循环
loop
exit when;
end loop;
b.while循环
while 循环条件 loop
end loop;
declare
	var_i number:=1;
begin
	while var_i<=10 loop
		dbms_output.put_line(var_i);
		var_i:=var_i+1;
	end loop;
end;
c.for循环 ----智能循环
for 变量 in 区间 loop

end loop;
整数的区间 1..10
--------
begin
	for var_i in (reverse) 1..10 loop -- reverse反向
		dbms_output.put_line(var_i);
		exit when var_i=5;
	end loop; -- for循环中的变量不用在delcare中赋值，也不能被修改
end;
---------------------
多重循环的退出（三种方案）（修改外层循环的变量的值，然后跳过去）
declare
	var_m number;
	var_n number;
begin
	while var_m<4 loop
		var_n:=1;
		while var_n<4 loop
			dbms_output.put_line(var_n);
			exit when var_n=2;
			var_n:=var_n+1;
		end loop;	
		var_m:=var_m+1;
	end loop;
end;
3.goto 语句
declare
var_m number:=1;
begin
<<myloop>>
if var_m<11 then
	dbms_output.put_line(var_m);
	var_m:=var_m+1;
	goto myloop;
end if;
dbms_output.put_line('game over!');
end;
sql的标签后面必须有语句
---------------
sql语句在plsql中的分类
1.select 语句在plsql中使用是 要和into结合变量使用
select first_name into var_name from s_emp where id=var_id;
2.insert delete update dml
commit rollback savepint tcl
这些语句可以直接在plsql中使用
declare
var_id number:=1;
var_name varchar2(30):='test';
begin
insert into testplsql values(2,'app');
insert into testplsql values
(var_id,var_name);
end;
3.ddl 	create table
	drop table
	alter table
这些语句不能直接在plsql中使用，需要使用动态sql的语法
begin
	create table testplsql(id number,
	name varchar2(30));
end;
动态 sql:
把sql语句变成字符串
把一个字符串对应的sql语句 当作真正sql来执行
declare
sqlstr varchar2(100);
begin
	sqlstr:='create table testplsql(id number)';
	sqlstr:=substr(sqlstr,1,length(sqlstr)-1);
	sqlstr:=sqlstr||','||'namevarchar(30)';
	-- 把字符串对应sql当真正sql来执行
	execute immediate sqlstr;
end;
4.dml语句静态sql和动态sql
5.select 语句动态sql
只能返回一个结果，多了少了都会报错
-----------------------------
一次可以放多条数据
处理多条数据的数据结构 游标 cursor
cursor 的使用步骤
1.声明游标 cursor 游标名 is sql语句;
2.打开游标 open 游标名;
3.提取数据 处理数据 fetch 游标名 into 变量;
4.关闭游标
close 游标名;
declare
	cursor empcursor is select * from s_emp;
	var_emp empcursor%rowtype;
begin
	open empcursor;
	fetch empcursor into var_emp;
	dbms_output.put_line(var_emp.id||':'||var_emp.first_name||':'||var_emp.salary);
	close empcursor;
end;
游标的遍历
游标的属性
found	当提取数据时 提取到新数据就返回真
	没有提取到新数据就返回假
	游标必须处于打开状态，不处于打开状态就是非法游标。
	打开不fetch使用这个属性就返回NULL值。
notfound游标必须处于打开状态 否则报错
	打开不fetch 返回NULL
	如果提取到新数据 返回假
	没有提取到新数据 返回真	
isopen	游标是否打开
	打开就返回真
	关闭就返回假
	打开的游标不能再打开 关闭的游标不能再关闭
rowcount游标指针偏移量

智能循环 和 游标遍历
for循环 会自动打开游标 自动提取 自动关闭
declare
	cursor empcursor is select * from s_emp;
begin
	for var_emp in empcursor loop
	dbms_output.put_line();
	end loop;
end;
带参游标：动态sql 和 游标的结合。
plsql中的参数不能有任何长度修饰
但是可以使用 %type 
参考游标（引用游标）
定义引用游标类型
type myrefcursor is refcursor
使用类型定义游标变量
emp_cursor myrefcursor;
使用引用类型游标
open emp_cursor for sqlstr;
如果sqlstr中有占位符
/*  */
declare 
	type myrefcursor is ref cursor;-- 定义参考游标类型
	empcursor myrefcursor;
	sqlstr varchar2(100):='select * from s_emp' where id>:b0';
	var_emp s_emp%rowtype;
	var_id s_emp.id%type:=15;
begin
	-- 打开游标 关联到字符串
	open empcursor for sqlstr using var_id;
	loop
	fetch empcursor into var_emp;
	exit when empcursor%notfound;
	dbms_output.put_line();
	end loop;
	close empcursor;
end;
-------------------------------------------
存储过程 和 函数
1.存储过程 procedure
给我们的匿名块起个名字 然后存储到数据库中。
设计两个整数参数 打印其中的最大值
create or replace procedure getmax(x number,y number)
is
	var_x number;
	var_y number;
begin
	var_x:=x;
	var_y:=y;
	if var_x<var_y then
		dbms_output.put_line(var_y);
	else
		dbms_output.put_line(var_x);
	end if;
end;
2.查看存储过程
desc 过程名;
desc getmax;
显示：参数的名字、参数的类型、参数的模式
参数的模式：
in	负责给存储过程传入值
out	做指针的效果（传出值）
in out	既负责传入值 又负责传出值 out修饰的参数必须是变量

3.调用存储过程
exec getmax(100,200);
call getmax(1.201);
匿名块调用 或者 有名块调用
declare
	x number:=1;
	y number:=99;
begin
	getmax(x,y);
end;
-------------------------------------
设计一个存储过程 把两个整数参数的和放入第三个参数中
create or replace procedure getmax(x number,y number,z out number)
is
begin
	z:=x+y;
end;
declare
	var_z number:=0;
begin
	getsum(y=>1,x=>2,z=>var_z);-- 传参的一种写法而已，前形参
	dbms_output.put_line();
end;
----------------------------------
设计一个存储过程 传入两个整数参数
要求输出两个整数参数最大值 还要求把两个参数的和放入第二个参数中。
查看存储过程 并调用验证过程的功能。
create or replace procedure fun(x in number,y out number)
is
begin
	if x>y
	dbms_output.put_line();
	else
	dbms_output.put_line();
	end if;
	y:=x+y;
end;
declare
	var_z number:=0;
begin
	fun(y=>1,x=>var_z);-- 传参的一种写法而已，前形参
	dbms_output.put_line();
end;
函数
函数和存储过程的区别
1.关键字不同
procedure function
2.过程没有返回值 和 返回值类型
函数有返回值类型 和 返回值
return
3.存储过程可以直接在匿名块中 或者有名块中调用。
函数必须组成表达式 或者在sql中使用。
设计一个函数 传入两个整数参数 返回两个参数的最大值。
create or replace function getmaxfun -- 参数默认就是in类型
(x in number,y in number)return number
is
begin
	if x<y then
	return y;
	end if;
	return x;
end;
查看函数
desc fungetmax; -- 跟存储过程一样（只要没有说不一样的，都是一样的）
测试函数
select fungetmax(1,2) from dual;
declare
	var_z number:=0;
begin
	var_z:=fungetmax(1,2);
	dbms_output.put_line();
end;
----------------------
create or replace function getmaxandsum(x number,y out number)return number
is
	var_temp number;
begin
	var_temp:=y;
	y:=x+y;
	if x>var_temp then
	return x;
	end if;
	return var_temp;
end;
desc getmaxandsum;
declare
	var_res number;
	var_y number:=0
begin
	var_res:=getmaxandsum(1,var_y);
	dbms_output.put_lint();
end;
---------------------------
参数的默认值
create or replace function testpardef
(x number,y number:=123)return number -- 跟C语言一样
is 
begin
	if x<y then
	return y;
	else
	return x;
	end if;
end;

select testpardef(1) from dual
----------------------------------
1.建立存储过程的语句
create or replace procedure 过程名
(参数名 参数的模式 类型）
is
begin
end;
2.查看存储过程
desc 过程名;
参数的名字
参数的类型
参数的模式 （in out in out）
参数的默认值
3.调用存储过程
sqlplus call exec
匿名块 有名块
declare
begin
end;
4.删除存储过程
drop procedure 过程名;
5.函数与存储过程的区别
1.2.3.
6.参数的默认值
---------------------------
包：package
系统提供的包
dbms_output -- 输入输出包
dbms_random -- 随机数包
desc dbms_random
select dbms_random.value(1,100)from dual;
select trunc(dbms_random.value(1,100))from dual;
dbms_job    -- 定时任务调度包 定时调用存储过程	
submit(job binary_integer,what varchar2,next_date date,interval varchar2);
会把定时任务提交给系统，系统会为这个任务分配一个编号放入job中。
what 就是要定时调用的存储过程
next_date 第一次调用的时间
interval 下一次调用的时间
run(job binary_integer);
运行定时任务
remove(job binary_integer);
删除定时任务

1.建立一张表
create table testjob(
	id number primary key,
	name varchar2(30)
);
2.建立一个序列
create sequence testjob_id;
3.写一个存储过程 向表中添加一条数据
create or replace procedure insert_job
is
begin
	insert into testjob values(
	testjob_id,nextval,'test'||testjob.id.currval);
	commit; -- 事务
end;
4.把存储过程的调用 交给dbms_job
declare
	jobno binary_integer;
begin
	dbms_job.submit(jobno,'insert_job;',
	sysdate,'sysdate+1/(24*60)');
	dbms_output.put_line('jobno='||jobno);
	dbms_job.run(jobno);
end;
5.select job from user_jobs;
begin
	dbms_job.remove(1570);
end;
--------------------------------	
自定义包		package
把一组相关的函数 变量 过程等放入一个逻辑结构中。
相当于C中的头文件
create or repalce package mypack
is
	procedure getmax(x number,y number);
	function  getmin(x number,y number) return number;
end;

包体 相当于C中的实现文件
create or replace package body mypack
is
	procedure getmax(x number,y number)
	is
	begin
		if x<y then
		dbms_output.put_line(y);
		else
		dbms_output.put_line(x);
		end if;
	end;
	function getmin(x number,y number)
	return number
	is
	begin
		if x<y then
		return x;
		end if;
		return y;
	end;
end;
-- 如何调用包中的数据
在数据前加 包名即可。
begin
	mypack.getmax(1,9527);
end;
-------------------------------
动态sql -- 在块里的sql语句，相对于在控制台里的sql语句
select into
dml tcl 直接可以使用
ddl需要使用动态sql
dml的动态sql 占位符和字符串拼接
查看源代码 user_source
查看编译错误 show errors
运行时错误
a.系统定义的异常
declare
	var_name s_emp.first_name%type;
begin
	select first_name into var_name from s_emp where id=1;
	dbms_output.put_line();
exception --出错后自动跳到这里
	when no_data_found then
	dbms_output.put_line();
b.自定义异常
1.定义异常
2.根据条件 抛出异常
3.捕获异常
4.处理异常
declare
	many_emp exception;
begin
	if 1=1 then
		raise many_emp;
	end if;
exception
	when others then -- others能代表所有的异常
	dbms_output.put_line();
end;
----------------------------------
触发器：
在做dml操作时操作可以被系统得知并做相应的操作。
before after /insert delete update

create or replace trigger myemptrigger
before update on s_emp
declare
begin
	dbms_output.put_line();
end;
无论sql语句影响多少行都触发一次 这种触发器叫语句级触发器。
为了得到触发器影响的每一行数据
要使用行级触发器。
create or replace trigger myemp9537trigger
before update on myemp9537 for each row
declare
begin
	dbms_output.put_line();
	dbms_output.put_line();
	dbms_output.put_line();
end;
update--> :old :new -- dbms_output.put_line()里面
delete--> :old
insert--> :new
触发器的限制：
不能有事务控制语句:不能出现commit\rollback\.
