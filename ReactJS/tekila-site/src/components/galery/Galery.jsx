import React from 'react';
import {ImagesAlb} from './ImagesAlb';
import './Galery.css';
import Album from '../Album/Album';

export default function Galery(){
  return (
    <React.Fragment>
    <div className='galery' id='galery'>
      <h3>גלריה</h3>
      <div className='cards'>
          <div className='albcards'>
            {ImagesAlb.map((image) => {
                  return (
                    <Album
                      image = {image.img}
                      imgalt={image.id}
                      />
                  )
              })}                
          </div>
      </div>
  </div>  
    </React.Fragment>
  )
};