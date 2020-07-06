import re

import tweepy 
from stanfordcorenlp import StanfordCoreNLP
from openie import StanfordOpenIE

import config


class StreamListener(tweepy.StreamListener):
    def __init__(self):
        super(StreamListener, self).__init__()
        self.counter = 1 

    def on_status(self, status):
        print("")
        if hasattr(status, 'extended_tweet'):
            tweet = status.extended_tweet['full_text']
        else:
            tweet = status.text
        print(tweet)
        self.counter += 1
        if self.counter > 100:
            exit()

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
    



