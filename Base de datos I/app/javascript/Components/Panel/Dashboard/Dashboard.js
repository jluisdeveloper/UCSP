import React, {Component} from 'react'
import axios from "axios"
import { passCsrfToken } from "../../../helpers/csrfToken";

import {
    CCardGroup,
    CCol,
    CRow,
    CWidgetIcon,
    CWidgetProgressIcon,
    CProgress,
} from '@coreui/react'

import CIcon from '@coreui/icons-react'

class Dashboard extends Component {
    constructor(props) {
        super(props);
        this.state= {
            numberPatients: 0
        }
    }


    componentDidMount() {
        axios.get('panel/full_patients').then(
            (response) => {
                this.setState({
                    numberPatients: response.data.patients.length
                })
            }
        ).catch(
            (error) => {
                console.log(error)
            }
        )
    }


    render() {
        const { numberPatients } = this.state
        return (
            <>
                <CRow>
                    <CCol xs="12" sm="6" lg="3">
                        <CWidgetIcon text="Jorge Huanca" header="Integrante DEV" color="info" iconPadding={false}>
                            <CIcon width={24} name="cil-user"/>
                        </CWidgetIcon>
                    </CCol>
                    <CCol xs="12" sm="6" lg="3">
                        <CWidgetIcon text="Miguel Motta" header="Integrante DEV" color="info" iconPadding={false}>
                            <CIcon width={24} name="cil-user"/>
                        </CWidgetIcon>
                    </CCol>
                    <CCol xs="12" sm="6" lg="3">
                        <CWidgetIcon text="Dario Diaz" header="Integrante DEV" color="info" iconPadding={false}>
                            <CIcon width={24} name="cil-user"/>
                        </CWidgetIcon>
                    </CCol>
                    <CCol xs="12" sm="6" lg="3">
                        <CWidgetIcon text="Elias Vilca" header="Integrante DEV" color="info" iconPadding={false}>
                            <CIcon width={24} name="cil-user"/>
                        </CWidgetIcon>

                    </CCol>
                </CRow>

                <CCardGroup className="mb-4">
                    <CWidgetProgressIcon
                        header={ numberPatients }
                        text="Pacientes Registrados"
                        color="gradient-info"
                    >
                        <CIcon name="cil-people" height="36"/>
                    </CWidgetProgressIcon>
                    <CWidgetProgressIcon
                        header="385"
                        text="Consultas Registradas"
                        color="gradient-success"
                    >
                        <CIcon name="cil-userFollow" height="36"/>
                    </CWidgetProgressIcon>
                    <CWidgetProgressIcon
                        header="1238"
                        text="Farmaceuticos vendidos"
                        color="gradient-warning"
                    >
                        <CIcon name="cil-basket" height="36"/>
                    </CWidgetProgressIcon>
                    <CWidgetProgressIcon
                        header="28%"
                        text="Returning Visitors"
                    >
                        <CIcon name="cil-chartPie" height="36"/>
                    </CWidgetProgressIcon>
                    <CWidgetProgressIcon
                        header="5:34:11"
                        text="Avg. Time"
                        color="gradient-danger"
                        progressSlot={
                            <CProgress color="danger" size="xs" value={75} animated className="my-3"
                            />}
                    >
                        <CIcon name="cil-speedometer" height="36"/>
                    </CWidgetProgressIcon>
                </CCardGroup>
            </>
        );
    }
}

export default Dashboard;