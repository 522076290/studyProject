import React, { Component } from 'react'
import { Button } from 'antd';
import {WechatOutlined,WeiboCircleOutlined} from '@ant-design/icons'

export default class App extends Component {
  render() {
    return (
      <div>
      App
      <button>button</button>
      <Button type="primary">Primary Button</Button>
      <WechatOutlined />
      <WeiboCircleOutlined />
      </div>
    )
  }
}
