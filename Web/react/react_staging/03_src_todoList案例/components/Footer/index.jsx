import React, { Component } from "react";
import PropTypes from "prop-types";
import "./index.css"

export default class Footer extends Component {

  //对接收的props类型以及必要性的限制
  static propTypes = {
    todos: PropTypes.array.isRequired,
    checkAllTodo: PropTypes.func.isRequired,
    cleanALlDone: PropTypes.func.isRequired,
  }

  //全选checkbox的回调
  handleCheckAll = (event) => {
    this.props.checkAllTodo(event.target.checked);
  }

  //清除所有已完成的回调
  handleClearAllDone = () => {
    this.props.cleanALlDone();
  }

  render() {
    const { todos} = this.props;
    //已完成的个数
    const downCount = todos.reduce((pre,todo)=> pre + (todo.done ? 1 : 0),0)
    //总数
    const total = todos.length
    return (
      <div className="todo-footer">
        <label>
          <input type="checkbox" onChange={this.handleCheckAll} checked={downCount===total && total !== 0} />
        </label>
        <span>
          <span>已完成{downCount}</span> / 全部{total}
        </span>
        <button onClick={this.handleClearAllDone} className="btn btn-danger">清除已完成任务</button>
      </div>
    );
  }
}
