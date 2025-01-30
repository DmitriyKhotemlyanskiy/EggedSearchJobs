import React from 'react';

import './Album.css';

export default function Album({image, imgalt}){
  return (
    <div className='album'>
        <img 
        src={image}
      alt={imgalt} />
    </div>
  )
};