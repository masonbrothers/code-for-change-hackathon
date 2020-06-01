import React from 'react';

import InputGroup from 'react-bootstrap/InputGroup';
import FormControl from 'react-bootstrap/FormControl';

import Form from 'react-bootstrap/Form';
import Col from 'react-bootstrap/Col';

function KeyAndName({onKeyChange, onNameChange}) {
  return (
    <div>
    <Form>
      <Form.Row>
        <Col>
          {/* Private Key */}
          <InputGroup className="mb-3">
          <InputGroup.Prepend>
            <InputGroup.Text id="basic-addon1">Private Key</InputGroup.Text>
          </InputGroup.Prepend>
          <FormControl
            placeholder=""
            aria-label="Private Keys"
            aria-describedby="basic-addon1"
            onChange={onKeyChange}
          />
          </InputGroup>
        </Col>
        <Col>
          {/* EOS Account */}
          <InputGroup className="mb-3">
          <InputGroup.Prepend>
            <InputGroup.Text id="basic-addon2">EOS Account</InputGroup.Text>
          </InputGroup.Prepend>
          <FormControl
            placeholder=""
            aria-label="EOS Account"
            aria-describedby="basic-addon2"
            onChange={onNameChange}
          />
          </InputGroup>
        </Col>
      </Form.Row>
    </Form>
    </div>
  );
}

export default KeyAndName;
