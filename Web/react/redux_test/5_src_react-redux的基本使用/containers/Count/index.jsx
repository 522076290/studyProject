//引入Count的UI组件
import CountUI from '../../components/Count'
import { createIncreatementAction, createDecreamentAction, createIncreatementAsyncAction } from '../../redux/count_action'

//引入connect 用于连接UI组件与redux
import { connect } from 'react-redux'

//mapStateToProps() 用于将redux的state映射到UI组件的props上
function mapStateToProps(state) {
    return { count: state.count }
}

//mapDispatchToProps() 用于将redux的action映射到UI组件的props上
function mapDispatchToProps(dispatch) {
    return {
        add:number => dispatch(createIncreatementAction(number)),
        minus:number => dispatch(createDecreamentAction(number)),
        asyncAdd:(number,time) => dispatch(createIncreatementAsyncAction(number,time))
    }
}

//使用connect()()创建并暴露一个Count的容器组件
export default  connect(mapStateToProps, mapDispatchToProps)(CountUI)

