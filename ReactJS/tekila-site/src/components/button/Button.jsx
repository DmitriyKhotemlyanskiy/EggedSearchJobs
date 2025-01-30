import React from 'react';
import './Button.css';

export default function Button(props){
    return (
        <a href={props.linkTo}><button className='linkButton'>{props.strValue}</button></a>
    )
  }