// 导入模块
const { app, BrowserWindow } = require('electron/main')

// createWindow() 函数将您的页面加载到新的 BrowserWindow 实例中
const createWindow = () => {
    // 设置window大小
  const win = new BrowserWindow({
    width: 800,
    height: 600
  })
//   装载页面
  win.loadFile('index.html')
}

// 在应用准备就绪时调用函数
// 在 Electron 中，只有在 app 模块的 ready 事件触发后才能创建 BrowserWindows 实例。
app.whenReady().then(() => {
  createWindow()
  app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) {
      createWindow()
    }
  })
})

// 在 Windows 和 Linux 上，我们通常希望在关闭一个应用的所有窗口后让它退出。
//  要在您的Electron应用中实现这一点，您可以监听 app 模块的 window-all-closed 事件，并调用 app.quit() 来退出您的应用程序。此方法不适用于 macOS。
app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit()
  }
})