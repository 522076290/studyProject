import React, { PureComponent } from "react";
import './index.css'

export default class Parent extends PureComponent {

    state = {carName:"奔驰C63"}

    changeCar = () => {
        this.setState({carName:"迈巴赫"})
    }

    // shouldComponentUpdate(nextProps,nextState){
    //     console.log(this.state)
    //     console.log(nextState)
    //     return this.state.carName !== nextState.carName
     
    // }

  render() {
    console.log("父组件渲染")
    const {carName} = this.state
    return (
      <div className="parent">
        <h3>我是Parent组件</h3>
        <p>我的车名字是：{carName}</p>
        <button onClick={this.changeCar}>点我换车</button>
        <Child carName={carName}/>
      </div>
    );
  }
}

class Child extends PureComponent {

  // shouldComponentUpdate(nextProps,nextState){
  //   console.log(this.props)
  //   console.log(nextProps)
  //   return !this.props.carName !== nextProps.carName 

  // }

  render() {
    console.log("子组件渲染");
    return (
      <div className="child">
        <h3>我是Child组件</h3>
        <p>我接到的的车名字是：{this.props.carName}</p>
      </div>
    );
  }
}
