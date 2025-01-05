# Run this in the directory that you want to serve and then 
import http.server
import socketserver
import os
import sys

def run_static_file_server(directory, port):
    os.chdir(directory)  # Change the current working directory to the specified directory
    handler = http.server.SimpleHTTPRequestHandler
    with socketserver.TCPServer(("", port), handler) as httpd:
        print(f"Serving directory {directory} on port {port}")
        httpd.serve_forever()

if __name__ == "__main__":
    print("Running server at http://localhost:8080")
    run_static_file_server(".", 8080)

    # if len(sys.argv) < 3:
    #     print("Usage: python3 server.py [directory] [port]")
    # else:
    #     dir_path = sys.argv[1]
    #     port_num = int(sys.argv[2])
    #     run_server(dir_path, port_num)
        


