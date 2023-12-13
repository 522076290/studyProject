import React from "react";
import { useNavigate } from "react-router-dom";

// 在v6中统一使用useNavigate 在v5版本中使用withRouter函数 可以加工组件使其拥有 路由组件的属性
// withRouter的返回值是一个新组件

export default function Header() {

  const navigate = useNavigate();
  const back = () => {
    //函数体
    navigate(-1)
  }

  const forward = () => {
    //函数体
    navigate(1)
  }

    return (
      <div className="page-header">
        <h2>React Router Demo</h2>
        <button onClick={back}>回退</button> &nbsp;&nbsp;
        <button onClick={forward}>前进</button>
      </div>
    );
}
