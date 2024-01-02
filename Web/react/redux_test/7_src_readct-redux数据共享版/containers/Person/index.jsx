import React, { Component } from 'react'
import { nanoid } from 'nanoid'
import {connect} from 'react-redux'
import {createAddPersonAction} from '../../redux/actions/person'

class Person extends Component {

  addPerson = ()=>{
    const name = this.nameNode.value
    const age = this.ageNode.value
    const personObj = {
      id: nanoid(),
      name,
      age
    }
    this.props.addPersonAction(personObj)
    this.nameNode.value=''
    this.ageNode.value=''
  }

  render() {
    return (
      <div>
      <h2>我是Person组件,上方组件求和为{this.props.sum}</h2>
      {/* 输入名字年龄点击添加 */}
        <input type="text" ref={c=>this.nameNode = c} placeholder="请输入名字" />
        <input type="text" ref={c=>this.ageNode = c} placeholder="请输入年龄" />
        <button onClick={this.addPerson}>添加</button>
      {/* 显示名字年龄 */}
      <ul>
        {
          this.props.persons.map(person => (
            <li key={person.id}>
              {person.name} --  {person.age}
            </li>
          ))
        }
      </ul>
      </div>
    )
  }
}


export default connect(
  state => ({ 
    persons: state.persons,
    sum: state.count
}), //映射状态
  {addPersonAction:createAddPersonAction}
)(Person)
