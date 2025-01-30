import React from 'react';
import { useState } from "react";
import "./Carousel.css"


export default function Carousel({ images }){
        const [currentIndex, setCurrentIndex] = useState(0);
      
        const handleNext = () => {
          setCurrentIndex((prevIndex) =>
            prevIndex + 1 === images.length ? 0 : prevIndex + 1
          );
        };
        const handlePrevious = () => {
          setCurrentIndex((prevIndex) =>
            prevIndex - 1 < 0 ? images.length - 1 : prevIndex - 1
          );
        };
        return (
            <React.Fragment>
              <div className="carousel">
                <div className="left" onClick={handlePrevious}>
                    <i className="material-icons">arrow_back</i>
                </div>
                <img
                  key={currentIndex}
                  src={images[currentIndex]}
                  alt={currentIndex}
                />
                <div className="right" onClick={handleNext}>
                  <i className="material-icons">arrow_forward</i>
                </div>
              </div>
            </React.Fragment>
          );
  };