import React from "react";
import { Link, Routes, Route, useNavigate } from "react-router-dom";
import Detail from "./Detail";

export default function Message() {
  const state = {
    messageArr: [
      { id: 1, title: "消息1" },
      { id: 2, title: "消息2" },
      { id: 3, title: "消息3" },
    ],
  };
  const navigate = useNavigate();
  const replaceShow = (id, title) => {
    //编写一段代码让其实现Detail组件 且为replace跳转
    //用navigate实现编程式导航
    if (navigate) {
      // replace跳转 + 携带params参数
      // navigate(`/home/message/detail/${id}/${title}`, { replace: true });

      // replace跳转 + 携带search参数
      navigate(`/home/message/detail/?id=${id}&title=${title}`, { replace: true });

      // replace跳转 + 携带state参数
      // navigate(`/home/message/detail/`, { replace: true, state:{id:id,title:title}});
    }
  };
  const pushShow = (id, title) =>{
    //编写一段代码让其实现Detail组件 且为push跳转
    //用navigate实现编程式导航
    if (navigate) {
      // push跳转+ 携带 params 参数
      // navigate(`/home/message/detail/${id}/${title}`, { replace: false });

      // push跳转 + 携带search参数
      navigate(`/home/message/detail/?id=${id}&title=${title}`, { replace: false });

      // push跳转 + 携带state参数
      // navigate(`/home/message/detail/`, { replace: false, state:{id:id,title:title}});
    }
  }

  const back = () => {
    //函数体
    navigate(-1)
  }

  const forward = () => {
    //函数体
    navigate(1)
  }

  const { messageArr } = state;
  return (
    <div>
      <ul>
        {messageArr.map((msgObj) => {
          return (
            <li key={msgObj.id}>
              {/* 向路由组件传递params参数 */}
              {/* <Link to={`/home/message/detail/${msgObj.id}/${msgObj.title}`}>
                {msgObj.title}
              </Link> */}
              {/* 向路由组件传递search参数 */}
              <Link to={`/home/message/detail/?id=${msgObj.id}&title=${msgObj.title}`}>{msgObj.title}</Link>
              {/* 向路由组件传递state参数 */}
              {/* <Link to={"/home/message/detail/"} state={{id:msgObj.id,title:msgObj.title}}>{msgObj.title}</Link> */}
              &nbsp;<button
                onClick={() => {
                  pushShow(msgObj.id, msgObj.title);
                }}
              >push查看</button>
              &nbsp;
              <button
                onClick={() => {
                  replaceShow(msgObj.id, msgObj.title);
                }}
              >
                replace查看
              </button>
            </li>
          );
        })}
      </ul>
      <hr />
      <Routes>
        {/* 声明接收params参数 */}
        {/* <Route path="/detail/:id/:title" element={<Detail />} /> */}

        {/* search参数无需声明接收，正常注册路由即可 */}
        {/* <Route path="/detail" element={<Detail/>}/> */}

        {/* state参数无需声明接收，正常注册路由即可 */}
        <Route path="/detail" element={<Detail/>}/>
      </Routes>

      <button onClick={back}>回退</button> &nbsp;&nbsp;
      <button onClick={forward}>前进</button>
    </div>
  );
}
