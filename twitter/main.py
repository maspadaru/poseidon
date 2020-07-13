import sys
import time
import os 

from twitter import TwitterApi
from triple_extractor import TripleExtractor 
import raw_trident

FIFO_PATH = "/tmp/poseidon_stream.fifo"


def link_entities(triple):
    fsubj, subj = raw_trident.query(triple['subject'])
    frel, rel = raw_trident.query(triple['relation'])
    fobj, obj = raw_trident.query(triple['object'])
    if fsubj or frel or fobj:
        return (subj, rel, obj)
    return None


def handle_tweet(tweet, trpext, fifo):
        clean_tweet = trpext.clean_text(tweet) 
        triples = trpext.get_triples(clean_tweet)
        for triple in triples:
            rez = link_entities(triple)
            if rez != None:
                ares_triple_frmt = "{1} {0} {2} \n".format(
                        rez[0], rez[1], rez[2])
                fifo.write(ares_triple_frmt)    

    
def get_twitter_input(trpext):
    twitter_api = TwitterApi()
    while True: 
        fifo = open(FIFO_PATH, "w")
        try:    
            tweets = twitter_api.get_tweets()
            for tweet in tweets:
                handle_tweet(tweet, trpext, fifo)
            fifo.write("\n") # printing empty line after each time-point
        finally:
            fifo.close() # writes are buffered, closing will flush
        time.sleep(60)


def get_file_input(file_path, trpext):
    f = open(file_path, "r")
    fifo = open(FIFO_PATH, "w")
    try:    
        while True: 
            line = f.readline() 
            if not line: 
                break
            handle_tweet(line, trpext, fifo)
    finally:
        fifo.close() # writes are buffered, closing will flush
        f.close()
  

def main():
    trpext = TripleExtractor()
    if (not os.path.exists(FIFO_PATH)):
        os.mkfifo(FIFO_PATH)
    if (len(sys.argv) == 1):
        get_twitter_input(trpext)
    else :
        file_path =  sys.argv[1]
        get_file_input(file_path, trpext)

        
if __name__ == '__main__':
    main()
    



