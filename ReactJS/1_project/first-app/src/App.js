
import "./index.css";
import Navbar from './Navbar';
import Home from './Home';

function App() {
  let title="Welcome to the new Blog";
  const likes = 50;
  const link = "https://www.google.com";
  return (
    <div className="App">
      <Navbar />
      <div className="content">
          <h1>{title}</h1>
          <Home />
            <p>Liked {likes+1} times</p>
            <p>{ 10 }</p>
            <p>{[1,2,3,4,5,6,7]}</p>
            <p>{ "Hello" }</p>
            <a href={link}>Google Site</a>
            <p>{Math.random() * 100 }</p>
      </div>
    </div>
  );
}

export default App;
