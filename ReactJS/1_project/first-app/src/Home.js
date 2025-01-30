import {useState, useEffect} from 'react';
import BlogList from './BlogList';

const Home = () =>{
    //let count = 0;
    let[count, iterateConst] = useState(0);
    const[name, changeName] = useState("Artur");
    const[nameMarik, setName] = useState("Marik");

    const[blogs, setBlogs] = useState(null/*[
        {title: "My new website", body: "lorem ipsum...", author: "Mario", id: 1},
        {title: "Welcome party!", body: "lorem ipsum...", author: "Yosi", id: 2},
        {title: "Web dev tools", body: "lorem ipsum...", author: "Misha", id: 3}
    ]*/);

    
    const handleClick = () =>{
        console.log("Hello world");
        iterateConst(count++);
        changeName("Mitya");
    }
    const handleClickAgain = (name) =>{
        console.log("Hello, " + name);
    }

    const handleDelete = (id) =>{
        const newBlogs = blogs.filter(blog => blog.id !== id);
        setBlogs(newBlogs);
    }
//The Hook useEffect run continiously in every rerender the web-page
    useEffect(() => {
        fetch("http://localhost:8000/host")
        .then(res => {
            return res.json();
        })
        .then((data)=> {
            console.log(data);
            //setBlogs(data);
        });
    },[]);
//If you add an empty array at the end of the function, useEffect will only work on the first render.
useEffect(() => {
    console.log("Use Effect run");
}, []);
//Here you can run (trigger) useEffect only if nameMarik will change by clicking on the button Change Name
useEffect(() => {
    console.log("Use Effect run");
    console.log(nameMarik);
}, [nameMarik]);

    return (
        <div className="Home">
            <h2>Homepage</h2>
            <button onClick={handleClick}>Click me</button>
            <button onClick={()=>handleClickAgain("Dimas")}>ClickMeAgain</button>
            <p>Button was clicked {count} times and the name cahned to {name}</p>
            
            {blogs && <BlogList blogs = {blogs} title = "New title!" handleDelete={handleDelete}/>}
            {blogs && <BlogList blogs = {blogs.filter((blog)=> blog.author === "Mario")} title="Mario's blogs:" handleDelete={handleDelete}/>}
            <button onClick={()=>setName("Luigi")}>Change Name</button>
            <p>{nameMarik}</p>
        </div>
    );
}

export default Home; 