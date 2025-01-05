import os, sys, time, math, json, requests, csv
from datetime import datetime

def split_lines(dirs):
    dirs = dirs.split('\n')
    dirs = [ i.strip() for i in dirs ]
    return dirs


def write_file(filepath,data):
    with open(filepath,'wb') as f:
        f.write(data)

def read_file(filepath):
    with open(filepath,'rb') as f:
        data = f.read()
    return data

def save(filepath, data, indent=4):
    string = json.dumps(data,indent=indent)
    with open(filepath,'wb') as f:
        f.write(string.encode('utf-8'))

def load(filepath):
    with open(filepath,'rb') as f:
        string = f.read().decode('utf-8')
    return json.loads(string)

def log(*args):
    arg = [ str(i) for i in args ]
    with open("log.txt", "a") as f:
        f.write(time.ctime() +" "+ " ".join(arg) + "\n")


def make_dirs(file_path):
    # Make all the directories in the file path
    os.makedirs(os.path.dirname(file_path), exist_ok=True)
    # os.path.exists(directory):

def pwd():
    return os.getcwd()

def cd(dir):
    return os.chdir(dir)

def ls():
    return os.listdir()

def mkdir(dir):
    return os.mkdir(dir)

def uuid():
    import uuid as uuid_module
    return str(uuid_module.uuid4())
    # u = uuid()
    # u[-12:] # get the last part


def parse_time(datetime_string, format="%Y%m%d-%H%M%S"):
    """ Convert a datetime string to a Unix timestamp. """
    # %Y%m%d-%H%M%S%f" # microseconds (millionths of a second)
    dt_obj = datetime.strptime(datetime_string, format)
    return dt_obj.timestamp()

def format_time(timestamp, format="%Y%m%d-%H%M%S"):
    """ Convert a Unix timestamp to a formatted datetime string.
    Example: format_time(time.time())"""
    dt_obj = datetime.fromtimestamp(timestamp)
    return dt_obj.strftime(format)


def now_date(include_time=False):
    if time:
        return format_time(time.time(), format="%Y%m%d-%H%M%S")
    else:
        return format_time(time.time(), format="%Y%m%d")


# Spreadsheet, Excel unix time to date-time, google sheets
# =TEXT((B2/86400)+DATE(1970,1,1),"yyyy-mm-dd hh:mm:ss")



def index_files(root_dir, out, progress=False):
    # Walk through each file in the directory and its subdirectories
    for root, dirs, files in os.walk(root_dir):
        if progress:
            print(root)
        for file in files:
            file_path = os.path.join(root, file)
            out.append(file_path)
    return out


def read_deep(dir):
    return index_files(dir,[])

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


# search(read_deep('.'),'.json -package -emacs -settings -nrf')

# f = index_files('.',[])
# r = search(f, 'nordic')
# f.sort(key=os.path.getsize)
# a = [(f, os.path.getsize(f)) for f in f]
# a.sort(key=lambda x : x[1])




def find_file( dir='.', query=None, size_min=None, size_max=None, extension=None, isdir=None ):

    if size: 
        size = int(float(size))

    matches = []
    for root, dirs, files in os.walk(dir):
        for filename in files + dirs:
            keep = True 
            file_path = os.path.join(root, filename)
            if query:
                if not (query in file_path):
                    keep = False 

            if extension:
                if not filename.endswith("." + extension):
                    keep = False

            if size_min:
                file_size = os.path.getsize(file_path)
                if file_size < size:
                    keep = False

            if size_max:
                file_size = os.path.getsize(file_path)
                if file_size > size:
                    keep = False

            if isdir:
                if not os.path.isdir(file_path):
                    keep = False
                    
            if keep:
                print(file_path)
                matches.append(file_path)
                
    
    return matches


# find_file(size=1e7)
# find files greater than 10mb in current directory




def findall(string, substring):
    i = 0
    out = []
    while i < len(string):
        i = string.find(substring, i)
        if i == -1: break
        out.append(i)
        i += 1
    return out

# text = "The quick brown fox jumps over the lazy dog. How often does the fox jump?"
# keyword = "fox"
# matches = list(findall(text, keyword))
# print(matches)



import cryptography

from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.backends import default_backend

def ssh_keygen(key_size=2048):
    """
    Generate an SSH key pair.

    Args:
    key_size (int): The size of the RSA key to generate, in bits.

    Returns:
    tuple: (private_key, public_key) in PEM format.
    """
    # Generate private key
    private_key = rsa.generate_private_key(
        backend=default_backend(),
        public_exponent=65537,
        key_size=key_size
    )

    # Get the public key from the private key
    public_key = private_key.public_key()

    # Serialize private key in PEM format
    pem_private_key = private_key.private_bytes(
        encoding=serialization.Encoding.PEM,
        format=serialization.PrivateFormat.PKCS8,
        encryption_algorithm=serialization.NoEncryption()
    )

    # Serialize public key in OpenSSH format
    pem_public_key = public_key.public_bytes(
        encoding=serialization.Encoding.OpenSSH,
        format=serialization.PublicFormat.OpenSSH
    )


    # print(private_pem.decode())
    # print(public_pem.decode())

    # # Save the private key to a file
    # with open("private_key.pem", "wb") as f:
    #     f.write(private_pem)

    # # Save the public key to a file
    # with open("public_key.pem", "wb") as f:
    #     f.write(public_pem)


    return pem_private_key, pem_public_key




# # Example usage
# private_key, public_key = ssh_keygen()
# print("Private Key:\n", private_key)
# print("Public Key:\n", public_key)
# write_file(now_date()+"_private_key.pem", private_key)
# write_file(now_date()+"_public_key.pem", public_key)






# def get_unit_points(unit, date, account_number = "3173", api_key = "2489e07b3cae7774" ):

#     # unit = 20003
#     # date = '01/09/2023'
#     frm = int(time.mktime(time.strptime(date, '%d/%m/%Y')))
#     to = frm + 24*60*60
#     url = "https://connect.sensium.com.au/api" + '/history/'+str(unit)+'?frm='+str(frm)+'&to='+str(to)
#     auth = requests.auth.HTTPBasicAuth(str(account_number), str(api_key)) 

#     print('GET', url)
#     response = requests.request( 'GET', url, auth=auth )
#     status_code = response.status_code
#     formatted_status_code = requests.status_codes._codes[response.status_code][0]
#     print(status_code, formatted_status_code)
#     # if status_code != 200: # ok
#     #     return None

#     xml_string = response.text
#     xml_dict = xmltodict.parse(xml_string)
#     if xml_dict.get('error'):
#         return xml_dict
#     else:
#         points = xml_dict['history']['points']['point']
#         return points



# def flatten_points(points_data):

#     flattened_points = []
#     for i,point in enumerate(points_data):
#         fillpoints = point.get('truepath')
        
#         if fillpoints != None:

#             fillpoints = fillpoints.get('fillpoint')
#             # fillpoint can be none, a list, or a dict.  I think a dict is when there's only one data item.
#             if type(fillpoints) == list:
#                 for fp in fillpoints:
#                     flattened_points.append(fp.copy())
#             elif type(fillpoints) == dict:
#                 flattened_points.append(fillpoints.copy())

#             flattened_points.append(point)
#             point['truepath'] = None

#     return flattened_points



# points = get_unit_points('20003', '01/09/2023')
# df=pd.DataFrame(flatten_points(points))
# print(df)
# df.to_csv('out.csv',index=False)



