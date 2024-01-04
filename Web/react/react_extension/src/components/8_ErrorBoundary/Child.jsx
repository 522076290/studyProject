import React, { Component } from 'react'

export default class Child extends Component {

    state={
        // users:[
        //     {
        //         id:'001',
        //         name:'张三',
        //         age:20
        //     },
        //     {
        //         id:'002',
        //         name:'李四',
        //         age:21
        //     },
        //     {
        //         id:'003',
        //         name:'王五',
        //         age:22
        //     }
        // ]
        users:'abc'
    }

  render() {
    return (
      <div>
        <h2>我是Child组件</h2>
        {
            this.state.users.map(item=>{
                return (
                    <div key={item.id}>
                        <p>id:{item.id}</p>
                        <p>name:{item.name}</p>
                        <p>age:{item.age}</p>
                    </div>
                )
            })
        }
      </div>
    )
  }
}
