import os
import argparse

def find_case_insensitive(a, b):
    """Return the index of b in a (case-insensitive), or -1 if not found."""
    return a.lower().find(b.lower())

def check_match(full_path, query_words):
    was_found = True	
    for query_word in query_words:
        if -1 == find_case_insensitive(full_path, query_word):
            was_found = False
    return was_found
                        
def find_files(top_dir, query):
    """Search for files or directories matching the query in top_dir."""
    query_words = query.split()  # Split query into words

    for root, dirs, files in os.walk(top_dir):
        # Combine files and directories for search
        all_entries = files + dirs

        for entry in all_entries:
            full_path = os.path.join(root, entry)
            was_found = check_match(full_path, query_words)
            if was_found:
                print(full_path)
                
def main():
    # Set up argument parser
    parser = argparse.ArgumentParser(description="Search for files and directories containing specific keywords.")
    parser.add_argument("top_dir", type=str, help="The top-level directory to search.")
    parser.add_argument("query", type=str, help="Keywords to search for, separated by whitespace.")

    # Parse arguments
    args = parser.parse_args()

    # Run the search function
    find_files(args.top_dir, args.query)

if __name__ == "__main__":
    main()
