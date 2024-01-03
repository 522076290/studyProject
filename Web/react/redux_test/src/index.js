import React from 'react'
import ReactDOM from 'react-dom';
import App from './App'
import store from './redux/store'
import { Provider } from 'react-redux'


ReactDOM.render(
    // 此处需要用Provider包裹，目的是让App所有的子组件都能访问store
    <Provider store={store}>
        <App />
    </Provider>,
    document.getElementById('root')
    )



