# Jenkins部署（ubuntu20.04）
环境需求：由于我是使用的Docker来进行Jenkins的部署所以一些环境需要预装在实体机器通过挂载的方式放Jenkins去使用

## 预装环境

### Java 11

```shell
#安装java jdk
sudo apt-get install openjdk-11-jdk
```

### Maven3.8

```shell
#进入Maven官网
# 1.https://maven.apache.org/download.cgi
# 2.下载 apache-maven-3.8.8-bin.tar.gz 其他版本也可以 这边使用的是3.8
# 3.将文件上传到服务器任意路径中 我存放的位置是(/mydata/jenkins/maven) 没有这个路径创建即可
# 4.将文件夹解压 
tar -xzvf apache-maven-3.8.8-bin.tar.gz
# 解压后生成apache-maven-3.8.8目录 配置该目录到 /etc/profile下
vi /etc/profile
export MAVEN_HOME=/mydata/jenkins/maven/apache-maven-3.8.8
export CLASSPATH=${MAVEN_HOME}/lib:$CLASSPATH
export PATH=${MAVEN_HOME}/bin:$PATH
# 刷新环境变量
source /etc/profile
# 查看mvn环境是否配置成功
mvn -v
# 看见如下提示成功配置好Maven环境
Apache Maven 3.8.8 (4c87b05d9aedce574290d1acc98575ed5eb6cd39)
Maven home: /mydata/jenkins/maven/apache-maven-3.8.8
Java version: 11.0.20.1, vendor: Ubuntu, runtime: /usr/lib/jvm/java-11-openjdk-amd64
Default locale: zh_CN, platform encoding: UTF-8
OS name: "linux", version: "6.2.0-32-generic", arch: "amd64", family: "unix"
```

### Docker

```shell
# 卸载旧版本docker (如果有旧版本的docker 没有可以跳过)
sudo apt-get remove docker docker-engine docker.io containerd runc
# 1.更新及安装工具软件
sudo apt-get update
# 2.安装几个工具软件
sudo apt-get install \
    apt-transport-https \
    ca-certificates \
    curl \
    gnupg \
    lsb-release
# 3.增加一个docker的官方GPG key： gpgkey：是用来验证软件的真伪 ——防伪的
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg
# 4.下载仓库文件
echo \
  "deb [arch=amd64 signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] https://download.docker.com/linux/ubuntu \
  $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
# 安装docker
# 1、再次更新系统
sudo apt-get update
# 2、安装docker-ce软件
sudo apt-get install docker-ce docker-ce-cli containerd.io -y
# 查看docker是否安装成功
ps aux|grep docker
```

## Docker启动Jenkins

```shell
# 因为我需要将文件保存所以会将路径挂载出来

# 先创建/mydata/jenkins/jenkins_home 文件夹
mkdir -p /mydata/jenkins/jenkins_home

# 为了在容器中使用docker 还需要修改docker.sock的所有者
cd /var/run/docker.sock
chown root:root docker.sock

# docker启动 
docker run -d --name myjenkins -u root -p 18080:8080 -p 50000:50000 --restart=on-failure -v /mydata/jenkins/jenkins_home:/var/jenkins_home -v /mydata/jenkins/maven/apache-maven-3.8.8:/usr/local/maven/apache-maven-3.8.8 -v /var/run/docker.sock:/var/run/docker.sock -v /usr/bin/docker:/usr/bin/docker -v /etc/docker/daemon.json:/etc/docker/daemon.json  jenkins/jenkins:lts-jdk11 
```

-d 指定后台运行docker

--name 指定容器名字

-u 指定容器权限 以root用户

-p 指定暴露端口 18080:8080 (本地映射端口:容器内程序端口) 我这里是8080被占用换成了18080

--restart=on-failure 失败自动重启

-v /mydata/jenkins/jenkins_home:/var/jenkins_home  挂载jenkins_home 到本机的目录

-v /mydata/jenkins/maven/apache-maven-3.8.8:/usr/local/maven/apache-maven-3.8.8 挂载Maven给Jenkins使用

-v /var/run/docker.sock:/var/run/docker.sock 

-v /usr/bin/docker:/usr/bin/docker				挂载docker给jenkins使用

 -v /etc/docker/daemon.json:/etc/docker/daemon.json	挂载本地的镜像源给docker加速使用

 jenkins/jenkins:lts-jdk11 使用这个版本的jenkins

```shell
# 正常启动后查看 看见myjenkins status up正常启动
docker ps -a 
```

## Jenkins编译运行Maven项目
