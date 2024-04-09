import sys
import requests
from bs4 import BeautifulSoup
from urllib.parse import urlparse

def get_wikipedia_page(url):
    # Send Get-request to page
    response = requests.get(url)

    # Check if the request was successful
    if response.status_code != 200:
        print("Error on page loading:", response.status_code)
        return None

    # Getting the content and parse it
    html_content = response.text
    soup = BeautifulSoup(html_content, 'html.parser')
    return soup

def get_internal_links(soup, base_url):
    # Find all links on the page
    links = soup.find_all('a', href=True)
    internal_links = []

    for link in links:
        href = link.get('href')
        if not href.startswith('/wiki/'):
            continue

        # Get full URL
        full_url = urlparse(base_url)._replace(path=href).geturl()
        internal_links.append(full_url)

    return internal_links

if __name__ == "__main__":
    # Read the Wiki link from stdin
    link = sys.stdin.readline().strip()

    # Load the Wikipedia page
    soup = get_wikipedia_page(link)
    if not soup:
        sys.exit(1)

    # Get internal links
    internal_links = get_internal_links(soup, link)

    # Output internal links to stdout
    for internal_link in internal_links:
        print(internal_link)
