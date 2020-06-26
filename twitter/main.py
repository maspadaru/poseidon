import tweepy 
import config

class StreamListener(tweepy.StreamListener):
    def on_status(self, status):
        print(status.text)

    def on_error(self, status_code):
        if status_code == 420:
            return False

def main():
    auth = tweepy.OAuthHandler(config.TWITTER_API_KEY, config.TWITTER_API_SECRET)
    auth.set_access_token(config.TWITTER_ACCESS_TOKEN, config.TWITTER_ACCESS_SECRET)
    api = tweepy.API(auth)
    stream_listener = StreamListener()
    stream = tweepy.Stream(auth=api.auth, listener=stream_listener)
    stream.filter(track=["xbox", "series X", "Xbox Series X", "Xbox One"])

        
if __name__ == '__main__':
    main()
