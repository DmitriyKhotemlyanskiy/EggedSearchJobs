let offset = 0;
const sliderLine = document.querySelector('.slider-line');

document.querySelector('.slider-next').addEventListener('click', function(){
    offset -= 300;
    if(offset < -900){
        offset = 0;
    }
    sliderLine.style.left = offset + 'px';
});
document.querySelector('.slider-prev').addEventListener('click', function(){
    offset += 300;
    if(offset > 0){
        offset = -900;
    }
    sliderLine.style.left = offset + 'px';
});