import React, {Component} from 'react'
import axios from "axios"
import { passCsrfToken } from "../../../helpers/csrfToken"

import ReactHTMLTableToExcel from "react-html-table-to-excel";

import {
    CButton,
    CCard,
    CCardBody,
    CCardGroup,
    CCardHeader,
    CCol,
    CForm,
    CFormGroup,
    CInput,
    CLabel,
    CModal,
    CModalBody, CModalFooter,
    CModalHeader,
    CModalTitle,
    CPagination,
    CRow, CSelect
} from '@coreui/react'

import {
    CChartBar,
} from '@coreui/react-chartjs'


class PatientsReports extends Component {
    constructor(props) {
        super(props)
        this.state = {
            patients: []
        }
    }

    async componentDidMount() {
        await this.getPatientsAll()
        passCsrfToken(document,axios)
    }

    getPatientsAll = async () => {
        axios.get('/panel/full_patients', {}).then(
            (response) => {
                this.setState({
                    patients: response.data.patients
                })
            }
        ).catch(
            (error) => {
                console.log(error)
            }
        )
    }


    render() {
        const { patients } = this.state

        return (
            <>
                <CRow>
                    <CCol lg={12}>
                        <CCard>
                            <CCardHeader>
                                Reporte de Pacientes
                            </CCardHeader>
                            <CCardBody>
                                <ReactHTMLTableToExcel
                                    className="mb-3 float-right btn btn-success btn-sm"
                                    table="reportePacientes"
                                    filename="reporteBD1"
                                    sheet="pagina 1"
                                    buttonText="Generar Reporte"
                                />

                                <table className="table table-striped table-hover" id="reportePacientes" >
                                    <thead>
                                    <tr>
                                        <th> # </th>
                                        <th> Nombre </th>
                                        <th> Codigo de Registro </th>
                                        <th> Tipo de Sangre </th>
                                        <th> Telefono </th>
                                        <th> Direccion </th>
                                        <th> Fecha de Registro </th>
                                    </tr>
                                    </thead>
                                    <tbody>
                                    {
                                        patients.length > 0 ?
                                            patients.map((patient, index) => (
                                                <tr key={ patient.id }>
                                                    <td> { (index + 1) } </td>
                                                    <td> { patient.full_name } </td>
                                                    <td> { patient.nro_register } </td>
                                                    <td> { patient.blood_type } </td>
                                                    <td> { patient.phone } </td>
                                                    <td> { patient.address } </td>
                                                    <td> { patient.created_at } </td>
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



                {/*<CCardGroup columns className = "cols-2" >*/}
                {/*    <CCard>*/}
                {/*        <CCardHeader>*/}
                {/*            Bar Chart*/}
                {/*            <div className="card-header-actions">*/}
                {/*                <a href="http://www.chartjs.org" className="card-header-action">*/}
                {/*                    <small className="text-muted">docs</small>*/}
                {/*                </a>*/}
                {/*            </div>*/}
                {/*        </CCardHeader>*/}
                {/*        <CCardBody>*/}
                {/*            <CChartBar*/}
                {/*                type="bar"*/}
                {/*                datasets={[*/}
                {/*                    {*/}
                {/*                        label: 'Pacientes Registrados',*/}
                {/*                        backgroundColor: '#f87979',*/}
                {/*                        data: [40, 20, 12, 39, 10, 40, 39, 80, 40, 20, 12, 11]*/}
                {/*                    }*/}
                {/*                ]}*/}
                {/*                labels="months"*/}
                {/*                options={{*/}
                {/*                    tooltips: {*/}
                {/*                        enabled: true*/}
                {/*                    }*/}
                {/*                }}*/}
                {/*            />*/}
                {/*        </CCardBody>*/}
                {/*    </CCard>*/}
                {/*</CCardGroup>*/}
            </>
        );
    }
}

export default PatientsReports