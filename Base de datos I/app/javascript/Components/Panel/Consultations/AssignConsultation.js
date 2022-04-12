import React, {Component} from 'react'
import axios from "axios"
import { passCsrfToken } from "../../../helpers/csrfToken"

import {
    CBadge,
    CCard,
    CCardBody,
    CCardHeader,
    CCol,
    CRow,
    CButton,
    CPagination, CModalHeader, CModalTitle, CForm, CModalBody, CFormGroup, CLabel, CInput, CModalFooter, CModal, CSelect
} from "@coreui/react"

class AssignConsultation extends Component {
    constructor(props) {
        super(props);
        this.state = {
            triages: [],
            triage: {},
            patients: [],
            specialities: [],

            // Doctores (Usuarios)
            users: [],
            user_id: 0,
            hour:'',

            modalType: '',
            modalStatus: false,

            page: 0,
            pages: 0,
            perPages: 0
        }
    }

    async componentDidMount() {
        await this.getTriages(1)
        passCsrfToken(document, axios)
    }

    assignConsultation = async () => {
        const formData = {
            user_id: this.state.user_id,
            triage_id: this.state.triage.id,
            hour: 'test de hora'
        }

        await axios.post('/panel/consultations', formData)
            .then(() => {
                this.getTriages(1)
                this.showModal(false);
            }).catch(error => {
                console.log(error);
            })
    }

    getColorBadge = (status) => {
        switch (status) {
            case 'alta': return 'danger'
            case 'media': return 'warning'
            case 'leve': return 'secondary'
            default: return 'primary'
        }
    }

    getTriages = async (page) => {
        await axios.get('/panel/triages.json' + 'page=' + String(page), {}).then(
            (response) => {
                this.setState({
                    triages: response.data.triages,
                    patients: response.data.patients,
                    users: response.data.users,
                    specialities: response.data.specialities
                })
            }
        ).catch(
            (error) => {
                console.log(error)
            }
        )
    }

    getSpecialityName = (id_speciality) => {
        if (this.state.specialities.length > 0)
            return this.state.specialities.find(speciality => speciality.id === id_speciality).name
    }

    setTriage = (triage) => {
        this.setState({
            modalType: 'update',
            triage :{
                id: triage.id,
                patient_id: triage.patient_id,
                weight: triage.weight,
                height: triage.height,
                blood_pressure: triage.blood_pressure,
            }
        })
    }

    showModal = (show) => {
        this.setState({
            modalStatus: show
        })
    }

    handleChangeUser = async (event) => {
        event.persist()
        await this.setState({
            ...this.state.user_id,
            user_id: event.target.value
        })
    }

    render() {
        const { patients, patient } = this.state
        const { triages, triage } = this.state
        const { users } = this.state
        const { page, pages, perPages } = this.state
        const { modalType, modalStatus } = this.state
        const { professions, specialities } = this.state

        return (
            <>
                <CRow>
                    <CCol lg={12}>
                        <CCard>
                            <CCardHeader>
                                Panel de Pacientes
                            </CCardHeader>
                            <CCardBody>
                                <table className="table table-striped table-hover">
                                    <thead>
                                    <tr>
                                        <th> # </th>
                                        <th> Nombre de Paciente </th>
                                        <th> Codigo de Paciente </th>
                                        <th> Prioridad </th>
                                        <th> Acciones </th>
                                    </tr>
                                    </thead>
                                    <tbody>
                                    {
                                        triages.length > 0 ?
                                            triages.map((triage, index) => (
                                                <tr key={ triage.id }>
                                                    <td> { (index + 1) + (page - 1) * perPages } </td>
                                                    <td>
                                                        { patients.find(patient => patient.id === triage.patient_id) ? patients.find(patient => patient.id === triage.patient_id).full_name : '' }
                                                    </td>
                                                    <td>
                                                        { patients.find(patient => patient.id === triage.patient_id) ? patients.find(patient => patient.id === triage.patient_id).nro_register : '' }
                                                    </td>
                                                    <td>
                                                        <CBadge color={ this.getColorBadge(triage.priority) }>
                                                            { triage ? triage.priority.toUpperCase() : '' }
                                                        </CBadge>
                                                    </td>
                                                    <td>
                                                        <CButton
                                                            color="success"
                                                            size="sm"
                                                            className="mr-2"
                                                            onClick ={ ()=> {
                                                                this.setTriage(triage)
                                                                this.showModal(true);
                                                                }
                                                            }
                                                        >
                                                            Asignar Consulta
                                                        </CButton>
                                                        <CButton
                                                            color="danger"
                                                            size="sm"
                                                            className="mr-2"
                                                            // onClick ={ ()=> this.handleDelete(user) }
                                                        >
                                                            Eliminar
                                                        </CButton>
                                                        {/*<CButton*/}
                                                        {/*    color="info"*/}
                                                        {/*    size="sm"*/}
                                                        {/*    // onClick ={ ()=> {*/}
                                                        {/*    //     this.setUser(user)*/}
                                                        {/*    //     this.showModal(true);*/}
                                                        {/*    // }*/}
                                                        {/*    // }*/}
                                                        {/*>*/}
                                                        {/*    Ver Perfil Completo*/}
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

                                <CPagination
                                    align="end"
                                    activePage={ page }
                                    pages={ pages }
                                    onActivePageChange={(page) => this.handlePage(page)}
                                />

                                <CModal show={ modalStatus } onClose={ ()=> this.showModal(false) } >
                                    {
                                        <div>
                                            <CModalHeader closeButton>
                                                <CModalTitle>
                                                    Asignar Consulta
                                                </CModalTitle>
                                            </CModalHeader>
                                            <CForm action="" method="post" className="form-horizontal">
                                                <CModalBody>
                                                    <CFormGroup row>
                                                        <CCol md="5">
                                                            <CLabel htmlFor="hf-email">Nombre del Paciente</CLabel>
                                                        </CCol>
                                                        <CCol xs="12" md="7">
                                                            <CInput
                                                                type="text"
                                                                value={ triage ? triage.patient_id : '' }
                                                                disabled
                                                            />
                                                        </CCol>
                                                    </CFormGroup>
                                                    <CFormGroup row>
                                                        <CCol md="5">
                                                            <CLabel htmlFor="hf-email">Peso</CLabel>
                                                        </CCol>
                                                        <CCol xs="12" md="7">
                                                            <CInput
                                                                type="text"
                                                                value={ triage ? triage.weight : '' }
                                                                disabled
                                                            />
                                                        </CCol>
                                                    </CFormGroup>
                                                    <CFormGroup row>
                                                        <CCol md="5">
                                                            <CLabel htmlFor="hf-email">Estatura</CLabel>
                                                        </CCol>
                                                        <CCol xs="12" md="7">
                                                            <CInput
                                                                type="text"
                                                                value={ triage ? triage.height : '' }
                                                                disabled
                                                            />
                                                        </CCol>
                                                    </CFormGroup>
                                                    <CFormGroup row>
                                                        <CCol md="5">
                                                            <CLabel htmlFor="hf-email">Presion Sanguinea</CLabel>
                                                        </CCol>
                                                        <CCol xs="12" md="7">
                                                            <CInput
                                                                type="text"
                                                                value={ triage ? triage.blood_pressure : '' }
                                                                disabled
                                                            />
                                                        </CCol>
                                                    </CFormGroup>

                                                    <CFormGroup row>
                                                        <CCol md="5">
                                                            <CLabel htmlFor="hf-email">Doctor (Especialidad)</CLabel>
                                                        </CCol>
                                                        <CCol xs="12" md="7">
                                                            <CSelect custom name="user_id" id="user_id" onChange={this.handleChangeUser} >
                                                                {users.map((user) => (
                                                                    <option key={user.id} value={user.id}>{user.full_name } - { this.getSpecialityName(user.speciality_id) } </option>
                                                                ))}>
                                                            </CSelect>
                                                        </CCol>
                                                    </CFormGroup>
                                                </CModalBody>
                                                <CModalFooter>
                                                    <CButton color="danger" onClick={ ()=> this.showModal(false) } >
                                                        Cancelar
                                                    </CButton>
                                                    { modalType === 'new'?
                                                        <CButton color="success" onClick={ this.handleNew }>
                                                            Registrar
                                                        </CButton>
                                                        :
                                                        <CButton color="success" onClick={ ()=>this.assignConsultation() }>
                                                            Asignar Consulta
                                                        </CButton>
                                                    }
                                                </CModalFooter>
                                            </CForm>
                                        </div>
                                    }
                                </CModal>

                            </CCardBody>
                        </CCard>
                    </CCol>
                </CRow>
            </>
        );
    }
}

export default AssignConsultation