// 创建“外壳”组件App
import React,{Component} from 'react';
import './index.css'

export default class Welcome extends Component {
    render(){
        return (
            <div>
                <h2 className='demo'>Welcome</h2>
            </div>
        )
    }
}