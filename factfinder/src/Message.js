import React from 'react';

import Card from 'react-bootstrap/Card';
import Form from 'react-bootstrap/Form';
import Col from 'react-bootstrap/Col';
import Row from 'react-bootstrap/Row';
import Button from 'react-bootstrap/Button';
import Badge from 'react-bootstrap/Badge';
import eos from './eos';

class Message extends React.Component {
    state = {
        is_true: true,
        amount: 0
    }

    onis_trueChange = (value) => {
        this.setState({is_true: value})
    }

    submitVote = async () => {
        eos.castvote(this.props.key, this.state.name, this.props.message_id, this.state.amount, this.state.is_true)
    }

    render() {
        return (
            <Card>
            <Card.Body>
            <h6>
                <Badge variant="secondary">{this.props.name}</Badge>
            </h6>
            <h2>{this.props.message}</h2>
            
        

            <Form>
                <fieldset>
                    <Form.Group as={Row}>
                    <Form.Label as="legend" column sm={2}>
                        The Message is
                    </Form.Label>
                    <Col sm={10}>
                        <Form.Check
                        type="radio"
                        label="True"
                        onChange={() => this.onis_trueChange(true)}
                        checked={this.state.is_true}
                        />
                        <Form.Check
                        type="radio"
                        label="False"
                        onChange={() => this.onis_trueChange(false)}
                        checked={!this.state.is_true}
                        />
                    </Col>
                    </Form.Group>
                </fieldset>

                <Form.Group as={Row}>
                    <Form.Label column sm={2}>
                    Stake Amount
                    </Form.Label>
                    <Col sm={10}>
                    <Form.Control type="number" placeholder="Stake Amount" value={this.state.amount} onChange={(e) => {this.setState({amount: e.target.value})}}/>
                    </Col>
                </Form.Group>

                <Form.Group as={Row}>
                <Col sm={{ span: 10, offset: 2 }}>
                <Button onClick={
                    this.submitVote
                }>Stake</Button>
                </Col>
            </Form.Group>
            </Form>
            
            </Card.Body>
            </Card>
        );
    }
}

export default Message;
