/**
 * 该文件专门为Count组件生成action对象
 */
import { INCREAMENT,DECREAMENT } from "../constant";

// 同步action 就是指 action的值为Object类型的一般对象
export const increament =  data => ({type:INCREAMENT,data})

export const decreament =  data => ({type:DECREAMENT,data})

// 异步action 就是指 action的值为函数 异步action中一般都会调用同步action
export const increamentAsync = (data,time) => {
    return (dispatch) => {
        setTimeout(() => {
            dispatch(increament(data))
        }, time);
    }
}