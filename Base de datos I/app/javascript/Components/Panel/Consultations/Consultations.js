import React, {Component} from 'react'
import axios from "axios"
import { passCsrfToken } from "../../../helpers/csrfToken"

import { BrowserRouter, Switch, Route, Link } from "react-router-dom";

import {
    CButton,
    CBadge,
    CCard,
    CCardBody,
    CCardHeader,
    CCol, CRow
} from "@coreui/react";

class Consultations extends Component {
    constructor(props) {
        super(props);
        this.state = {
            currentUser: this.props.currentUser,
            consultations: []
        }
    }

    async componentDidMount(){
        await this.getConsultations()
        passCsrfToken(document,axios)
    }

    getConsultations = async () => {
        await axios.get('/panel/consultations.json', {}).then(
            (response) => {
                this.setState({
                    consultations: response.data.filter(consultation => consultation.user.id === this.state.currentUser.id)
                })
            }
        ).catch(
            (error) => {
                console.log(error)
            }
        )
    }

    render() {
        const { consultations } = this.state
        return (
            <>
                <CRow>
                    <CCol lg={12}>
                        <CCard>
                            <CCardHeader>
                                Panel de Consultas
                            </CCardHeader>
                            <CCardBody>
                                <table className="table table-striped table-hover">
                                    <thead>
                                    <tr>
                                        <th> # </th>
                                        <th> Nombre de Paciente</th>
                                        <th> Codigo de Paciente </th>
                                        <th> Prioridad </th>
                                        <th> Hora </th>
                                        <th> Estado </th>
                                        <th> Acciones </th>
                                    </tr>
                                    </thead>
                                    <tbody>
                                    {
                                        consultations.length > 0 ?
                                            consultations.map((consultation, index) => (
                                                <tr key={ consultation.id }>
                                                    <td> { (index + 1) } </td>
                                                    <td> { consultation.triage.patient.full_name } </td>
                                                    <td> { consultation.triage.patient.nro_register } </td>
                                                    <td> { consultation.triage.priority } </td>
                                                    <td> { consultation.hour } </td>
                                                    <td> { consultation.status === 'on_hold' ?
                                                            <CBadge color="info">En Espera'</CBadge> :
                                                            <CBadge color="success">Atendido'</CBadge>
                                                    }
                                                    </td>
                                                    <td>


                                                        { consultation.status === 'on_hold' ?
                                                            <Link
                                                                to={{
                                                                    pathname: `/consultas/atender/${consultation.triage.id}`,
                                                                }}
                                                                className="btn btn-sm btn-success mr-2">Atender</Link> :
                                                            <Link
                                                                to={{
                                                                    pathname: `/consultas/ver/${consultation.id}`,
                                                                }}
                                                                className="btn btn-sm btn-info mr-2">Ver</Link>
                                                        }


                                                        {/*<CButton*/}
                                                        {/*    color="danger"*/}
                                                        {/*    size="sm"*/}
                                                        {/*    className="mr-2"*/}
                                                        {/*    onClick ={ ()=> this.handleDelete(user) }*/}
                                                        {/*>*/}
                                                        {/*    Eliminar*/}
                                                        {/*</CButton>*/}
                                                    </td>
                                                </tr>
                                            )) :
                                            <tr>
                                                <td>
                                                    No hay registros para mostrar
                                                </td>
                                            </tr>
                                    }
                                    </tbody>
                                </table>
                            </CCardBody>
                        </CCard>
                    </CCol>
                </CRow>
            </>
        );
    }
}

export default Consultations