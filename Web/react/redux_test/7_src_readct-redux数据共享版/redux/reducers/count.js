/**
 * 1.该文件是用于创建一个为CountReducer服务的reducer reducer的本质是一个函数
 * 2.reducer会接收到两个参数 分别为：之前的状态(preState),动作对象(action)
 */
import { INCREAMENT,DECREAMENT } from "../constant";

const initState = 0
export default function countReducer(preState=initState,action){
    console.log(preState,action)
    if(preState === undefined) preState = 0
    //从action对象中获取type和data属性
    const {type,data} = action;
    //根据type属性的值来进行不同的操作
    switch(type){
        case INCREAMENT: //如果是加
        return preState + data;
        case DECREAMENT: //如果是减
        return preState - data;
        default:
        return preState;
    }
}