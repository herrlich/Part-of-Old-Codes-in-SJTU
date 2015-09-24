from BeautifulSoup import BeautifulSoup
import urllib2
import re
import urlparse
import os
import urllib
import socket
import threading
import Queue
import time
import chardet


def valid_filename(s):
    import string
    valid_chars = "-_.() %s%s" % (string.ascii_letters, string.digits)
    s = ''.join(c for c in s if c in valid_chars)
    return s

def get_page(page):
    time.sleep(0.001)
    try:
        content=urllib2.urlopen(page,timeout=3).read()
        result = chardet.detect(content)['encoding']
        if result=='GB2312':
            content=content.decode('gbk').encode('utf8')
        if result=='ascii':
            content=content.encode('utf8')
        return content
    except:
        #There is an error.#
        return []

def get_all_links(content, page):
    if content==[]:
        return []
    links = []
    tempset=set()
    soup=BeautifulSoup(content)
    for i in soup.findAll('a',{'href':re.compile(('^http|^/'))}):
        tempset.add(i['href'])
    for i in tempset:
        links.append(urlparse.urljoin(page,i))
    return links

def add_page_to_folder(page, content):
    folder = 'F:\\html'
    index_filename = 'F:\\html\index.txt'
    filename = valid_filename(page)
    index = open(index_filename, 'a')
    index.write(filename + ';' + page + '\n')
    index.close()
    if not os.path.exists(folder):
        os.mkdir(folder)
    f = open(os.path.join(folder, filename), 'w')
    f.write(content)
    f.close()

def working():
    page_num=0
    while page_num<task_per_thread:
        page = q.get()
        if page not in crawled:
            content = get_page(page)
            outlinks = get_all_links(content,page)
            if outlinks==[]:
                q.task_done()
                continue
            page_num+=1
            add_page_to_folder(page,content)
            for link in outlinks:
                q.put(link)
            if varLock.acquire():
                crawled.append(page)
                varLock.release()
                q.task_done()
            else:
                q.task_done()
        else:
            q.task_done()
    while q.empty()==False:
        q.get()
        q.task_done()

if not os.path.exists("F:\\html"):
    os.mkdir("F:\\html")
NUM = 10
task_per_thread=10
crawled = []
varLock = threading.Lock()
q = Queue.Queue()
q.put('http://www.hao123.com')
for i in range(NUM):
    t=threading.Thread(target=working)
    t.setDaemon(True)
    t.start()
q.join()
print "That's all you want."
