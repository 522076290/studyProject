import React from 'react'
import ReactDOM from'react-dom'

//类式组件
// export default class Demo extends React.Component {

//   state = {
//     count: 0,
//   }

//   myRef = React.createRef()

//   add = () => {
//     //函数式的setState
//     this.setState(state => ({count: state.count + 1}), () => {
//       console.log('更新完成',this.state.count)
//     })
//   }

//   unmount = () => {
//     ReactDOM.unmountComponentAtNode(document.getElementById('root'))
//   }


//   show = () => {
//     alert(this.myRef.current.value)
//   }

//   componentDidMount() {
//     this.timer = setInterval(() => {
//       this.setState(state => ({count: state.count + 1}))
//     }, 1000)
//   }

//   componentWillUnmount() {
//     clearInterval(this.timer)
//   }

//   render() {
//     return (
//       <div>
//         <input type="text" ref={this.myRef}/>
//         <h1>当前求和为：{this.state.count}</h1>
//         <button onClick={this.add}>点我+1</button>
//         <button onClick={this.unmount}>卸载组件</button>
//         <button onClick={this.show}>点击提示数据</button>
//       </div>
//     )
//   }
// }

export default function Demo() {
  const [count, setCount] = React.useState(0)
  const [name, setName] = React.useState('tom')
  const myRef = React.useRef()

  React.useEffect(() => {
    let timer = setInterval(() => {
      setCount(count => count + 1)
    }, 1000)
    return () => {
      clearInterval(timer)
      console.log('卸载了')
    }
  }, [])
  
  //加的回调
  const add = () => {
    setCount(count + 1)
  }
  //更改名字的回调
  const changeName = () => {
    setName('jack')
  }

  const unmount = () => {
    ReactDOM.unmountComponentAtNode(document.getElementById('root'))
  }

  const show = () => {
    alert(myRef.current.value)
  }
  
  return (
    <div>
      <input type="text" ref={myRef}/>
      <h1>当前求和为：{count}</h1>
      <h2>当前姓名为：{name}</h2>
      <button onClick={add}>点我+1</button>
      <button onClick={changeName}>点我改姓名</button>
      <button onClick={unmount}>卸载组件</button>
      <button onClick={show}>点击提示数据</button>
    </div>
  )
}