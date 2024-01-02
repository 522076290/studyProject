/**
 * 该文件专门用于暴露一个sotre对象 整个应用只有一个store对象
 */
//引入store 专门用于创建redux中最为核心的store对象
import {configureStore} from '@reduxjs/toolkit'
//引入为 counter 组件创建的reducer
import countReducer from './reducers/count'
//引入为 person 组件创建的reducer
import personReducer from './reducers/person'

//创建store对象 并暴露
export default configureStore({
    reducer: {
      count: countReducer,  // 使用键来指定reducer
      persons: personReducer,
    }
  });