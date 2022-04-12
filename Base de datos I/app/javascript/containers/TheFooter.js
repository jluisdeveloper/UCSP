import React from 'react'
import { CFooter } from '@coreui/react'

const TheFooter = () => {
  return (
    <CFooter fixed={false}>
      <div>
        <a href="#" target="_blank" rel="noopener noreferrer">Base de Datos 1</a>
        <span className="ml-1">2020 UCSP.</span>
      </div>
      <div className="mfs-auto">
        <span className="mr-1">Trabajo final </span>
        <a href="#" target="_blank" rel="noopener noreferrer">Grupo 1</a>
      </div>
    </CFooter>
  )
}

export default React.memo(TheFooter)
