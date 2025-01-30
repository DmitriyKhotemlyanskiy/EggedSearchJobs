import React from 'react';
import './Lifestyle.css';
import Carousel from '../carousel/Carousel';
import Images from './Images';

export default function Lifestyle(){
    return (
        <div className='life_style' id='life_style'>
            <div className='about_lifestyle'>
                <h2 id='headLifeStyle'>מה זה לייף סטייל?</h2>
            </div>
            <div className='life_carousel'>
                <Carousel images={Images}/>
            </div>
            
            <div className='textLifeStyle'>
                <p>
                אני אדם שמעריך את הטבעיות. וזה לא קשור לאיפור, לבוש פשוט או בחירת מקומות בטבע. אסתטיקה עבורי היא הסיפורים שאנחנו יוצרים כל יום. אם אתם מעדיפים תלבושות בהירות, צבעים ומקומות אקספרסיביים, זו הטבעיות האמיתית שלכם.
                </p>
                <p>
                זה בעצם מה שעומד בבסיס הסגנון "לייף סטייל" שאני עושה. אין כאן תקני יופי. אחרי הכל, כל אדם הוא ייחודי, והמשימה שלי היא להראות אותכם כפי שאתם, לשמור על היופי והייחודיות שלכם, מבלי להפריע להרמוניה הטבעית שלכם.
                </p>
                <p>
                אני עוזרת לכם להירגע במהלך הצילומים, יוצרת אווירה של אמון ונוחות. המטרה שלי היא לערב אותכם בתהליך הצילום, כך שאתם אפילו לא תשימו לב כמה טבעי אתם יוצאים בתמונה. הצילום הוא כמו משחק קל וטבעי, ולאף אחד לא נמאס להצטלם - לא לילדים, לא לבעלים, ואפילו לא לחברים שלנו עם זנב.
                </p>
            </div>
        </div>
    )
  };