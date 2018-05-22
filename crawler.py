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

def getcounts(words=None):
    counts = collections.Counter(words)

    wordsused = len(counts)

    shortwords = [word for word in counts if len(word) < 3] 
    ignore = shortwords + \
        ['after', 'all', 'and', 'are', 'because', 'been', 'but', 'for', 'from',
         'has', 'have', 'her', 'more', 'not', 'now', 'our', 'than', 'that',
         'the', 'these', 'they', 'their', 'this', 'was', 'were', 'when', 'who',
         'will', 'with', 'year', 'hpv19slimfeature', 'div']
    for word in ignore:
        counts.pop(word, None)

    tempcopy = [_ for _ in words]
    for word in tempcopy:
        if noalpha(word):
            counts.pop(word, None)

    return (counts, wordsused)

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
    wordcount(soup) 
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

def wordcount(soup):
    rawtext = soup.get_text()
    print(rawtext)
    words = getwords(rawtext)
    counts, _ = getcounts(words)
    if counts.most_common(1)[0][1] < 10:
        print('This page does not have any words used more than 10 times.')
    else:
        print(counts.most_common(10))

if __name__ == "__main__":
    START = default_timer()
    crawler('https://ganool.im/', maxpages=1, singledomain=True) #input web address
    END = default_timer()
    print('Elapsed time (seconds) = ' + str(END-START))
