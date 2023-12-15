import React, { Component } from 'react'
//引入store 用于获取 redux中保存的状态
import store from '../../redux/store'
//引入actionCreator 用于创建action对象
import {
  createIncreatementAction,
  createDecreamentAction
} from '../../redux/count_action'

export default class Count extends Component {

  state = {}


  // componentDidMount(){
  //   //订阅redux中状态的变化
  //   store.subscribe(()=>{
  //     //获取redux中保存的状态
  //     this.setState({})
  //   })
  // }

  //加法
  increament = () => {
    //函数体
    const{value} = this.selectNumbr
    store.dispatch(createIncreatementAction(value*1))
  }
  //减法
  decreament = () => {
    //函数体
    const{value} = this.selectNumbr
    store.dispatch(createDecreamentAction(value*1))
  }
  //奇数再加
  increamentIfOdd = () => {
    const{value} = this.selectNumbr
    const count = store.getState().count
    if(count%2===1){
      store.dispatch(createIncreatementAction(value*1))
    } 
  }
  //异步加
  increamentAsync = () => {
    const{value} = this.selectNumbr
    setTimeout(() => {
      store.dispatch(createIncreatementAction(value*1))
    }, 1000)
  }

  render() {
    return (
      <div>
        <h1>当前求和为:{store.getState().count}</h1>
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
