import sys
import time

from twitter import TwitterApi
from triple_extractor import TripleExtractor 
import raw_trident

def link_entities(triple):
    fsubj, subj = raw_trident.query(triple['subject'])
    frel, rel = raw_trident.query(triple['relation'])
    fobj, obj = raw_trident.query(triple['object'])
    if fsubj and frel and fobj:
        return (subj, rel, obj)
    return None


def handle_tweet(tweet, trpext):
        # print(tweet)
        # print("=== Cleaned ==== ")
        clean_tweet = trpext.clean_text(tweet) 
        # print(clean_tweet)
        # print(" === Entities: ===")
        # entities = trpext.extract_entities(clean_tweet)
        # print(entities)
        # print(" === Triples: ===")
        triples = trpext.get_triples(clean_tweet)
        for triple in triples:
            # print('|-', triple)
            # ares_triple_frmt = "{1} {0} {2}".format(
                    # triple['subject'], triple['relation'], triple['object'])
            readable_triple_frmt = "{0} :: {1} :: {2}".format(
                    triple['subject'], triple['relation'], triple['object'])
            # print(ares_triple_frmt)
            print(readable_triple_frmt)
            rez = link_entities(triple)
            if rez != None:
                print("Found entities!")
            else:
                print ("Entities not found!")

def get_twitter_input(trpext):
    filter=["Amsterdam", "Stockholm", "Copenhagen", "Toronto"]
    twitter_api = TwitterApi(filter)
    while True: 
        # print(" ")
        # print("=== ============== START TIMEPOINT ==================== ==== ")
        tweets = twitter_api.get_tweets()
        for tweet in tweets:
            handle_tweet(tweet, trpext)
        print(" ") # printing empty line after each time-point
        time.sleep(1)

def get_file_input(file_path, trpext):
    f = open(file_path, "r")
    while True: 
        line = f.readline() 
        if not line: 
            break
        handle_tweet(line, trpext)
  
    f.close()

def main():
    trpext = TripleExtractor()
    if (len(sys.argv) == 1):
        get_twitter_input(trpext)
    else :
        file_path =  sys.argv[1]
        get_file_input(file_path, trpext)

        
if __name__ == '__main__':
    main()
    



