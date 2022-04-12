import React, {Component} from 'react';
import { HashRouter, Switch, Route } from 'react-router-dom'
import '../../scss/style.scss';

const loading = (
    <div className="pt-3 text-center">
        <div className="sk-spinner sk-spinner-pulse"> </div>
    </div>
)

const TheLayout = React.lazy(() => import('../../containers/TheLayout'));

class Panel extends Component {
    constructor(props) {
        super(props);
    }

    render() {
        return (
            <HashRouter>
                <React.Suspense fallback={loading}>
                    <Switch>
                        <Route path="/" render={props => <TheLayout {...props }/>} />
                    </Switch>
                </React.Suspense>
            </HashRouter>
        );
    }
}

export default Panel;