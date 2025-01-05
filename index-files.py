# To Do: Make graphical file finder

import os

def index_files(root, out, progress=False):
    try:
        files = os.listdir(root)
    except PermissionError as e:
        print(f"PermissionError: {e}")
        return out

    for f in files:
        path = os.path.join(root, f)
        out.append(path)

        # Print the path as soon as it is encountered
        if progress and os.path.isdir(path):
            print(path)

        # Recurse into directories
        if os.path.isdir(path) and not os.path.islink(path):
            index_files(path, out, progress=progress)

    return out

def read_deep(dir):
    return index_files(dir, [])

def demo_index_files():    
    root = '/Users/nicolas/'   
    out=[]
    index_files(root, out, progress=True)    
    print(out)
    return out

def demo_index_files2():

    root = '/Users/nicolas/'
    dirs = [ 'Code', 'Desktop', 'Documents', 'Downloads', 'Movies', 'Music', 'My Music', 'Parallels', 'Pictures', 'Public', 'Qemu', 'Torrents', 'VirtualBox VMs', 'bin' ]
    dirs = [os.path.join(root, d) for d in dirs]
    out = []
    for d in dirs:
        index_files(d, out, progress=True)
    print(out)
    return(out)


    
def search(strings, query):  
    # search(list_of_strings, 'containsthis -doesntcontainthis')

    query_terms = query.split()
    results_list = []
    for item in strings:
        keep_item = True
        for query_term in query_terms:
            if query_term[0] == "-":
                if query_term[1:] in item:
                    keep_item = False 
                    break 
            else:
                if not query_term in item:
                    keep_item = False 
                    break 
        if keep_item:
            results_list.append(item)
    return results_list

    


