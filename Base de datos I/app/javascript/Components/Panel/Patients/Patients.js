import React, {Component} from 'react';
import axios from 'axios'
import {
    CCard,
    CCardBody,
    CCardHeader,
    CCol,
    CRow,
    CButton,
    CPagination, CModalHeader, CModalTitle, CForm, CModalBody, CFormGroup, CLabel, CInput, CModalFooter, CModal, CSelect
} from "@coreui/react";

import { passCsrfToken } from "../../../helpers/csrfToken";

class Patients extends Component {

    constructor(props) {
        super(props);
        this.state = {
            patients : [],
            patient: {
                id: 0,
                full_name: '',
                nro_register : '',
                phone : '',
                blood_type : '',
                address : '',
            },

            insertTriage: false,
            triage: {},

            modalType: '',
            modalStatus: false,
            modalFor: '',

            page: 0,
            pages: 0,
            perPages: 0
        }
    }

    async componentDidMount() {
        await this.getPatients(1);
        passCsrfToken(document, axios)
    }

    handleNewPatient = async(e) =>{
        e.preventDefault();
        let formData = new FormData();
        formData.append('patient[full_name]', this.state.patient.full_name);
        formData.append('patient[nro_register]', this.state.patient.nro_register);
        formData.append('patient[phone]', this.state.patient.phone);
        formData.append('patient[blood_type]', this.state.patient.blood_type);
        formData.append('patient[address]', this.state.patient.address);

        formData.append('patient[triages_attributes]['+ 0 +'][weight]', this.state.triage.weight);
        formData.append('patient[triages_attributes]['+ 0 +'][height]', this.state.triage.height );
        formData.append('patient[triages_attributes]['+ 0 +'][blood_pressure]', this.state.triage.blood_pressure );
        formData.append('patient[triages_attributes]['+ 0 +'][priority]', this.state.triage.priority );


        await axios.post('/panel/patients', formData)
            .then(() => {
                this.getPatients(1)
                this.showModal(false);
            }).catch(error => {
                console.log(error);
            })


    }

    handleDeletePatient= async (patient) =>{
        await  axios.delete('/panel/patients/'+patient.id.toString(), {})
            .then(() => {
                this.getPatients(1)
            })
    }

    handleUpdatePatient = async () => {
        const patient = this.state.patient
        await axios.put('/panel/patients/'+ String(patient.id), patient)
            .then(() => {
                this.showModal(false);
                this.getPatients(1);
            })
    }

    setPatient = (patient) => {
        this.setState({
            modalType: 'update',
            patient :{
                id: patient.id,
                full_name: patient.full_name,
                nro_register : patient.nro_register,
                phone : patient.phone,
                blood_type : patient.blood_type,
                address : patient.address
            }
        })
    }

    handleChangePatient = async event => {
        event.persist()
        await this.setState({
            patient: {
                ...this.state.patient,
                [event.target.name] : event.target.value
            }
        })
    }

    handleChangeTriage = async event => {
        event.persist()
        await this.setState({
            triage: {
                ...this.state.triage,
                [event.target.name] : event.target.value
            }
        })
    }

    handleNewTriage = async() => {
        const newTriage = {
            patient_id: this.state.patient.id,
            weight: this.state.triage.weight,
            height: this.state.triage.height,
            blood_pressure: this.state.triage.blood_pressure,
            priority: this.state.triage.priority,
        }
        await axios.post('/panel/triages', newTriage)
            .then(() => {
                this.getPatients(1)
                this.showModal(false);
            }).catch(error => {
                console.log(error);
            })
    }


    getPatients = async(page) =>{
        let urlFull = '/panel/patients.json?'+ 'page=' + page.toString();
        await axios.get(urlFull, {}).then(
            (response)=> {
                this.setState({
                    patients: response.data.patients,
                    page: response.data.current_page,
                    pages: response.data.total_pages,
                    perPages: response.data.per_pages,
                })
            }
        ).catch(
            (error)=>{
                console.log(error)
            }
        )
    }

    showModal = (show) => {
        this.setState({
            modalStatus: show
        })
    }

    handlePage = async (page) =>{
        await this.getPatients(page)
    }

    render() {
        const { patient, patients } = this.state
        const { modalType, modalStatus, modalFor } = this.state
        const { insertTriage } = this.state
        return(
            <div>
                <CRow>
                    <CCol lg={12}>
                        <CCard>
                            <CCardHeader>
                                Panel de Pacientes
                            </CCardHeader>
                            <CCardBody>
                                <CButton
                                    color="success"
                                    size="sm"
                                    onClick ={ ()=>{this.setState({ patient: null, modalType: 'new', modalFor: 'patient'}); this.showModal(true) }}
                                    className="mb-3 float-right"
                                >
                                    Registrar Nuevo Paciente
                                </CButton>
                                <table className="table table-striped table-hover">
                                    <thead>
                                    <tr>
                                        <th> # </th>
                                        <th> Nombre </th>
                                        <th> Codigo de Registro </th>
                                        <th> Tipo de Sangre </th>
                                        <th> Telefono </th>
                                        <th> Direccion </th>
                                        <th> Fecha de Registro </th>
                                        <th> Acciones </th>
                                    </tr>
                                    </thead>
                                    <tbody>
                                    {
                                        patients.length > 0 ?
                                            patients.map((patient, index) => (
                                                <tr key={ patient.id }>
                                                    <td> { (index + 1) + (this.state.page - 1) * this.state.perPages } </td>
                                                    <td> { patient.full_name } </td>
                                                    <td> { patient.nro_register } </td>
                                                    <td> { patient.blood_type } </td>
                                                    <td> { patient.phone } </td>
                                                    <td> { patient.address } </td>
                                                    <td> { patient.created_at } </td>
                                                    <td>
                                                        <CButton
                                                            color="warning"
                                                            size="sm"
                                                            className="mr-2"
                                                            onClick ={ ()=> {
                                                                this.setPatient(patient)
                                                                this.setState({ modalFor: 'patient' })
                                                                this.showModal(true);
                                                            }
                                                            }
                                                        >
                                                            Editar
                                                        </CButton>
                                                        <CButton
                                                            color="danger"
                                                            size="sm"
                                                            className="mr-2"
                                                            onClick ={ ()=> this.handleDeletePatient(patient) }
                                                        >
                                                            Eliminar
                                                        </CButton>
                                                        <CButton
                                                            color="info"
                                                            size="sm"
                                                            onClick ={ ()=> {
                                                                this.setPatient(patient)
                                                                this.setState({ modalFor: 'triage' })
                                                                this.showModal(true);
                                                            }
                                                            }
                                                        >
                                                            Ingresar a Triaje
                                                        </CButton>
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
                                    activePage={this.state.page}
                                    pages={this.state.pages}
                                    onActivePageChange={(page) => this.handlePage(page)}
                                />

                                <CModal show={ modalStatus } onClose={ ()=> this.showModal(false) } >
                                    {
                                        modalFor === 'patient' ?
                                            <div>
                                                <CModalHeader closeButton>
                                                    <CModalTitle>
                                                        Registrar nuevo Paciente
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
                                                                    name="full_name"
                                                                    type="text"
                                                                    onChange={this.handleChangePatient}
                                                                    value={ patient ? patient.full_name : '' }
                                                                />
                                                            </CCol>
                                                        </CFormGroup>
                                                        <CFormGroup row>
                                                            <CCol md="5">
                                                                <CLabel htmlFor="hf-email">Numero de Registro</CLabel>
                                                            </CCol>
                                                            <CCol xs="12" md="7">
                                                                <CInput
                                                                    name="nro_register"
                                                                    type="text"
                                                                    onChange={this.handleChangePatient}
                                                                    value={ patient ? patient.nro_register : '' }
                                                                />
                                                            </CCol>
                                                        </CFormGroup>
                                                        <CFormGroup row>
                                                            <CCol md="5">
                                                                <CLabel htmlFor="hf-email">Tipo de Sangre</CLabel>
                                                            </CCol>
                                                            <CCol xs="12" md="7">
                                                                <CInput
                                                                    name="blood_type"
                                                                    type="text"
                                                                    onChange={this.handleChangePatient}
                                                                    value={ patient ? patient.blood_type : '' }
                                                                />
                                                            </CCol>
                                                        </CFormGroup>
                                                        <CFormGroup row>
                                                            <CCol md="5">
                                                                <CLabel htmlFor="hf-email">Telefono / Celular</CLabel>
                                                            </CCol>
                                                            <CCol xs="12" md="7">
                                                                <CInput
                                                                    name="phone"
                                                                    type="text"
                                                                    onChange={this.handleChangePatient}
                                                                    value={ patient ? patient.phone : '' }
                                                                />
                                                            </CCol>
                                                        </CFormGroup>
                                                        <CFormGroup row>
                                                            <CCol md="5">
                                                                <CLabel htmlFor="hf-email">Direccion</CLabel>
                                                            </CCol>
                                                            <CCol xs="12" md="7">
                                                                <CInput
                                                                    name="address"
                                                                    type="text"
                                                                    onChange={this.handleChangePatient}
                                                                    value={ patient ? patient.address : '' }
                                                                />
                                                            </CCol>
                                                        </CFormGroup>

                                                        <CFormGroup row>
                                                            <CCol md="5">
                                                            </CCol>
                                                            <CCol xs="12" md="7">
                                                                {
                                                                    modalType === 'new' ?
                                                                        insertTriage === false ?
                                                                            <CButton
                                                                                color="info"
                                                                                onClick={ ()=> { this.setState({ insertTriage: true }) } }
                                                                            >
                                                                                Registrar Triaje
                                                                            </CButton>
                                                                            : <CButton
                                                                                color="danger"
                                                                                onClick={ ()=> { this.setState({ insertTriage: false }) } }
                                                                            >
                                                                                Cancelar
                                                                            </CButton>
                                                                        :
                                                                        <div>

                                                                        </div>
                                                                }
                                                            </CCol>
                                                        </CFormGroup>

                                                        {
                                                            insertTriage === true ?
                                                                <div>
                                                                    <CFormGroup row>
                                                                        <CCol md="5">
                                                                            <CLabel htmlFor="weight">Peso</CLabel>
                                                                        </CCol>
                                                                        <CCol xs="12" md="7">
                                                                            <CInput
                                                                                name="weight"
                                                                                type="text"
                                                                                onChange={this.handleChangeTriage}
                                                                            />
                                                                        </CCol>
                                                                    </CFormGroup>
                                                                    <CFormGroup row>
                                                                        <CCol md="5">
                                                                            <CLabel htmlFor="weight">Altura</CLabel>
                                                                        </CCol>
                                                                        <CCol xs="12" md="7">
                                                                            <CInput
                                                                                name="height"
                                                                                type="text"
                                                                                onChange={this.handleChangeTriage}
                                                                            />
                                                                        </CCol>
                                                                    </CFormGroup>
                                                                    <CFormGroup row>
                                                                        <CCol md="5">
                                                                            <CLabel htmlFor="blood_pressure">Presion Sanguinea</CLabel>
                                                                        </CCol>
                                                                        <CCol xs="12" md="7">
                                                                            <CInput
                                                                                name="blood_pressure"
                                                                                type="text"
                                                                                onChange={this.handleChangeTriage}
                                                                            />
                                                                        </CCol>
                                                                    </CFormGroup>
                                                                    <CFormGroup row>
                                                                        <CCol md="5">
                                                                            <CLabel htmlFor="priority">Prioridad de Atencion</CLabel>
                                                                        </CCol>
                                                                        <CCol xs="12" md="7">
                                                                            <CSelect custom name="priority" id="priority" onChange={this.handleChangeTriage} >
                                                                                <option value="alta">Alta</option>
                                                                                <option value="media">Media</option>
                                                                                <option value="leve">Leve</option>
                                                                            </CSelect>
                                                                        </CCol>
                                                                    </CFormGroup>
                                                                </div> :
                                                                <div>

                                                                </div>
                                                        }

                                                    </CModalBody>
                                                    <CModalFooter>
                                                        <CButton color="danger" onClick={ ()=> this.showModal(false) } >
                                                            Cancelar
                                                        </CButton>
                                                        { modalType === 'new'?
                                                            <CButton color="success" onClick={ this.handleNewPatient }>
                                                                Registrar
                                                            </CButton>
                                                            :
                                                            <CButton color="success" onClick={ ()=>this.handleUpdatePatient() }>
                                                                Actualizar
                                                            </CButton>
                                                        }
                                                    </CModalFooter>
                                                </CForm>
                                            </div>
                                            :
                                            <div>
                                                <CModalHeader closeButton>
                                                    <CModalTitle>
                                                        Ingresar a Triaje
                                                    </CModalTitle>
                                                </CModalHeader>
                                                <CForm className="form-horizontal">
                                                    <CModalBody>
                                                        <CFormGroup row>
                                                            <CCol md="5">
                                                                <CLabel htmlFor="name">Paciente</CLabel>
                                                            </CCol>
                                                            <CCol xs="12" md="7">
                                                                <CInput
                                                                    name="full_name"
                                                                    type="text"
                                                                    disabled
                                                                    value={ patient.full_name }
                                                                />
                                                            </CCol>
                                                        </CFormGroup>
                                                        <CFormGroup row>
                                                            <CCol md="5">
                                                                <CLabel htmlFor="weight">Peso</CLabel>
                                                            </CCol>
                                                            <CCol xs="12" md="7">
                                                                <CInput
                                                                    name="weight"
                                                                    type="text"
                                                                    onChange={this.handleChangeTriage}
                                                                />
                                                            </CCol>
                                                        </CFormGroup>
                                                        <CFormGroup row>
                                                            <CCol md="5">
                                                                <CLabel htmlFor="weight">Altura</CLabel>
                                                            </CCol>
                                                            <CCol xs="12" md="7">
                                                                <CInput
                                                                    name="height"
                                                                    type="text"
                                                                    onChange={this.handleChangeTriage}
                                                                />
                                                            </CCol>
                                                        </CFormGroup>
                                                        <CFormGroup row>
                                                            <CCol md="5">
                                                                <CLabel htmlFor="blood_pressure">Presion Sanguinea</CLabel>
                                                            </CCol>
                                                            <CCol xs="12" md="7">
                                                                <CInput
                                                                    name="blood_pressure"
                                                                    type="text"
                                                                    onChange={this.handleChangeTriage}
                                                                />
                                                            </CCol>
                                                        </CFormGroup>
                                                        <CFormGroup row>
                                                            <CCol md="5">
                                                                <CLabel htmlFor="blood_pressure">Prioridad</CLabel>
                                                            </CCol>
                                                            <CCol xs="12" md="7">
                                                                <CSelect custom name="priority" id="priority" onChange={this.handleChangeTriage} >
                                                                    <option value="alta">Alta</option>
                                                                    <option value="media">Media</option>
                                                                    <option value="leve">Leve</option>
                                                                </CSelect>
                                                            </CCol>



                                                        </CFormGroup>
                                                    </CModalBody>
                                                    <CModalFooter>
                                                        <CButton color="danger" onClick={ ()=> this.showModal(false) } >
                                                            Cancelar
                                                        </CButton>
                                                        <CButton
                                                            color="success"
                                                            onClick ={ this.handleNewTriage }
                                                        >
                                                            Registrar Triaje
                                                        </CButton>

                                                    </CModalFooter>
                                                </CForm>
                                            </div>
                                    }

                                </CModal>

                            </CCardBody>
                        </CCard>
                    </CCol>
                </CRow>
            </div>
        )
    }
}

export default Patients;