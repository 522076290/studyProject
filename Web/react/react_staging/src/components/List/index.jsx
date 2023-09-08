import React, { Component } from "react";

export default class List extends Component {
  render() {
    return (
      <ul class="todo-main">
        <li>
          <label>
            <input type="checkbox" />
            <span>xxxxx</span>
          </label>
          <button class="btn btn-danger" style="display:none">
            删除
          </button>
        </li>
        <li>
          <label>
            <input type="checkbox" />
            <span>yyyy</span>
          </label>
          <button class="btn btn-danger" style="display:none">
            删除
          </button>
        </li>
      </ul>
    );
  }
}
