# Lab 8: More Complex HTTP Server

## Exercise 1 – Create a More Complex HTTP Server

### Overview
The goal of this exercise is to extend the previous simplistic HTTP server to handle requests for files from a local folder and return them to the client upon receiving a properly formatted HTTP request.

### Exercise Steps

1. **Modify the HTTP Server Code**
   - Copy the original `httpServer.c` file and rename it to `httpServerFile.c`.
   - Modify the code to implement more comprehensive HTTP server functionality, such as enabling file opening and handling HTTP requests to serve files.

2. **Create Local HTML Files**
   - Create an `index.html` file and an `error.html` file with typical HTML content. Ensure these files are small in size, as one of them will be returned to the client based on the request.

3. **Test the Server**
   - Test the modified server by printing relevant data to both the client and server terminals to ensure the server is processing the HTTP requests correctly.

4. **Add HTTP Headers**
   - Implement the following HTTP headers to be returned in the response:
     - `Content-Length`: The length of the file content (determined from the open file).
     - `Cache-Control`: `no-cache` (ensures the browser does not cache the response).
     - `Connection`: `close` (indicates that the connection should be closed after the response).

5. **Test with a Browser**
   - Test your server by making requests from a browser (e.g., Chrome or Mozilla) to ensure it returns the correct file content and headers.

### Server Logic (Pseudocode)

The following pseudocode outlines the logic for implementing the server:

1. **Initialize Server**
   - Set up three character arrays to store the HTTP request components: `char discard1[50], path[64] = {‘.’}, discard2[50];`

2. **Server Loop**
   - Start an infinite loop to accept incoming client connections.

3. **Receive Data**
   - Accept the next connection and start a `recv()` loop to read the incoming data from the socket.
   - Store the received data in an incoming buffer and null terminate it.
   - Print the data to the local terminal.
   - Search for the end of the HTTP request (use `strstr()`) and break from the loop.

4. **Parse HTTP Request**
   - Parse the HTTP components from the incoming buffer and store them in the arrays: `discard1`, `path`, and `discard2` (use `sscanf()`).

5. **File Handling**
   - If the `path` contains an empty slash (i.e., the root path), replace it with `./index.html`.
   - Attempt to open the requested file using the `fopen()` function.
   
6. **Handle File Existence**
   - If the file exists:
     - Store the positive (200) HTTP headers in the outgoing buffer.
     - Use `stat()` to determine the number of bytes in the file and include this in the `Content-Length` header.
   - If the file does not exist:
     - Open the `error.html` file and store negative (404) HTTP headers in the outgoing buffer.
     - Again, use `stat()` to determine the number of bytes for the `Content-Length` header.

7. **Send Response**
   - Return the HTTP headers and file contents to the connected socket:
     - The outgoing buffer should first contain the HTTP headers.
     - Then, insert the contents of the open file byte by byte into the outgoing buffer and send this as the body of the HTTP response.

8. **Close Connection**
   - Close the connected socket and reset variables, buffers, and counters.
   
9. **End Loop**
   - Continue the infinite loop to handle additional incoming connections.

---

### How to Run the Code

1. **Clone this repository**:
   If you haven't already cloned the repository, you can do so by running:
   ```bash
   git clone https://github.com/yourusername/your-repository-name.git
   cd your-repository-name
   ```

2. **Compile the Server Code**:
   Assuming you've renamed the source file to `httpServerFile.c`, you can compile the server code with the following command:
   ```bash
   gcc -o httpServerTest httpServerFile.c -lws2_32
   ```

3. **Run the Server**:
   After compiling the code, run the server with:
   ```bash
   ./httpServerTest.exe
   ```
   This will start the server, which will listen for HTTP requests on port `8080`.

4. **Test the Server**:
   - Open a web browser (e.g., Chrome or Mozilla) and visit `http://localhost:8080/` to test the server.
   - If the server receives a valid request, it will respond with the content of the `index.html` file.
   - If the request is for a non-existent file, the server will return the `error.html` file with a `404 Not Found` response.

5. **Stop the Server**:
   To stop the server, simply press `Ctrl + C` in your terminal.