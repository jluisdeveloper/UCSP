import React, {Component} from 'react';
import axios from "axios";
import { passCsrfToken } from "../../../helpers/csrfToken";
import {
    CCard,
    CCardBody,
    CCardHeader,
    CBadge,
    CCol, CRow, CForm, CFormGroup, CLabel, CInput
} from "@coreui/react";

class ShowConsultation extends Component {
    constructor(props) {
        super(props);
        this.state = {
            hour: '',
            status: '',
            triage: {
                id:0,
                blood_pressure: '',
                priority: '',
                patient: {},
            },
            treatment: {
                diagnostic: '',
                prescriptions: [],
                orders: []
            },
            user: {},

            typeOrders: [],

        }
    }

    async componentDidMount() {
        await this.getConsultation()
        passCsrfToken(document,axios)
    }


    getConsultation = async () => {
        await axios.get('/panel/consultations/' + String(this.props.match.params.id), {}).then(
            (response) => {
                this.setState({
                    hour: response.data.hour,
                    status: response.data.status,
                    triage: response.data.triage,
                    treatment: response.data.treatment,
                    user: response.data.user,
                })
            }
        )
    }


    render() {
        console.log(this.state.triage)
        return (
            <>
                <CRow>
                    <CCol xs="12" md="6">
                        <CCard>
                            <CCardHeader>
                                Datos del
                                <small> Paciente</small>
                            </CCardHeader>
                            <CCardBody>
                                <CForm action="" method="post" encType="multipart/form-data" className="form-horizontal">
                                    <CFormGroup row>
                                        <CCol md="3">
                                            <CLabel htmlFor="disabled-input">Nombres</CLabel>
                                        </CCol>
                                        <CCol xs="12" md="9">
                                            <CInput
                                                placeholder={ this.state.triage.patient.full_name }
                                                disabled />
                                        </CCol>
                                    </CFormGroup>
                                    <CFormGroup row>
                                        <CCol md="3">
                                            <CLabel htmlFor="disabled-input">Presion Sanguinea</CLabel>
                                        </CCol>
                                        <CCol xs="12" md="9">
                                            <CInput
                                                placeholder={ this.state.triage.blood_pressure }
                                                disabled />
                                        </CCol>
                                    </CFormGroup>
                                    <CFormGroup row>
                                        <CCol md="3">
                                            <CLabel htmlFor="disabled-input">Peso</CLabel>
                                        </CCol>
                                        <CCol xs="12" md="9">
                                            <CInput
                                                placeholder={ this.state.triage.weight }
                                                disabled />
                                        </CCol>
                                    </CFormGroup>
                                    <CFormGroup row>
                                        <CCol md="3">
                                            <CLabel htmlFor="disabled-input">Estatura </CLabel>
                                        </CCol>
                                        <CCol xs="12" md="9">
                                            <CInput
                                                placeholder={ this.state.triage.height }
                                                disabled />
                                        </CCol>
                                    </CFormGroup>
                                    <CFormGroup row>
                                        <CCol md="3">
                                            <CLabel htmlFor="disabled-input">Diagnostico </CLabel>
                                        </CCol>
                                        <CCol xs="12" md="9">
                                            <CInput
                                                placeholder={ this.state.treatment.diagnostic }
                                                disabled />
                                        </CCol>
                                    </CFormGroup>
                                </CForm>
                            </CCardBody>
                        </CCard>
                    </CCol>

                    <CCol xs="12" md="6">
                        <CCard>
                            <CCardHeader>
                                Tratamiento y/o Ordenes del
                                <small> Paciente</small>
                            </CCardHeader>
                            <CCardBody>
                                <CForm action="" method="post" encType="multipart/form-data" className="form-horizontal">
                                    <CFormGroup row>
                                        <CCol md="3">
                                            <CLabel htmlFor="disabled-input">Receta</CLabel>
                                        </CCol>
                                        <CCol xs="12" md="9">
                                            {
                                                this.state.treatment.prescriptions.map(prescription => (
                                                    <>
                                                        <CInput
                                                            placeholder={ prescription.description }
                                                            disabled />
                                                            <br/>
                                                    </>

                                                ))
                                            }
                                        </CCol>
                                    </CFormGroup>

                                    <CFormGroup row>
                                        <CCol md="3">
                                            <CLabel htmlFor="disabled-input">Ordenes </CLabel>
                                        </CCol>
                                        <CCol xs="12" md="9">
                                            {
                                                this.state.treatment.orders.map(order => (
                                                    <>
                                                        <CInput
                                                            placeholder={ order.type_order.name }
                                                            disabled />

                                                        <CBadge color="success" >
                                                            { order.priority_order }
                                                        </CBadge>

                                                        <CBadge color="info" >
                                                            { order.status_order }
                                                        </CBadge>
                                                        <br/>
                                                    </>

                                                ))
                                            }
                                        </CCol>
                                    </CFormGroup>
                                </CForm>
                            </CCardBody>
                        </CCard>
                    </CCol>

                </CRow>
            </>
        );
    }
}

export default ShowConsultation;