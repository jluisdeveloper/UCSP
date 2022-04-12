import React from 'react'
import ReactDOM from 'react-dom'
import FrontPage from "../Components/FrontPage/FrontPage";

import '../scss/FrontPage/estilos.scss'

document.addEventListener('DOMContentLoaded', () => {
    ReactDOM.render(
        <FrontPage/>,
        document.body.appendChild(document.createElement('div')),
    )
})
