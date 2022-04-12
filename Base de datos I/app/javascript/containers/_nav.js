export default [
  {
    _tag: 'CSidebarNavTitle',
    _children: ['AREA ADMINISTRATIVA']
  },
  {
    _tag: 'CSidebarNavItem',
    name: 'Dashboard',
    to: '/',
    icon: 'cil-speedometer',
  },
  {
    _tag: 'CSidebarNavItem',
    name: 'Reportes de Clientes',
    to: '/reports/patients',
    icon: 'cil-bar-chart',
  },
  {
    _tag: 'CSidebarNavTitle',
    _children: ['Area de Personal Laboral']
  },
  {
    _tag: 'CSidebarNavItem',
    name: 'Personal',
    to: '/personal',
    icon: 'cil-people',
  },
  {
    _tag: 'CSidebarNavTitle',
    _children: ['Farmacia']
  },
  {
    _tag: 'CSidebarNavItem',
    name: 'Farmacia',
    to: '/drugstore',
    icon: 'cil-apple',
  },
  {
    _tag: 'CSidebarNavItem',
    name: 'Reporte de Movimientos',
    to: '/drugstore/report',
    icon: 'cil-chart-line',
  },
  {
    _tag: 'CSidebarNavTitle',
    _children: ['AREA DE PACIENTES']
  },
  {
    _tag: 'CSidebarNavItem',
    name: 'Pacientes',
    to: '/pacientes',
    icon: 'cil-people',
  },
  {
    _tag: 'CSidebarNavItem',
    name: 'Asignar Consulta',
    to: '/asignar-consulta',
    icon: 'cil-people',
  },
  {
    _tag: 'CSidebarNavItem',
    name: 'Consultas',
    to: '/consultas',
    icon: 'cil-people',
  },
  {
    _tag: 'CSidebarNavItem',
    name: 'Resultados',
    to: '/pacientes/resultado',
    icon: 'cil-address-book',
  },
]

