// 创建“外壳”组件App
import React,{Component} from 'react';
import hello from './index.module.css'

export default class Hello extends Component {
    render(){
        return (
            <div>
                <h2 className={hello.title}>hello world</h2>
            </div>
        )
    }
}