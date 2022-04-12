import React from 'react';

const Dashboard = React.lazy(() => import('./Components/Panel/Dashboard/Dashboard'));
const Users = React.lazy(() => import('./Components/Panel/Users/Users'));
const Patients = React.lazy(() => import('./Components/Panel/Patients/Patients'));
const ReportPatients = React.lazy(() => import('./Components/Panel/Reports/PatientsReports'));
const AssignConsultation = React.lazy(() => import('./Components/Panel/Consultations/AssignConsultation'));
const Consultations = React.lazy(() => import('./Components/Panel/Consultations/Consultations'));
const AttendPatient = React.lazy(() => import('./Components/Panel/Consultations/AttendPatient'));
const ShowConsultation = React.lazy(() => import('./Components/Panel/Consultations/ShowConsultation'));

const routes = [
  { path: '/', exact: true, name: 'Dashboard', component: Dashboard },
  { path: '/personal', exact: true, name: 'Usuarios', component: Users },
  { path: '/pacientes', exact: true, name: 'Paciente', component: Patients },
  { path: '/reports/patients', exact: true, name: 'Reporte de Pacientes', component: ReportPatients },
  { path: '/asignar-consulta', exact: true, name: 'Asignar Consultas', component: AssignConsultation },
  { path: '/consultas', exact: true, name: 'Consultas', component: Consultations },
  { path: '/consultas/atender/:id', name: 'Atender Paciente', component: AttendPatient },
  { path: '/consultas/ver/:id', name: 'Ver Consulta Atendida', component: ShowConsultation },

];

export default routes;
