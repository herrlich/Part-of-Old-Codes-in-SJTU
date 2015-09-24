from BeautifulSoup import BeautifulSoup
import urllib2
import re
import urlparse
import os
import urllib

def valid_filename(s):
    import string
    valid_chars = "-_.() %s%s" % (string.ascii_letters, string.digits)
    s = ''.join(c for c in s if c in valid_chars)
    return s

def get_page(page):
    content = ''
    import urllib2
    import socket
    try:
        content=urllib2.urlopen(page,timeout=10).read()
        return content
    except:
        print 'There is an error.'
        return 0

def get_all_links(content, page):
    import re
    import urlparse
    from BeautifulSoup import BeautifulSoup
    links = []
    tempset=set()
    soup=BeautifulSoup(content)
    for i in soup.findAll('a',{'href':re.compile(('^http|^/'))}):
        tempset.add(i['href'])
    for i in tempset:
        links.append(urlparse.urljoin(page,i))
    return links

def union_dfs(a,b):
    for e in b:
        if e not in a:
            a.append(e)

def union_bfs(a,b):
    for i in b:
        if i not in a:
            a.insert(0,i)

def add_page_to_folder(page, content):
    index_filename = 'index.txt'
    folder = 'html'
    filename = valid_filename(page)
    index = open(index_filename, 'a')
    index.write(page.encode('ascii', 'ignore') + '\t' + filename + '\n')
    index.close()
    if not os.path.exists(folder):
        os.mkdir(folder)
    f = open(os.path.join(folder, filename), 'w')
    f.write(content)
    f.close()

def crawl(seed, method, max_page):
    tocrawl = [seed]
    crawled = []
    graph = {}
    count = 0

    while tocrawl:
        page = tocrawl.pop()
        if page not in crawled and count<max_page:
            count+=1
            print page
            content = get_page(page)
            if content:
                add_page_to_folder(page, content)
                outlinks = get_all_links(content, page)
                globals()['union_%s' % method](tocrawl, outlinks)
                if method=='dfs':
                    crawled.append(page)
                if method=='bfs':
                    crawled.insert(0,page)
    if method=='bfs':
        crawled.reverse()
    return graph, crawled