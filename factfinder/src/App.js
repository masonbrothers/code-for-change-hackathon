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
import KeyAndName from './KeyAndName';
import Message from './Message';
import Navbar from 'react-bootstrap/Navbar'



function App() {
  return (
    <div>
      <link
      rel="stylesheet"
      href="https://maxcdn.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css"
      integrity="sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh"
      crossOrigin="anonymous"
      />


      <Navbar bg="light" expand="lg">
        <Navbar.Brand href="#home">FactFinder</Navbar.Brand>
        <Navbar.Toggle aria-controls="basic-navbar-nav" />
      </Navbar>

      <div className="App">
        <KeyAndName 
          onKeyChange={(e)=>{console.log("Key:", e.target.value)}}
          onNameChange={(e)=>{console.log("Name:", e.target.value)}}
        />
        
        <InputGroup> 
        
          <FormControl
            as="textarea"
            placeholder="Message"
            aria-label="Message"
            onChange={(e) => {console.log(e.target.value)}}
          />
        </InputGroup>
        
        {/* EOS Account */}
        <InputGroup className="mb-3">
        <InputGroup.Prepend>
          <InputGroup.Text id="basic-addon3">Reply To</InputGroup.Text>
        </InputGroup.Prepend>
        <FormControl
          placeholder=""
          aria-label="Reply To"
          aria-describedby="basic-addon3"
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

    


    

        <Button>Post</Button>

        <Message name='eosuser' message='COVID is transmitted by insects' isTrue={false} onIsTrueChange={console.log}/>

      </div>
    </div>
  );
}

export default App;
