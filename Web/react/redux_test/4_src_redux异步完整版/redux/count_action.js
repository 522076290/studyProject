/**
 * 该文件专门为Count组件生成action对象
 */
import { INCREAMENT,DECREAMENT } from "./constant";

// 同步action 就是指 action的值为Object类型的一般对象
export const createIncreatementAction =  data => ({type:INCREAMENT,data})

export const createDecreamentAction =  data => ({type:DECREAMENT,data})

// 异步action 就是指 action的值为函数 异步action中一般都会调用同步action
export const createIncreatementAsyncAction = (data,time) => {
    return (dispatch) => {
        setTimeout(() => {
            dispatch(createIncreatementAction(data))
        }, time);
    }
}