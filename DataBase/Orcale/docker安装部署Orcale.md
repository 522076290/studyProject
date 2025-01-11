# Docker安装部署Oracle11g

事先需安装好Docker

#### 1.1 拉取镜像

```
# 1.下面是拉取一个镜像该如何配置成上面那样的
docker pull registry.cn-shanghai.aliyuncs.com/techerwang/oracle:ora11g11204
# 2.重新打tag
docker tag registry.cn-shanghai.aliyuncs.com/techerwang/oracle:ora11g11204 jemora11g:11204
```

#### 1.2 创建容器

```bash
#创建容器
# 这边映射的端口是将1521 映射到了主机的21521 用远程连接的时候注意
docker run -itd --name jemora11204 -h jemora11204 \
--privileged=true -p 21521:1521 -p 222:22  -p 21158:1158 \
jemora11g:11204 init
#这里要说明的是：这里给容器起的名字就是jemora11204，容器里面listener.ora和tnsnames.ora文件里面的host也是这个，如果不一致的话将报错，无法启动listener
```

#### 1.3 进入容器

```bash
#进入容器
docker exec -it jemora11204 bash
```

#### 1.4 启动数据库和监听

```bash
# 切换到oracle用户
[root@jemora11204 /]# su - oracle
# 启动监听
[oracle@jemora11204 ~]$ lsnrctl start

# 在启动oracle数据库之前先要修改一下配置文件 这边拉取下来的镜像是有问题的
# 进入dbs路径
[oracle@jemora11204 dbs]$ cd /u01/app/oracle/product/11.2.0.4/dbhome_1/dbs
# 复制一个配置文件
[oracle@jemora11204 dbs]$ cp spfileJEM11GR2.ora  initJEM11GR2.ora
```

initJEM11GR2配置内容如下

```bash
# 原来的里面是有乱码的 修改成如下配置
JEM12GR2.__db_cache_size=142606336
JEM11GR2.__java_pool_size=4194304
JEM11GR2.__large_pool_size=8388608
JEM11GR2.__oracle_base='/u01/app/oracle'#ORACLE_BASE set from environment
JEM11GR2.__pga_aggregate_target=142606336
JEM11GR2.__sga_target=268435456
JEM11GR2.__shared_io_pool_size=0
JEM11GR2.__shared_pool_size=100663296
JEM11GR2.__streams_pool_size=0
*.audit_file_dest='/u01/app/oracle/admin/JEM11GR2/adump'
*.audit_trail='db'
*.compatible='11.2.0.4.0'
*.control_files='/u01/app/oracle/oradata/JEM11GR2/control01.ctl','/u01/app/oracle/flash_recovery_area/JEM11GR2/control02.ctl'
*.db_block_size=8192
*.db_domain=''
*.db_name='JEM11GR2'
*.db_recovery_file_dest='/u01/app/oracle/flash_recovery_area'
*.db_recovery_file_dest_size=4385144832
*.diagnostic_dest='/u01/app/oracle'
*.dispatchers='(PROTOCOL=TCP) (SERVICE=JEM11GR2XDB)'
*.memory_target=1073741824
*.open_cursors=300
*.processes=150
*.remote_login_passwordfile='EXCLUSIVE'
*.undo_tablespace='UNDOTBS1'
```



```bash
# 之后即可正常进行启动oracle数据库
[oracle@jemora11204 ~]$ sqlplus / as sysdba
SYS@JEM11G2> startup
# 查询如下则成功启动数据库
SYS@JEM11GR2> select * from v$version;

BANNER
----------------------------------------------------------------------------------------------------------------------------------------------------------------
Oracle Database 11g Enterprise Edition Release 11.2.0.4.0 - 64bit Production
PL/SQL Release 11.2.0.4.0 - Production
CORE	11.2.0.4.0	Production
TNS for Linux: Version 11.2.0.4.0 - Production
NLSRTL Version 11.2.0.4.0 - Production
```



#### 1.5 外部连接容器内的数据库

```bash
可以使用navcat 或者其他工具进行连接 
注意：此处访问宿主机端口为21521，容器内部是1521，端口映射,系统管理员密码为jem

# 配置信息如下
端口: 21521
服务名: JEM11GR2
用户名: system
密码: jem

```