## 一、文档

[简介 | Electron (electronjs.org)](https://www.electronjs.org/zh/docs/latest/) 

## 二、基础综合介绍：

- 虽然B/S是目前开发的主流，但是C/S仍然有很大的市场需求。受限于浏览器的沙盒限制，网页应用无法满足某些场景下的使用需求，而桌面应用可以读写本地文件、调用更多系统资源，再加上Web开发的低成本、高效率的优势，这种跨平台方式越来越受到开发者的喜爱。
- Electron是一个基于Chromium和 Node.js，使用 HTML、CSS和JavaScript来构建跨平台应用的跨平台开发框架，兼容 Mac、Windows 和 Linux。目前，Electron已经创建了包括VScode和Atom在内的大量应用。
- 该项目的目的，是为了要避免使用 vue 手动建立起 electron 应用程序。electron-vue 充分利用 `vue-cli` 作为脚手架工具，加上拥有 `vue-loader` 的 `webpack`、`electron-packager` 或是 `electron-builder`，以及一些最常用的插件，如`vue-router`、`vuex` 等等。
- **Electron相当于一个浏览器的外壳，可以把网页程序嵌入到壳里面，构成 - 可以运行在桌面上的一个程序，也就是 - 把网页打包成一个在桌面运行的程序 / 软件。**

### 1、环境搭建：

安装一些常用的工具，如Node、vue和Electron等

#### 1、安装Electron - /ɪˈlektrɒn/ 

使用如下命令安装Electron插件。

```javascript
cnpm install -g electron
```

为了验证是否安装成功，可以使用如下的命令。

```sql
electron --version
```

#### 2、系统配置

`init`初始化命令会提示您在项目初始化配置中设置一些值 为本教程的目的，有几条规则需要遵循：

- `entry point` 应为 `main.js`.
- `author` 与 `description` 可为任意值，但对于[应用打包](https://www.electronjs.org/docs/tutorial/quick-start#package-and-distribute-your-application)是必填项。

你的 `package.json` 文件应该像这样：

```javascript
{

  "name": "my-electron-app",

  "version": "1.0.0",

  "description": "Hello World!",

  "main": "main.js",

  "author": "Jane Doe",

  "license": "MIT"

}
```



### 2、Electron应用程序分成三个基础模块：主进程、渲染进程和进程间通信。

#### 1、【主进程】

Electron 运行 package.json 的 main 脚本（background.js）的进程被称为主进程。 在主进程中运行的脚本通过创建web页面来展示用户界面。 一个 Electron 应用总是有 - 且只有一个主进程。

在主进程中运行的脚本控制应用程序的生命周期，并显示图形用户界面及其元素。执行本机操作系统交互，并在网页中创建渲染程序。

#### 2、【渲染进程】

由于 Electron 使用了 Chromium 来展示 Web 页面，所以 Chromium 的多进程架构也被使用到。 每个 Electron 中的 Web 页面运行在它自己的渲染进程中。在普通的浏览器中，Web页面通常在一个沙盒环境中运行，不被允许去接触原生的资源。 ***\*然而 Electron 允许用户在  Node.js 的 API 支持下 对页面中和操作系统 进行一些底层交互。\****

例：

现在您有了一个页面，将它加载进应用窗口中。 要做到这一点，你需要 两个Electron模块：

- [app](https://www.electronjs.org/docs/api/app) 模块，它控制应用程序的事件生命周期。
- [BrowserWindow](https://www.electronjs.org/docs/api/browser-window) 模块，它创建和管理应用程序 窗口。

因为主进程运行着Node.js，您可以在文件头部将他们导入作为[公共JS](https://nodejs.org/docs/latest/api/modules.html#modules_modules_commonjs_modules)模块：

```javascript
const { app, BrowserWindow } = require('electron')
```

然后，添加一个`createWindow()`方法来将`index.html`加载进一个新的`BrowserWindow`实例。

```javascript
function createWindow () {

  const win = new BrowserWindow({

    width: 800,

    height: 600

  })

  win.loadFile('index.html')

}
```

接着，调用`createWindow()`函数来打开您的窗口。

#### 3、【主进程与渲染进程通信】

主进程使用 BrowserWindow 实例 **【Electron自带的】** 创建页面。 每个 BrowserWindow 实例都在自己的渲染进程里运行页面。 当一个 BrowserWindow 实例被销毁后，相应的渲染进程也会被终止 **【每次改动index.js页面都会重新渲染】**。主进程管理所有的Web页面和它们对应的渲染进程。 每个渲染进程都是独立的，它只关心它所运行的 Web 页面。

#### 4、【如何在渲染进程中通讯主进程】

> 通讯的操控主要在主进程 ，通过主进程来控制渲染进程，然后渲染进程会将把响应的事件返回到主进程，然后再对我们的页面进行操作

![img](https://img-blog.csdnimg.cn/20210603152753319.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0hlaV9sb3ZlbHlfY2F0,size_16,color_FFFFFF,t_70)

**1、src目录结构**

在Electron目录中，src会包包含main和renderer两个目录。

**2、main目录**

main目录会包含index.js和index.dev.js两个文件。

- index.js：应用程序的主文件，electron 也从这里启动的，它也被用作 webpack 产品构建的入口文件，所有的 main 进程工作都应该从这里开始。
- index.dev.js：此文件专门用于开发阶段，因为它会安装 electron-debug 和 vue-devtools。一般不需要修改此文件，但它可以扩展开发的需求。

**3、渲染进程目录**

renderer是渲染进程目录，平时项目开发源码的存放目录，包含assets、components、router、store、App.vue和main.js。

\- assets：assets下的文件如（js、css）都会在dist文件夹下面的项目目录分别合并到一个文件里面去。

\- components：此文件用于存放应用开发的组件，可以是自定义的组件。

\- router：如果你了解vue-router，那么Electron项目的路由的使用方式和vue-router的使用方式类似。

\- store：electron-vue 利用 vuex 的模块结构创建多个数据存储，并保存在 src/renderer/store/index 中。

## **三、经典例 —建议QQ音乐播放器**

#### 1、qq音乐播放器

[qq音乐播放器](https://link.zhihu.com/?target=https%3A//github.com/SmallRuralDog/electron-vue-music)基于 electron-vue 开发的音乐播放器，界面模仿QQ音乐，使用的技术栈electron-vue+vue+vuex+vue-router+element- UI。可以使用如下的方式来运行项目。

```bash
git clone https://github.com/SmallRuralDog/electron-vue-music.git

cd electron-vue-music

npm install

# 运行开发模式
npm run dev

# 打包安装文件 
npm run build
```

部分运行效果如下图。

![img](https://img-blog.csdnimg.cn/img_convert/94901b3469f6e9971a4e4677adc3fc3a.png)



#### 2、网易云音乐

[electron-vue-cloud-music](https://link.zhihu.com/?target=https%3A//github.com/xiaozhu188/electron-vue-cloud-music)是一款使用Electron+Vue+Ant Design Vue技术开发跨平台桌面应用。下载链接：[https://github.com/xiaozhu188/electron-vue-cloud-music](https://link.zhihu.com/?target=https%3A//github.com/xiaozhu188/electron-vue-cloud-music)。具有如下特点： - 拖拽播放 - 桌面歌词 - mini模式 - 自定义托盘右键菜单 - 任务栏缩略图，歌曲操作 - 音频可视化 - 自动/手动检查更新 - Nedb数据库持久化 - 自定义安装路径，安装界面美化 - 浏览器中启动客户端 - Travis CL，AppVeyor自动构建 - 换肤，下载，本地歌曲匹配，网络变化桌面通知，分享歌曲/歌单/MV/视频等到QQ空间 - 登录，私人Fm，歌单，专辑，歌手，排行榜，MV，视频，评论，搜索，用户，动态，粉丝，关注，云盘，收藏... - 心动模式，歌词微调，下一首播放，追加播放，单曲循环，随机播放，列表循环 - 路由导向，局部刷新，首页栏目调整并持久化...

以下是部分运行效果：

![img](https://img-blog.csdnimg.cn/img_convert/c4baac05969c8ce06dc80b47e69ecf9d.png)

![img](https://img-blog.csdnimg.cn/img_convert/53f8e6e469cfe693701b7b9d0ae36f88.png)

#### PS:

#### 洛雪音乐助手源码使用方法

环境要求：Node.js 12.x+

```html
# 开发模式
npm run dev

# 构建免安装版
npm run pack:dir

# 构建安装包（Windows版）
npm run pack:win

# 构建安装包（Mac版）
npm run pack:mac

# 构建安装包（Linux版）
npm run pack:linux
```

#### 3、其他基于 ELECTRON-VUE 的作品

看看一些基于 electron-vue 建造的了不起的的项目。

- [Surfbird](https://github.com/surfbirdapp/surfbird): 一个基于 Electron 和 Vue 的 Twitter 客户端
- [Lulumi-browser](https://github.com/qazbnm456/lulumi-browser): Lulumi-browser 是一个轻量级的浏览器，基于 Vue.js 2 和 Electron
- [Space-Snake](https://github.com/ilyagru/Space-Snake): 使用 Electron 和 Vue.js 构建的桌面游戏。
- [Forrest](https://github.com/stefanjudis/forrest): 一个 npm 脚本的桌面客户端
- [miikun](https://github.com/hiro0218/miikun): 一个简单的 Markdown 编辑器
- [Dakika](https://github.com/Madawar/Dakika): 超省时的应用程序，使写作变得轻而易举
- [Dynamoc](https://github.com/ieiayaobb/dynamoc): Dynamoc 是一个 dynamodb-local、 dynalite 和 AWS dynamodb 的图形化界面客户端
- [Dockeron](https://github.com/dockeron/dockeron): Dockeron 项目, 基于 Electron + Vue.js 的 Docker 桌面客户端
- [Easysubs](https://github.com/matiastucci/easysubs): 快速简单地下载字幕
- 洛雪音乐助手：[GitHub - lyswhut/lx-music-desktop at dev](https://github.com/lyswhut/lx-music-desktop/tree/dev) (注意版权)