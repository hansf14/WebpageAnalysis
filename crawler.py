import collections,string,bs4,requests

from timeit import default_timer
from urllib.parse import urldefrag, urljoin, urlparse

def crawler(startpage, maxpages=100, singledomain=True):
    pagequeue = collections.deque()
    pagequeue.append(startpage)
    crawled = [] 
    domain = urlparse(startpage).netloc if singledomain else None

    pages = 0 
    failed = 0 

    sess = requests.session()
    while pages < maxpages and pagequeue:
        url = pagequeue.popleft() 

        try:
            response = sess.get(url)
        except (requests.exceptions.MissingSchema,
                requests.exceptions.InvalidSchema):
            print("*FAILED*:", url)
            failed += 1
            continue
        if not response.headers['content-type'].startswith('text/html'):
            continue 

        soup = bs4.BeautifulSoup(response.text, "html.parser")

        crawled.append(url)
        pages += 1
        if pagehandler(url, response, soup):
            links = getlinks(url, domain, soup)
            for link in links:
                if not url_in_list(link, crawled) and not url_in_list(link, pagequeue):
                    pagequeue.append(link)

    print('{0} pages crawled, {1} links failed.'.format(pages, failed))

def getlinks(pageurl, domain, soup):
    links = [a.attrs.get('href') for a in soup.select('a[href]')]

    links = [urldefrag(link)[0] for link in links]

    links = [link for link in links if link]

    links = [link if bool(urlparse(link).netloc) else urljoin(pageurl, link) \
        for link in links]

    if domain:
        links = [link for link in links if samedomain(urlparse(link).netloc, domain)]

    return links

def getwords(rawtext):
    words = []
    cruft = ',./():;!"' + "<>'â{}" 
    for raw_word in rawtext.split():
        word = raw_word.strip(string.whitespace + cruft + '-').lower()

        if word[-2:] == "'s":
            word = word[:-2]

        if word:
            words.append(word)

    return words

def pagehandler(pageurl, pageresponse, soup):
    print('Crawling:' + pageurl + ' ({0} bytes)'.format(len(pageresponse.text)))
    printtext(soup) 
    return True

def noalpha(word):
    for char in word:
        if char.isalpha():
            return False
    return True

def samedomain(netloc1, netloc2):
    domain1 = netloc1.lower()
    if '.' in domain1:
        domain1 = domain1.split('.')[-2] + '.' + domain1.split('.')[-1]

    domain2 = netloc2.lower()
    if '.' in domain2:
        domain2 = domain2.split('.')[-2] + '.' + domain2.split('.')[-1]

    return domain1 == domain2

def url_in_list(url, listobj):
    http_version = url.replace('https://', 'http://')
    https_version = url.replace('http://', 'https://')
    return (http_version in listobj) or (https_version in listobj)

def printtext(soup):
    rawtext = soup.get_text()
    print(rawtext)

if __name__ == "__main__":
    START = default_timer()
    crawler('https://ganool.im/', maxpages=1, singledomain=True) #input web address
    END = default_timer()
    print('Elapsed time (seconds) = ' + str(END-START))
