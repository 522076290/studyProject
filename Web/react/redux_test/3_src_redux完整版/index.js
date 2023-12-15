import React from 'react'
import ReactDOM from 'react-dom';
import App from './App'
import store from './redux/store'

store.subscribe(() => {
    ReactDOM.render(
        <App />,
        document.getElementById('root')
    )
})

ReactDOM.render(
    <App />,
    document.getElementById('root')
    )