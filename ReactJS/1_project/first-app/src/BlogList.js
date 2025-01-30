const BlogList = ({blogs, title, handleDelete}) =>{
    return (
        <div className="blog-list">
            <h2>{title}</h2>
            {blogs.map((blog) => (
                <div className="blog-preview" key={blog.id}>
                    <h3>{blog.title}</h3>
                    <p>{blog.body}</p>
                    <p>Written by {blog.author}</p>
                    <button onClick={() => handleDelete(blog.id)}>delete blog</button>
                </div>    
            ))}
        </div>
        );
}

export default BlogList;