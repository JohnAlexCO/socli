# socli

socli is an application for interacting
with decentralized social media like
[bluesky](),
[mastodon](),
and RSS feeds from one shared interface

## Getting Started

1. Either build from source,
or download a binary executable for your system from
[the releases page](https://github.com/JohnAlexCO/socli/releases)
2. Move the executable to somewhere in your `$PATH`,
such as:
    - Windows\*: `C:\Users\<YourUsername>\bin`
    - Linux & MacOS: `/usr/bin`
3. Decide on a pass-phrase for socli.
It is used to store the credentials
for logging in to each platform,
and you will be unable to log in without it
4. For each platform you'd like to use,
run its configuration step
5. After that, just run socli to start seeing posts

## Usage
- `socli` with no arguments fetches and displays your feed
- `socli reset` will delete all locally saved credentials
- connect to to various platforms with:
    - `socli bluesky`
    - `socli mastodon`

> [!NOTE] more platforms are eventually planned

### Postfeed
When viewing your feed, there will be an `>` next to
the currently selected post.
Pressing the `right-arrow` key will zoom in on the post,
and the `left-arrow` will back out again.
`Space` will like the selected post,
and `Backspace` will unlike the selected post.

### Posts
When a post is selected or zoomed,
`Space` and `Backspace` will like or unlike the post.
Pressing `A` will show information about the author.

### Pages / Users
From posts or the user's page,
you can press `F` to follow a user
and `U` to unfollow them.

## Build from Source

> [!IMPORTANT]
> building requires the following:
> - bash or similar shell
> - a C compiler (C11 or newer)
> - python 3.11.\*
> - cython 3.\*.\*
> - pip 23.\*.\*
> - atproto
> - argparse
> - base64
> - cryptography

The build process for socli is pretty minimal.
socli builds into a binary for each platform
it interacts with, and then the main application
that interfaces each of them.

Running the `./build` script should auto-magically
fill the `./bin` directory with binaries for your system.
Installation is then as simple as moving
the main binary and its dependencies to somewhere
in your environment's `$PATH`

## Security

> [!NOTE]
> the `pass-key` required by socli on startup
> is never saved.
> credentials given during `setup` are obfuscated when saved

> [!CAUTION]
> socli only obfuscates the data it saves locally,
> it is not secure against determined attacks,
> but intended to be good enough to prevent
> simple privacy violations by someone
> with physical access to your machine.

> [!CAUTION]
> socli communicates through standard process pipes.
> Running it from within other applications
> means they may see your pass-key or other
> sensitive data,
> and programs which attach to these pipes may
> be a security vulnerability.

## Contributing

Contributions are accepted through
[the GitHub page](https://github.com/JohnAlexCO/socli),
and the process is just two steps:

1. open an issue describing what problem you're addressing, changes you're making, or features you're adding. Keep the name short and the description specific.
2. submit a pull request who's name _begins with the number of the issue_, such as `#1 add keygen`

> [!TIP]
> we recommend using a `.gitignore` with at least the following entries:
> ```
> generated/
> bin/
> .*
> ```

By submitting code to this repository, you implictly
agree to only submit works of your own creation
and which you have the rights to.