/**
 * 该文件专门为Count组件生成action对象
 */
import { INCREAMENT,DECREAMENT } from "./constant";

export const createIncreatementAction =  data => ({type:INCREAMENT,data})

export const createDecreamentAction =  data => ({type:DECREAMENT,data})