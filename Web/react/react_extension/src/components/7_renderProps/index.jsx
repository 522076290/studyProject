import React, { Component } from "react";
import './index.css'
import C from '../1_setState'

export default class Parent extends Component {

  render() {
    return (
      <div className="parent">
        <h3>我是Parent组件</h3>
        <A render={(name) => <C name={name}/>}/>
      </div>
    );
  }
}

class A extends Component {
  render() {
    console.log("子组件渲染");
    const {name} = this.props;
    return (
      <div className="a">
        <h3>我是A组件</h3>
        {this.props.render(name)}
        <B carName={name}/>
      </div>
    );
  }
}


class B extends Component {
  render() {
    console.log("子组件渲染");
    return (
      <div className="b">
        <h3>我是B组件</h3>
      </div>
    );
  }
}