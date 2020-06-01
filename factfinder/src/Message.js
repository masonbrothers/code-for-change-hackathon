import React from 'react';

import InputGroup from 'react-bootstrap/InputGroup';
import FormControl from 'react-bootstrap/FormControl';
import Card from 'react-bootstrap/Card';
import Form from 'react-bootstrap/Form';
import Col from 'react-bootstrap/Col';
import Row from 'react-bootstrap/Row';
import Button from 'react-bootstrap/Button';
import Badge from 'react-bootstrap/Badge';

function Message ({name, message, isTrue, onIsTrueChange}) {
        return (
            <Card>
            <Card.Body>
            <h6>
                <Badge variant="secondary">{name}</Badge>
            </h6>
            <h2>{message}</h2>
            
        

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
                        onClick={() => onIsTrueChange(true)}
                        checked={isTrue}
                        />
                        <Form.Check
                        type="radio"
                        label="False"
                        onClick={() => onIsTrueChange(false)}
                        checked={!isTrue}
                        />
                    </Col>
                    </Form.Group>
                </fieldset>

                <Form.Group as={Row}>
                    <Form.Label column sm={2}>
                    Stake Amount
                    </Form.Label>
                    <Col sm={10}>
                    <Form.Control type="number" placeholder="Stake Amount" />
                    </Col>
                </Form.Group>

                <Form.Group as={Row}>
                <Col sm={{ span: 10, offset: 2 }}>
                <Button type="submit">Stake</Button>
                </Col>
            </Form.Group>
            </Form>
            
            </Card.Body>
            </Card>
        );
}

export default Message;
