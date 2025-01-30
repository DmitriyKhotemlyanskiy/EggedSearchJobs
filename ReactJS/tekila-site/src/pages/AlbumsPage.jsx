import React from 'react';
import { Photos } from '../components/Album/photos/Photos';


import './AlbumsPage.css';

export default function AlbumsPage(){
    return (
        <React.Fragment>
        <main className='albumpage'>
            <div className='photos'>
                <div className='photo'>
                    {Photos.map((photo)=>{
                        return (
                            <img src={photo.img} alt={photo.id}/>
                        )                            
                    })}
                </div>
            </div>
        </main>
        </React.Fragment>
        );
};