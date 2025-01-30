import React from 'react';
import myPic from './img/me.png';
import './About.css';

export default function About(){
    return (
        <div className='aboutMe' id='aboutMe'>
            <div className='textAboutMe'>
                <h2 id='headAbout'>שלום! שמי תהילה</h2>
                <p>שמי תהילה אבל החברים והקולגות קוראים לי טקילה.
                     אני עוסקת בצילום כבר 7 שנים.
מגיל עשר התחלתי לעבוד עם ילדים והייתי מדריכה
 גם בבית הספר וגם בארגון יהודי "סוכנות", וכיום הניסיון 
הזה עוזר לי ליצור צילומים ייחודיים, במיוחד עם ילדים.
אני גרה בישראל מגיל 15 ומכיוון שאני
 כאן לבד, התמונות המשפחתיות נורא מיוחדות עבורי. וכדי שכל
 תמונה תתמלא בחום הזה, בחרתי בסגנון הצילום "לייף סטייל".</p>
            </div>
            <div className='myPict'>
                <img src={myPic} alt='Me'/>
            </div>
        </div>
    )
  };