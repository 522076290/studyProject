import React from 'react'
import {useParams} from 'react-router-dom'


const DetailData = [
    {id:'1',content:'你好，中国'},
    {id:'2',content:'你好，尚硅谷'},
    {id:'3',content:'你好，未来的自己'}
]

export default function Detail() {
  // 通过解构赋值，拿到params传递的参数
  const {id,title} = useParams()
  const findResult = DetailData.find((datailObj)=>{
    return datailObj.id === id
  })
  return (
    <ul>
      <li>ID:{id}</li>
      <li>TITLE:{title}</li>
      <li>CONTENT:{findResult.content}</li>
    </ul>
  )
}
