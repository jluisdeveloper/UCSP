import React, {Component} from 'react';
import axios from "axios";
import { passCsrfToken } from "../helpers/csrfToken";
import {
  CDropdown,
  CDropdownItem,
  CDropdownMenu,
  CDropdownToggle,
  CImg
} from '@coreui/react'
import CIcon from '@coreui/icons-react'

class TheHeaderDropdown extends Component {
  constructor(props) {
    super(props);
  }

  componentDidMount() {
    passCsrfToken(document,axios)
  }


  handleSignOut = async () => {
    axios.delete('/users/sign_out').then(
      setTimeout (() => {
        location.reload();
      }, 2000)
    )
  }

  render() {
    return (
        <CDropdown
            inNav
            className="c-header-nav-items mx-2"
            direction="down"
        >
          <CDropdownToggle className="c-header-nav-link" caret={false}>
            <div className="c-avatar">
              <CImg
                  src={ this.props.currentUser.avatar.thumb.url }
                  className="c-avatar-img"
                  alt={ this.props.currentUser.full_name }
              />
            </div>
          </CDropdownToggle>
          <CDropdownMenu className="pt-0" placement="bottom-end">
            <CDropdownItem
                header
                tag="div"
                color="light"
                className="text-center"
            >
              <strong>Opciones</strong>
            </CDropdownItem>
            <CDropdownItem>
              <CIcon name="cil-user" className="mfe-2" />Ver Perfil
            </CDropdownItem>
            <CDropdownItem>
              <CIcon name="cil-settings" className="mfe-2" />
              Actualizar Cuenta
            </CDropdownItem>
            <CDropdownItem>
              <CIcon name="cil-credit-card" className="mfe-2" />
              Pagos / Fechas
            </CDropdownItem>
            <CDropdownItem divider />
            <CDropdownItem
              onClick={this.handleSignOut}
            >
              <CIcon name="cil-lock-locked" className="mfe-2" />
              Cerrar Sesion
            </CDropdownItem>
          </CDropdownMenu>
        </CDropdown>
    )
  }
}

export default TheHeaderDropdown;
