import React from 'react';
import Button from "../button/Button";

import './Header.css';

export default function Header(){
    return (
      <header className="header">
        <h1>Tekila Photo</h1>
        <nav>
          <div className="buttons">
              <Button strValue={'קצת עליי'} linkTo={'#aboutMe'}/>
              <Button strValue={'מה זה לייף סטייל'} linkTo={'#life_style'}/>
              <Button strValue={'גלריה'} linkTo={'#galery'}/>
              <Button strValue={'מחירון'} linkTo={'#costs'}/>
              <Button strValue={'דברו איתי'} linkTo={'#contact'}/>
          </div>
        </nav>
      </header>
    )
  };