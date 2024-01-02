import { createIncreatementAction, createDecreamentAction, createIncreatementAsyncAction } from '../../redux/actions/count'
//引入connect 用于连接UI组件与redux
import { connect } from 'react-redux'
import React, { Component } from 'react'

//定义UI组件
class Count extends Component {

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
        <h2>我是Count组件</h2>
        <h1>当前求和为:{this.props.count},下方组件总人数为：{this.props.personcount}</h1>
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


//使用connect()()创建并暴露一个Count的容器组件
export default  connect(
    state => ({ count: state.count, personcount: state.persons.length }),
    // mapDispatchToProps 的一般写法
    // dispatch => (
    //     {
    //         add:number => dispatch(createIncreatementAction(number)),
    //         minus:number => dispatch(createDecreamentAction(number)),
    //         asyncAdd:(number,time) => dispatch(createIncreatementAsyncAction(number,time))
    //     }
    // )
    
    //mapDispatchToProps的简写
    {
        add: createIncreatementAction,
        minus: createDecreamentAction,
        asyncAdd: createIncreatementAsyncAction
    }
)(Count)

