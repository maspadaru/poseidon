import re

import tweepy 
from stanfordcorenlp import StanfordCoreNLP

import config


class StreamListener(tweepy.StreamListener):
    def __init__(self):
        super(StreamListener, self).__init__()
        self.nlp = StanfordCoreNLP('../../stanford-corenlp-4.0.0/', memory='8g')
        self.regex_pattern = r'[^\x00-\x7F]+' 
        self.nlp.ner("init")

    def on_status(self, status):
        print("")
        print("================== Tweet ================= ")
        print("=== Original ==== ")
        tweet = status.text
        print(tweet)
        print("=== Cleaned ==== ")
        clean_tweet =  re.sub(self.regex_pattern, ' ', tweet)
        print(clean_tweet)
        print(" === Entities: ===")
        entities = self.nlp.ner(clean_tweet)
        print(entities)

    def on_error(self, status_code):
        if status_code == 420:
            return False

def main():
    auth = tweepy.OAuthHandler(config.TWITTER_API_KEY, config.TWITTER_API_SECRET)
    auth.set_access_token(config.TWITTER_ACCESS_TOKEN, config.TWITTER_ACCESS_SECRET)
    api = tweepy.API(auth)
    stream_listener = StreamListener()
    stream = tweepy.Stream(auth=api.auth, listener=stream_listener)
    stream.filter(track=["Amsterdam", "Stockholm", "Copenhagen", "Toronto"])

        
if __name__ == '__main__':
    main()
    



# TODO:
# 1. NLP extract Subject Predicate Object 
#            -> Standford NLP has a parser that can do this somehow, I think
# 2. Match <S, P, O> entities to wididata
# 3. tweepy returns truncated tweets. Find a way to get the full tweet.
# 4. Format RDF triples in Ares readable stream
# 5. Write stream to named pipe from which Poseidon can read them.
