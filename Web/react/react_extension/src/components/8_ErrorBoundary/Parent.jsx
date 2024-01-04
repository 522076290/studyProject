import React, { Component } from 'react'
import Child from './Child'

export default class Parent extends Component {

    state={
        hasError:'' //用于标识子组件是否产生错误
    }
    //当Parent的子组件出现报错的时候 会触发getDerivedStateFromError方法调用，并携带错误信息
    static getDerivedStateFromError(error) {
        console.log('@@@error', error)
        return {
            hasError:error
        }
    }

    componentDidCatch(error, info) {
        console.log('@@@error', error)
        console.log('@@@info', info)
        console.log('统计错误次数，发送给后台')
    }

  render() {
    return (
      <div>
        <h2>
         我是Parent组件
        </h2>
        {this.props.hasError ? <h2>当前网络不稳定，请稍后再试</h2> : <Child />}
      </div>
    )
  }
}
