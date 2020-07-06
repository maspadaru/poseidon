import config
import tweepy 

class StreamListener(tweepy.StreamListener):
    def __init__(self):
        super(StreamListener, self).__init__()
        self.recent_tweets = []

    def on_status(self, status):
        tweet = ""
        if hasattr(status, 'extended_tweet'):
            tweet = status.extended_tweet['full_text']
        else:
            tweet = status.text
        self.recent_tweets.append(tweet)

    def on_error(self, status_code):
        if status_code == 420:
            return False

    def get_recent_tweets(self):
        result = self.recent_tweets
        self.recent_tweets = []
        return result

class TwitterApi():
    def __init__(self, filter_list):
        self.auth = tweepy.OAuthHandler(config.TWITTER_API_KEY, config.TWITTER_API_SECRET)
        self.auth.set_access_token(config.TWITTER_ACCESS_TOKEN, config.TWITTER_ACCESS_SECRET)
        self.api = tweepy.API(self.auth)
        self.stream_listener = StreamListener()
        self.stream = tweepy.Stream(auth=self.api.auth, listener=self.stream_listener)
        self.stream.filter(track=filter_list, is_async=True)

    def get_tweets(self):
        return self.stream_listener.get_recent_tweets()

