import datetime
import math
import time

import requests


def compute_some():
    print("Computing...")
    for _ in range(1, 10_000_000):
        math.sqrt(25 ** 25 + .01)


def download_some():
    print("Downloading...")
    url = 'https://talkpython.fm/episodes/show/174/coming-into-python-from-another-industry-part-2'
    resp = requests.get(url)
    resp.raise_for_status()

    text = resp.text

    print(f"Downloaded (more) {len(text):,} characters.")


def download_some_more():
    print("Downloading more ...")
    url = 'https://pythonbytes.fm/episodes/show/92/will-your-python-be-compiled'
    resp = requests.get(url)
    resp.raise_for_status()

    text = resp.text

    print(f"Downloaded {len(text):,} characters.")


def wait_some():
    print("Waiting...")
    for _ in range(1, 1000):
        time.sleep(.001)


def main():
    t0 = datetime.datetime.now()

    # cpu
    compute_some()
    compute_some()
    compute_some()
    # io (not using cpu at all!!!)
    download_some()
    download_some()
    download_some_more()
    download_some_more()
    # waste cpu cycles ( process goes to waiting (blocked state))
    wait_some()
    wait_some()
    wait_some()
    wait_some()

    dt = datetime.datetime.now() - t0
    print(f"Synchronous version done in {dt.total_seconds():,.2f} seconds.")


if __name__ == '__main__':
    main()
