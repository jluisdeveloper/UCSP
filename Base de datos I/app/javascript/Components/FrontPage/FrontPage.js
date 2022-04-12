import React, {Component} from 'react';

import Logo from '../FrontPage/images/logo.png'
import BGSlider1 from '../FrontPage/images/sliderbg1.jpg'
import BGSlider2 from '../FrontPage/images/sliderbg2.jpg'
import SingleFive from '../FrontPage/images/single-five-img.png'

import Speciality1 from '../FrontPage/images/single-img-nine-300x200.jpg'
import Speciality2 from '../FrontPage/images/single-img-ten-300x200.jpg'
import Speciality3 from '../FrontPage/images/single-imh-eight-300x200.jpg'

import BigOneForm from '../FrontPage/images/tm-col-bg-img-one.jpg'

class FrontPage extends Component {
    render() {
        return (
            <div>
                <div className="top-bar">
                    <div className="container">
                        <div className="top-bar-contenido d-flex align-items-center">
                            <div className="col-6">
                                <ul className="contacto d-flex  justify-content-start align-items-center">
                                    <li>
                                        <i className="fas fa-map-marker-alt"></i>
                                        234 Triumph, Los Angeles, California, US
                                    </li>
                                    <li className="padding-left-10">
                                        <i className="fas fa-stopwatch"></i>
                                        Mon - Sat 8.00 - 18.00. Sunday CLOSED
                                    </li>
                                </ul>
                            </div>
                            <div className="col-6">
                                <ul className="contacto d-flex justify-content-end align-items-center">
                                    <li>
                                        <i className="padding-left-10 fab fa-facebook-f"></i>
                                        <i className="padding-left-10 fab fa-twitter"></i>
                                        <i className="padding-left-10 fab fa-linkedin-in"></i>
                                    </li>
                                    <li className="padding-left-20">
                                        <a href="#cita" className="button-verde">GET A APPOINTMENT!</a>
                                    </li>
                                </ul>
                            </div>
                        </div>

                    </div>
                </div>

                <div className="header fixed-top">
                    <nav className="navbar navbar-expand-lg navbar-light bg-light">
                        <div className="container">
                            <a className="navbar-brand" href="#">
                                <img src={ Logo } alt=""/>
                            </a>
                            <button className="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarTogglerDemo02" aria-controls="navbarTogglerDemo02" aria-expanded="false" aria-label="Toggle navigation">
                                <span className="navbar-toggler-icon"></span>
                            </button>
                            <div className="collapse navbar-collapse d-flex justify-content-end " id="navbarTogglerDemo02">
                                <ul className="navbar-nav  ">
                                    <li className="nav-item">
                                        <a className="nav-link active" aria-current="page" href="#">Inicio</a>
                                    </li>
                                    <li className="nav-item">
                                        <a className="nav-link menu-principal" href="#nosotros">Nosotros</a>
                                    </li>
                                    <li className="nav-item">
                                        <a className="nav-link menu-principal "  href="#servicios">Servicios</a>
                                    </li>
                                    <li className="nav-item">
                                        <a className="nav-link menu-principal" href="/users/sign_in">Iniciar Sesion</a>
                                    </li>
                                    <li className="nav-item">
                                        <a className="nav-link menu-principal" href="#cita">Buscar mi resultado</a>
                                    </li>


                                </ul>
                                <form className="d-flex padding-left-20">
                                    <i className="fas fa-search">
                                    </i>
                                </form>
                            </div>
                        </div>
                    </nav>
                </div>

                <div id="carouselExampleFade" className="carousel slide carousel-fade" data-bs-ride="carousel">
                    <div className="carousel-inner">
                        <div className="carousel-item active">
                            <img src={BGSlider1} className="d-block w-100" />
                                <div className="texto-slider">
                                    <h5>Sistema Hospital Base de Datos I</h5>
                                    <p>Hospital donde te sentiras bien en esta vida o en la otra.</p>
                                </div>
                        </div>
                        <div className="carousel-item">
                            <img src={BGSlider2} className="d-block w-100" />
                                <div className="texto-slider2">
                                    <h5>Segundo SLide</h5>
                                    <p>Hospital donde te sentiras bien en esta vida o en la otra.</p>
                                </div>
                        </div>

                    </div>
                    <a className="carousel-control-prev" href="#carouselExampleFade" role="button" data-bs-slide="prev">
                        <span className="carousel-control-prev-icon" aria-hidden="true"></span>
                        <span className="visually-hidden">Previous</span>
                    </a>
                    <a className="carousel-control-next" href="#carouselExampleFade" role="button" data-bs-slide="next">
                        <span className="carousel-control-next-icon" aria-hidden="true"></span>
                        <span className="visually-hidden">Next</span>
                    </a>
                </div>

                <div className="nosotros" id="nosotros">
                    <div className="container d-flex ">
                        <div className="col-lg-6 padding-top-15 ">
                            <img src={SingleFive} alt=""/>
                        </div>
                        <div className="col-lg-6 p-lg-5 margin-top-2 texto-izquierda ">
                            <h5>Nuestros Medicos</h5>
                            <h2>Calificados para darte una mejor atencion</h2>
                            <p>Lorem ipsum dolor sit amet consectetur adipisicing elit. Iure dolore neque sunt impedit! Iste impedit, sunt doloremque illo quas architecto consectetur corrupti alias, reprehenderit eligendi consequuntur error! Eveniet, ducimus voluptate..</p>
                            <h3>Servicios especiales</h3>
                            <ul className="list-none">
                                <li>
                                    <i className="fa fa-arrow-circle-right">
                                    </i>
                                    Atencion de Adultos Mayores
                                </li>
                                <li>
                                    <i className="fa fa-arrow-circle-right">
                                    </i>
                                    Atencion de Adultos Mayores
                                </li>
                                <li>
                                    <i className="fa fa-arrow-circle-right">
                                    </i>
                                    Atencion de Adultos Mayores
                                </li>
                            </ul>
                        </div>
                    </div>
                </div>

                <div className="servicios text-center paddin-center" id="servicios">
                    <h5 className="margin-top-15">Nuestros Servicios</h5>
                    <h2>Servicios especiales a tu disposicion</h2>
                    <p>
                        Desde su fundación, Hospitalito ha brindado a sus pacientes la atención médica completa, como neurología, laboratorio, diagnóstico por imágenes y más.
                    </p>
                    <div className="lista-servicios d-flex justify-content-evenly ">
                        <div className="card" style={{ width: "18rem" }} >
                            <img src={Speciality1} className="card-img-top" alt="..." />
                                <div className="card-body">
                                    <h3>Cardiologia</h3>
                                    <p className="card-text">Some quick example text to build on the card title and make up the bulk of the card's content.</p>
                                </div>
                        </div>
                        <div className="card" style={{ width: "18rem" }} >
                            <img src={Speciality2} className="card-img-top" alt="..." />
                                <div className="card-body">
                                    <h3>Oncologia</h3>
                                    <p className="card-text">Some quick example text to build on the card title and make up the bulk of the card's content.</p>
                                </div>
                        </div>
                        <div className="card" style={{ width: "18rem" }} >
                            <img src={Speciality3} className="card-img-top" alt="..." />
                                <div className="card-body">
                                    <h3>Inmunologia</h3>
                                    <p className="card-text">Some quick example text to build on the card title and make up the bulk of the card's content.</p>
                                </div>
                        </div>
                    </div>
                </div>

                <div className="prefooter  margin-center-50 paddin-center">
                    <div className=" container d-flex">
                        <div className="col-lg-4 d-flex ">
                            <div className="tel1 centrar-vertical">
                                <i className="fas fa-phone-alt"></i>
                            </div>
                            <div className="cont-tel margin-left-20 ">
                                <span>
                                  <h5 >+51 4265556 </h5>
                                    <h6>Llama ahora llama ya </h6>
                                </span>
                            </div>

                        </div>
                        <div className="col-lg-4 d-flex">
                            <div className="tel1 centrar-vertical">
                                <i className="fas fa-envelope"></i>
                            </div>
                            <div className="cont-tel margin-left-20 ">
                                <span>
                                  <h5 >info@basededato1.com </h5>
                                    <h6>necesitas ayuda?</h6>
                                </span>
                            </div>
                        </div>
                        <div className="col-lg-4 d-flex">
                            <div className="tel1 centrar-vertical">
                                <i className="fas fa-clock"></i>
                            </div>
                            <div className="cont-tel margin-left-20 ">
                                <span>
                                  <h5>Lunes – Sabado 07:00 – 21:00 </h5>
                                    <h6>Estamos atendiendo</h6>
                                </span>
                            </div>
                        </div>
                    </div>
                </div>

                <div class="cita container d-flex justify-content-around paddin-center" id="cita">
                    <div class="col-lg-5 margin-top-15 ">
                        <img src={BigOneForm} alt="" />
                    </div>
                    <div class="col-lg-7 p-lg-5 m-auto ">
                        <h2>Buscar Resultado</h2>
                        <p>Si ya fuiste atendido en nuestro hospital puedes buscar tus resultados de examenes con tu dni.</p>
                        <form action="">
                            <div class="row pt-3 ">
                                <div class="col-lg-12 d-flex align-items-center  ">
                                    <i class="fas fa-user form-ico margin-left-10">
                                    </i>
                                    <span class="form-name w-100">
                                        <input type="text" class="form-control padding-left-30 " id="formGroupExampleInput" placeholder="Ingrese su DNI" />
                                    </span>
                                </div>
                            </div>

                            <div class="row pt-3 ">
                                <div class="col-lg-12 d-flex align-items-center ">
                                    <a href="" class="button-verde w-100 text-center">Buscar Resultado</a>
                                </div>
                            </div>
                        </form>
                    </div>
                 </div>
            </div>
        );
    }
}

export default FrontPage;