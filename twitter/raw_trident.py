import os
import subprocess

TRIDENT_EMPTY_RESULT = "<empty result>"
TRIDENT_KNOWN_EMPTY = "<empty result -- known empty>"
TRIDENT_PATH="../../trident/"
TRIDENT_EXEC="build/trident"
DATASTORE="data/wdumpwebsite"
QUERY_FILE="temp.qry"
BASH_COMMAND = "{0}{1} query -i {0}{2} -q {3}".format(TRIDENT_PATH, 
        TRIDENT_EXEC, DATASTORE, QUERY_FILE) 
QUERY_STRING = """
SELECT ?s WHERE {{
  ?s <http://www.w3.org/2000/01/rdf-schema#label> "\\\"{0}\\\"@en "
}}
LIMIT 1
    """ 

def query(entity):
    """
    (str) -> (bool, str) 
     - based on params generate query string
     - write query to file
     - query trident and store result
     - close and remove query file
     - parse result 
    """
    query_string = QUERY_STRING.format(entity)
    query_file = open(QUERY_FILE, "w+")
    query_file.write(query_string)
    query_file.close()
    process = subprocess.Popen(BASH_COMMAND.split(), stdout=subprocess.PIPE, 
            stderr=subprocess.DEVNULL)
    output, error = process.communicate()
    output = output.decode("utf-8").strip()
    if (len(output) > 0 and output != TRIDENT_EMPTY_RESULT
            and output != TRIDENT_KNOWN_EMPTY):
        # print("Entity = {0} :: Link =  {1} ".format(entity, output))
        return (True, output)
    # print("Entity = {0} :: NOT FOUND ".format(entity))
    return (False, entity)
