import os
import argparse
import fnmatch
import time
from datetime import datetime

def convert_size_to_bytes(size_str):
    """
    Convert a size string (like '1M', '500K', '10G') to bytes.
    """
    if not size_str:
        return None
        
    units = {
        'K': 1024,
        'M': 1024 * 1024,
        'G': 1024 * 1024 * 1024,
        'B': 1
    }
    
    unit = size_str[-1].upper()
    if unit in units:
        try:
            return int(float(size_str[:-1]) * units[unit])
        except ValueError:
            raise ValueError(f"Invalid size format: {size_str}")
    else:
        try:
            return int(float(size_str))  # Assume bytes if no unit specified
        except ValueError:
            raise ValueError(f"Invalid size format: {size_str}")

def find_files(start_path, name_pattern=None, type_filter=None, mtime=None, 
               min_size=None, max_size=None):
    """
    Recursively find files/directories starting from start_path.
    
    Args:
        start_path (str): Starting directory for search
        name_pattern (str): Pattern to match filenames (supports wildcards)
        type_filter (str): 'f' for files only, 'd' for directories only
        mtime (int): Find files modified in the last n days
        min_size (int): Minimum file size in bytes
        max_size (int): Maximum file size in bytes
    """
    # name_pattern = improve_pattern(name_pattern)
    try:
        for root, dirs, files in os.walk(start_path):
            # Handle directory matches
            if type_filter != 'f':  # If we're not looking for files only
                for dirname in dirs:
                    full_path = os.path.join(root, dirname)
                    if matches_criteria(full_path, name_pattern, 'd', mtime, min_size, max_size):
                        yield full_path
            
            # Handle file matches
            if type_filter != 'd':  # If we're not looking for directories only
                for filename in files:
                    full_path = os.path.join(root, filename)
                    if matches_criteria(full_path, name_pattern, 'f', mtime, min_size, max_size):
                        yield full_path
                        
    except PermissionError as e:
        print(f"Permission denied: {e}")
    except Exception as e:
        print(f"Error during search: {e}")



def matches_criteria(path, query, file_type, mtime, min_size, max_size):
    """Check if a path matches all the search criteria."""
    try:
        # That all the words in the query are there
        if query is not None:
            query_words = query.split()  # Split query into words
            for query_word in query_words:
                result = path.lower().find(query_word.lower())
                if result == -1:
                    return False

        
        # Check file type
        is_file = os.path.isfile(path)
        if file_type == 'f' and not is_file:
            return False
        if file_type == 'd' and is_file:
            return False
            
        # Check modification time
        if mtime is not None:
            file_mtime = os.path.getmtime(path)
            if time.time() - file_mtime > mtime * 24 * 3600:
                return False
        
        # Check file size (only for files, not directories)
        if min_size is not None or max_size is not None:
            if not is_file:
                return False 
            file_size = os.path.getsize(path)
            if min_size is not None and file_size < min_size:
                return False
            if max_size is not None and file_size > max_size:
                return False
                
        return True
        
    except Exception as e:
        print(f"Error checking path {path}: {e}")
        return False

def main():
    parser = argparse.ArgumentParser(description='A simple find command implementation')
    parser.add_argument('path', nargs='?', default='.', 
                      help='Starting path for search (default: current directory)')
    parser.add_argument('-name', help='Pattern to match (supports wildcards)')
    parser.add_argument('-type', choices=['f', 'd'], 
                      help='f: files only, d: directories only')
    parser.add_argument('-mtime', type=int,
                      help='Find files modified in the last n days')
    parser.add_argument('-size_min', 
                      help='Minimum file size (e.g., 1M, 500K, 10G)')
    parser.add_argument('-size_max',
                      help='Maximum file size (e.g., 1M, 500K, 10G)')
    
    args = parser.parse_args()
    
    try:
        # Convert size arguments to bytes
        min_size = convert_size_to_bytes(args.size_min) if args.size_min else None
        max_size = convert_size_to_bytes(args.size_max) if args.size_max else None
        
        for found_path in find_files(args.path, args.name, args.type, args.mtime,
                                   min_size, max_size):
            # Get file size for display
            size_str = ''
            if os.path.isfile(found_path):
                size = os.path.getsize(found_path)
                if size >= 1024 * 1024 * 1024:
                    size_str = f" ({size / (1024 * 1024 * 1024):.2f}G)"
                elif size >= 1024 * 1024:
                    size_str = f" ({size / (1024 * 1024):.2f}M)"
                elif size >= 1024:
                    size_str = f" ({size / 1024:.2f}K)"
                else:
                    size_str = f" ({size}B)"
            
            print(f"{found_path}{size_str}")
            
    except KeyboardInterrupt:
        print("\nSearch interrupted by user")
    except ValueError as e:
        print(f"Error: {e}")
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()
