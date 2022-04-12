import React from 'react'
import ReactDOM from 'react-dom'
import 'react-app-polyfill/ie11'
import 'react-app-polyfill/stable'
import { Provider } from 'react-redux'
import store from "../store";
import { icons } from "../assets/icons";
React.icons = icons

import Panel from "../Components/Panel/Panel";

document.addEventListener('DOMContentLoaded', () => {
  ReactDOM.render(
      <Provider store={ store }>
        <Panel/>
      </Provider>,
    document.body.appendChild(document.createElement('div')),
  )
})
