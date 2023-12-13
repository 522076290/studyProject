import React,{useEffect} from "react";
import { useNavigate} from "react-router-dom";





export default function News() {

  const navigate  = useNavigate();

  useEffect(() => {
    //函数体
    setTimeout(() => {
        navigate('/home/message')
      },2000)
  })

  return (
    <ul>
      <li>news001</li>
      <li>news002</li>
      <li>news003</li>
    </ul>
  );
}
