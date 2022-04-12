import React, { Component } from 'react'
import axios from 'axios'
import {
    TheContent,
    TheSidebar,
    TheFooter,
    TheHeader
} from './index'

class TheLayout extends Component {
    constructor() {
        super();
        this.state = {
            currentUser : {
                id: '',
                full_name: '',
                email: '',
                salary: 0.0,
                payment_date: '',
                hiring_date: '',
                phone: '',
                address: '',
                code_job: '',
                avatar: {
                    url: '',
                    thumb: {
                        url: ''
                    },
                    medium: {
                        url: ''
                    }
                },
                profession:{
                    id: 0,
                    name: ''
                },
                speciality:{
                    id: 0,
                    name: ''
                },
                created_at: '',
                updated_at: ''
            }
        }
    }

    async componentDidMount() {
        await axios.get('/panel/current_user', {}).then(
            (response) => {
                this.setState({
                    currentUser: response.data
                })
            }
        ).catch(
            (error) => {
                console.log(error)
            }
        )
    }

    render() {
        const { currentUser } = this.state
        return(
            <div className="c-app c-default-layout">
                <TheSidebar/>
                <div className="c-wrapper">
                    <TheHeader currentUser={ currentUser }/>
                    <div className="c-body">
                        <TheContent currentUser={ currentUser } />
                    </div>
                    <TheFooter/>
                </div>
            </div>
        )
    }
}
export default TheLayout
