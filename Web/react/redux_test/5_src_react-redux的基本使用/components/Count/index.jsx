import React, { Component } from 'react'

export default class Count extends Component {

  state = {}

  //加法
  increament = () => {
    //函数体
    const{value} = this.selectNumbr
    this.props.add(value*1)
  }
  //减法
  decreament = () => {
    //函数体
    const{value} = this.selectNumbr
    this.props.minus(value*1)
  }
  //奇数再加
  increamentIfOdd = () => {
    const{value} = this.selectNumbr
    if(this.props.count%2!== 0){
      this.props.add(value*1)
    }
  }
  //异步加
  increamentAsync = () => {
    const{value} = this.selectNumbr
    this.props.asyncAdd(value*1,1000)
  }

  render() {
    return (
      <div>
        <h1>当前求和为:{this.props.count}</h1>
        <select ref={c =>this.selectNumbr = c}>
            <option value="1">1</option>
            <option value="2">2</option>
            <option value="3">3</option>
        </select>&nbsp;
        <button onClick={this.increament}>+</button> &nbsp;
        <button onClick={this.decreament}>-</button>&nbsp;
        <button onClick={this.increamentIfOdd}>当前求和为基数再加</button>&nbsp;
        <button onClick={this.increamentAsync}>异步加</button>&nbsp;
      </div>
    )
  }
}
