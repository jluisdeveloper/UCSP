import React, {Component} from 'react'
import axios from 'axios'
import { passCsrfToken } from "../../../helpers/csrfToken"

import {
    CCard,
    CCardBody,
    CCardHeader,
    CCol,
    CRow,
    CButton,
    CPagination, CModalHeader, CModalTitle, CForm, CModalBody, CFormGroup, CLabel, CInput, CModalFooter, CModal
} from "@coreui/react"

class Users extends Component {
    constructor(props) {
        super(props);
        this.state = {
            users : [],
            user: {},

            professions: [],
            specialities: [],

            modalType: '',
            modalStatus: false,

            page: 0,
            pages: 0,
            perPages: 0
        }
    }

    async componentDidMount() {
        await this.getUsers(1)
        await this.getProfessions()
        await this.getSpecialities()
        passCsrfToken(document, axios)
    }

    getProfessions = async () => {
        await axios.get('/professions', {}).then(
            (response) => {
                this.setState({
                    professions : response.data.professions
                })
            }
        ).catch(
            (error) => {
                console.log(error)
            }
        )
    }

    getSpecialities = async () => {
        await axios.get('/specialities', {}).then(
            (response) => {
                this.setState({
                    specialities : response.data.specialities
                })
            }
        ).catch(
            (error) => {
                console.log(error)
            }
        )
    }

    getUsers = async (page) => {
        await axios.get('/panel/users.json' + 'page=' + String(page), {}).then(
            (response)=> {
                this.setState({
                    users: response.data.users,
                    page: response.data.current_page,
                    pages: response.data.total_pages,
                    perPages: response.data.per_pages
                })
            }
        ).catch(
            (error)=> {
                console.log(error)
            }
        )
    }

    showModal = (show) => {
        this.setState({
            modalStatus: show
        })
    }

    setUser = (user) => {
        this.setState({
            modalType: 'update',
            user :{
                id: user.id,
                full_name: user.full_name,
                code_job: user.code_job,
                salary: user.salary,
                payment_date: user.payment_date,
                hiring_date: user.hiring_date,
                profession_id: user.profession_id,
                speciality_id: user.speciality_id,
                phone : user.phone,
                address : user.address,
                email : user.email
            }
        })
    }

    handlePage = async (page) =>{
        await this.getUsers(page)
    }

    handleDelete = async (user) => {
        await  axios.delete('/panel/users/'+ String(user.id), {})
            .then(() => {
                this.getUsers(1)
            })
    }

    handleNew = async () => {
        await axios.post('/panel/users', this.state.user)
            .then(() => {
                this.getUsers(1)
                this.showModal(false);
            }).catch(error => {
                console.log(error);
            })
    }
    
    handleUpdate = async () => {

    }
    
    handleChange = async (event) => {
        event.persist()
        await this.setState({
            user: {
                ...this.state.user,
                [event.target.name] : event.target.value
            }
        })
    }

    render() {
        const { users, user } = this.state
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
                                <CButton
                                    color="success"
                                    size="sm"
                                    onClick ={ ()=>{this.setState({ user: null, modalType: 'new'}); this.showModal(true) }}
                                    className="mb-3 float-right"
                                >
                                    Registrar Nuevo Usuario
                                </CButton>
                                <table className="table table-striped table-hover">
                                    <thead>
                                    <tr>
                                        <th> # </th>
                                        <th> Nombre </th>
                                        <th> Codigo de Trabajo </th>
                                        <th> Oficio </th>
                                        <th> Especialidad </th>
                                        <th> Telefono </th>
                                        <th> Direccion </th>
                                        <th> Acciones </th>
                                    </tr>
                                    </thead>
                                    <tbody>
                                    {
                                        users.length > 0 ?
                                            users.map((user, index) => (
                                                <tr key={ user.id }>
                                                    <td> { (index + 1) + (page - 1) * perPages } </td>
                                                    <td> { user.full_name } </td>
                                                    <td> { user.code_job } </td>
                                                    <td> { professions.find(profession => profession.id === user.profession_id) ? professions.find(profession => profession.id === user.profession_id).name : '' } </td>
                                                    <td> { specialities.find(speciality => speciality.id === user.speciality_id) ? specialities.find(speciality => speciality.id === user.speciality_id).name : '' } </td>
                                                    <td> { user.phone } </td>
                                                    <td> { user.address } </td>
                                                    <td>
                                                        <CButton
                                                            color="warning"
                                                            size="sm"
                                                            className="mr-2"
                                                            onClick ={ ()=> {
                                                                this.setUser(user)
                                                                this.showModal(true);
                                                                }
                                                            }
                                                        >
                                                            Actualizar
                                                        </CButton>
                                                        <CButton
                                                            color="danger"
                                                            size="sm"
                                                            className="mr-2"
                                                            onClick ={ ()=> this.handleDelete(user) }
                                                        >
                                                            Eliminar
                                                        </CButton>
                                                        <CButton
                                                            color="info"
                                                            size="sm"
                                                            onClick ={ ()=> {
                                                                this.setUser(user)
                                                                this.showModal(true);
                                                            }
                                                            }
                                                        >
                                                            Ver Perfil Completo
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
                                    activePage={ page }
                                    pages={ pages }
                                    onActivePageChange={(page) => this.handlePage(page)}
                                />

                                <CModal show={ modalStatus } onClose={ ()=> this.showModal(false) } >
                                    {
                                        <div>
                                            <CModalHeader closeButton>
                                                <CModalTitle>
                                                    Registro de Personal
                                                </CModalTitle>
                                            </CModalHeader>
                                            <CForm action="" method="post" className="form-horizontal">
                                                <CModalBody>
                                                    <CFormGroup row>
                                                        <CCol md="5">
                                                            <CLabel htmlFor="hf-email">Nombre de Usuario</CLabel>
                                                        </CCol>
                                                        <CCol xs="12" md="7">
                                                            <CInput
                                                                name="full_name"
                                                                type="text"
                                                                onChange={ this.handleChange }
                                                                value={ user ? user.full_name : '' }
                                                            />
                                                        </CCol>
                                                    </CFormGroup>

                                                    <CFormGroup row>
                                                        <CCol md="5">
                                                            <CLabel htmlFor="hf-email">Cargo</CLabel>
                                                        </CCol>
                                                        <CCol xs="12" md="7">
                                                            <select
                                                                value={user ? user.profession_id : 1}
                                                                name="profession_id"
                                                                onChange={ this.handleChange }
                                                            >
                                                                {professions.map((profession) => (
                                                                    <option key={profession.id} value={profession.id}>{profession.name}</option>
                                                                ))}
                                                            </select>
                                                        </CCol>
                                                    </CFormGroup>

                                                    <CFormGroup row>
                                                        <CCol md="5">
                                                            <CLabel htmlFor="hf-email">Especialidad</CLabel>
                                                        </CCol>
                                                        <CCol xs="12" md="7">
                                                            <select
                                                                value={user ? user.speciality_id : 1}
                                                                name="speciality_id"
                                                                onChange={ this.handleChange }
                                                            >
                                                                {specialities.map((speciality) => (
                                                                    <option key={speciality.id}
                                                                            value={speciality.id}
                                                                    >
                                                                        {speciality.name}
                                                                    </option>
                                                                ))}
                                                            </select>
                                                        </CCol>
                                                    </CFormGroup>

                                                    <CFormGroup row>
                                                        <CCol md="5">
                                                            <CLabel htmlFor="hf-email">Password</CLabel>
                                                        </CCol>
                                                        <CCol xs="12" md="7">
                                                            <CInput
                                                                name="password"
                                                                type="password"
                                                                onChange={ this.handleChange }
                                                            />
                                                        </CCol>
                                                    </CFormGroup>

                                                    <CFormGroup row>
                                                        <CCol md="5">
                                                            <CLabel htmlFor="hf-email">Confirmar Password</CLabel>
                                                        </CCol>
                                                        <CCol xs="12" md="7">
                                                            <CInput
                                                                name="password_confirmation"
                                                                type="password"
                                                                onChange={ this.handleChange }
                                                            />
                                                        </CCol>
                                                    </CFormGroup>

                                                    <CFormGroup row>
                                                        <CCol md="5">
                                                            <CLabel htmlFor="hf-email">Codigo Laboral</CLabel>
                                                        </CCol>
                                                        <CCol xs="12" md="7">
                                                            <CInput
                                                                name="code_job"
                                                                type="text"
                                                                onChange={ this.handleChange }
                                                                value={ user ? user.code_job : '' }
                                                            />
                                                        </CCol>
                                                    </CFormGroup>
                                                    <CFormGroup row>
                                                        <CCol md="5">
                                                            <CLabel htmlFor="hf-email">Salario</CLabel>
                                                        </CCol>
                                                        <CCol xs="12" md="7">
                                                            <CInput
                                                                name="salary"
                                                                type="text"
                                                                onChange={ this.handleChange }
                                                                value={ user ? user.salary : '' }
                                                            />
                                                        </CCol>
                                                    </CFormGroup>
                                                    <CFormGroup row>
                                                        <CCol md="5">
                                                            <CLabel htmlFor="hf-email">Fecha de Contrato</CLabel>
                                                        </CCol>
                                                        <CCol xs="12" md="7">
                                                            <CInput
                                                                name="hiring_date"
                                                                type="date"
                                                                onChange={ this.handleChange }
                                                                // value={ user ? user.hiring_date : '' }
                                                                // defaultValue={ user ? user.hiring_date.slice(1,10) : '' }
                                                            />
                                                        </CCol>
                                                    </CFormGroup>

                                                    <CFormGroup row>
                                                        <CCol md="5">
                                                            <CLabel htmlFor="hf-email">Fecha de Pago</CLabel>
                                                        </CCol>
                                                        <CCol xs="12" md="7">
                                                            <CInput
                                                                name="payment_date"
                                                                type="date"
                                                                onChange={ this.handleChange }
                                                                value={ user ? user.payment_date : '' }
                                                            />
                                                        </CCol>
                                                    </CFormGroup>

                                                    <CFormGroup row>
                                                        <CCol md="5">
                                                            <CLabel htmlFor="hf-email">Email</CLabel>
                                                        </CCol>
                                                        <CCol xs="12" md="7">
                                                            <CInput
                                                                name="email"
                                                                type="text"
                                                                onChange={ this.handleChange }
                                                                value={ user ? user.email : '' }
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
                                                                onChange={ this.handleChange }
                                                                value={ user ? user.phone : '' }
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
                                                                onChange={ this.handleChange }
                                                                value={ user ? user.address : '' }
                                                            />
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
                                                        <CButton color="success" onClick={ ()=>this.handleUpdate }>
                                                            Actualizar
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

export default Users