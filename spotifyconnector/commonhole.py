from flask import Flask, redirect, request
import requests
import threading
import time
import base64
from pydub import AudioSegment
from pydub.playback import play
import os
import random

CLIENT_ID = ""
CLIENT_SECRET = ""
REDIRECT_URI = "http://localhost:5000/callback"

AUTH_CODE = None
ACCESS_TOKEN = None
REFRESH_TOKEN = None
REFRESH_AT = None


def request_access_token():
    global CLIENT_ID, CLIENT_SECRET, REDIRECT_URI, AUTH_CODE, REFRESH_TOKEN, ACCESS_TOKEN

    print("\nRequesting Spotify access token...")

    res = requests.post("https://accounts.spotify.com/api/token", data={
        "grant_type": "authorization_code",
        "client_id": CLIENT_ID,
        "client_secret": CLIENT_SECRET,
        "code": AUTH_CODE,
        "redirect_uri": REDIRECT_URI
    })

    content = res.json()
    ACCESS_TOKEN = content["access_token"]
    REFRESH_TOKEN = content["refresh_token"]
    REFRESH_AT = time.time() + int(content["expires_in"])


def refresh_access_token():
    global REFRESH_TOKEN, CLIENT_ID, CLIENT_SECRET, ACCESS_TOKEN
    print("\nRefreshing Spotify access token...")

    res = requests.post("https://accounts.spotify.com/api/token", data={
        "grant_type": "refresh_token",
        "refresh_token": REFRESH_TOKEN,
        "client_id": CLIENT_ID,
        "client_secret": CLIENT_SECRET
    })

    content = res.json()
    ACCESS_TOKEN = content["access_token"]


def do_refresh_access_token():
    global REFRESH_TOKEN

    while True:
        if REFRESH_TOKEN:
            refresh_access_token()

        else:
            print("No valid auth code - not refreshing...")
        time.sleep(3540)


threading.Thread(target=do_refresh_access_token).start()


def get_playing_info(access_token):
    res = requests.get(
        "https://api.spotify.com/v1/me/player/currently-playing", headers={
            'Authorization': 'Bearer ' + access_token
        })

    if res.status_code != 204:
        return res.json()

    return {"is_playing": False, "item": {"name": "Not listening to anything"}}


def get_ji(fname):
    return AudioSegment.from_wav(fname)


def get_random_ji():
    return get_ji("jingles/" + random.choice(os.listdir("jingles")))


def pause_spotify(access_token):
    res = requests.put("https://api.spotify.com/v1/me/player/pause", headers={
        'Authorization': 'Bearer ' + access_token
    })


def resume_spotify(access_token):
    res = requests.put("https://api.spotify.com/v1/me/player/play", headers={
        'Authorization': 'Bearer ' + ACCESS_TOKEN
    })


app = Flask(__name__)


@app.route('/init')
def init():
    return redirect("https://accounts.spotify.com/authorize?client_id=%s&response_type=code&redirect_uri=%s&scope=user-read-playback-state%%20user-modify-playback-state" % (CLIENT_ID, REDIRECT_URI))


@app.route('/callback')
def callback():
    global authorized, AUTH_CODE

    args = request.args
    if "error" in args:
        return "Access denied.", 400

    AUTH_CODE = args["code"]
    request_access_token()

    return "Permissions granted.", 200


@app.route('/listeningto')
def listeningto():
    global ACCESS_TOKEN
    print("\nattempting to fetch listen state")
    content = get_playing_info(ACCESS_TOKEN)

    return "song: " + content["item"]["name"] + "<br />is playing: " + str(content["is_playing"])


@app.route("/playpause")
def playpause():
    global ACCESS_TOKEN
    print("\nattempting to pause listen state")
    playing_info = get_playing_info(ACCESS_TOKEN)

    if playing_info["is_playing"]:
        pause_spotify(ACCESS_TOKEN)
    else:
        resume_spotify(ACCESS_TOKEN)

    return redirect("listeningto")


@app.route("/jingle")
def jingle():
    global ACCESS_TOKEN
    print("\nWill (1) pause spotify playback (if any), (2) play jingle and (3) resume spotify playback.")

    jingle = get_ji('faen.wav')

    pause_spotify(ACCESS_TOKEN)
    threading.Thread(target=lambda: play(jingle)).start()
    time.sleep(jingle.duration_seconds-1)
    resume_spotify(ACCESS_TOKEN)
    return redirect('listeningto')


@app.route('/main')
def mainpage():
    main()
    return "main loop stopped."


def main():
    global ACCESS_TOKEN
    while True:
        cmd = input("cmd: ")
        if cmd == "pling":
            print("pling start")
            pause_spotify(ACCESS_TOKEN)
            ji = get_random_ji()
            threading.Thread(target=lambda: play(ji)).start()
            time.sleep(ji.duration_seconds)
            resume_spotify(ACCESS_TOKEN)
            print("pling end")

            # Logger plings.
            with open("plinglog.txt", "a+") as f:
                f.write(str(time.time()) + "\n")
