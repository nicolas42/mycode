import argparse
import requests
from urllib.parse import urlparse
import os
from tqdm import tqdm

def download_file(url, output_path=None):
    """
    Download a file from a given URL, similar to wget.
    
    Args:
        url (str): The URL to download from
        output_path (str, optional): Path where to save the file. If None, uses the filename from URL
    """
    try:
        # Send a GET request with stream=True to handle large files
        response = requests.get(url, stream=True)
        response.raise_for_status()
        
        # Get filename from URL if output path is not specified
        if not output_path:
            filename = os.path.basename(urlparse(url).path)
            if not filename:
                filename = 'downloaded_file'
        else:
            filename = output_path
            
        # Get file size for progress bar
        total_size = int(response.headers.get('content-length', 0))
        
        # Open file and write with progress bar
        with open(filename, 'wb') as file, tqdm(
            desc=filename,
            total=total_size,
            unit='iB',
            unit_scale=True,
            unit_divisor=1024,
        ) as progress_bar:
            for data in response.iter_content(chunk_size=1024):
                size = file.write(data)
                progress_bar.update(size)
                
        print(f"Successfully downloaded {filename}")
        
    except requests.exceptions.RequestException as e:
        print(f"Error downloading file: {e}")
        return False
    
    return True

def main():
    parser = argparse.ArgumentParser(description='A simple wget-like downloader')
    parser.add_argument('url', help='URL of the file to download')
    parser.add_argument('-O', '--output-document', help='Write documents to FILE', default=None)
    
    args = parser.parse_args()
    download_file(args.url, args.output_document)

if __name__ == "__main__":
    main()
