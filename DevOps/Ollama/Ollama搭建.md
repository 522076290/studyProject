### Ollama搭建

| 操作系统 | Ubuntu22.04 |
| -------- | ----------- |

## 1.Docker安装	

更新软件包列表并安装依赖

```shell
sudo apt install apt-transport-https ca-certificates curl software-properties-common -y
```

添加 Docker 官方 GPG 密钥并安装 Docker 如果提示443 修改https为http：

```shell
# 获取GPG秘钥
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg

#更新包列表
sudo apt update

#安装docker
sudo apt install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin -y

# 修改docker镜像源 如果实在用不了只能尝试代理了
sudo mkdir -p /etc/docker
sudo nano /etc/docker/daemon.json
{
	"registry-mirrors": ["https://hub-mirror.c.163.com", "https://docker.m.daocloud.io"]
}

# 重启docker服务
sudo systemctl daemon-reload
sudo systemctl restart docker



# 参考内容 
# Docker 使用代理（拉取镜像时）
# 新增一个代理配置文件
sudo mkdir -p /etc/systemd/system/docker.service.d
sudo nano /etc/systemd/system/docker.service.d/http-proxy.conf

# 写入下面内容 （注意127.0.0.1替换成你的代理地址）
[Service]
Environment="HTTP_PROXY=http://127.0.0.1:7890"
Environment="HTTPS_PROXY=http://127.0.0.1:7890"
Environment="NO_PROXY=localhost,127.0.0.1,docker-registry.somecorporation.com"

# 重启doker
sudo systemctl daemon-reload
sudo systemctl restart docker
```

## 2.**NVIDIA Container Toolkit** 安装

```shell
# 设置环境变量（获取系统信息）
distribution=$(. /etc/os-release;echo $ID$VERSION_ID)

# 下载并添加 NVIDIA 的 GPG 公钥（到推荐位置）
curl -fsSL https://nvidia.github.io/nvidia-docker/gpgkey | sudo gpg --dearmor -o /usr/share/keyrings/nvidia-docker-archive-keyring.gpg

# 添加 NVIDIA Docker 软件源（使用新语法）
curl -s -L "https://nvidia.github.io/nvidia-docker/$distribution/nvidia-docker.list" | \
sudo sed 's#deb https://#deb [signed-by=/usr/share/keyrings/nvidia-docker-archive-keyring.gpg] https://#g' | \
sudo tee /etc/apt/sources.list.d/nvidia-docker.list

# 更新apt
sudo apt-get update

# 安装 nvidia-docker2 并重启 Docker 服务
sudo apt-get install -y nvidia-docker2
sudo systemctl restart docker
```

## 3.下载ollama镜像

```shell
# 拉取镜像
docker pull ollama/ollama

# 创建运行ollama
docker run -d --gpus=all -v /root/docker/ollama:/root/.ollama -p 11434:11434 --name ollama ollama/ollama

# 运行一个model
docker exec -it ollama ollama run llama3
```

- `-d`: 让容器在后台运行。
- `--name ollama`: 为容器指定一个名称，这里是ollama。
- `--gpus all`: 允许容器访问主机上的所有GPU，这对于需要进行大量计算的任务（如机器学习模型的推理）非常有用。
- `-v /root/docker/ollama:/root/.ollama`, ``: 这些参数用于将主机的目录挂载到容器内部的特定路径，以便于数据持久化和共享。
- `-p 11434:11434`: 将主机的11434端口映射到容器的11434端口，允许外部通过主机的该端口访问容器的服务。
- `ollama/ollama`: 指定要使用的镜像和标签，这里使用的是ollama/ollama镜像的latest版本。



运行后打开浏览器 访问对应的ip加端口 能看到页面正常显示则成功

例如访问 http://192.168.1.12:11434/