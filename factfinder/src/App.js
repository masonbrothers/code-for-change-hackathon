import React from 'react';
import logo from './logo.svg';
import './App.css';
import 'bootstrap/dist/css/bootstrap.min.css';

import Button from 'react-bootstrap/Button';
import InputGroup from 'react-bootstrap/InputGroup';
import FormControl from 'react-bootstrap/FormControl';

import Form from 'react-bootstrap/Form';
import Col from 'react-bootstrap/Col';

import Input from 'react-bootstrap/Button';
import eos from './eos';
import update from 'react-addons-update'; // ES6
import KeyAndName from './KeyAndName';
import Message from './Message';
import Navbar from 'react-bootstrap/Navbar'


class App  extends React.Component {

  state = {
    message: '',
    key: '',
    name: '',
    messages: [
      {
        name: 'eosuser',
        message: 'COVID is transmitted by insects',
        message_id: 1
      }
    ]
  }

  render() {
  return (
    <div>
      <Navbar bg="light" expand="lg">
        <Navbar.Brand href="#home">FactFinder</Navbar.Brand>
        <Navbar.Toggle aria-controls="basic-navbar-nav" />
      </Navbar>

      <div className="App">
        <KeyAndName 
          onKeyChange={(e)=>{this.setState({key: e.target.value})}}
          onNameChange={(e)=>{this.setState({name: e.target.value})}}
        />
        
        <InputGroup> 
          <FormControl
            as="textarea"
            placeholder="Message"
            aria-label="Message"
            onChange={(e) => {this.setState({message: e.target.value})}}
          />
        </InputGroup>

        {/* Stake Amount */}
        <InputGroup className="mb-3">
        <InputGroup.Prepend>
          <InputGroup.Text id="basic-addon3">Stake Amount</InputGroup.Text>
        </InputGroup.Prepend>
        <FormControl
          placeholder=""
          aria-label="Stake Amount"
          aria-describedby="basic-addon3"
        />
        </InputGroup>
        
        <Button onClick={() => {eos.post(this.state.key, this.state.name, this.state.message)}}>Post</Button>
        <br/><br/><br/>
        {this.state.messages.map((message) => {return (
          <Message name={message.name} message={message.message} key={this.state.key} voter={this.state.name} message_id={message.message_id}/>
        )}) }

      </div>
    </div>
  );
      }
}

export default App;
