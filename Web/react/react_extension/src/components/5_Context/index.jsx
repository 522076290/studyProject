import React, { Component } from "react";
import './index.css'

// 创建一个context 
const MyContext = React.createContext();
const { Provider } = MyContext;

export default class A extends Component {
  state = { username: "tom",age: 20 };

  render() {
    return (
      <div className="parent">
        <h3>我是A组件</h3>
        <h4>我的用户名是:{this.state.username}</h4>
        <Provider value={this.state}>
          <B />
        </Provider>
      </div>
    );
  }
}

class B extends Component {
  render() {
    return (
      <div className="child">
        <h3>我是B组件</h3>
        <h4>我从A组件接收到的用户名是:</h4>
        <C />
      </div>
    );
  }
}

// class C extends Component {
//   //声明接收Context
//   static contextType = MyContext;
//   render() {
//     const { username,age } = this.context;
//     return (
//       <div className="grand">
//         <h3>我是C组件</h3>
//         <h4>我从B组件接收到的用户名是:{username},年龄是:{age}</h4>
//       </div>
//     );
//   }
// }

function C() {
  //声明接收Context
  const { username,age } = React.useContext(MyContext);
  return (
    <div className="grand">
      <h3>我是C组件</h3>
      <h4>我从B组件接收到的用户名是:{username},年龄是:{age}</h4>
    </div>
  );
}