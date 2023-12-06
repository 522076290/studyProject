import React, { Component } from "react";
import {Route, Routes, Navigate} from 'react-router-dom';
import About from "./pages/About"; //About是路由组件
import Home from "./pages/Home"; //Home是路由组件
import Header from "./components/Header"; // Header是一般组件
import MyNavLink from "./components/MyNavLink";

export default class App extends Component {
  render() {
    return (
      <div>
        <div className="row">
          <div className="col-xs-offset-2 col-xs-8">
            <Header/>
          </div>
        </div>
        <div className="row">
          <div className="col-xs-2 col-xs-offset-2">
            <div className="list-group">
              {/* 原生html中 靠<a>跳转不同的页面 */}
              {/* <a className="list-group-item" href="./about.html">
                About
              </a>
              <a className="list-group-item active" href="./home.html">
                Home
              </a> */}
              
              {/* 在react中靠路由链接实现切换组件 */}
              <MyNavLink to="/about">About</MyNavLink>
              <MyNavLink to="/home">Home</MyNavLink>
            </div>
          </div>
          <div className="col-xs-6">
            <div className="panel">
              <div className="panel-body">
                {/* 注册路由 */}
                {/* Routes 组件也可以实现 Switch组件的效果 */}
                <Routes> 
                  <Route path="/about" element={<About/>}/>
                  <Route path="/home" element={<Home/>}/>
                  <Route path="*" element={<Navigate to="about" />} />{/* Navigate 实现重定向功能 */}
                </Routes>
              </div>
            </div>
          </div>
        </div>
      </div>
    );
  }
}
