import React, {Component} from 'react'
import axios from "axios";
import { passCsrfToken } from "../../../helpers/csrfToken";

import {
    CButton,
    CCard,
    CCardBody,
    CCardFooter,
    CCardHeader,
    CCol,
    CForm,
    CFormGroup,
    CTextarea,
    CInput,
    CInputGroup,
    CInputGroupAppend,
    CLabel,
    CSelect,
    CRow
} from '@coreui/react'
import CIcon from '@coreui/icons-react'


class AttendPatient extends Component {
    constructor(props) {
        super(props);
        this.state = {
            diagnostic: '',

            triage: {
                patient: {},
                consultation: {}
            },
            prescriptions: [
                { description: '' }
            ],

            orders: [
                {
                    type_order_id: 0,
                    priority_order: '',
                }
            ],
            typeOrders: [],


        }
    }

    async componentDidMount() {
        await this.getTriage()
        await this.getTypeOrders()
        passCsrfToken( document, axios )
    }

    getTypeOrders = async () => {
        axios.get('/panel/type_orders.json', {}).then(
            (response) => {
                this.setState({
                    typeOrders: response.data.type_orders
                })
            }
        ).catch(
            (error)=>{
                console.log(error)
            }
        )
    }


    getTriage = async () => {
        await axios.get('/panel/triages/' + String(this.props.match.params.id), {}).then(
            (response) => {
                this.setState({
                    triage: response.data
                })
            }
        )
    }

    handleNewTreatment = async (e) => {
        e.preventDefault();

        let formData = new FormData();
        formData.append('treatment[diagnostic]', this.state.diagnostic)
        formData.append('treatment[consultation_id]', this.state.triage.consultation.id)

        this.state.prescriptions.map((prescription, index) => {
            formData.append('treatment[prescriptions_attributes]['+ index +'][description]', prescription.description )
        })

        this.state.orders.map((order, index) => {
            formData.append('treatment[orders_attributes]['+ index +'][type_order_id]', order.type_order_id )
            formData.append('treatment[orders_attributes]['+ index +'][priority_order]', order.priority_order )
        })

        await axios.post('/panel/treatments', formData)
            .then(() => {
                this.props.history.push('/consultas')
            }).catch(error => {
                console.log(error);
            })
    }


    handleAddPrescription = () => {
        this.setState({
            prescriptions: [...this.state.prescriptions, { description: '' }]
        })
    }

    handleRemovePrescription = (index) => {
        const list = [ ...this.state.prescriptions ];
        list.splice(index, 1);

        this.setState({
            prescriptions: list
        })
    }

    handleChangePrescription = (e, index) => {
        const { name, value } = e.target;
        const list = [ ...this.state.prescriptions ];
        this.state.prescriptions[index][name] = value;

        this.setState({
            prescription: list
        })
    }

    handleAddOrder = () => {
        this.setState({
            orders: [
                ...this.state.orders,
                {
                    type_order_id: 0,
                    status: '',
                }
            ]
        })
    }

    handleRemoveOrder = (index) => {
        const listOrder = [ ...this.state.orders ];
        listOrder.splice(index, 1);

        this.setState({
            orders: listOrder
        })
    }

    handleChangeOrder = (e, index) => {
        const { name, value } = e.target;
        const listOrder = [ ...this.state.orders ];
        this.state.orders[index][name] = value;

        this.setState({
            orders: listOrder
        })
    }

    render() {
        const { prescriptions, orders } = this.state
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
                                            <CLabel htmlFor="disabled-input">Codigo de Paciente</CLabel>
                                        </CCol>
                                        <CCol xs="12" md="9">
                                            <CInput
                                                placeholder={ this.state.triage.patient.nro_register }
                                                disabled />
                                        </CCol>
                                    </CFormGroup>
                                    <CFormGroup row>
                                        <CCol md="3">
                                            <CLabel htmlFor="disabled-input">Telefono del Paciente</CLabel>
                                        </CCol>
                                        <CCol xs="12" md="9">
                                            <CInput
                                                placeholder={ this.state.triage.patient.phone }
                                                disabled />
                                        </CCol>
                                    </CFormGroup>
                                    <CFormGroup row>
                                        <CCol md="3">
                                            <CLabel htmlFor="disabled-input">Direccion del Paciente</CLabel>
                                        </CCol>
                                        <CCol xs="12" md="9">
                                            <CInput
                                                placeholder={ this.state.triage.patient.address }
                                                disabled />
                                        </CCol>
                                    </CFormGroup>
                                    <CFormGroup row>
                                        <CCol md="3">
                                            <CLabel htmlFor="disabled-input">Tipo de Sangre</CLabel>
                                        </CCol>
                                        <CCol xs="12" md="9">
                                            <CInput
                                                placeholder={ this.state.triage.patient.blood_type }
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
                                </CForm>
                            </CCardBody>
                        </CCard>
                    </CCol>

                    <CCol xs="12" md="6">
                        <CCard>
                            <CCardHeader>
                                Diagnostico
                                <small> Tratamiento</small>
                            </CCardHeader>
                            <CCardBody>
                                <CForm className="form-horizontal">
                                    <CFormGroup row>
                                        <CLabel sm="2" col="sm" htmlFor="input-small">Diagnostico</CLabel>
                                        <CCol sm="10">
                                            <CTextarea
                                                size="sm"
                                                rows="9"
                                                id="input-small"
                                                onChange = { (event)=>this.setState({ diagnostic: event.target.value }) }
                                                name="input-small" className="input-sm" placeholder="El paciente padece de . . ."
                                            >
                                            </CTextarea>
                                        </CCol>
                                    </CFormGroup>
                                </CForm>

                                {prescriptions.map((prescription, i) => {
                                    return(
                                        <CForm className="form-horizontal" key={i}>
                                            <CFormGroup row>
                                                <CLabel sm="2" col="sm" >Receta</CLabel>
                                                <CCol sm="10">
                                                    <CInputGroup>
                                                        <CInput
                                                            type="text"
                                                            name="description"
                                                            placeholder="Describir receta"
                                                            onChange={ e => this.handleChangePrescription(e, i) }
                                                        />

                                                        { ( prescriptions.length - 1 > 0) &&
                                                        <CInputGroupAppend>
                                                            <CButton
                                                                type="button"
                                                                color="danger"
                                                                onClick={ ()=>this.handleRemovePrescription(i) }
                                                            >Quitar</CButton>
                                                        </CInputGroupAppend>
                                                        }

                                                        { prescriptions.length - 1 === i &&

                                                        <CButton
                                                            type="button"
                                                            color="warning"
                                                            onClick={ (event)=>this.handleAddPrescription(event) }
                                                        >
                                                            Agregar
                                                        </CButton>
                                                        }
                                                    </CInputGroup>
                                                </CCol>
                                            </CFormGroup>
                                        </CForm>
                                    )
                                })}

                                { orders.map((order, i) => {
                                    return(
                                        <CForm className="form-horizontal" key={i}>
                                            <CFormGroup row>
                                                <CLabel sm="2" col="sm" >Orden</CLabel>
                                                <CCol sm="10">
                                                    <CInputGroup>
                                                        <CSelect custom
                                                                 name="priority_order"
                                                                 id="priority_order"
                                                                 onChange={ e => this.handleChangeOrder(e, i) }
                                                        >
                                                            <option value="urgente">Alta</option>
                                                            <option value="medio">Media</option>
                                                            <option value="opcional">Leve</option>
                                                        </CSelect>

                                                        <CSelect custom
                                                                 name="type_order_id"
                                                                 id="priority_order"
                                                                 onChange={ e => this.handleChangeOrder(e, i) }
                                                        >
                                                            {
                                                                this.state.typeOrders.map(type_order => (
                                                                    <option value={type_order.id} key={type_order.id}>{type_order.name}</option>
                                                                ))
                                                            }
                                                        </CSelect>

                                                        { ( orders.length - 1 > 0) &&
                                                        <CInputGroupAppend>
                                                            <CButton
                                                                type="button"
                                                                color="danger"
                                                                onClick={ ()=>this.handleRemoveOrder(i) }
                                                            >Quitar</CButton>
                                                        </CInputGroupAppend>
                                                        }

                                                        { orders.length - 1 === i &&

                                                        <CButton
                                                            type="button"
                                                            color="warning"
                                                            onClick={ (event)=>this.handleAddOrder(event) }
                                                        >
                                                            Agregar
                                                        </CButton>
                                                        }
                                                    </CInputGroup>
                                                </CCol>
                                            </CFormGroup>
                                        </CForm>
                                    )
                                })}


                            </CCardBody>
                            <CCardFooter>
                                <CButton
                                    size="sm"
                                    color="primary"
                                    onClick={ this.handleNewTreatment }
                                >
                                    <CIcon name="cil-scrubber" /> Terminar Consulta
                                </CButton>
                            </CCardFooter>
                        </CCard>
                    </CCol>
                </CRow>
            </>
        );
    }
}

export default AttendPatient