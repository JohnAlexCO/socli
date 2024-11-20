# https://www.geeksforgeeks.org/encrypt-and-decrypt-files-using-python/
# https://docs.bsky.app/docs/get-started
import atproto
from cryptography.fernet import Fernet
import argparse
import base64

# the key passed to login and signup will be implemented at a later point
def login(key:str):
    user = {}
    with open('.bsky', 'rb') as file:
        content = file.read().decode()
    session = atproto.Client()
    user['handle'] = content.split('\n')[0]
    user['passkey'] = content.split('\n')[1]
    session.login(user['handle'], user['passkey'])
    user['session'] = session
    return user

def signup(key:str, user:str, passkey:str):
    with open('.bsky', 'wb') as file:
        file.write( (user + '\n' + passkey).encode('utf-8') )

def userFollow(user, username):
    session = user['session']
    data = session.get_profile(actor=username)
    did = data.did
    return session.follow(did)

def userUnfollow(user, username):
    session = user['session']
    data = session.get_profile(actor=username)
    did = data.did
    return session.delete_follow(did)

def likePost(user, uri, cid):
    session = user['session']
    return session.like(uri, cid)

def unlikePost(user, uri):
    session = user['session']
    return session.delete_like(uri)

def makePost(user:dict, content:str):
    session = user['session']
    post = session.send_post(content)
    return post.uri

def getTimeline(user:dict):
    session = user['session']
    data = session.get_timeline(cursor='', limit=50)
    raw_feed = data.feed
    writeFeed(raw_feed)
    return

def procPost(object):
    post = object['post']
    # for key in post:
    #     print(key)
    return {
        'handle': post.author.handle,
        'content': post.record.text,
        'likes': str(post.like_count),
        'replies': str(post.reply_count),
        'shares': str(post.repost_count),
        'uri': post.uri,
        'cid': post.cid
    }

def writeFeed(feedList):
    content = ''
    for item in feedList:
        post = procPost(item)
        content += post['handle'] + ' '
        content += post['likes'] + ','
        content += post['replies'] + ','
        content += post['shares'] + ' '
        content += post['uri'] + ' '
        content += post['cid'] + ' '
        content += (post['content']).replace('\n', '  ') + '\n'
    with open('bsky.txt', 'wb') as file:
        file.write( content.encode('utf-8'))

def main():
    # Create an argument parser
    parser = argparse.ArgumentParser(description="Process some CLI arguments.")

    # Add argument parsers for each option
    parser.add_argument('-s', nargs=3, metavar=('key', 'handle', 'pass'), help="save encrypted user credentials")
    parser.add_argument('-t', nargs=1, metavar=('key'), help="fetch the user's Bluesky feed")
    parser.add_argument('-p', nargs='?', metavar=('key'), help="share a post to Bluesky with saved credentials")
    parser.add_argument('-like', nargs=3, metavar=('key', 'uri', 'cid'), help="like a post")
    parser.add_argument('-unlike', nargs=2, metavar=('key', 'uri'), help="unlike a post")
    parser.add_argument('-add', nargs=2, metavar=('key', 'handle'), help="follow a user")
    parser.add_argument('-unadd', nargs=2, metavar=('key', 'handle'), help="unfollow a user")
    parser.add_argument('other_arguments', nargs=argparse.REMAINDER, help="")

    # Parse the arguments
    args = parser.parse_args()

    if args.s:
        key, handle, passkey = args.s
        signup(key, handle, passkey)
        return

    if args.p is not None:
        key = args.p
        arguments_text = " ".join(args.other_arguments)
        user = login(key)
        post = makePost(user, arguments_text)
        return

    if args.t:
        key = args.t
        user = login(key)
        getTimeline(user)
        return

    if args.like:
        key, uri, cid = args.like
        user = login(key)
        likePost(user, uri, cid)
        return

    if args.unlike:
        key, uri = args.unlike
        user = login(key)
        unlikePost(user, uri)
        return

    if args.add:
        key, handle = args.add
        user = login(key)
        userFollow(user, handle)
        return

    if args.unadd:
        key, handle = args.add
        user = login(key)
        userUnfollow(user, handle)
        return


# Run the main function
if __name__ == '__main__':
    main()